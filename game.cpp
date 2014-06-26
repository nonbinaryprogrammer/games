/*********************************************************************
** Program Filename: game.cpp
** Author: Helena Bales
** Date: 04/23/2014
** Description: game class
** Input: none
** Output: none
********************************************************************/

#include"./game.h"

/*********************************************************************
** Function: game::game
** Description: the default constructor for the game class
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: the number of players is set to 2 and the game
** 		is set up for two players and the deck is initialized to 0
********************************************************************/ 

game::game() {

   numplayers = 2;

   players = new player[2];
   for(int i = 0; i < numplayers; i++) {
      players[i].num = (i+1);
      players[i].score = 0;
   }

   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 13; j++) {
	 deck[i][j].held = 0;
	 deck[i][j].rank = j+1;
	 deck[i][j].suit = i+1;
      }
   }

}

/*********************************************************************
** Function: game::game
** Description: the non-default constructor for the game class
** Parameters: number of players from the user
** Pre-Conditions: num_players is in range
** Post-Conditions: game is set up for the number of players defined
**		by the user, and the board is initialized
********************************************************************/ 

game::game(int num_players) {

   numplayers = num_players;

   players = new player[numplayers];
   for(int i = 0; i < numplayers; i++) {
      players[i].num = (i+1);
      players[i].score = 0;
   }

   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 13; j++) {
	 deck[i][j].held = 0;
	 deck[i][j].suit = i+1;
	 deck[i][j].rank = j+1;
      }
   }

}

/*********************************************************************
** Function: game::game
** Description: copy constructor for the game class
** Parameters: const game, passed by reference
** Pre-Conditions: the game that is passed already exists
** Post-Conditions: the two things of type game are equal
********************************************************************/ 

/*game::game(const game &g) {

   numplayers = g.numplayers;

   players = new player[numplayers];
   for(int i = 0; i < numplayers; i++) {
      players[i].num = g.players[i].num;
      players[i].score = g.players[i].score;
   }

   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 13; j++) {
	 deck[i][j].held = g.deck[i][j].held;
	 deck[i][j].suit = g.deck[i][j].suit;
	 deck[i][j].rank = g.deck[i][j].rank;
      }
   }

}*/

/*********************************************************************
** Function: game::~game
** Description: deconstructor for game
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: the player array on the heap is freed
********************************************************************/ 

game::~game() {

   if(players != NULL)
      delete [] players;

}

/*********************************************************************
** Function: game::operator =
** Description: operator overload for equals
** Parameters: const game, passed by reference
** Pre-Conditions: the game passed by reference exists
** Post-Conditions: the two games are equal
********************************************************************/ 

/*game::operator = (game &other) {


}*/

/*********************************************************************
** Function: game::draw
** Description: draws a random card from the draw pile and assigns it
** 		to the player passed into the function
** Parameters: playernum
** Pre-Conditions: playernum contains a number
** Post-Conditions: deck.held at a random location has been assigned
** 		playernum
********************************************************************/ 

card game::draw(int playernum) {
   card newcard;
   int x, y;

   do{
	   //selects a random number between 0 and 3 for the suit
	   //selects a random number between 0 and 12 for the rank
      x = rand()%4;
      y = rand()%13;
      //repeats this loop if that selected card is
      //being held by a player
   }while(deck[x][y].held != 0);

	//sets the cards "held" property to the player number
   deck[x][y].held = playernum;

   newcard.suit = x+1;
   newcard.rank = y+1;

   return newcard;
}

/*********************************************************************
** Function: game::printd
** Description: for debugging; prints the contents of the deck
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
********************************************************************/ 

void game::printd() {

   for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 13; j++) {
	 cout << deck[i][j].held << "  ";
      }
      cout << endl;
   }

}


/*********************************************************************
** Function: getnump
** Description: gets the number of players that the user wants to use
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: numplayers contains the number of players
********************************************************************/ 

int game::getnump() {
	
	cout << "How many people want to play? (enter 2-6 now): ";
   cin >> numplayers;

   if(numplayers <= 6 && numplayers >= 2)
      return numplayers;
   else
      numplayers = getnump();
      
      return numplayers;
}

/*********************************************************************
** Function: spam
** Description: spams the screen with endl's
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: the screen appears blank
********************************************************************/

void game::spam() {
	
	for(int i = 0; i < 100; i++)
		cout << endl;
	}
