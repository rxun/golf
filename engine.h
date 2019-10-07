#ifndef ENGINE_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define ENGINE_H

#include "player.h"
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

enum gameState { START, DRAWN, SWITCH, END, SCORE };

class Engine {
    private:
        std::vector<std::string> deck;
        std::string discard;
        std::vector<Player*> players;
        Player * currPlayer;
        int currIndex;
        bool gameRunning;
    public:
        Engine();
        void runEngine(int numPlayers);

        void setup(int numPlayers);

        bool handleStart();
        bool handleDraw(Player *player);
        bool handleSwitch(Player *player);
        bool handleEnd(Player *player);
        bool handleScore();

        std::vector<std::string> getDeck();
        std::string drawTopCard();

        int cardNameToInt(std::string card);
        std::string intToCardName(int cardNum);
        std::vector<std::string> genDeck();

        void dealStock(Player *player);

        void printAll();

        static int myrandom(int i) { return std::rand()%i; }

};


#endif