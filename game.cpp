
// File: game.cpp
// Game class implementation

#include "game.h"

// Member functions
// Constructors
game::game()
{
    //maximum rounds
    Max_Rounds = 10;

    //current round to 1
    Current_Round = 1;

    //random time seed
    srand (time(NULL));

    //load alphabet & set guesses to 0
    for (int i = 0; i < 26; i ++)
    {
        Alpha[i] = i+65;
        Guessed_Alpha[i] = false;
    }

    //set box spin values
    Num_Box_Values = 7;
    Spin_Value = -1;
    Box_Values[0] = "Bankrupt";
    Box_Values[1] = "200";
    Box_Values[2] = "400";
    Box_Values[3] = "600";
    Box_Values[4] = "800";
    Box_Values[5] = "1000";
    Box_Values[6] = "Lose A Turn";
    Box_Num_Values[0] = 0;
    Box_Num_Values[1] = 200;
    Box_Num_Values[2] = 400;
    Box_Num_Values[3] = 600;
    Box_Num_Values[4] = 800;
    Box_Num_Values[5] = 1000;
    Box_Num_Values[6] = -1;

    //vowel cost
    Vowel_Cost = 200;

    //used words
    Num_Used_Words = 0;

}

void game::reset_guessed()
{
    for (int i = 0; i < 26; i++)
        Guessed_Alpha[i] = false;
}

void game::set_current_word(int Num_Words)
{
    //pick random word from
    this->Current_Word = (rand() % Num_Words +1);
}

int game::get_current_word()
{
    return this->Current_Word;
}

void game::set_num_players(int Num_Players)
{
    this->Num_Players = Num_Players;
}

int game::get_num_players()
{
    return this->Num_Players;
}

void game::set_player_turn(int Player_Turn)
{
    this->Player_Turn = Player_Turn;
}

int game::get_player_turn()
{
    return this->Player_Turn;
}

void game::set_current_round(int Current_Round)
{
    this->Current_Round = Current_Round;
}

int game::get_current_round()
{
    return this->Current_Round;
}

void game::set_max_rounds(int Max_Rounds)
{
    this->Max_Rounds = Max_Rounds;
}

int game::get_max_rounds()
{
    return this->Max_Rounds;
}

void game::set_num_words(int Num_Words)
{
    this->Num_Words = Num_Words;
}

int game::get_num_words()
{
    return this->Num_Words;
}

char game::get_alphabet(int Index)
{
    return Alpha[Index];
}

bool game::get_alphabet(char Check, bool CONS)
{
    const char A = 'A';
    const char E = 'E';
    const char I = 'I';
    const char O = 'O';
    const char U = 'U';

    bool Vowel = false;
    bool Cons = false;

    if (65 <= Check && Check <= 91)
        switch (Check) {
            case A:
                Vowel = true;
                break;
            case E:
                Vowel = true;
                break;
            case I:
                Vowel = true;
                break;
            case O:
                Vowel = true;
                break;
            case U:
                Vowel = true;
                break;
            default:
                Vowel = false;
                Cons = true;

        }//end switch

    if (CONS)
        return Cons;
    else
        return Vowel;
}

void game::set_guessed_alpha(int Index, bool Set)
{
    Guessed_Alpha[Index] = Set;
}

bool game::get_guessed_alpha(int Index)
{
    return Guessed_Alpha[Index];
}

void game::set_guessed_pos(int Index, bool Set)
{
    Guessed_Pos[Index] = Set;
}

bool game::get_guessed_pos(int Index)
{
    return Guessed_Pos[Index];
}

string game::get_box_value(int Index)
{
    return Box_Values[Index];
}

int game::get_num_box_value(int Index)
{
    return Box_Num_Values[Index];
}

int game::get_num_box_values()
{
    return Num_Box_Values;
}

void game::spin()
{
    int Spin;

    //biased spin value
    Spin = rand() % 125;

    if (0 < Spin && Spin < 5)
    {
        Spin_Value = 0;
    }
    else if (4 < Spin && Spin < 10)
    {
        Spin_Value = 6;
    }
    else
    {
        Spin_Value = (Spin - 10) % 5 + 1;
    }
}

void game::set_spin_value(int Spin_Value)
{
    this->Spin_Value = Spin_Value;
}

int game::get_spin_value()
{
    return Spin_Value;
}

int game::get_vowel_cost()
{
    return Vowel_Cost;
}

int game::get_num_used_words()
{
    return Num_Used_Words;
}

void game::set_num_used_words(int Num_Used_Words)
{
    this->Num_Used_Words = Num_Used_Words;
}
