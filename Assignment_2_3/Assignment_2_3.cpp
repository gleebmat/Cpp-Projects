#include <iostream>
#include <string>
#include <cmath>
#include <conio.h>
#include <ctime>

using namespace std;

class Player {
private:
    string name;
    int health{ 100 };
    int positionX, positionY;
    int maxMovement{ 0 };
    int attackPower{ 0 };

public:
    Player(string n, int x, int y) : name(n), positionX(x), positionY(y) {}

    void Setup() {
        cout << "\n--- Player's Setup " << name << " ---" << endl;
        cout << "You have 20 points. Divide them for the maximum amount you can gothrough for each turn (Axis X+Axis Y).\nThe rest will be your attack rate." << endl;
        cout << "The farther you go - the weaker your attack!" << endl;

        int move;
        while (true) {
            cout << "Type the maximum amount of your travel each turn"<<endl;
            cin >> move;
            if (move >= 1 && move < 20) {
                maxMovement = move;
                attackPower = 20 - move;
                cout << "The settings are managed.\nMaximum displace (Axis X, Axis Y) " << maxMovement << ", Attack Rate " << attackPower << endl;
                break;
            }
            cout << "Error! The number must be greater than 0 and less that 20" << endl;
        }
    }

 
    void TakeTurn(Player& opponent) {
        if (!isAlive()) return;

        cout << "\nTurn: " << name << " (HP: " << health << ") [" << positionX << ":" << positionY << "]" << endl;
        cout << "1. Move\n2. Attack\nYour choice: ";
        int choice;
        cin >> choice;

        if (choice == 1) {
            int dx, dy;
            cout << "How much do you want your displacement by Axis X could be? (The sum must not be greater than " << maxMovement << "): ";
            cin >> dx;
            cout << "How much do you want your displacement by Axis Y could be? (The sum must not be greater than " << maxMovement << "): ";
            cin >> dy;

            Movement(dx, dy);
        }
        else if (choice == 2) {
            Attack(opponent);
        }
        else {
            cout << "It seems you did miss the keyboard... Skip the turn then!" << endl;
        }
    }


    void Movement(int dx, int dy) {
        if (abs(dx) + abs(dy) <= maxMovement) {
            positionX += dx;
            positionY += dy;
            
            if (positionX < 0) positionX = 0; if (positionX > 99) positionX = 99;
            if (positionY < 0) positionY = 0; if (positionY > 99) positionY = 99;
            cout << "New position: " << positionX << ", " << positionY << endl;
        }
        else {
            cout << "Too far. Your limit: " << maxMovement << endl;
        }
    }
    int getX() { return positionX; }
    int getY() { return positionY; }
    void Attack(Player& opponent) {
        if (attackEnabled(opponent)) {
            opponent.health -= attackPower;
            cout << name << " hit " << opponent.name << " with " << attackPower << " attack rate!" << endl;
            if (opponent.health < 0) opponent.health = 0;
        }
        else {
            cout << "The opponent is too far to attack them" << endl;
        }
    }

    bool attackEnabled(Player& opponent) {
        return (abs(positionX - opponent.positionX) <= 2 && abs(positionY - opponent.positionY) <= 2);
    }

    bool isAlive() { return health > 0; }
    string getName() { return name; }
};
void DrawMap(Player& p1, Player& p2) {
    const int displaySize = 20;
    cout << "\n    ==== BATTLE FIELD (Scale 1:5) ====" << endl;
    cout << "  Y ^ ";
    for (int i = 0; i < displaySize; i++) cout << "---";
    cout << endl;


    for (int y = displaySize - 1; y >= 0; y--) {
        printf(" %2d | ", y * 5);
        for (int x = 0; x < displaySize; x++) {

            int mX1 = p1.getX() / 5;
            int mY1 = p1.getY() / 5;
            int mX2 = p2.getX() / 5;
            int mY2 = p2.getY() / 5;

            if (x == mX1 && y == mY1) cout << " A ";
            else if (x == mX2 && y == mY2) cout << " B ";
            else cout << " . ";
        }
        cout << "|" << endl;
    }

    cout << "       ";
    for (int i = 0; i < displaySize; i++) cout << "---";
    cout << "\n       ";

    for (int i = 0; i < displaySize; i += 2) printf("%-6d", i * 5);
    cout << " > X" << endl;

    cout << "\n    (A: " << p1.getName() << " | B: " << p2.getName() << ")" << endl;
}

void ClearScreen() {
    std::cout << "\033[2J\033[H";
}

int main() {
    srand(time(0));
    string name1, name2;
    cout << "The name of the first player" << endl;
    cin >> name1;
    cout << "The name of the second player" << endl;
    cin >> name2;
    int position1X = int(rand() % 100);
    int position1Y = int(rand() % 100);
    int position2X = int(rand() % 100);
    int position2Y = int(rand() % 100);
    Player pA(name1, position1X, position1Y);
    Player pB(name2, position2X,position2Y);

    pA.Setup();
    pB.Setup();
    ClearScreen();

    while (pA.isAlive() && pB.isAlive()) {
        

        DrawMap(pA, pB);
        pA.TakeTurn(pB);
        _getch();
        ClearScreen();

        DrawMap(pA, pB);
        pB.TakeTurn(pA);
        _getch();
        ClearScreen();
    }

    cout << "\nThe game is over!" << endl;
    if (pA.isAlive()) cout << "The winner is: " << pA.getName() << endl;
    else cout << "The winner is: " << pB.getName() << endl;

    return 0;
}