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

// resets guessed chars
void game::reset_guessed()
{
    for (int i = 0; i < 26; i++)
        Guessed_Alpha[i] = false;
}

// set current word to next random word
void game::set_current_word(int Num_Words)
{
    //pick random word from
    this->Current_Word = (rand() % Num_Words +1);
}

// get current word
int game::get_current_word()
{
    return this->Current_Word;
}

// set num of players playing
void game::set_num_players(int Num_Players)
{
    this->Num_Players = Num_Players;
}

// get num of players playing
int game::get_num_players()
{
    return this->Num_Players;
}

// set players turn
void game::set_player_turn(int Player_Turn)
{
    this->Player_Turn = Player_Turn;
}

// get players turn
int game::get_player_turn()
{
    return this->Player_Turn;
}

// set current round number
void game::set_current_round(int Current_Round)
{
    this->Current_Round = Current_Round;
}

// get current round number
int game::get_current_round()
{
    return this->Current_Round;
}

// set number rounds to play
void game::set_max_rounds(int Max_Rounds)
{
    this->Max_Rounds = Max_Rounds;
}

// get number rounds to play
int game::get_max_rounds()
{
    return this->Max_Rounds;
}

// set number of words in file
void game::set_num_words(int Num_Words)
{
    this->Num_Words = Num_Words;
}

// get number of words in file
int game::get_num_words()
{
    return this->Num_Words;
}

// get alphabet character at index
char game::get_alphabet(int Index)
{
    return Alpha[Index];
}

// get if passed char is consonant, vowel or neither
bool game::get_alphabet(char Check, bool CONS)
{
    // vowel constants
    const char A = 'A';
    const char E = 'E';
    const char I = 'I';
    const char O = 'O';
    const char U = 'U';

    // so far char is neither vowel or consonant
    bool Vowel = false;
    bool Cons = false;

    // is char in alphabet
    if (65 <= Check && Check <= 91)

        // is char a vowel
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

    //checking for consonant
    if (CONS)
        return Cons;

    //checking for vowel
    else
        return Vowel;
}

// set if char is guessed or not
void game::set_guessed_alpha(int Index, bool Set)
{
    Guessed_Alpha[Index] = Set;
}

// get if char is guessed or not
bool game::get_guessed_alpha(int Index)
{
    return Guessed_Alpha[Index];
}

// get box value at index
string game::get_box_value(int Index)
{
    return Box_Values[Index];
}

// get int box value at index
int game::get_num_box_value(int Index)
{
    return Box_Num_Values[Index];
}

// get number of box spins there are
int game::get_num_box_values()
{
    return Num_Box_Values;
}

// spin the box
void game::spin()
{
    // spin position
    int Spin;

    // spin value (0 - 124)
    Spin = rand() % 125;

    // (1/25 chance for bankrupt (0))
    if (0 <= Spin && Spin < 5)
    {
        Spin_Value = 0;
    }
    // (1/25 chance for lose turn (6))
    else if (4 < Spin && Spin < 10)
    {
        Spin_Value = 6;
    }
    // (23/25 chance of getting 1 - 5)
    else
    {
        Spin_Value = (Spin - 10) % 5 + 1;
    }
}

// set spin value
void game::set_spin_value(int Spin_Value)
{
    this->Spin_Value = Spin_Value;
}

// get spin value
int game::get_spin_value()
{
    return Spin_Value;
}

// get cost to buy vowel
int game::get_vowel_cost()
{
    return Vowel_Cost;
}

// get number of used words
int game::get_num_used_words()
{
    return Num_Used_Words;
}

// set number of used words
void game::set_num_used_words(int Num_Used_Words)
{
    this->Num_Used_Words = Num_Used_Words;
}
