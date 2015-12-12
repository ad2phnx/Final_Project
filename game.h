// File: game.h
// Game class definition

#ifndef GAME_H
#define GAME_H

#include "word.h"
#include "player.h"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <time.h>

using namespace std;

class game
{
    public:
        // Member Functions
        // Constructors
        game();

        //words in game
        word words[99];

        //used words word pointer array
        word *used_words[99];

        //players in game
        player players[3];

        //set & get next random word
        void set_current_word(int);
        int get_current_word();

        //set & get max rounds
        void set_max_rounds(int);
        int get_max_rounds();

        //set & get current rounds
        void set_current_round(int);
        int get_current_round();

        //set & get # players
        void set_num_players(int);
        int get_num_players();

        //set & get player turn #
        void set_player_turn(int);
        int get_player_turn();

        //set & get number of words
        void set_num_words(int);
        int get_num_words();

        //get alphabet char
        char get_alphabet(int);

        //get if char is valid
        bool get_alphabet(char, bool);

        //set & get guessed chars
        void set_guessed_alpha(int, bool);
        bool get_guessed_alpha(int);

        //get box values
        string get_box_value(int);
        int get_num_box_value(int);

        //get box size
        int get_num_box_values();

        //spin box
        void spin();

        //get & set spin values
        void set_spin_value(int);
        int get_spin_value();

        //get vowel cost
        int get_vowel_cost();

        //reset alphabet
        void reset_guessed();

        //set & get num used words
        void set_num_used_words(int);
        int get_num_used_words();

    private:

        //game info
        int Num_Players;                            // num of players playing
        int Player_Turn;                            // whose turn it is
        int Max_Rounds;                             // num of rounds in game
        int Current_Round;                          // current round number
        int Num_Words;                              // number of words in file
        int Current_Word;                           // current word (phrase)
        int Spin_Value;                             // spin represents
        int Num_Box_Values;                         // number of different spins
        int Vowel_Cost;                             // cost to buy vowel
        int Num_Used_Words;                         // count # used words
        char Alpha[26];                             // alphabet in char array
        string Box_Values[7];                       // values in spinner
        int Box_Num_Values[7];                      // int values in spinner
        bool Guessed_Alpha[26];                     // if alpha char guessed

};//end game

#endif // GAME_H
