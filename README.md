# GOLF

## RULES
Assembled from (here)[https://bicyclecards.com/how-to-play/six-card-golf/].

### The Deal
Each player is dealt 6 cards face down from the deck. The remainder of the cards are placed face down, and the top card is turned up to start the discard pile beside it. Players arrange their 6 cards in 2 rows of 3 in front of them and turn 2 of these cards face up. The remaining cards stay face down and cannot be looked at.

### The Play
The object is for players to have the lowest value of the cards in front of them by either swapping them for lesser value cards or by pairing them up with cards of equal rank.

Beginning with the player to the dealer's left, players take turns drawing single cards from either the stock or discard piles. The drawn card may either be swapped for one of that player's 6 face-down cards, or discarded. If the card is swapped for one of the face down cards, the card swapped in remains face up. The round ends when all of a player's cards are face-up.

## SCORING
Each ace (A) counts 1 point.
Each 2 counts minus 2 points.
Each numeral card from 3 to 10 scores face value.
Each jack (J) or queen (Q) scores 10 points.
Each king (K) scores zero points.
A pair of equal cards scores zero points for the column (even if the equal cards are 2s).

## RUNNING FROM TERMINAL
Clone the repository to your computer.

Run "make" in your terminal and then "./golf" to begin playing the game.

This is intended for two people to play and switch off. The terminal will tell you whose turn it is and what you ought to do.

If you'd like to run tests, you can run "make test" and then ./test to look through the unit tests available.

## RATIONALE
Two classes -- the Engine and a Player. The main Engine handles player turns, game states, printing things, getting user input, tracking stocks/discard. The player handles all the actions regarding their own cards.

Chose a vector to store the "stock" or the 6 cards each player has, as well as which positions were face up, because vectors have constant time when accessing an element.

To randomly generate cards, I made a vector for ints 0-51, then used a function to convert each to a card (0-9, T for ten, J for Jack, Q for Queen, A for Ace), then I did a vector random_shuffle. Then every subsequent draw is already random which is nice. Although suits do not matter in this particular version, there are some versions that might need it, so I kept it in -- plus, it looks much nicer.

With a little more time, checking for duplicates in the stock could have been quicker -- I could have used a hashmap to store duplicates. That would've been much quicker than looping through the seen vector every time. 

## LIMITATIONS
Traditionally, a game is nine "holes" (deals), and the player with the lowest total score is the winner, but this will only run for one game. This would be fairly easily implemented within the Engine class, carrying over scores when restarting.

There are some edge cases I could have more rigorously checked (for instance, I don't check frequently for if the deck is exhausted).

The command line options are a little exhausting within the code. I probably could have incorporated stdin better into the main runEngine() function and passed in lines to helper functions, rather than calling stdin directly from each of these handleGAMESTATE() functions. It would've made unit testing easier too, since the majority of my testing was mostly fiddling with command line and my print functions.  

Currently, this game is optimized for a two person game but should be able to handle up to 4 (the game won't stop you from doing anymore than that, which it should). This number is hard-coded in main.cpp -- feel free to change it if you want to change up the number of players.
