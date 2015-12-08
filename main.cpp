/**
 * Includes
 */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string>
#include <windows.h>
#include "game.h"

using namespace std;

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

/**
 * Function prototypes
 */
int display_menu();                         // returns menu choice
bool open_file(game&, string);              // open a file from user
void create_players(game&);                 // creates players for game
void display(game&);                        // displays basic screen
void display_winner(game&);                 // display winner and scores
void play(game&);                           // play game
void title();                               // displays title
void trim(string&);                         // trim strings of whitespace

/**
 * Main
 */
int main()
{
    //local constants
    const int NEW_GAME    = 1;              // start a new game
    const int LOAD_FILE   = 2;              // load a file full of words
    const int HOW_TO_PLAY = 3;              // show a how to play screen
    const int QUIT        = 0;              // quits the game
    const string DEFAULT_FILE = "words.txt"; // default words file

    //local variables
    int Choice;                             // holds menu choice
    bool Loaded_File = false;               // holds menu choice

    game main_game;                         // new game

    /******************* main program *******************/

    //title
    system("cls");
    title();

    //menu
    Choice = display_menu();

    //while user didn't quit
    while (Choice != QUIT)
    {
        //line spacer
        cout << "\n";

        //menu switches
        switch (Choice)
        {
            //start new game
            case NEW_GAME:
                if (Loaded_File)
                {
                    cout << setw(40 + 12/2) << "File Loaded.\n";
                }
                else
                {
                    if (!open_file(main_game, DEFAULT_FILE))
                        break;

                }//end if
                create_players(main_game);
                cout << "\n" << setw(40 + 9) << "Starting New Game.\n";
                play(main_game);
                break;

            //load a file
            case LOAD_FILE:
                if (!open_file(main_game, DEFAULT_FILE))
                    break;
                Loaded_File = true;
                break;

            //help screen
            case HOW_TO_PLAY:
                cout << "How To Play";
                break;

            //user didn't choose available option
            default:
                cout << setw(40 + 33 / 2) << "That's not an option! Try again." << "\n\n";
                break;

        }//end switch

        //title
        title();

        //get next choice from user
        Choice = display_menu();

    }//end while

    //exit
    return 0;

}//end main

void title()
{
    //local constants

    //local variables

    /*************************************/

    cout << "\n\n\n\n";
    cout << setw(40 + 20) << "----------------------------------------" << endl;
    cout << setw(40 + 20) << "|            Box of Fortune            |" << endl;
    cout << setw(40 + 20) << "----------------------------------------" << endl;
    cout << "\n\n";

}//end title

int display_menu()
{
    //local constants
    const int MENU_SIZE = 4;

    //local variables
    int Choice;
    string Menu [MENU_SIZE] = {"[1] New Game",
                               "[2] Load File",
                               "[3] How to Play",
                               "[0] Quit"};

    /**********************************************/

    //print menu
    for (int i = 0; i < MENU_SIZE; i++)
    {
        cout << setw(33 + Menu[i].length()) << Menu[i] << "\n";
    }

    //get choice
    cout << "\n\n";
    cout << setw(40) << "Enter choice #: ";
    cin >> Choice;

    //check if inputs not an integer
    if (!cin)
    {
        //clean cin input
        cin.clear();

        //ignore what was in input buffer
        cin.ignore(256, '\n');

        //set choice to wrong
        Choice = 0;

    }//end if

    //return choice
    return Choice;

}//end display_menu

