// File: game.h
// Game class definition

#ifndef GAME_H
#define GAME_H

#include "word.h"
#include "player.h"
#include <iostream>
#include <vector>

using namespace std;

class game
{
    public:

        // Member Functions
        // Constructors
        game();

        //set & get player turn #
        void set_player_turn(int);
        int get_player_turn();

        //words in game
        word words[99];

        //players in game
        player players[3];

    private:

        //game info
        int Num_Players;
        int Player_Turn;

};//end game

#endif // GAME_H
