#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<time.h>

using namespace std;

// BlackJack
/////////////////////////////////////////////////////////////////////////////////////////////////
enum Suits { spades = 0, hearts, diamonds, clubs };
enum Value { Ace = 1, two, three, four, five, six, seven, eight, nine, ten, jack, queen, king };
class Card {
private:
    Suits suit;
    Value value;
    bool position; // true == face
public:
    Card(Suits suit, Value value, bool pos) :suit(suit), value(value), position(position) {}
    void Flip() { position = !position; }
    unsigned int GetValue() const {
        unsigned int res = 0;
        if (position) {
            if (value > 10) res = 10;
            else res = value;
        }
        return res;
    }
    friend ostream& operator<<(ostream& os, Card& card);
    ~Card() {}
};
class Hand {
protected:
    vector<Card*> cards;
public:
    Hand() {}
    void Add(Card* newCard) {
        cards.push_back(newCard);
        return;
    }
    void Clear() {
        for (auto temp : cards) delete temp;
        cards.clear();
        return;
    }
    unsigned int GetTotal() const {
        unsigned int res = 0;
        bool have_ace = false;

        if (!cards[0]->GetValue()) return res;

        for (auto it : cards) {
            unsigned int temp = it->GetValue();
            res += temp;
            if (temp == 1) have_ace = true;
        }

        if (have_ace && (res + 10) <= 21) res += 10;

        return res;
    }
    ~Hand() {}
};
class GenericPlayer : public Hand {
protected:
    string playerName;
public:
    GenericPlayer(string playerName) :playerName(playerName) {}
    virtual bool IsHitting() const = 0;
    bool  IsBoosted() { return Hand::GetTotal() > 21; }
    void Bust() {
        cout << "Name:= " << playerName << '\n';
        cout << "OVERKILL\n";
    }
    friend ostream& operator<<(ostream& os, GenericPlayer& CP);
    ~GenericPlayer() {}
};
class Player : public GenericPlayer {
protected:

public:
    Player(string playerName) :GenericPlayer::GenericPlayer(playerName) {}
    bool IsHitting() const override {
        char ch;
        cout << playerName << " Do you need new card (Y/N)?";
        cin >> ch;
        cout << '\n';
        return (ch == 'Y' || ch == 'y');
    }
    void Win() const { cout << playerName << " won\n"; }
    void Lose() const { cout << playerName << " lost\n"; }
    void Push() const { cout << playerName << " draw\n"; }
    ~Player() {}
};
class House :public GenericPlayer {
protected:

public:
    House():GenericPlayer::GenericPlayer("House") {}
    bool IsHitting() const override {
        return GetTotal() <= 16;
    }
    void FlipFirstCard() { 
        if (!cards.empty()) cards[0]->Flip();
        else cout << "No cards\n";
    }
    ~House() {}
};
class Deck : public Hand {
private:
public:
    Deck() {}
    void Populate() {
        for (int i = 0; i < 4; i++)
            for (int j = 1; j <= 13; j++)
                cards.push_back(new Card((Suits)i, (Value)(j), false));
    }
    void Shuffle() {
        random_shuffle(cards.begin(), cards.end());
    }
    void Deal(Hand& aHand) {
        if (!cards.empty()) {
            aHand.Add(cards.back());
            cards.pop_back();
        }
    }
    void AddltionalCards(GenericPlayer& aGenericPlayer) {
        while (!(aGenericPlayer.IsBoosted()) && aGenericPlayer.IsHitting()){
            Deal(aGenericPlayer);
            cout << aGenericPlayer << endl;
            if (aGenericPlayer.IsBoosted()) aGenericPlayer.Bust();
        }

    }
    ~Deck() {}
};
class Game {
private:
    Deck deck;
    House house;
    vector<Player*> players;
public:
    Game(vector<string>&names) {
        for (auto it : names) players.push_back(new Player(it));
        srand(time(0));
        deck.Populate();
        deck.Shuffle();
    }
    void play() {
        // two cards everybody
        for (int i = 0; i < 2; i++) {
            for (auto it : players) {
                deck.Deal(*it);
                deck.Deal(house);
            }
        }

        house.FlipFirstCard();

        for (auto it : players) cout << *it << endl;
        cout << house << endl;

        for (auto it : players) deck.AddltionalCards(*it);
        
        house.FlipFirstCard();
        cout << '\n' << house;

        deck.AddltionalCards(house);

        if (house.IsBoosted()) {
            for (auto it : players) {
                if (!it->IsBoosted()) it->Win();
            }
        }
        else {
            for (auto it : players) {
                if (!it->IsBoosted()) {
                    if (it->GetTotal() > house.GetTotal()) it->Win();
                    else if (it->GetTotal() < house.GetTotal()) it->Lose();
                    else it->Push();
                }
            }
        }

        for (auto it : players) it->Clear();
        house.Clear();

    }

    ~Game() {}
};
ostream& operator<<(ostream& os, Card& card) {
    if (!card.position) os << "XX";
    else switch (card.suit)
    {
    case spades:
        os << "spades ";
        if (card.value > 10) os << 10;
        else os << card.value;
        break;
    case hearts:
        os << "hearts ";
        if (card.value > 10) os << 10;
        else os << card.value;
        break;
    case diamonds:
        os << "diamonds ";
        if (card.value > 10) os << 10;
        else os << card.value;
        break;
    case clubs:
        os << "clubs ";
        if (card.value > 10) os << 10;
        else os << card.value;
        break;
    default:
        break;
    }
    os << '\n';
    return os;
}
ostream& operator<<(ostream& os, GenericPlayer& CP) {
    os << CP.playerName << '\n';
    os << "Cards:\n";
    if (CP.cards.size())
        for (size_t i = 0; i < CP.cards.size(); i++)
            os << i + 1 << ". " << *(CP.cards[i]);
    else os << "No cards\n";
    os << "Total:= " << CP.GetTotal() << '\n';
    return os;
}

int main() {
 
    cout << "\t\tWelcome to Blackjack!\n\n";

    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7){
        cout << "How many players? (1 - 7): ";
        cin >> numPlayers;
    }

    vector<string> names;
    string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        cout << "Enter player name: ";
        cin >> name;
        names.push_back(name);
    }
    cout << '\n';

    Game aGame(names);
    char again = 'y';
    while (again != 'n' && again != 'N')
    {
        system("cls");
        aGame.play();
        cout << "\nDo you want to play again? (Y/N): ";
        cin >> again;
    }

	return 0;
}

