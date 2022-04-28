#include<iostream>
#include<vector>
#include<Windows.h>
#include<conio.h>
#include<chrono>
#include<thread>
#include<string>
#include<time.h>
#define handle GetStdHandle(STD_OUTPUT_HANDLE)

using namespace std;

unsigned short StrToInt(const string& str) {
    unsigned short res = 0;
    for (auto ch : str) {
        if (ch < '0' || ch>'9') return res;
        res *= 10;
        res += ch - '0';
    }
    return res;
}
// For position cursor
void goToXY(const COORD position) {
    SetConsoleCursorPosition(handle, position);
}
bool CMP_COORD(COORD& first, COORD& second) {
    if (first.X != second.X) return false;
    if (first.Y != second.Y) return false;
    return true;
}
bool count_COORD(vector<COORD>& points, COORD& second) {
    auto begin = points.begin();
    while (begin != points.end()) {
        if (CMP_COORD(*begin, second)) return true;
        begin++;
    }
    return false;
}
unsigned int if_have_speed() {
    while (_kbhit()) {
        int key = _getch();
        if (key == 224 || !key) {
            key = _getch();
            return key;
        }
    }
    return 0;
}
unsigned int if_no_speed() {
    unsigned int key;
    do {
        key = _getch();
    } while (key != 224 || !key);
    return _getch();
}