bool open_file(game &Game, string Default)
{
    //local constants
    const string O_ERROR = "File not found! Open Error. Try again.";
                                                // Error when file not found
    //local variables
    bool Success;                               // returns file open success
    string File;                                // file to open
    string Line;                                // lines to parse
    string Cat;                                 // category from line
    string Words;                               // words from line
    int Count_Phr;                              // counts total phrases

    ifstream fs;                                // input filestream
    stringstream ss;                            // string stream (needed ?)

    /**********************************************/

    //input a file name
    system("cls");
    title();
    cout << setw(40 + 6) << "Loading File" << "\n\n";
    cout << setw(40) << "Enter file name [words.txt]: ";
    cin.ignore(100, '\n');
    getline(cin, File);

    //check if default file or user specified
    if (File.empty())
        File = Default;

    //open file
    fs.open(File.c_str());

    //if file didn't open properly
    if (fs.fail())
    {
        //error
        cout << "\n" << setw(40 + O_ERROR.length() / 2) << O_ERROR << "\n\n";

        //pause
        system("pause");

        //success
        Success = false;
    }
    else // file opened
    {
        //get first line
        getline(fs, Line);

        //initialize counters to 0
        Count_Phr = 0;

        //while not end of file
        while (!fs.eof())
        {
            //cout << "Cat: " << Cat << " Phrase: " << Words << "\n";
            getline(fs, Cat, '#');
            getline(fs, Words);

            //trim
            trim(Cat);
            trim(Words);

            //insert word
            Count_Phr++;

            for (int i = 0; i < Words.length(); i++)
            {
                Game.words[Count_Phr].phrase[i] = toupper(Words[i]);

            }//end for

            //set current words category
            Game.words[Count_Phr].set_name(Cat);

            //set current word length
            Game.words[Count_Phr].set_size(Words.length());

        }//end while

        //close file
        fs.close();

        if (Count_Phr < 10)
        {
            Success = false;

            cout << "\n" << setw(40 + 24/2) << "File open failed!";
            cout << "\n" << setw(40 + 24/2) << "Make sure you have at least 10 entries.";

        }
        else
        {
            //save number of words
            Game.set_num_words(Count_Phr);

            //file opened success
            cout << "\n" << setw(40 + 25/2) << "File opened successfully!" << "\n\n";

            //success
            Success = true;

        }//end if

        //pause
        system("pause");

        //cls
        system("cls");

    }//end if

    //return success
    return Success;

}//end open_file

void create_players(game &Game)
{
    //local constants
    const int NUM_PLYR_DEF = 3;             // default players

    //local variables
    int Num_Players = 3;                    // amount of players 
    bool PASSED = false;                    // if user input is ok
    string S;                               // temp input string
    string Player_Name;                     // a players name

    /**************************************************/

    while (!PASSED)
    {
        //assume passed
        PASSED = true;

        //ask for number of players
        system("cls");

        //title
        title();

        //creating players
        cout << setw(40 + 7) << "Creating Players" << "\n\n\n";

        //get # of players
        cout << setw(40) << "Enter number players (2 - 3) [3]: ";
        getline(cin, S);
        if (!S.empty())
        {
            stringstream (S) >> Num_Players;
            
            if (Num_Players > 3 || Num_Players < 2)
            {
                cout << "\n\n" << setw(40 + 20/2) << "Number of players must be either 2 or 3";

                PASSED = false;

                system("pause");

            }//end if

        }
        else
        {
            Num_Players = NUM_PLYR_DEF;

        }//end if

        cout << "\n";

    }//end while

    //get each players name
    for (int i = 0; i < Num_Players; i++)
    {
        //get player info
        cout << setw(32) << "Player " << (i+1) << " Name: ";
        cin >> Player_Name;

        //insert player
        Game.players[i].set_name(Player_Name);
        Game.players[i].set_pos(i+1);

    }//end for

    //set first player to go first
    Game.set_player_turn(0);

    //save number of players
    Game.set_num_players(Num_Players);

    //players created
    cout << "\n\n";
    cout << setw(30 + 2) << Num_Players << " Players Created." << endl;

    //pause
    system("pause");

    //cls
    system("cls");

}//end create_players

