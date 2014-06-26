
/*********************************************************************
** Program Filename: poker.cpp
** Author: Helena Bales
** Date: 04/23/2014
** Description: poker class
** Input: none
** Output: none
********************************************************************/

#include"./poker.hpp"
#include <iostream>

//#define DEBUG
//#define BUGSl
//#define BUGSm

using namespace std;

/*********************************************************************
** Function: poker::poker
** Description: default constructor. acutally does nothing
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
********************************************************************/ 

poker::poker() {
	//default constructor doesn't actually do anything
	//that's why it's empty.
}

/*********************************************************************
** Function: poker::play
** Description: handles the gameplay
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
********************************************************************/ 

bool poker::play() {
	int cont;
	
	//seeds the random number generator (only do once)
   srand(time(NULL));
   
   #ifndef DEBUG
   //gets the number of players from the user
	numplayers = getnump();
	#endif
	
	#ifdef DEBUG
	//sets the number of players to 6 if you are in debug mode
	numplayers = 6;
	#endif
	
	//prints the deck for debugging/grading
	#ifdef DEBUG
	printd();
	#endif
	
	do {
		
		//initializes the deck
		ideck();
		
		#ifndef DEBUG
		//gives random cards to each player
		setup(starthand);
		#endif
		
		#ifdef DEBUG
		//this sets each player to have a different winning hand
		//so that someone can actually win this damn game
		//for testing.
		checkthreekind(1);
		checkfourkind(2);
		checkstraight(3);
		checkflush(4);
		checkfullhouse(5);
		checkstraightflush(6);
		#endif
		
		for(int p = 0; p < numplayers; p++) {
			
			#ifndef DEBUG
			//clears out the screen
			spam();
			
			//lets the player continue or quit
			cout << "Player " << p+1 << " it is your turn." << endl;
			cout << "Enter a 1 to continue. (0 will quit the game): ";
			cin >> cont;
			if(!cont)
				return 0;
			
			//clears out the screen again
			spam();
			#endif
				
			//prints out the player's hand
			cout << "Here is your hand: " << endl;
			printhand(p+1);
			
			#ifndef DEBUG
			//allows the player to discard up to 4 cards
			discard(p+1);
			//continue or quit again
			cout << "Enter a 1 to continue. (0 will quit the game): ";
			cin >> cont;
			if(!cont)
				return 0;
			#endif
			
		}
		
		for(int p = 0; p < numplayers; p++) {
			#ifdef BUGSl
			//this header is for debugging so you can see what player's
			//hand is being evaluated
			cout << "===========" << p+1 << "===========" << endl;
			#endif
			//calculates each player's scores
			pscores(p+1);
		}
		
		//checks who has won
		won();
		
		//allows the players to play again or not
		cout << "Do you want to play another hand?" << endl;
		cout << "Enter a 1 to play again, or a 0 to quit: ";
		cin >> cont;
		
	}while(cont);
}

/*********************************************************************
** Function: poker::discard
** Description: allows user to discard up to 4 cards and get new ones
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: p contains a valid number
** Post-Conditions: the player still has the same number of cards
********************************************************************/ 

void poker::discard(int p) {
	int discarded = 0;
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 13; j++) {
			if(deck[i][j].held == p) {
				if(discarded == 4) {
					cout << "You have discarded the max number of cards per hand." << endl;
				}
				else {
					bool kept;
					cout << "Do you want to discard your ";
					printcard(p, i, j);
					cout << "? (enter 1 to discard, 0 to keep): ";
					cin >> kept;
					if(kept == 1) {
						deck[i][j].held = 0;
						discarded += 1;
					}
				}
			}
		}
	}
	
	for(int c = 0; c < discarded; c++) {
		draw(p);
	}
	
	cout << "Here is your new hand: " << endl;
	printhand(p);
	
}

/*********************************************************************
** Function: poker::setup
** Description: draws starting hands for each player
** Parameters: numcards, the number of cards to start with
** Pre-Conditions: numcards is 5, and player* exists
** Post-Conditions: 5 cards are drawn to each player
********************************************************************/ 