class GameMap {
private:
    unsigned short X;
    unsigned short Y;
    COORD now_food_position;
public:
    GameMap() { X = 50; Y = 10; }
    void print_MAP(const unsigned short& X, const unsigned short& Y) {
        system("cls");
        for (int i = 0; i < X + 2; i++) cout << '+';
        cout << endl;

        COORD temp;
        temp.X = X + 1;
        for (int i = 1; i <= Y; i++) {
            cout << '|';
            temp.Y = i;
            goToXY(temp);
            cout << '|' << endl;
        }

        for (int i = 0; i < X + 2; i++) cout << '+';
    }
    unsigned short WelcomUser() {
        unsigned short speed = 1;

        print_WELCOME();
        string str;

        do {
            cout << "Please enter the length (min 50, max 120): "; cin >> str;
            X = StrToInt(str);
        } while (X < 50 || X>120);

        do
        {
            cout << "Please enter the width (min 10, max 40): "; cin >> str;
            Y = StrToInt(str);
        } while (Y < 10 || Y>40);

        cout << '\n'
            << "1. Slow\n"
            << "2. Normal\n"
            << "3. Fast\n"
            << "4. By pressing\n";

        do {
            cout << "Please change number of speed: "; cin >> str;
            speed = StrToInt(str);
        } while (speed < 1 || speed>4);

        print_MAP(X, Y);
        return speed;
    }
    void print_GAMEOVER() {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t  .d8888b.                                          .d88888b.                                     888\n"
            << "\td88P  Y88b                                         d88P   Y88b                                    888 \n"
            << "\t888    888                                         888     888                                    888 \n"
            << "\t888          8888b.   88888b.d88b.   .d88b.        888     888  888  888   .d88b.   888d888       888\n"
            << "\t888  88888      '88b  888  888  88b d8P  Y8b       888     888  888  888  d8P  Y8b  888P          888\n"
            << "\t888    888  .d888888  888  888  888 88888888       888     888  Y88  88P  88888888  888           Y8P\n"
            << "\tY88b  d88P  888  888  888  888  888 Y8b            .Y88b..d88P   Y8bd8P   Y8b.      888                     \n"
            << "\tY8888P88     Y888888  888  888  888   Y8888          Y88888P      Y88P     Y8888    888           888 \n\n\n";

    }
    void print_WINGAME() {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\tY88b   d88P   .d88888b.   888     888       888       888   .d88888b.   888b    888\n"
            << "\t\t Y88b d88P   d88P   Y88b  888     888       888   o   888  d88P   Y88b  8888b   888\n"
            << "\t\t  Y88o88P    888     888  888     888       888  d8b  888  888     888  88888b  888\n"
            << "\t\t   Y888P     888     888  888     888       888 d888b 888  888     888  888Y88b 888\n"
            << "\t\t    888      888     888  888     888       888d88888b888  888     888  888 Y88b888\n"
            << "\t\t    888      888     888  888     888       88888P Y88888  888     888  888  Y88888\n"
            << "\t\t    888      Y88b..d88P   Y88b..d88P        8888P   Y8888  Y88b..d88P   888   Y8888\n"
            << "\t\t    888        Y88888P      Y88888P         888P     Y888    Y88888P    888    Y888\n\n\n";
    }
    void print_WELCOME() {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n";
        cout << "\t\t\t888   o   888               888\n"
            << "\t\t\t888  d8b  888               888\n"
            << "\t\t\t888 d888b 888     .d88b.    888     .d8888b     .d88b.      88888b.d88b.\n"
            << "\t\t\t888d88888b888    d8P  Y8b   888     d88P        d88  88b    888  888  88b\n"
            << "\t\t\t88888P Y88888    88888888   888     888         888  888    888  888  888\n"
            << "\t\t\t8888P   Y8888    Y8b.       888     Y88b.       Y88..88P    888  888  888\n"
            << "\t\t\t888P     Y888      Y8888    888      Y8888P       Y88P      888  888  888\n\n\n";
    }
    void new_food(vector<COORD>& snake_position) {
        int size = (X * Y) - snake_position.size();

        int index = 0;
        COORD* food_position = new COORD[size];

        COORD temp;
        temp.X = 1;
        temp.Y = 1;

        for (int i = 0; i < Y; i++) {
            for (int j = 0; j < X; j++) {
                if (!count_COORD(snake_position, temp)) {
                    food_position[index].X = temp.X;
                    food_position[index].Y = temp.Y;
                    index++;
                }
                temp.X++;
            }
            temp.X = 1;
            temp.Y++;
        }
        now_food_position = food_position[(rand() + rand()) % size];

        delete[] food_position;
    }
    void print_food(vector<COORD>& snake_points) {
        new_food(snake_points);
        goToXY(now_food_position);
        cout << '@';
    }
    unsigned short getX() { return X; }
    unsigned short getY() { return Y; }
    unsigned short getMapSize() { return X * Y; }
    COORD getPosition() { return now_food_position; }
    ~GameMap() {}
};
class Snake {
private:
    vector<COORD> points;
    COORD last_point;
    COORD score_position;
    unsigned int score;
    unsigned int banned_command;
    unsigned int now_command;
    unsigned int speed;

public:
    Snake(unsigned short Y) {
        score = 0;
        speed = 35;
        now_command = 77;
        banned_command = 75;

        COORD temp;
        temp.Y = (Y / 2) + 1;
        for (int i = 3; i > 0; i--) {
            temp.X = i;
            points.push_back(temp);
        }

        //
        last_point.X = 120;
        last_point.Y = 0;

        score_position.X = 1;
        score_position.Y = Y + 2;
    }
    void add_point(GameMap& food) {
        points.push_back(last_point);
        switch (speed) {
        case 100:
            score += 2;
            break;
        case 50:
            score += 3;
            break;
        case 35:
            score += 5;
            break;
        case 4:
            score++;
        }
        food.print_food(points);
        goToXY(score_position);
        for (int i = 0; i < 30; i++) { cout << ' '; }
        goToXY(score_position);
        cout << "Score = " << score;
    }
    bool check_trash(GameMap& map_size) {
        if (points[0].X < 1 || points[0].X>map_size.getX()) return true;
        if (points[0].Y < 1 || points[0].Y>map_size.getY()) return true;
        for (int i = 1; i < points.size(); i++)
            if (CMP_COORD(points[i], points[0])) return true;
        return false;
    }
    int next_move(unsigned int& key, GameMap& map) {
        int game_status = 0;

        if (key == banned_command ||
            (key != 72 && key != 75 && key != 77 && key != 80)) key = now_command;

        last_point = *(points.end() - 1);

        points.erase(points.end() - 1);
        points.insert(points.begin() + 1, *points.begin());

        switch (key)
        {
        case 72:
            points[0].Y--;
            banned_command = 80;
            break;
        case 77:
            points[0].X++;
            banned_command = 75;
            break;
        case 80:
            points[0].Y++;
            banned_command = 72;
            break;
        case 75:
            points[0].X--;
            banned_command = 77;
            break;
        default: break;
        }

        if (check_trash(map)) game_status = -1;

        bool add = false;

        if (game_status != -1)
            if (map.getPosition().X == points[0].X &&
                map.getPosition().Y == points[0].Y) {
                if (map.getMapSize() - 1 == points.size()) game_status = 1;
                else { add_point(map); add = true; };
            }

        print_snake(add);

        now_command = key;

        if (speed != 4) {
            if (now_command == 72 || now_command == 80)
                Sleep(speed * 1.6);
            else
                Sleep(speed);
        }
        return game_status;
    }
    void print_snake(bool add) {
        goToXY(last_point);
        if (!add)
            cout << ' ';
        else
            cout << '*';
        goToXY(points[1]);
        cout << '*';
        goToXY(points[0]);
        cout << char(1);
    }
    void print_snaka_first_time(GameMap& food) {
        for (int i = 0; i < points.size(); i++) {
            goToXY(points[i]);
            if (!i)cout << char(1);
            else cout << '*';
        }
        goToXY(score_position);
        cout << "Score = " << score;

        food.print_food(points);

    }
    unsigned short getScore() { return score; }
    unsigned short getSnakeSize() { return points.size(); }
    vector<COORD>& getPoints() { return points; }
    void setSpeed(unsigned short speed) {
        switch (speed) {
        case 1:
            this->speed = 100;
            break;
        case 2:
            this->speed = 50;
            break;
        case 3:
            this->speed = 35;
            break;
        case 4:
            this->speed = speed;
            break;
        default:break;
        }
    }
    ~Snake() {}
};

int main() {

    srand(time(0));
    system("mode con cols=130 lines=50");
    char keep_going = 'N';

    GameMap map;

    do {
        unsigned int key = 77;
        int status = 0;

        unsigned short speed = map.WelcomUser();

        Snake MySnake(map.getY());
        MySnake.print_snaka_first_time(map);
        MySnake.setSpeed(speed);

        do {
            if (speed != 4) key = if_have_speed();
            else key = if_no_speed();
            status = MySnake.next_move(key, map);
        } while (!status);

        if (status == -1) map.print_GAMEOVER();
        else map.print_WINGAME();

        cout << "Do you want to play again (Y/N) ?... "; cin >> keep_going;
    } while (keep_going == 'Y' || keep_going == 'y');

    return 0;
}