void play(game &Game)
{
    //local constants
    const char SPIN  = 's';                         //spin
    const char GUESS = 'g';                         //guess phrase
    const char BUY   = 'b';                         //buy vowel
    const bool CONS  = true;                        //pass to get consonants

    //local variables
    bool Choice_Pass;                               //choice was correct
    bool Round_Over;                                //if rounds over
    bool Guess_Pass;                                //checks if guess is good
    bool Guessed;                                   //if guess was right
    bool Phrase_Pass;                               //phrase guess pass/fail
    bool Phrase_Done;                               //phrase was finished
    bool Spin_Pass;                                 //if consonants left
    bool Buy_Pass;                                  //if vowels left
    bool New_Phrase;                                //if phrase wasn't played
    char Choice;                                    //choice of spin/guess/buy
    char Guess;                                     //guess letter
    string Phrase;                                  //phrase guess

    /**************************************************/

    //set used pointers to null
    for (int i = 0; i < 99; i++)
    {
        Game.used_words[i] = NULL;
    }

    //set total scores to none
    for (int i = 0; i < Game.get_num_players(); i++)
        Game.players[i].set_tot_score(0);

    while (Game.get_current_round() <= Game.get_max_rounds())
    {
        New_Phrase = false;

        while (!New_Phrase)
        {
            //set next random word
            Game.set_current_word(Game.get_num_words());

            if (Game.used_words[Game.get_current_word()] != &Game.words[Game.get_current_word()])
                New_Phrase = true;

        }//end while

        //reset guessed
        Game.reset_guessed();

        //round start
        Round_Over = false;

        //reset scores
        for (int i = 0; i < Game.get_num_players(); i ++)
            Game.players[i].set_score(0);

        while (!Round_Over)
        {
            //check if player lost turn
            if (Game.players[Game.get_player_turn()].get_turn_miss())
            {
                Game.players[Game.get_player_turn()].set_turn_miss(false);
                //next player
                if (Game.get_player_turn() < (Game.get_num_players()-1))
                    Game.set_player_turn(Game.get_player_turn() + 1);
                else
                    Game.set_player_turn(0);
            }
                
            //display screen
            display(Game);

            //current choice is bad
            Choice_Pass = false;
            //get player input
            cout << "\n\n (S)pin -- (G)uess -- (B)uy vowel : ";
            cin >> Choice;

            while (!Choice_Pass)
            {
                Choice_Pass = true;

                switch (Choice)
                {
                    case SPIN:
                        Spin_Pass = false;
                        for (int i = 0; i < 26; i++)
                        {
                            if (Game.get_alphabet('A'+i, CONS) && !Game.get_guessed_alpha(i))
                                    Spin_Pass = true;
                        }

                        if (Spin_Pass)
                        {
                            Game.spin();
                            display(Game);
                            if (Game.get_spin_value() == 0)
                            {
                                Game.players[Game.get_player_turn()].set_score(0);
                                cout << "\n";
                                cout << setw(45) << "Bankrupt!\n";
                            }
                            else if (Game.get_spin_value() == 6)
                            {
                                Game.players[Game.get_player_turn()].set_turn_miss(true);
                                cout << "\n";
                                cout << setw(51) << "Sorry You lose a turn!\n";
                            }
                            else {
                                Guess_Pass = false;
                                Guessed = false;
                                while (!Guess_Pass)
                                {
                                    cout << "\n\n Guess Consonant : ";
                                    cin >> Guess;
                                    Guess = toupper(Guess);
                                    Guess_Pass = Game.get_alphabet(Guess, CONS);
                                    if (!Guess_Pass)
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n That's not a consonant. Try again.";

                                    }//end if

                                    if (Game.get_guessed_alpha(Guess-65))
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n That letter was already guessed.";
                                        Guess_Pass = false;
                                    }

                                }//end while

                                Game.set_guessed_alpha(Guess-65, true);

                                for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                                {
                                    if (Guess == Game.words[Game.get_current_word()].phrase[i])
                                    {
                                        Game.players[Game.get_player_turn()].set_score(Game.players[Game.get_player_turn()].get_score() + (Game.get_num_box_value(Game.get_spin_value())));
                                        Guessed = true;

                                    }//end if

                                }//end for

                                if (Guessed)
                                {
                                    cout << setw(55) << "Congratulations. You go again!\n";
                                    Game.set_player_turn(Game.get_player_turn() - 1);
                                }
                                else
                                {
                                    cout << setw(61) << "That letter is not in the phrase. Sorry!\n";

                                }//end if

                            }//end if
                            system("pause");
                        }
                        else
                        {
                            cout << "\n";
                            cout << setw(60) << "No more consonants left. Guess or buy vowel.\n";
                            system("pause");
                            Game.set_player_turn(Game.get_player_turn() - 1);

                        }//end if
                        Game.set_spin_value(-1);
                        break;

                    case GUESS:
                        cout << "\n Guess phrase: ";
                        cin.ignore(1000, '\n');
                        getline(cin, Phrase);
                        Phrase_Pass = true;
                        for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                        {
                            if (toupper(Phrase[i]) != Game.words[Game.get_current_word()].phrase[i])
                                    Phrase_Pass = false;

                        }//end for
                        if (Phrase_Pass)
                        {
                            Game.players[Game.get_player_turn()].set_score(Game.players[Game.get_player_turn()].get_score() + 1000);
                            for (int i = 0; i < 26; i++)
                                Game.set_guessed_alpha(i,true);
                            Game.players[Game.get_player_turn()].set_tot_score(Game.players[Game.get_player_turn()].get_score() + Game.players[Game.get_player_turn()].get_tot_score());
                            Round_Over = true;
                            system("cls");
                            display(Game);
                            cout << setw(40 + 20) << "Congratulations. You win this round!\n";
                            Game.set_player_turn(Game.get_player_turn() - 1);
                        }
                        else
                        {
                            cout << setw(40 + 20) << "Sorry that is not the correct phrase.\n";

                        }//end if
                        system("pause");
                        break;

                    case BUY:
                        Buy_Pass = false;
                        for (int i = 0; i < 26; i++)
                        {
                            if (Game.get_alphabet('A'+i, !CONS) && !Game.get_guessed_alpha(i))
                                    Buy_Pass = true;
                        }

                        if (Buy_Pass)
                        {
                            if (Game.players[Game.get_player_turn()].get_score() < Game.get_vowel_cost())
                            {
                                cout << "\n";
                                cout << setw(43) << "Sorry vowels cost $" << Game.get_vowel_cost() << " a piece\n";
                                Game.set_player_turn(Game.get_player_turn() - 1);
                            }
                            else
                            {
                                Guess_Pass = false;
                                Guessed = false;
                                Game.players[Game.get_player_turn()].set_score(Game.players[Game.get_player_turn()].get_score() - 200);
                                while (!Guess_Pass)
                                {
                                    cout << "\n\n Buy Vowel: ";
                                    cin >> Guess;
                                    Guess = toupper(Guess);
                                    Guess_Pass = Game.get_alphabet(Guess, !CONS);
                                    if (!Guess_Pass)
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n That's not a vowel. Try again.";

                                    }//end if

                                    if (Game.get_guessed_alpha(Guess-65))
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n That letter was already guessed.";
                                        Guess_Pass = false;
                                    }

                                }//end while

                                Game.set_guessed_alpha(Guess-65, true);

                                for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                                {
                                    if (Guess == Game.words[Game.get_current_word()].phrase[i])
                                    {
                                        Guessed = true;

                                    }//end if

                                }//end for

                                if (Guessed)
                                {
                                    cout << setw(55) << "Congratulations. You go again!\n";
                                    Game.set_player_turn(Game.get_player_turn() - 1);
                                }
                                else
                                {
                                    cout << setw(61) << "That letter is not in the phrase. Sorry!\n";

                                }//end if

                            }//end if

                        }
                        else
                        {
                            cout << "\n";
                            cout << setw(60) << "No more vowels left. Guess or spin.\n";
                            system("pause");

                        }//end if

                        system("pause");
                        break;

                    default:
                        cout << "\nThat is not an option\n";
                        system("pause");
                        Choice_Pass = false;
                        system("cls");
                        display(Game);
                        cout << "\n\n (S)pin -- (G)uess -- (B)uy vowel : ";
                        cin >> Choice;
                        break;
                }//end switch

            }//end while

            Phrase_Done = true;

            //check if phrase complete
            for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                if (!Game.get_guessed_alpha(Game.words[Game.get_current_word()].phrase[i]-65) &&
                   !(Game.words[Game.get_current_word()].phrase[i] == ' ' ||
                    Game.words[Game.get_current_word()].phrase[i] == '\''))
                    Phrase_Done = false;

            if (Phrase_Done && !Round_Over)
            {
                cout << "\nPhrase is complete you win this round!\n";
                system("pause");
                Round_Over = true;
                Game.players[Game.get_player_turn()].set_tot_score(Game.players[Game.get_player_turn()].get_score() + Game.players[Game.get_player_turn()].get_tot_score());
            }

            //next player
            if (Game.get_player_turn() < (Game.get_num_players()-1))
                Game.set_player_turn(Game.get_player_turn() + 1);
            else
                Game.set_player_turn(0);

        }//end while

        //set word done
        Game.used_words[Game.get_current_word()] = &Game.words[Game.get_current_word()];
        Game.set_num_used_words(Game.get_num_used_words() + 1);

        //increase round
        Game.set_current_round(Game.get_current_round() + 1);

    }//end while

    //show winner screen
    display_winner(Game);

    //reset rounds
    Game.set_current_round(1);

}//end play

