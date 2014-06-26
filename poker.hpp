/*********************************************************************
** Program Filename: poker.hpp
** Author: Helena Bales
** Date: 04/23/2014
** Description: poker class- child of game class
** Input: none
** Output: none
********************************************************************/

#include"./game.h"

class poker : public game {
	
	public:
	poker();
	bool play();
	void printscores();
	void printhand(int);
	void printcard(int, int, int);
	void ideck();
	bool won();
	void discard(int);
	
	private:
	void setup(int);
	int pscores(int);
	bool threekind(int);
	bool fourkind(int);
	bool straight(int);
	bool flush(int);
	bool fullhouse(int);
	bool straightflush(int);
	static const int starthand = 5;
	
	void checkthreekind(int);
	void checkfourkind(int);
	void checkstraight(int);
	void checkflush(int);
	void checkfullhouse(int);
	void checkstraightflush(int);

};
