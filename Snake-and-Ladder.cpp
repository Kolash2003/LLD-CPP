#include <bits/stdc++.h>
#include <random>

using namespace std;

class Player {
    string playerName;
    int playerId;

    public:
    Player(string playerName, int playerId) {
        this->playerName = playerName;
        this->playerId = playerId;
    }

    int getplayerId() {
        return playerId;
    }

    string getplayerName() {
        return playerName;
    }

    void Addplyers(string name, int id) {

    }
};

class Dice {
    int sides = 6;
    
    public: 
    int numberofDice;
    Dice() : numberofDice(1), sides(6) {}
    Dice(int numberofDice, int sides=6) {
        if(numberofDice < 1) {
            cout << "Atleast one die is needed to start the game!" << endl;
            return;
        }
        this->numberofDice = numberofDice;
    }

    int roll(int numberofDice) {
        random_device rd;  // Random seed
        mt19937 gen(rd()); // Mersenne Twister RNG
        uniform_int_distribution<> distr(1*numberofDice, 6 * numberofDice); // Range [0, 6 * numberOfDice]

        return distr(gen);
    }
};

class Jump {
    protected:
    int startpoint;
    int endpoint;

    public:
    Jump(int statpoint, int endpoint) {
        this->startpoint = startpoint;    // for snake startpoint > endpoint
        this->endpoint = endpoint;         // for ladder startpoint < endpoint
    }

    void printJump() {
        cout << "Jump ladder : " << startpoint << " endpoint : " << endpoint << endl;
    }
};


class Ladder: public Jump {
    public:
    Ladder() : Jump(startpoint, endpoint) {}
    Ladder(int startpoint, int endpoint) : Jump(startpoint, endpoint) {
        if(startpoint >= endpoint) cout << "For ladder start < end." << endl;
    }
    
    void show() {
        printJump();
    }
};

class Snake : public Jump {
    public:
    Snake(int startpoint, int endpoint) : Jump(startpoint, endpoint) {
        if(startpoint <= endpoint) cout << "For snake start > end." << endl;
    }

};


class boardpoint {
    int endpoint;

    public:
    boardpoint() : endpoint(100) {}
    boardpoint(int endpoint) {
        this->endpoint = endpoint;
    }
};

class gameboard {
    Dice dice;
    queue<Player> players;
    vector<Ladder> ladders;
    vector<Snake> snakes;
    unordered_map<int, int> playerposition; // ✅ FIXED TYPE
    boardpoint endpoint;
    unordered_map<int, pair<int, int>> assets;
    int numberofDice;

    public:
    gameboard(Dice dice, queue<Player> players, vector<Ladder> ladders, vector<Snake> snakes,
              unordered_map<int, int> playerposition, boardpoint endpoint, int numberofDice) {
        
        this->dice = dice;
        this->players = players;
        this->ladders = ladders;
        this->snakes = snakes;
        this->playerposition = playerposition;
        this->endpoint = endpoint;
        this->numberofDice = numberofDice;
    }


    bool addSnake(int i, int j) {
        if(assets.count(i)) {
            cout << "An assest already exixts at this position" << endl;
        }

        if(i<=j) {
            cout << "Error, need start > end" << endl;
            return false;
        }

        assets[i] = {j, 0};

        snakes.push_back(Snake(i, j));
        return true;    
    }

    bool addLadder(int i, int j) {
        if(assets.count(i)) {
            cout << "An assest already exixts at this position" << endl;
        }

        if(i>=j) {
            cout << "Error, need start < end" << endl;
            return false;
        }

        assets[i] = {j, 1};

        ladders.push_back(Ladder(i, j));
        return true;    
    }

    void startgame() {
        while (true && players.size() > 1) {
            Player player = players.front();
            players.pop();

            int pos = playerposition[player.getplayerId()];
            int rollValue = dice.roll(numberofDice);
            int newPos = pos + rollValue;

            // Check for snake or ladder
            while (assets.count(newPos)) {
                pair<int, int> jump = assets[newPos];
                if (jump.second == 0)
                    cout << "Oops! Snake from " << newPos << " to " << jump.first << endl;
                else
                    cout << "Yay! Ladder from " << newPos << " to " << jump.first << endl;

                newPos = jump.first;
            }

            playerposition[player.getplayerId()] = newPos;
            cout << player.getplayerName() << " moved to " << newPos << endl;

            if (newPos >= 100) {
                cout << player.getplayerName() << " has won the game!" << endl;
                break;
            }

            players.push(player); // Put player back for next round
        }
    }
};


int main() {
    // Create players
    Player p1("Alice", 1);
    Player p2("Bob", 2);
    
    queue<Player> playerQueue;
    playerQueue.push(p1);
    playerQueue.push(p2);

    // Create dice
    Dice dice(1);  // One dice

    // Create ladders and snakes
    vector<Ladder> ladders;
    vector<Snake> snakes;

    // Initial player positions
    unordered_map<int, int> playerPositions;
    playerPositions[p1.getplayerId()] = 0;
    playerPositions[p2.getplayerId()] = 0;

    // Endpoint (100 by default)
    boardpoint endpoint;

    // Create the gameboard
    gameboard gb(dice, playerQueue, ladders, snakes, playerPositions, endpoint, 1);

    // Add ladders
    gb.addLadder(2, 38);
    gb.addLadder(7, 14);
    gb.addLadder(8, 31);
    gb.addLadder(15, 26);
    gb.addLadder(21, 42);
    gb.addLadder(28, 84);
    gb.addLadder(36, 44);
    gb.addLadder(51, 67);
    gb.addLadder(71, 91);
    gb.addLadder(78, 98);
    gb.addLadder(87, 94);

    // Add snakes
    gb.addSnake(16, 6);
    gb.addSnake(46, 25);
    gb.addSnake(49, 11);
    gb.addSnake(62, 19);
    gb.addSnake(64, 60);
    gb.addSnake(74, 53);
    gb.addSnake(89, 68);
    gb.addSnake(92, 88);
    gb.addSnake(95, 75);
    gb.addSnake(99, 80);

    // Start the game
    gb.startgame();

    return 0;
}