void display(game &Game)
{
    //local constants
    const bool SHORT    = true;                    //used for short names

    //local variables

    /**************************************************/

    //cls
    system("cls");

    //horizontal line
    for (int i = 0; i < 80; i++)
        cout << "-";

    //cout << "\n";

    //game title
    cout << " Round # " << Game.get_current_round();

    //display players
    cout << setw(29) << " P1: ";
    if (Game.get_player_turn() == 0)
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
    cout << Game.players[0].get_name(SHORT);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    cout << setw(15 - Game.players[0].get_name(SHORT).length()) << " P2: ";
    if (Game.get_player_turn() == 1)
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
    cout << Game.players[1].get_name(SHORT);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    if (Game.get_num_players() == 3)
    {
        cout << setw(15 - Game.players[1].get_name(SHORT).length()) << " P3: ";
        if (Game.get_player_turn() == 2)
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
        cout << Game.players[2].get_name(SHORT);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    }
    cout << "\n";

    //display current word category
    cout << " Category [" << Game.words[Game.get_current_word()].get_name() << "]";

    //display scores
    cout << setw(25 - Game.words[Game.get_current_word()].get_name().length()) << "$" << Game.players[0].get_score();
    cout << setw(15 - patch::to_string(Game.players[0].get_score()).length()) << "$"<< Game.players[1].get_score();
    if (Game.get_num_players() == 3)
    {
        cout << setw(15 - patch::to_string(Game.players[1].get_score()).length()) << "$" << Game.players[2].get_score();
    }
    cout << "\n";

    //horizontal line
    for (int i = 0; i < 80; i++)
        cout << "-";

    cout << "\n ";

    //show phrase (with underscores)
    for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
    {
        if (Game.words[Game.get_current_word()].phrase[i] == ' ' ||
            Game.words[Game.get_current_word()].phrase[i] == '\'')
            cout << Game.words[Game.get_current_word()].phrase[i];
        else
            if (Game.get_guessed_alpha(Game.words[Game.get_current_word()].phrase[i]-65))
                cout << Game.words[Game.get_current_word()].phrase[i];
            else
                cout << "_";
        //cout << Game.words[Game.get_current_word()].phrase[i];
        cout << " ";
    }

    //display alphabet
    cout << "\n\n\n";
    cout << setw(40 + 4) << "Alphabet";
    cout << "\n\n";
    cout << "             ";
    for (int i = 0; i < 26; i++)
    {
        if (Game.get_guessed_alpha(i))
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x08);
        cout << " " << Game.get_alphabet(i);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    }

    //display box
    cout << "\n\n\n";
    cout << setw(40 + 7) << "Box of Fortune";
    cout << "\n\n        ";
    for (int i = 0; i < 62; i++)
        cout << "=";
    cout << "\n       | ";
    //cout << "\n\n\n          |";
    for (int i = 0; i < Game.get_num_box_values(); i++)
    {
        if (Game.get_spin_value() == i)
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0d);
        i != (Game.get_num_box_values() - 1) ? cout << Game.get_box_value(i) << "    " : cout << Game.get_box_value(i);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    }

    cout << "  |\n        ";
    for (int i = 0; i < 62; i++)
        cout << "=";

}//end display

