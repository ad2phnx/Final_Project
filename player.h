// File: player.h
// Player class definition

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

using namespace std;

class player
{
   public:
       
       // Member Functions
       // Constructors
       player();
       player(string, int, int, bool);

       //set & get name
       void set_name(string);
       string get_name();

       //set & get pos
       void set_pos(int);
       int get_pos();

       //set & get score
       void set_score(int);
       int get_score();

       //set & get turn
       void set_turn(bool);
       bool get_turn();

   private:

       //player info
       string Name;
       int Pos;
       int Score;
       char Guess [99];
       bool Miss_Turn;

};//end game

#endif // PLAYER_H
