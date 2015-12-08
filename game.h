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

        //used words
        word *used_words[99];

        //players in game
        player players[3];

        //set next random word
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
        bool get_alphabet(char, bool);

        //set & get guessed chars
        void set_guessed_alpha(int, bool);
        bool get_guessed_alpha(int);

        //set & get guessed word chars
        void set_guessed_pos(int, bool);
        bool get_guessed_pos(int);

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
        int Num_Players;
        int Player_Turn;
        int Max_Rounds;
        int Current_Round;
        int Num_Words;
        int Current_Word;
        int Spin_Value;
        int Num_Box_Values;
        int Vowel_Cost;
        int Num_Used_Words;
        char Alpha[26];
        string Box_Values[7];
        int Box_Num_Values[7];
        bool Guessed_Pos[99];
        bool Guessed_Alpha[26];

};//end game

#endif // GAME_H
