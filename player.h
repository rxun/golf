#ifndef PLAYER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PLAYER_H
#include <vector>
#include <string>
#include <iostream>

class Player {
    private:
        std::vector<std::string> stock;
        std::vector<bool> faceUp;
        
        std::string currCard;
        bool currCardIsDiscard;
    public:
        Player();
        int faceUpCount;
        

        std::vector<std::string> getStock();
        std::vector<bool> getFaceUp();
        int getFaceUpCount();
        void holdCard(std::string card);
        void setAllStock(std::vector<std::string> givenStock);
        void setStock(int position, std::string card);
        std::string getStockCard(int position);
        std::string getHeldCard();
        void setOrientation(int position, bool isUp);
        bool isFaceUp(int position);
        void incrementFaceUpCount();

        void printStock();
        void printAllStock();

        int calculateScore();

        void addToStock(std::string card);

        void setCurrCardType(bool isDiscard);
        bool getCurrCardType();
};
#endif