void poker::setup(int numcards) {

   for(int i = 0; i < numplayers; i++) {
	   //for each player, run draw number of cards times
      for(int j = 0; j < numcards; j++)
			draw(i+1);
   }

}

/*********************************************************************
** Function: poker::pscores
** Description: calculates the player's score
** Parameters: int playernum, the character that identifies the
** 		player as holding a certain card in the deck
** Pre-Conditions: playernum contains a valid number in range
** Post-Conditions: the score of the player is returned (in num suit
** 		matches
********************************************************************/ 

int poker::pscores(int playernum) {
   
   players[playernum-1].score = 0;
   if(straightflush(playernum)) {
		players[playernum-1].score = 50;
		return players[playernum].score;
	}
	else if(fourkind(playernum)) {
		players[playernum-1].score = 30;
		return players[playernum].score;
	}
	else if(fullhouse(playernum)) {
		players[playernum-1].score = 25;
		return players[playernum].score;
	}
	else if(flush(playernum)) {
		players[playernum-1].score = 20;
		return players[playernum].score;
	}
	else if(straight(playernum)) {
		players[playernum-1].score = 15;
		return players[playernum].score;
	}
	else if(threekind(playernum)) {
		players[playernum-1].score = 10;
		return players[playernum].score;
	}
   
   return players[playernum].score;
}

/*********************************************************************
** Function: poker::printscores
** Description: prints out each player's scores
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
********************************************************************/ 

void poker::printscores() {
	
	cout << "=======Hand Scores=======" << endl;
	for(int i = 0; i < numplayers; i++) {
		cout << "Player " << (i+1) << ": " << players[i].score << endl;
	}
	
}

/*********************************************************************
** Function: poker::threekind
** Description: checks if the player has a three of a kind
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: the player has cards
** Post-Conditions: a 1 is returned if they have 3 of a kind, else 0
********************************************************************/ 

