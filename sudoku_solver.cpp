#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_set>
#include<array>

using namespace std;
void eraseMatrix(vector<pair<array<int,2>,unordered_set<int>>> &points,int X, int Y, int value){
    if(X < 3) X = 0;
    else if(X < 6) X = 3;
    else X = 6;

    if(Y < 3) Y = 0;
    else if(Y < 6) Y = 3;
    else Y = 6;

    for(int i{X}; i < X+3; i++)
        for(int j{Y}; j < Y+3; j++)
            for(int a{0}; a < points.size(); a++)
                if(points[a].first[0] == i && points[a].first[1] == j)
                    points[a].second.erase(value);
}
void eraseInVariants(vector<vector<char>>& board,unordered_set<int> &variants,int X,int Y){
    for(int i{0}; i < 9; i++){
        variants.erase(board[X][i] - '0');
        variants.erase(board[i][Y] - '0');
    }

    if(X < 3) X = 0;
    else if(X < 6) X = 3;
    else X = 6;

    if(Y < 3) Y = 0;
    else if(Y < 6) Y = 3;
    else Y = 6;

    for(int i{X}; i < X+3; i++)
        for(int j{Y}; j < Y+3; j++)
            variants.erase(board[i][j] - '0');
}

bool solveSudoku(vector<vector<char>>& board) {
    vector<pair<array<int,2>,unordered_set<int>>> pointsAndVariant; // x,y poinst and variants value

    for(int i{0}; i < 9; i++){
        for(int j{0}; j < 9; j++){
            if(board[i][j] == '.'){
                pointsAndVariant.push_back(pair<array<int,2>,unordered_set<int>>{array<int,2>{i,j},unordered_set<int>{1,2,3,4,5,6,7,8,9}});
                eraseInVariants(board,(pointsAndVariant.end()-1)->second,i,j);
            }
        }
    }

    while(pointsAndVariant.size()){ 
        auto minSizeVariants = min_element(pointsAndVariant.begin(),pointsAndVariant.end(),[](pair<array<int,2>,unordered_set<int>> &f,
                                                                                      pair<array<int,2>,unordered_set<int>> &s){
                                                                                        return f.second.size() <  s.second.size();
                                                                                      });

        // printBoard(board);
        // cout<<"\n\n";                        
        // printVariants(pointsAndVariant);
        // cout<<minSizeVariants->first[0]<<':'<<minSizeVariants->first[1];
        
        if(minSizeVariants->second.empty()) {
            return false;
        }                                                                                                                                                     

        int X;
        int Y;
        int value;

        do{
            X = minSizeVariants->first[0];
            Y = minSizeVariants->first[1];
            value = *(minSizeVariants->second.begin());
        
            minSizeVariants->second.erase(value);
        
            board[X][Y] = value + '0'; // set value in board

            if(!minSizeVariants->second.empty()){
                auto saveBoard = board;
                if(solveSudoku(board)) return true;
                board = saveBoard;
            }

        }while(!minSizeVariants->second.empty());

        pointsAndVariant.erase(minSizeVariants);

        eraseMatrix(pointsAndVariant,X,Y,value);
        
        for(auto &it : pointsAndVariant){
            int _x{it.first[0]};
            int _y{it.first[1]};

            if(_x == X){
                it.second.erase(value);
            }
            if(_y == Y){
                it.second.erase(value);
            }

        }

        // cin.get();
        // cout<<"Next\n\n\n\n\n\n\n\n\n";
    }
    return true;
}

int main(){

    vector<vector<char>> board {{'5','3','.','.','7','.','.','.','.'},
                                {'6','.','.','1','9','5','.','.','.'},
                                {'.','9','8','.','.','.','.','6','.'},
                                {'8','.','.','.','6','.','.','.','3'},
                                {'4','.','.','8','.','3','.','.','1'},
                                {'7','.','.','.','2','.','.','.','6'},
                                {'.','6','.','.','.','.','2','8','.'},
                                {'.','.','.','4','1','9','.','.','5'},
                                {'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(board);

    return 0;
}
