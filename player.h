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
       //player(string, int, int, bool);

       //set & get name
       void set_name(string);
       //string get_name();
       string get_name(bool);

       //set & get pos
       void set_pos(int);
       int get_pos();

       //set & get round score
       void set_score(int);
       int get_score();

       //set & get total score
       void set_tot_score(int);
       int get_tot_score();

       //set & get turn
       void set_turn_miss(bool);
       bool get_turn_miss();

   private:
       string Name;                         // players name
       int Pos;                             // players position
       int Score;                           // players round score
       int Tot_Score;                       // players total score
       char Guess [99];                     // players guess in char array
       bool Miss_Turn;                      // if player misses turn

};//end game

#endif // PLAYER_H