bool poker::threekind(int p) {
	
	for(int i = 0; i < 13; i++) {
		int kind = 0;
		for(int j = 0; j < 4; j++) {
			#ifdef BUGSm
			cout << "In threekind checking " << j << ", " << i << endl;
			#endif
			if(deck[j][i].held == p) {
				kind += 1;
				#ifdef BUGSl
				cout << "threekind: " << kind << endl;
				#endif
			}
		}
		if(kind == 3) {
			#ifdef BUGSl
			cout << "returning 1 for three of a kind" << endl;
			#endif
			return 1;
		}
	}
	
	#ifdef BUGSl
	cout << "returning 0 for three of a kind." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: poker::straight
** Description: checks if the player has a straight
** Parameters: int p, # of player whose turn it is
** Pre-Conditions: player has 5 cards
** Post-Conditions: 1 is returned if straight, else 0
********************************************************************/ 

bool poker::straight(int p) {
	
	for(int i = 0; i < 8; i++) {
		int consec = 0;
		for(int j = 0; j < 5; j++) {
			#ifdef BUGSm
			cout << "In straight checking " << "0" << ", " << i+j << endl;
			#endif
			if((deck[0][i+j].held == p) || (deck[1][i+j].held == p) || (deck[2][i+j].held == p) || (deck[3][i+j].held == p)) {
				consec += 1;
				#ifdef BUGSl
				cout << "consec straight: " << consec << endl;
				#endif
			}
			else {
				consec = 0;
				break;
			}
		}
		if(consec == 5) {
			#ifdef BUGSl
			cout << "returning 1 for straight." << endl;
			#endif
			return 1;
		}
	}
	
	#ifdef BUGSl
	cout << "returning 0 for straight." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: poker::flush
** Description: checks if the player has a flush
** Parameters: p, the player number
** Pre-Conditions: p contains a valid number
** Post-Conditions: 1 is returned if flush, else 0
********************************************************************/ 

bool poker::flush(int p) {
	
	for(int i = 0; i < 4; i++) {
		int flushed = 0;
		for(int j = 0; j < 13; j++) {
			#ifdef BUGSm
			cout << "in flush checking " << i << ", " << j << endl;
			#endif
			if(deck[i][j].held == p) {
				flushed += 1;
				#ifdef BUGSl
				cout << "flushed: " << flushed << endl;
				#endif
			}
		}
		if(flushed == 5) {
			#ifdef BUGSl
			cout << "returning 1 for flush " << endl;
			#endif
			return 1;
		}
	}
	
	#ifdef BUGSl
	cout << "returning 0 for flush." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: poker::fullhouse
** Description: checks if the player has a fullhouse
** Parameters: p, the player number
** Pre-Conditions: p contains a valid number
** Post-Conditions: 1 is returned if flush, else 0
********************************************************************/ 

bool poker::fullhouse(int p) {
	
	for(int j = 0; j < 13; j++) {
		int three = 0;
		for(int i = 0; i < 4; i++) {
			#ifdef BUGSm
			cout << "In fullhouse checking " << i << ", " << j << endl;
			#endif
			if(deck[i][j].held == p) {
				three += 1;
				#ifdef BUGSl
				cout << "three: " << three << endl;
				#endif
			}
		}
		if(three == 3) {
			for(int m = 0; m < 13; m++) {
				int two = 0;
				for(int n = 0; n < 4; n++) {
					#ifdef BUGSm
					cout << "In threekind checking " << n << ", " << m << endl;
					#endif
					if(deck[n][m].held == p) {
						two += 1;
						#ifdef BUGSl
						cout << "two: " << two << endl;
						#endif
					}
				}
				if(two == 2) {
					#ifdef BUGSl
					cout << "returning 1 for fullhouse!" << endl;
					#endif
					return 1;
				}
			}
		}
	}
	
	#ifdef BUGSl
	cout << "returning 0 for fullhouse." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: poker::fourkind
** Description: checks if the player has four of a kind
** Parameters: p, the player number
** Pre-Conditions: p contains a valid number
** Post-Conditions: 1 is returned if true, else 0
********************************************************************/ 

bool poker::fourkind(int p) {
	int score = 0;
	
	for(int i = 0; i < 13; i++) {
		int kind = 0;
		for(int j = 0; j < 4; j++) {
			#ifdef BUGSm
			cout << "in fourkind checking " << j << ", " << i << endl;
			#endif
			if(deck[j][i].held == p) {
				#ifdef BUGSl
				cout << "fourkind: " << kind << endl;
				#endif
				kind += 1;
			}
		}
		if(kind == 4) {
			#ifdef BUGSl
			cout << "returning 1 from four of a kind." << endl;
			#endif
			return 1;
		}
	}
	
	#ifdef BUGSl
	cout << "returning 0 from four of a kind." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: poker::straightflush
** Description: checks if the player has a straight flush
** Parameters: p, the player number
** Pre-Conditions: p contains a valid number
** Post-Conditions: 1 is returned if straightflush, else 0
********************************************************************/ 

bool poker::straightflush(int p) {
	
	#ifdef BUGSl
	cout << "in straightflush" << endl;
	#endif
	
	if(straight(p) && flush(p)) {
		#ifdef BUGSl
		cout << "returning 1 for straightflush." << endl;
		#endif
		return 1;
	}
	
	#ifdef BUGSl
	cout << "returning 0 for straightflush." << endl;
	#endif
	return 0;
}

/*********************************************************************
** Function: game::printhand
** Description: prints the cards held by the player passed in
** Parameters: int playernum, the number of the player to print
** Pre-Conditions: playernum contains a number
** Post-Conditions: none
********************************************************************/ 

void poker::printhand(int playernum) {

   for(int j = 0; j < 13; j++) {
      for(int i = 0; i < 4; i++) {
	 if(deck[i][j].held == playernum) {
	    cout << deck[i][j].rank << " of ";
	    //this switch statement turns the number suits to strings
	    switch(deck[i][j].suit) {
			case 1: cout << "hearts" << endl; break;
			case 2: cout << "clubs" << endl; break;
			case 3: cout << "spades" << endl; break;
			case 4: cout << "diamonds" << endl; break;
		}
	 }
      }
   }

}

/*********************************************************************
** Function: game::printcard
** Description: prints the card in the spot passed in
** Parameters: int playernum, the number of the player, i = suite,
** 	and j = rank
** Pre-Conditions: playernum contains a number, 0 <= suite <4,
** 	0 <= rank < 13
** Post-Conditions: none
********************************************************************/ 

void poker::printcard(int playernum, int i, int j) {
	
	if(deck[i][j].held == playernum) {
	    cout << deck[i][j].rank << " of ";
	    //this switch statement turns the number suits to strings
	    switch(deck[i][j].suit) {
			case 1: cout << "hearts" << endl; break;
			case 2: cout << "clubs" << endl; break;
			case 3: cout << "spades" << endl; break;
			case 4: cout << "diamonds" << endl; break;
		}
	 }
}

/*********************************************************************
** Function: poker::won
** Description: checks who won the game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: 1 is returned if someone won
********************************************************************/ 

bool poker::won() {
	int winner = 0;
	
	for(int i = 1; i < numplayers; i++) {
		if(players[i].score > players[winner].score) {
			winner = i;
		}
	}
	
	printscores();
	
	if(players[winner].score != 0)
		cout << "Player " << winner+1 << " has won!" << endl;
	else
		cout << "Draw!" << endl;
	
	return 1;
}

/*********************************************************************
** Function: poker::checkthreekind
** Description: sets it up so the player has a three of a kind
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has 3 of a kind
********************************************************************/ 

void poker::checkthreekind(int p) {
	
	for(int j = 0; j < 3; j++) {
		deck[j][1].held = p;
	}
	
	deck[0][11].held = p;
	deck[0][12].held = p;
	
}

/*********************************************************************
** Function: poker::checkfourkind
** Description: sets it up so the player has a four of a kind
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has 4 of a kind
********************************************************************/

void poker::checkfourkind(int p) {
	
	for(int i = 0; i < 4; i++) {
		deck[i][0].held = p;
	}
	
	deck[1][12].held = p;
	
}

/*********************************************************************
** Function: poker::checkstraight
** Description: sets it up so the player has a straight
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has a sraight
********************************************************************/

void poker::checkstraight(int p) {
	
		for(int j = 2; j < 6; j++) {
			deck[0][j].held = p;
		}
	
	deck[3][1].held = p;
	
}

/*********************************************************************
** Function: poker::checkflush
** Description: sets it up so the player has a flush
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has a flush
********************************************************************/

void poker::checkflush(int p) {
	
	for(int i = 2; i < 8; i++) {
		deck[3][i].held = p;
	}
	
	deck[3][5].held = 0;
	
}

/*********************************************************************
** Function: poker::checkfullhouse
** Description: sets it up so the player has a fullhouse
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has a fullhouse
********************************************************************/

void poker::checkfullhouse(int p) {
	
	deck[1][2].held = p;
	deck[2][2].held = p;
	deck[1][5].held = p;
	deck[2][5].held = p;
	deck[3][5].held = p;
	
}

/*********************************************************************
** Function: poker::straightflush
** Description: sets it up so the player has a straight flush
** Parameters: int p, the number of player whose turn it is
** Pre-Conditions: none
** Post-Conditions: player has a straight flush
********************************************************************/

void poker::checkstraightflush(int p) {
	
	for(int i = 6; i < 11; i++) {
		deck[2][i].held = p;
	}
	
}

/*********************************************************************
** Function: poker::ideck
** Description: initializes the deck to not be held by anyone
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: deck isn't held by anyone
********************************************************************/

void poker::ideck() {
	
	for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 13; j++) {
			deck[i][j].held = 0;
		}
	}
	
}
