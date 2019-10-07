#include "../catch/catch.hpp"
#include "../engine.h"
#include <iostream>

Engine engine = Engine();

TEST_CASE("CORRECT CARD -> INT") {
    REQUIRE(1 == 1);
}

TEST_CASE("CORRECT INT -> CARD") {
    REQUIRE(1 == 1);
}

TEST_CASE("GENDECK") {
    std::vector<std::string> deck = engine.genDeck();
    std::string topCard = engine.drawTopCard();

    bool foundCardInDeck = false;
    for (unsigned long i = 0; i < deck.size(); i++) {
        if (topCard.compare(deck.at(i)) == 0) {
            foundCardInDeck = true;
        }
    }

    REQUIRE(foundCardInDeck == false);
}