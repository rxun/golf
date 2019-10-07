
#include "engine.h"

Engine::Engine() {
    gameRunning = false;
}

void Engine::runEngine(int numPlayers) {
    // need to check numPlayers is reasonable...
    gameRunning = true;
    std::string line;

    std::srand(std::time(0));

    setup(numPlayers);

    gameState gameProgress = START;

    std::cout << "start game\n";
    while (gameRunning) {
        switch(gameProgress) {
            case START:
                bool startSuccess;
                startSuccess = handleStart(currPlayer);
                if (startSuccess) gameProgress = DRAWN;
                break;
            case DRAWN:
                bool drawSuccess;
                drawSuccess = handleDraw(currPlayer);
                if (drawSuccess) gameProgress = SWITCH;
                break;
            case SWITCH:
                bool switchSuccess;
                switchSuccess = handleSwitch(currPlayer);
                if (switchSuccess) gameProgress = END;
                break;
            case END:
                bool endSuccess;
                endSuccess = handleEnd(currPlayer);
                if (endSuccess) {
                    gameProgress = SCORE;
                } else {
                    gameProgress = START;
                }
                break;
            case SCORE:
                bool scoreSuccess;
                scoreSuccess = handleScore();
                if (scoreSuccess) gameRunning = false;
                break;
            default:
                std::cout << "Something has gone wrong oh no!!\n";
        }
    }

    std::cout << "The game is over!\n";
}

void Engine::setup(int numPlayers) {
    deck = genDeck();
    discard = drawTopCard();
    currIndex = 0;

    for (int i = 0; i < numPlayers; i++) {
        Player *newPlayer = new Player();
        players.push_back(newPlayer);
        newPlayer->faceUpCount = 0;

        dealStock(newPlayer);
    }

    currPlayer = players[0];
    printAll();
}

// GAME STATE STUFF
bool Engine::handleStart() {
    std::string line;
    std::cout << "CURRENTLY PLAYER " << currIndex << "'S TURN\n";
    
    for (unsigned long i = 0; i < players.size(); i++) {
        Player *currPlayer = players[i];
        std::cout << "It is currently Player " << i << "'s turn to flip up two cards.\n";
        while (player->getFaceUpCount() < 2) {
            std::cout << "Select one position (0-5) that you would like to reveal: ";
            std::getline(std::cin, line);
            
            if (line.empty()) continue;

            int num = stoi(line);
            if (num > 5 || num < 0 || player->isFaceUp(num)) {
                std::cout << "Please enter a valid number.\n";
            } else {
                player->setOrientation(num, true);
                player->incrementFaceUpCount();
                player->printStock();
            }
        }
    }
    return true;
}

bool Engine::handleDraw(Player *player) {
    bool handled = false;
    std::string line;
    
    std::cout << "Type 'discard' to take from the discard pile. Type 'draw' to draw a new card from the deck.\n";
    while (!handled) {
        std::getline(std::cin, line);
        if (line.empty()) continue;

        // TODO: lowercase line
        if (line.compare("draw") == 0) {
            std::string card = drawTopCard();
            player->holdCard(card);
            std::cout << "You drew " << card << "\n";
            player->setCurrCardType(false);
            handled = true;
        } else if (line.compare("discard") == 0) {
            std::cout << "You drew " << discard << "\n";
            player->holdCard(discard);
            player->setCurrCardType(true);
            discard = "";
            handled = true;
        } else {
            std::cout << "Please type in either 'discard' or 'draw'\n";
        }
    }
    return handled;
}

