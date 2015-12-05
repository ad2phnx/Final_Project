/**
 * Includes
 */
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include "game.h"

using namespace std;

/**
 * Function prototypes
 */
int display_menu();                         // returns menu choice
void create_players(game);                  // creates players for game
void open_file(game, string);               // open a file from user
void title();                               // displays title

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
                    cout << "File Already Loaded";
                else
                    open_file(main_game, DEFAULT_FILE);
                create_players(main_game);
                cout << "New game";
                break;

            //load a file
            case LOAD_FILE:
                open_file(main_game, DEFAULT_FILE);
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

    cout << setw(52) << "----------------------------------------" << endl;
    cout << setw(52) << "|            Box of Fortune            |" << endl;
    cout << setw(52) << "----------------------------------------" << "\n\n";

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
        cout << setw(25 + Menu[i].length()) << Menu[i] << "\n";
    }

    //get choice
    cout << "Enter choice # : ";
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

void open_file(game Game, string Default)
{
    //local constants
    const string O_ERROR = "File not found! Open Error. Try again.";
                                                // Error when file not found
    //local variables
    string File;                                // file to open
    string Line;                                // lines to parse
    string Cat;                                 // category from line
    string Words;                               // words from line
    int Count_Phr;                              // counts total phrases

    ifstream fs;                                // input filestream
    stringstream ss;                            // string stream (needed ?)

    /**********************************************/

    //input a file name
    cout << "Enter file name [words.txt]: ";
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

            //insert word
            Count_Phr++;

            for (int i = 0; i < Words.length(); i++)
            {
                Game.words[Count_Phr].phrase[i] = Words[i];
                Game.words[Count_Phr].set_name(Cat);

            }//end for

        }//end while

        //close file
        fs.close();

        //file opened success
        cout << "\n" << setw(40 + 25/2) << "File opened successfully!" << "\n\n";

        //pause
        system("pause");

    }//end if

}//end open_file

void create_players(game Game)
{
    //local constants
    
    //local variables
    int Num_Players;                        // amount of players
    string Player_Name;                     // a players name
    
    /**************************************************/

    //ask for number of players
    system("clear");

    //get # of players
    cout << setw(40 + 20 / 2) << "Enter number players [2 - 3]; ";
    cin >> Num_Players;

    //get each players name
    for (int i = 0; i < Num_Players; i++)
    {
        //get player info
        cout << setw(40 + 20 / 2) << "Player Name: ";
        cin >> Player_Name;

        //insert player
        Game.players[i].set_name(Player_Name);
        Game.players[i].set_pos(i+1);

    }//end for

    //set first player to go first
    Game.set_player_turn(1);

}//end create_players
