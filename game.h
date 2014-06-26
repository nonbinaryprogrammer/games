#ifndef GAME
#define GAME

#include<iostream>
#include<cstdlib>
#include<cstring>

#include"./card.h"
#include"./player.h"

/*********************************************************************
** Program Filename: driver.h
** Author: Helena Bales
** Date: 04/23/2014
** Description: starts the game class
** Input: none
** Output: none
********************************************************************/

using namespace std;

class game {
   public:
      game();
      game(int);
      //game(const game &);
      virtual ~game();
      //void operator =(const game &);

      virtual bool play() = 0;
      card draw(int);
      int getnump();
      void printd();
      virtual void printhand(int) = 0;
      virtual void setup(int) = 0;
      void spam();

   protected:
      card deck[4][13];
      int numplayers;
      player *players;

};

#endif