bool Engine::handleSwitch(Player *player) {
    bool handled = false;
    std::string line;
    std::string decision = "";
    
    bool isDiscard = player->getCurrCardType();
    std::string currCard = player->getHeldCard();
    if (isDiscard) {
        std::cout << "Please choose a face down card to swap with " << currCard << "\n";
        decision = "swap";
    } else {
        std::cout << "You can swap your card with one of the face-down cards ('swap') OR discard and reveal one of your face-down cards ('discard') \n";
    }

    while (!handled) {
        std::getline(std::cin, line);
        if (line.empty()) continue;
        if (decision.compare("") == 0) {
            if (line.compare("swap") == 0) {
                decision = line;
                std::cout << "Select a card to swap it with.\n";
            } else if (line.compare("discard") == 0) {
                if (isDiscard) {
                    std::cout << "You can't discard the card that was already discarded! Please swap with a card.\n";
                } else {
                    decision = line;
                    std::cout << "Select a card to put face up.\n";
                }
            } else {
                std::cout << "Please either 'swap' or 'discard' " << currCard << "\n";
            }
        } else {
            // need to check decision is definitely swap or discard...
            int num = stoi(line);
            if (num < 0 || num > 5) {
                std::cout << "Please select a valid number between 0-5\n";
            } else if (player->isFaceUp(num)) {
                std::cout << "Please select something that is face-down.";
            }
            
            if(decision.compare("swap") == 0) {
                discard = player->getStockCard(num);
                std::cout << "Your decision was to swap with " << discard << "\n";
                player->setStock(num, currCard);
                player->setOrientation(num, true);
                player->holdCard("");
                
                handled = true;
                break;
            } else if (decision.compare("discard") == 0) {
                std::cout << "Your decision was to discard and reveal this " << player->getStockCard(num) << "\n";
                discard = currCard;
                player->setOrientation(num, true);
                player->holdCard("");
                handled = true;
                break;
            }
        }
    }
    printAll();
    return handled;
}

bool Engine::handleEnd(Player *player) {
    bool allFaceUp = true;
    for (unsigned long i = 0; i < players.size(); i++) {
        if (players[i]->getFaceUpCount() != 6) {
            allFaceUp = false;
            break;
        }
    }

    if (allFaceUp) {
        std::cout << "ALL CARDS ARE FACE UP...Calculating Score.\n";
        return true;
    } else {
        currIndex = (currIndex + 1) % players.size();
        currPlayer = players[currIndex];
        std::cout << "Now it's Player " << currIndex << "'s turn\n";
        return false;
    }
}

bool Engine::handleScore() {
    // each ace counts 1 point
    // each two counts minus two points
    // each numeral card from 3 to 10 scores face value
    // each jack or queen scores 10 points
    // each king scores zero points
    // each pair of equal cards scores zero points 
    
    std::vector<int> scores;
    for (unsigned long i = 0; i < players.size(); i++) {
        Player * currPlayer = players[i];
        int score = currPlayer->calculateScore();
        scores.push_back(score);
    }

    for (unsigned long i = 0; i < scores.size(); i++) {
        std::cout << "Player " << i << " had " << scores[i] << "\n";
    }
    return true;
}

// CARD STUFF
std::string Engine::intToCardName(int card) {
    int suit = card % 4;
    int numInt = card / 4;
    
    std::string cardNum = "";
    
    switch (numInt) {
        case 8:
            cardNum = "T";
            break;
        case 9:
            cardNum = "J";
            break;
        case 10:
            cardNum = "Q";
            break;
        case 11:
            cardNum = "K";
            break;
        case 12:
            cardNum = "A"; 
            break;
        default:
            cardNum = std::to_string(numInt + 2);
    }
    
    std::string cardSuit = "";
    switch(suit) {
        case 0:
            cardSuit = "C";
            break;
        case 1:
            cardSuit = "D";
            break;
        case 2:
            cardSuit = "H";
            break;
        case 3:
            cardSuit = "S";
            break;
        default:
            printf("something has gone wrong");
    }

    std::string cardString = cardNum + cardSuit;
    return cardString;
}

// DECK STUFF
std::vector<std::string> Engine::getDeck() {
    return deck;
}

std::vector<std::string> Engine::genDeck() {
    std::vector<std::string> deck;
    for (int i = 0; i < 52; i++) {
        std::string newCard = intToCardName(i);
        deck.push_back(newCard);
    }

    std::random_shuffle(deck.begin(), deck.end(), myrandom);
    return deck;
}

std::string Engine::drawTopCard() {
    std::string topCard = this->deck.back();
    this->deck.pop_back();
    return topCard;
}

void Engine::dealStock(Player *player) {
    for (int i = 0; i < 6; i++) {
        std::string card = drawTopCard();
        player->addToStock(card);
    }
}


// PRINTING STUFF
void Engine::printAll() {
    size_t stock_size = players[0]->getStock().size();
    for (unsigned long i = 0; i < players.size(); i++) {
        std::cout << "Player " << i << "\n";
        Player * currPlayer = players[i];
        currPlayer->printStock();
        std::cout << "\n";
    }

    std::cout << "\nDISCARD TOP: " << discard << "\n";
}



