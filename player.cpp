#include "player.h"
#include <vector>
#include <string>

#include "player.h"

Player::Player() {
    for (int i = 0; i < 6; i++) {
        faceUp.push_back(false);
    }
    this->faceUpCount = 0;
    this->currCardIsDiscard = false;
}

std::vector<std::string> Player::getStock() {
    return stock;
}

std::vector<bool> Player::getFaceUp() {
    return faceUp;
}

int Player::getFaceUpCount() {
    return faceUpCount;
}

void Player::holdCard(std::string card) {
    currCard = card;
}

void Player::setAllStock(std::vector<std::string> givenStock) {
    stock = givenStock;
}

void Player::setStock(int position, std::string card) {
    stock[position] = card;
}

std::string Player::getHeldCard() {
    return currCard;
}

void Player::setOrientation(int position, bool isUp) {
    faceUp[position] = isUp;
}

bool Player::isFaceUp(int position) {
    return faceUp[position];
}

void Player::incrementFaceUpCount() {
    faceUpCount++;
    // std::cout << "incremeneted \n";
}

void Player::addToStock(std::string card) {
    if (stock.size() < 6) {
        stock.push_back(card);
    }
}

void Player::setCurrCardType(bool isDiscard) {
    currCardIsDiscard = isDiscard;
}

bool Player::getCurrCardType() {
    return currCardIsDiscard;
}

std::string Player::getStockCard(int position) {
    return stock[position];
}

int Player::calculateScore() {
    std::vector<char> seen; // mayeb change to map later
    int dupes = 0;
    int score = 0;
    for (unsigned long j = 0; j < getStock().size(); j++) {
        std::string currCard = getStockCard(j);
        char digit = currCard[0];
            
        bool found = false;
        for (unsigned long k = 0; k < seen.size(); k++) {
            if (digit == seen[k]) {
                seen.erase(seen.begin() + k);
                found = true;
                dupes++;
                break;
            }
        }

        if (!found) {
            seen.push_back(digit);
        } 
    }

        // maybe check for duplicates as we add in cards instead?

    for (unsigned long j = 0; j < seen.size(); j++) {
        char currCard = seen[j];
        if (currCard == 'A') {
            score += 1;
        } else if (currCard == '2') {
            score -= 2;
        } else if (currCard == 'J' || currCard == 'Q' || currCard == 'T') {
            score += 10;
        } else if (currCard == 'K') {
            score += 0;
        } else {
            score += currCard - '0';
        }
    }
    return score;
}

// PRINTING STUFF
void Player::printAllStock() {
    for (int i = 0; i < 6; i++) {
        std::cout << i << ": " << stock[i] << "  ";
        if (i == 2 || i == 5) std::cout << "\n";
    }
}

void Player::printStock() {
    for (int i = 0; i < 6; i++) {
        std::cout << i << ": ";
        if (isFaceUp(i)) {
            std::cout << stock[i] << "  ";
        } else {
            std::cout << "??  ";
        }
        if (i == 2 || i == 5) std::cout << "\n";
    }
}