void display_winner(game &Game)
{
    //local constants
    const bool SHORT = true;                        //get short name

    //local variables
    int Winner = 0;                                 //winner of game

    /**************************************************/

    //find winner(s)
    for (int i = 0; i < Game.get_num_players(); i++)
        if (Game.players[i].get_tot_score() > Game.players[Winner].get_tot_score())
            Winner = i;

    system("cls");

    cout << "\nStats:\n\n";

    //display scores
    for (int i = 0; i < Game.get_num_players(); i++)
    {
        cout << " P" << i+1 << ": ";
        if (i == Winner)
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
        cout << Game.players[i].get_name(!SHORT);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
        cout << "  $" << Game.players[i].get_tot_score() << "\n";

    }//end for

    //congrats
    cout << "\n\n\n";
    cout << setw(40) << "Congratulations! ";
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
    cout << Game.players[Winner].get_name(!SHORT);
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    cout << " has won the game with $" << Game.players[Winner].get_tot_score() << "\n\n\n";

    system("pause");

}//end display_winner

void trim(string& s)
{
    //local constants

    //local variables

    /**************************************************/

    //finds firt char that isn't whitespace
    size_t p = s.find_first_not_of(" \t");

    //erase whitespace to first char
    s.erase(0, p);

    //find last char of string
    p = s.find_last_not_of(" \t");

    //if there's no trailing whitespace return npos
    if (string::npos != p)
        s.erase(p + 1);

}//end trim
