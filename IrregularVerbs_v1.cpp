#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
#include<limits>
#include<algorithm>

#define FILE_NAME "allVerbs.txt"

using namespace std;

struct verbType{
    string firstForm;
    string secondForm;
    string thirdForm;
    string inRussian;
    int relevant;
    verbType():relevant(0){}
};

class MyLibrary{
private:
    vector<verbType> allVerbs;
public:
    MyLibrary(){}
    
    void showAllVerbs(){
        system("clear");
        for(auto it:allVerbs){
            cout<<it.firstForm<<"\t";
            if(it.firstForm.size()<=7) cout<<'\t';
            cout<<it.secondForm<<"\t";
            if(it.secondForm.size()<=7) cout<<'\t';
            cout<<it.thirdForm<<"\t\t";
            if(it.thirdForm.size()<=7) cout<<'\t';
            cout<<it.inRussian<<"\n\n";
        }
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
    }
    
    bool readFile(){
        fstream file(FILE_NAME,ios_base::openmode::_S_in);
        if(!file.is_open()) return false;

        while(!file.eof()){
            verbType temp;
            file>>temp.firstForm;
            file>>temp.secondForm;
            file>>temp.thirdForm;
            file>>temp.inRussian;
            file>>temp.relevant;

            if(temp.secondForm != "")
                allVerbs.push_back(temp);
        }
        return true;
    }
    
    bool writeFile(){
        fstream file(FILE_NAME,ios_base::openmode::_S_out);
        if(!file.is_open()) return false;
       
        for(auto it:allVerbs){
            file<<it.firstForm  <<' ';
            file<<it.secondForm <<' ';
            file<<it.thirdForm  <<' ';
            file<<it.inRussian  <<' ';
            file<<it.relevant   <<'\n';
        }

        return true;
    }
    
    void addVerbs(verbType verb){
        for(auto it:allVerbs)
            if(it.firstForm == verb.firstForm) return;

        allVerbs.push_back(verb);
        cout<<"Append\n";
    }
    
    void training(vector<int> indexs){
        size_t size = indexs.size();

        for(int i=0;i<size;i++)
            swap(indexs[rand()%size],indexs[rand()%size]);

        string first = "";
        string second = "";
        string third = "";
        int relv = 0;

        for(int i=0;i<size && first != "st";i++){
            system("clear");
            cout<<"Count = "<<size--<<endl<<endl;

            cout<<allVerbs[indexs[i]].inRussian<<endl<<endl;

            while(true){
                cout<<"Enter form over space:= ";cin>>first;
                if(first == "dk") {
                        relv+=2;
                        cout<<allVerbs[indexs[i]].firstForm<<"\t";
                        if(allVerbs[indexs[i]].firstForm.size()<=7) cout<<'\t';
                        cout<<allVerbs[indexs[i]].secondForm<<"\t";
                        if(allVerbs[indexs[i]].secondForm.size()<=7) cout<<'\t';
                        cout<<allVerbs[indexs[i]].thirdForm<<"\t\t";
                        if(allVerbs[indexs[i]].thirdForm.size()<=7) cout<<'\t';
                        cout<<allVerbs[indexs[i]].inRussian<<"\n\n";
                        continue;
                }
                else if(first == "st") break;

                cin>>second>>third;

                if(first!=allVerbs[indexs[i]].firstForm || second!=allVerbs[indexs[i]].secondForm || third!=allVerbs[indexs[i]].thirdForm) {
                    relv++;
                    continue;
                }

                break;
            } 
           
	        allVerbs[indexs[i]].relevant = relv;
            relv = 0;

            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        
    }
    
    void trainingProblems(){
        vector<int> indexs;
        int index = 0;

        for(auto it:allVerbs){
            if(it.relevant>1) indexs.push_back(index);
            index++;
        }
        training(indexs);
    }
    
    vector<int> getAllVerbs(){
        vector<int> indexs;
        for(int i=0;i<allVerbs.size();i++)
            indexs.push_back(i);
        return indexs;
    }
    
    ~MyLibrary(){}
};


verbType enterVerb(){
    system("clear");

    verbType res;
    string str;

    cout<<"Enter first form: ";cin>>str;
    res.firstForm = str;
    cout<<"Enter second form: ";cin>>str;
    res.secondForm = str;
    cout<<"Enter third form: ";cin>>str;
    res.thirdForm = str;
    cout<<"Enter in Russian: ";cin>>str;
    res.inRussian = str;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    return res;
}

int main(){
    setlocale(LC_ALL, "Russian");
    srand(time(NULL));

    MyLibrary ML;
    if(!ML.readFile()) return -1;

    int choose = 0;

    while(choose!=5){
        system("clear");
        cout<<"1. Показать все глаголы\n";
        cout<<"2. Добавить новый глагол\n";
        cout<<"3. Тренировать слова\n";
        cout<<"4. Тренировать проблемные\n";
        cout<<"5. Выйти\n";

        do{
            cin>>choose;
        }while(choose<=0 || choose>5);

        switch (choose)
        {
        case 1: ML.showAllVerbs(); break;
        case 2: ML.addVerbs(enterVerb()); break;
        case 3: ML.training(ML.getAllVerbs()); break;
        case 4: ML.trainingProblems(); break;
        default: break;
        }
        getchar();
    }

    ML.writeFile();


    return 0;
}
