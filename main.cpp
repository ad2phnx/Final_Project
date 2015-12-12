/*******************************************************************************
* Program Name          : Final Project - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : This program is meant to recreate the game Wheel
*       of Fortune. The user will be given a visual menu from where to make
*       a selection: 
*       New Game: The user will begin by selecting how many rounds they
*       would like to play and how many players are going to be playing 
*       in this game (Max number of players being three). If the player
*       has not loaded a file of their own; a preloaded file will be used.
*       Player one will then be the first player to be shown a menu of the
*       different actions that they can perform. If they would like to spin
*       and guess; this allowing the player to spin for a numeric value 
*       ranging from $200 to $1000 or if unlucky receiving a lose turn or a
*       bankrupt roll. If the player lands on lose turn they will lose the
*       current turn and also the next turn; if it landed on bankrupt the
*       players score shall fall to $0. After receiving a result from the
*       spin the player will be allowed to guess a letter from the word or
*       phrase being presented. If the letter is correct the player will be
*       allowed to go again; if the letter is incorrect the players turn
*       shall end and the guessed letter will be put on the screen as a 
*       letter that was guessed. If they would like to buy a vowel for a set
*       cost of $250; if the player does not have sufficient points they will
*       not be allowed to choose this option. The last option shall be to guess
*       the entire word or phrase. If they are incorrect it shall then be the
*       next players turn. If they are correct they get a $2000 bonus. A round
*       will consist of an entire word or phrase being solved, at the end of the
*       round the player with the highest score will then be allowed to go first
*       in the next round. Once all the rounds have been played a winner’screen
*       will be shown; this will consist of showing the overall winner and then
*       every other players score.
*       How to Play: A screen showing all the rules for the game will be
*       displayed. This will allow the user to understand the rules of the game
*       before they begin playing.
*       Quit: The user will be allowed to quit the program before playing a
*       game. Once either the games have been played, or the player has quit an
*       exit message will appear to the user.
*
* BEGIN Box of Fortune
*   Title
*   Display Menu
*   WHILE(User doesn't quit)
*       SWITCH(Menu choices)
*           Start a new game
*               IF(File loads correctly)
*                   Display correctly loaded message
*               ELSE(File has not opened properly)
*                   IF(File does not open correctly)
*                       Break
*                   END IF
*               END IF
*               Create players
*               Display starting game message
*               Play the game
*               Break
*           Help screen
*               Display a how to play screen
*               Break
*           Default (User didn't choose available option)
*               Send not an option message
*               Break
*       END SWITCH
*       Clear the screen
*       Title
*       Get next choice from user
*   END WHILE
*   Exit
* END Box of Fortune
*******************************************************************************/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string>
#include <windows.h>
#include "game.h"

using namespace std;

//patch to convert int to string
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//Prototypes//
int display_menu();                             // returns menu choice
bool open_file(game&, string);                  // open a file from user
void create_players(game&);                     // creates players for game
void set_number_rounds(game&);                  // set number of rounds to play
void display(game&);                            // displays basic screen
void display_winner(game&, bool);               // display winner and scores
void play(game&);                               // play game
void title();                                   // displays title
void trim(string&);                             // trim strings of whitespace
void how_to_play();                             // displays game rules

//Main//
int main()
{
    //local constants
    const int NEW_GAME        = 1;              // start a new game
    const int HOW_TO_PLAY     = 2;              // show a how to play screen
    const int QUIT            = 0;              // quits the game
    const string DEFAULT_FILE = "words.txt";    // default words file

    //local variables
    int Choice;                                 // holds menu choice
    bool Loaded_File = false;                   // holds menu choice
    game main_game;                             // new game

    /******************* main program *******************/

    //Title
    system("cls");
    title();

    //Menu
    Choice = display_menu();

    //WHILE(User doesn't quit)
    while (Choice != QUIT)
    {
        //Line Spacer
        cout << "\n";

        //SWITCH(Menu choices)
        switch (Choice)
        {
            //Start a new game
            case NEW_GAME:

                //reset file loaded
                Loaded_File = false;

                //file not loaded
                while (!Loaded_File)
                {
                    //load file and save if loaded successfully
                    Loaded_File = open_file(main_game, DEFAULT_FILE);

                }//end while

                //set number of rounds
                set_number_rounds(main_game);

                //Create players
                create_players(main_game);

                //Display starting game message
                cout << "\n" << setw(40 + 9) << "Starting New Game.\n";

                //Play the game
                play(main_game);

                //Break
                break;

            //Help screen
            case HOW_TO_PLAY:

                //Display game rules
                how_to_play();

                //Break
                break;

            //User didn't choose available option
            default:

                //Send not an option message
                cout << "\n";
                cout << setw(40 + 33 / 2) << "That's not an option! Try again." << "\n\n";

                //pause
                cout << "\n\n\n";
                system("pause");

                //Break
                break;

        }//END SWITCH

        //Clear the screen
        system("cls");

        //Title
        title();

        //Get next choice from user
        Choice = display_menu();

    }//END WHILE

    //Exit
    return 0;

}//END Box of Fortune

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Displays the title throughout the program.
*
* BEGIN Title
*   Display title
* END Title
*******************************************************************************/
void title()
{
    //local constants

    //local variables

    /*************************************/

    //Display title
    cout << "\n\n\n\n";
    cout << setw(40 + 20) << "----------------------------------------" << endl;
    cout << setw(40 + 20) << "|            Box of Fortune            |" << endl;
    cout << setw(40 + 20) << "----------------------------------------" << endl;
    cout << "\n\n";

}//END Title

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : Decemeber 11
* Course/Section        : CSC 263
* Program Description   : Displays the menu that allows the user to interact
*   with the program.
*
* BEGIN Display Menu
*   FOR(number of menu options)
*       Display the menu option to the user
*   END FOR
*   Get choice
*   IF(Input is not an integer)
*       Clear cin input
*       Ignore what was in input buffer
*       Set choice to wrong
*   END IF
*   Return choice
* END Display Menu
*******************************************************************************/
int display_menu()
{
    //local constants
    const int MENU_SIZE = 3;                        // num of menu options

    //local variables
    int Choice;                                     // menu choice number
    string Menu [MENU_SIZE] = {"[1] New Game",      // Menu displayed to user
                               "[2] How to Play",
                               "[0] Quit"};

    /**********************************************/

    //FOR(printing the menu)
    for (int i = 0; i < MENU_SIZE; i++)
    {
        //Display the menu to the user
        cout << setw(33 + Menu[i].length()) << Menu[i] << "\n";

    }//END FOR

    //Get choice
    cout << "\n\n";
    cout << setw(40) << "Enter choice #: ";
    cin >> Choice;

    //IF(Input is not an integer)
    if (!cin)
    {
        //Clean cin input
        cin.clear();

        //Ignore what was in input buffer
        cin.ignore(256, '\n');

        //Set choice to wrong
        Choice = -1;

    }//END IF

    //Return choice
    return Choice;

}//END Display Menu

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Loads either the user generated file into the
*   game, or gives the option for the user to use the premade default
*   file. It will also send error messages if the user uses a file that
*   does not have enough words to be used in the game.
*
*BEGIN Open File
*   Input a file name
*   IF(Checking for default or user generated)
*       Set file to default
*   END IF
*   Open file
*   IF(File did not open properly)
*       Display error message
*       Pause the screen
*       Success status
*   ELSE(File opened)
*       Get first line
*       Initialize counters to 0
*       WHILE(Not end of file)
*           Get data from the file
*           Trim
*           Insert word
*           FOR(Changing the words to all capital letters)
*               Make word all capital letters
*           END FOR
*           Set current words category
*           Set current word length
*       END WHILE
*       Close file
*       IF(There is not enough words in the user's file)
*           Not enough enteries
*           Display message stating error in enteries
*       ELSE(Save the information from user's file)
*           Save number of words
*           File opened success
*           Success
*       END IF
*       Pause the screen
*       Clear the screen
*   END IF
*   Return Success
* END Open File
*******************************************************************************/
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
    string S;                                   // temp input string
    int Count_Phr;                              // counts total phrases

    ifstream fs;                                // input filestream

    /**********************************************/

    //Input a file name
    system("cls");
    title();
    cout << setw(40 + 6) << "Loading File" << "\n\n";
    cout << setw(40) << "Enter file name [words.txt]: ";
    cin.ignore(100, '\n');
    getline(cin, File);

    //IF(Checking for default or user generated)
    if (File.empty())
    {
        //Set file to default
        File = Default;

    }//END IF

    //Open file
    fs.open(File.c_str());

    //IF(File did not open properly)
    if (fs.fail())
    {
        //Display error message
        cout << "\n\n" << setw(40 + O_ERROR.length() / 2) << O_ERROR << "\n\n";

        //Pause the screen
        cout << "\n\n\n\n\n\n";
        system("pause");

        //Success status
        Success = false;

    }
    else//file opened
    {
        //Get first line
        getline(fs, Line);

        //Initialize counters to 0
        Count_Phr = 0;

        //WHILE(Not end of file)
        while (!fs.eof())
        {
            //Get data from the file
            getline(fs, Cat, '#');
            getline(fs, Words);

            //Trim
            trim(Cat);
            trim(Words);

            //Insert word
            Count_Phr++;

            //FOR(Changing the words to all capital letters)
            for (int i = 0; i < Words.length(); i++)
            {
                //Make word all capital letters
                Game.words[Count_Phr].phrase[i] = toupper(Words[i]);

            }//END FOR

            //Set current words category
            Game.words[Count_Phr].set_name(Cat);

            //Set current word length
            Game.words[Count_Phr].set_size(Words.length());

        }//END WHILE

        //Close file
        fs.close();

        //IF(There is not enough words in the user's file)
        if (Count_Phr < 1)
        {
            //Not enough enteries
            Success = false;

            //Display message stating error in enteries
            cout << "\n" << setw(40 + 24/2) << "File open failed!";
            cout << "\n" << setw(40 + 24/2) << "Make sure you have at least one entry.";

        }
        else//ELSE(Save the information from user's file)
        {
            //Save number of words
            Game.set_num_words(Count_Phr);
            Game.set_max_rounds(Count_Phr);

            //File opened success
            cout << "\n" << setw(40 + 25/2) << "File opened successfully!" << "\n\n";

            //Success
            cout << "\n\n\n\n\n\n";
            Success = true;

        }//END IF

        //Pause the screen
        system("pause");

        //Clear the screen
        system("cls");

    }//END IF

    //Return Success
    return Success;

}//END Open File

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : We will be creating the players for the game. This
*   allows the user to enter different player names; it also allows a
*   maximum of three players per game.
*
*BEGIN Create Players
*   WHILE(A game is being played)
*       Assume passed
*       Ask for number of players
*       Title
*       Creating players
*       Get # of players
*       IF(Player amount is empty)
*           Obtain number of players
*           IF(Number of players is out of range)
*               Display out of range message
*               Set value to false
*               Pause the screen
*           END IF
*       ELSE
*           The default number of players is selected
*       END IF
*       Create space
*   END WHILE
*   FOR(getting each players name)
*       Get player info
*       Insert player information
*   END FOR
*   Set first player to go first
*   Save number of players
*   Players created
*   Pause the screen
*   Clear the screen
* END Create Players
*******************************************************************************/
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

    //WHILE(A game is being played)
    while (!PASSED)
    {
        //Assume passed
        PASSED = true;

        //Ask for number of players
        system("cls");

        //Title
        title();

        //Creating players
        cout << setw(40 + 8) << "Creating Players" << "\n\n\n";

        //Get # of players
        cout << setw(40) << "Enter number players (2 - 3) [3]: ";
        getline(cin, S);

        //IF(Player amount is empty)
        if (!S.empty())
        {
            //Obtain number of players
            stringstream (S) >> Num_Players;

            //IF(Number of players is out of range)
            if (Num_Players > 3 || Num_Players < 2)
            {
                //Display out of range message
                cout << "\n\n" << setw(40 + 20/2) << "Number of players must be either 2 or 3";

                //Set value to false
                PASSED = false;

                //Pause the screen
                system("pause");

            }//END IF

        }
        else//ELSE default num players
        {
            //The default number of players is selected
            Num_Players = NUM_PLYR_DEF;

        }//END IF

        //Create space
        cout << "\n";

    }//END WHILE

    //FOR(getting each players name)
    for (int i = 0; i < Num_Players; i++)
    {
        //Get player info
        cout << setw(32) << "Player " << (i+1) << " Name: ";
        cin >> Player_Name;

        //Insert player information
        Game.players[i].set_name(Player_Name);
        Game.players[i].set_pos(i+1);

    }//END FOR

    //Set first player to go first
    Game.set_player_turn(0);

    //Save number of players
    Game.set_num_players(Num_Players);

    //Players created
    cout << "\n\n";
    cout << setw(30 + 2) << Num_Players << " Players Created." << endl;

    //Pause the screen
    cout << "\n";
    system("pause");

    //Clear the screen
    system("cls");

}//END Create Players

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Ask user for number of rounds
*
*BEGIN Get Number Rounds
*   WHILE(A game is being played)
*       Assume passed
*       Ask for number of players
*       Title
*       Creating players
*       Get # of players
*       IF(Player amount is empty)
*           Obtain number of players
*           IF(Number of players is out of range)
*               Display out of range message
*               Set value to false
*               Pause the screen
*           END IF
*       ELSE
*           The default number of players is selected
*       END IF
*       Create space
*   END WHILE
*   FOR(getting each players name)
*       Get player info
*       Insert player information
*   END FOR
*   Set first player to go first
*   Save number of players
*   Players created
*   Pause the screen
*   Clear the screen
* END Get Number Rounds
*******************************************************************************/
void set_number_rounds(game &Game)
{
    //local constants

    //local variables
    int Num_Rounds_Def;                     // default rounds
    int Num_Rounds;                         // amount of rounds
    bool PASSED = false;                    // if user input is ok
    string S;                               // temp input string

    /**************************************************/

    //set default rounds
    if (Game.get_max_rounds() < 5)
        Num_Rounds_Def = 1;
    else if (Game.get_max_rounds() < 10)
        Num_Rounds_Def = 5;
    else
        Num_Rounds_Def = 10;

    //WHILE(A game is being played)
    while (!PASSED)
    {
        //Assume passed
        PASSED = true;

        //Ask for number of rounds
        system("cls");

        //Title
        title();

        //Creating players
        cout << setw(40 + 7) << "Rounds in Game" << "\n\n\n";

        //Get # of players
        cout << setw(40) << "Enter number of rounds to play (1 - "
             << Game.get_max_rounds() << ") ["
             << Num_Rounds_Def << "]: ";
        getline(cin, S);

        //IF(Rounds is empty)
        if (!S.empty())
        {
            //Obtain number of rounds
            stringstream (S) >> Num_Rounds;

            //IF(Number of players is out of range)
            if (Num_Rounds > Game.get_max_rounds() || Num_Rounds < 1)
            {
                //Display out of range message
                cout << "\n\n" << setw(40 + 39/2) << "Number of rounds must be between 1 and "
                     << Game.get_max_rounds() << ".\n";

                //Set value to false
                PASSED = false;

                //Pause the screen
                cout << "\n\n\n\n\n\n";
                system("pause");

            }//END IF

        }
        else//ELSE default num rounds
        {
            //The default number of rounds is selected
            Num_Rounds = Num_Rounds_Def;

        }//END IF

        //Create space
        cout << "\n";

    }//END WHILE

    //Save number of rounds
    Game.set_max_rounds(Num_Rounds);

    //Players created
    cout << "\n\n";
    cout << setw(30 + 3) << Num_Rounds << " Rounds to Play." << endl;

    //Pause the screen
    cout << "\n\n\n\n";
    system("pause");

    //Clear the screen
    system("cls");

}//END Create Players

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description:

* BEGIN Box of Fortune
* END Box of Fortune
**********************************************************************/
void play(game &Game)
{
    //local constants
    const char SPIN  = 's';                         //spin
    const char GUESS = 'g';                         //guess phrase
    const char BUY   = 'b';                         //buy vowel
    const bool CONS  = true;                        //pass to get consonants
    const bool ROUND = true;                        //pass display round stats

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

    }//END FOR

    //FOR(setting total scores to none)
    for (int i = 0; i < Game.get_num_players(); i++)
    {
        Game.players[i].set_tot_score(0);

    }//END FOR

    //WHILE(IT is a new round)
    while (Game.get_current_round() <= Game.get_max_rounds())
    {
        //There is no phrase
        New_Phrase = false;

        //WHILE(There is not a new phrase)
        while (!New_Phrase)
        {
            //set next random word
            Game.set_current_word(Game.get_num_words());

            //IF(New word is not an old used word)
            if (Game.used_words[Game.get_current_word()] !=
                    &Game.words[Game.get_current_word()])
            {
                //found a new phrase
                New_Phrase = true;

            }//END IF

        }//END WHILE

        //reset guessed
        Game.reset_guessed();

        //round start
        Round_Over = false;

        //FOR(resetting scores)
        for (int i = 0; i < Game.get_num_players(); i ++)
        {
            Game.players[i].set_score(0);

        }//END FOR

        //WHILE(The round is not over)
        while (!Round_Over)
        {
            //check if player lost turn
            if (Game.players[Game.get_player_turn()].get_turn_miss())
            {
                //
                Game.players[Game.get_player_turn()].set_turn_miss(false);

                //IF(next player)
                if (Game.get_player_turn() < (Game.get_num_players()-1))
                {
                    Game.set_player_turn(Game.get_player_turn() + 1);

                }
                else//ELSE set player 1's turn
                {
                    //Set players
                    Game.set_player_turn(0);

                }//END IF

            }//end if

            //display screen
            display(Game);

            //current choice is bad
            Choice_Pass = false;

            //get player input
            cout << "\n\n (S)pin -- (G)uess -- (B)uy vowel : ";
            cin >> Choice;

            //WHILE(Choice is not pass)
            while (!Choice_Pass)
            {
                Choice_Pass = true;

                    //SWITCH(Choice)
                    switch (Choice)
                    {
                        case SPIN:
                            Spin_Pass = false;

                            //FOR(run through alphabet)
                            for (int i = 0; i < 26; i++)
                            {
                                //IF(char is consonant and not guessed yet)
                                if (Game.get_alphabet('A'+i, CONS) &&
                                        !Game.get_guessed_alpha(i))
                                {
                                    //passes spin test
                                    Spin_Pass = true;

                                }//END IF

                            }//END FOR

                            //IF(Player wants to spin)
                            if (Spin_Pass)
                            {
                                //Spin
                                Game.spin();

                                //Display the game and spin selection
                                display(Game);

                                //IF(Player's choice lands on bankrupt)
                                if (Game.get_spin_value() == 0)
                                {
                                    //Player becomes bankrupt
                                    Game.players[Game.get_player_turn()].set_score(0);
                                    cout << "\n\n" << setw(45) << "Bankrupt!\n";
                                }
                                //ELSE IF(Player lands on lose a turn)
                                else if (Game.get_spin_value() == 6)
                                {
                                    //Player loses a turn
                                    Game.players[Game.get_player_turn()].set_turn_miss(true);
                                    cout << "\n\n" << setw(51) << "Sorry You lose a turn!\n";
                                }
                                else//ELSE
                                {
                                    Guess_Pass = false;
                                    Guessed = false;

                                    //WHILE(Player can guewss a letter)
                                    while (!Guess_Pass)
                                    {
                                        //Display instructions to player
                                        cout << "\n\n Guess Consonant : ";
                                        cin >> Guess;

                                        //Make guessed letter capital
                                        Guess = toupper(Guess);

                                        Guess_Pass = Game.get_alphabet(Guess, CONS);

                                        //IF(Player guesses something that is not a consonant)
                                        if (!Guess_Pass)
                                        {
                                            //Clear the screen
                                            system("cls");

                                            //Display message to player
                                            display(Game);
                                            cout << "\n\n That's not a consonant. Try again.";

                                        }//END IF

                                        //IF(Player guesses letter that was already guessed)
                                        if (Game.get_guessed_alpha(Guess-65))
                                        {
                                            //Clear the screen
                                            system("cls");

                                            //Display the game
                                            display(Game);
                                            cout << "\n\n That letter was already guessed.";
                                            Guess_Pass = false;

                                        }//END IF

                                    }//END WHILE

                                    Game.set_guessed_alpha(Guess-65, true);

                                    for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                                    {
                                        if (Guess == Game.words[Game.get_current_word()].phrase[i])
                                        {
                                            Game.players[Game.get_player_turn()].set_score(Game.players[Game.get_player_turn()].get_score() + (Game.get_num_box_value(Game.get_spin_value())));
                                        Guessed = true;

                                        }//END IF

                                    }//END FOR

                                    //IF(Player guessed correctly)
                                    if (Guessed)
                                    {
                                        //Show player winning message
                                        cout << "\n" << setw(55) << "Congratulations. You go again!\n";

                                        //Player gets to go again
                                        Game.set_player_turn(Game.get_player_turn() - 1);

                                    }
                                    else
                                    {
                                        //Send error message to player
                                        cout << "\n" << setw(61) << "That letter is not in the phrase. Sorry!\n";

                                    }//END IF

                                }//END IF

                            //Pause the screen
                            cout << "\n";
                            system("pause");

                        }
                        else
                        {
                            //
                            cout << "\n";
                            cout << setw(62) << "No more consonants left. Guess or buy vowel.\n";
                            cout << "\n\n\n";
                            system("pause");
                            Game.set_player_turn(Game.get_player_turn() - 1);

                        }//END IF

                        //
                        Game.set_spin_value(-1);
                        break;

                    case GUESS:
                        cout << "\n Guess phrase: ";
                        cin.ignore(1000, '\n');
                        getline(cin, Phrase);
                        Phrase_Pass = true;

                        //FOR(
                        for (int i = 0; i < Game.words[Game.get_current_word()].get_size(); i++)
                        {
                            if (toupper(Phrase[i]) != Game.words[Game.get_current_word()].phrase[i])
                                    Phrase_Pass = false;

                        }//END FOR

                        //IF(
                        if (Phrase_Pass)
                        {
                            Game.players[Game.get_player_turn()].set_score(Game.players[Game.get_player_turn()].get_score() + 1000);

                        //FOR(
                            for (int i = 0; i < 26; i++)
                            {
                                Game.set_guessed_alpha(i,true);
                            }//END FOR

                            Game.players[Game.get_player_turn()].set_tot_score(Game.players[Game.get_player_turn()].get_score() + Game.players[Game.get_player_turn()].get_tot_score());
                            Round_Over = true;

                            //Clear the screen
                            system("cls");

                            //Display the game
                            display(Game);
                            cout << "\n\n" << setw(40 + 36/2) << "Congratulations. You win this round!\n";
                            Game.set_player_turn(Game.get_player_turn() - 1);

                        }
                        else//ELSE
                        {
                            //Send incorrect answer message
                            cout << "\n" << setw(40 + 20) << "Sorry that is not the correct phrase.\n";

                        }//END IF

                        //Pause the screen
                        cout << "\n";
                        system("pause");
                        break;

                    //
                    case BUY:
                        Buy_Pass = false;

                        //FOR(
                        for (int i = 0; i < 26; i++)
                        {
                            //IF(
                            if (Game.get_alphabet('A'+i, !CONS) && !Game.get_guessed_alpha(i))
                                    Buy_Pass = true;

                        }//END FOR

                        //IF(
                        if (Buy_Pass)
                        {
                            //IF(
                            if (Game.players[Game.get_player_turn()].get_score() < Game.get_vowel_cost())
                            {
                                //
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
                                    cout << "\n Buy Vowel: ";
                                    cin >> Guess;
                                    Guess = toupper(Guess);
                                    Guess_Pass = Game.get_alphabet(Guess, !CONS);
                                    if (!Guess_Pass)
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n\n That's not a vowel. Try again.";

                                    }//end if

                                    else if (Game.get_guessed_alpha(Guess-65))
                                    {
                                        system("cls");
                                        display(Game);
                                        cout << "\n\n That vowel was already bought.";
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
                                    cout << "\n" << setw(61) << "That letter is not in the phrase. Sorry!\n";

                                }//end if

                            }//end if

                        }
                        else
                        {
                            cout << "\n";
                            cout << setw(60) << "No more vowels left. Guess or spin.\n";
                            system("pause");

                        }//end if

                        //pause
                        cout << "\n";
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
                system("cls");
                display(Game);
                cout << "\n\n" << setw(40 + 37/2) << "Phrase is complete you win this round!";
                cout << "\n\n\n\n\n";
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

        //display round stats
        if (Game.get_current_round() != Game.get_max_rounds())
            display_winner(Game, ROUND);

        //increase round
        Game.set_current_round(Game.get_current_round() + 1);

    }//end while

    //show winner screen
    display_winner(Game, !ROUND);

    //reset rounds
    Game.set_current_round(1);

}//end play

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   :

* BEGIN Display
* END Display
*******************************************************************************/
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
    cout << " Round  # " << Game.get_current_round() << " / " << Game.get_max_rounds();

    //display players
    cout << setw(23) << " P1: ";
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
            Game.words[Game.get_current_word()].phrase[i] == '-' ||
            Game.words[Game.get_current_word()].phrase[i] == '\'')
            cout << Game.words[Game.get_current_word()].phrase[i];
        else
            if (Game.get_guessed_alpha(Game.words[Game.get_current_word()].phrase[i]-65))
                cout << Game.words[Game.get_current_word()].phrase[i];
            else
                cout << "_";
        cout << " ";
    }

    //display alphabet
    cout << "\n\n";
    cout << setw(40 + 4) << "Alphabet";
    cout << "\n\n";
    cout << "             ";
    for (int i = 0; i < 26; i++)
    {
        if (Game.get_guessed_alpha(i))
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0c);
        cout << " " << Game.get_alphabet(i);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
    }

    //display box
    cout << "\n\n";
    cout << setw(40 + 7) << "Box of Fortune";
    cout << "\n        ";
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

    //
    cout << "  |\n        ";

    //FOR(
    for (int i = 0; i < 62; i++)
        cout << "=";

}//END Display

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Display the overall winner to the player that just
*   played the game.

* BEGIN Display Winner
*   FOR(finding the winner(s))
*       IF(Player has the highest score)
*           Set winner
*       END IF
*   END FOR
*   CLear the screen
*   Display stats
*   FOR(displaying scores)
*       Display player
*       IF(player is winner)
*           Highlight player
*       END IF
*       Display winner and score
*   END FOR
*   Display congratulations
*   Pause the screen
* END Display Winner
*******************************************************************************/
void display_winner(game &Game, bool Round)
{
    //local constants
    const bool SHORT = true;                        //get short name

    //local variables
    int Winner = 0;                                 //winner of game

    /**************************************************/

    //FOR(finding the winner(s))
    for (int i = 0; i < Game.get_num_players(); i++)
    {
        //IF(Player has the highest score)
        if (Game.players[i].get_tot_score() > Game.players[Winner].get_tot_score())
        {
                //Set winner
                Winner = i;

        }//END IF

    }//END FOR

    //CLear the screen
    system("cls");

    //Display stats
    cout << "\n\n\n\n" << setw(40 + 7) << "Overall Scores";
    cout << "\n" << setw(40 + 7) << "--------------";
    cout << "\n\n";

    //FOR(displaying scores)
    for (int i = 0; i < Game.get_num_players(); i++)
    {
        //Display player
        cout << setw(28) << "P" << i+1 << ": ";

        //IF(player is winner)
        if (i == Winner)
        {
            //Highlight player
            SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );

        }//END IF

        //Display players score
        cout << Game.players[i].get_name(!SHORT);
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
        cout << setw(20 - Game.players[i].get_name(!SHORT).length()) << "$" << Game.players[i].get_tot_score() << "\n";

    }//END FOR

    //Display congratulations
    if (!Round)
    {
        cout << "\n\n\n";
        cout << setw(40 + 8) << "Congratulations!";
        cout << "\n\n";
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x0a );
        cout << setw(40 + Game.players[Winner].get_name(!SHORT).length()/2) << Game.players[Winner].get_name(!SHORT);
        cout << "\n\n";
        SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), 0x07 );
        cout << setw(40 + 17/2) << "has won the game!";

        //Pause the screen
        cout << "\n\n\n";
        system("pause");

    }
    else
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
        system("pause");

    }//end if

}//END Display_Winner

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Remove whitespace found on words to get all
*   character information from the word being guessed on.
*
* BEGIN Trim
*   Finds firt char that isn't whitespace
*   Erase whitespace to first char
*   IF(There's no trailing whitespace return npos)
*       Erase whitespace
*   END IF
* END Trim
*******************************************************************************/
void trim(string& s)
{
    //local constants

    //local variables

    /**************************************************/

    //Finds firt char that isn't whitespace
    size_t p = s.find_first_not_of(" \t");

    //Erase whitespace to first char
    s.erase(0, p);

    //Find last char of string
    p = s.find_last_not_of(" \t");

    //IF(There's no trailing whitespace return npos)
    if (string::npos != p)
    {
        //Erase whitespace
        s.erase(p + 1);

    }//END IF

}//END Trim

/*******************************************************************************
* Program Name          : Final Program - Box of Fortune
* Author                : Anatoliy Dinis, Andy Garcia
* Due Date              : December 11, 2015
* Course/Section        : CSC 263
* Program Description   : Display the game info for the user.
*
* BEGIN How to Play
*   Create title
*   Display information to user
*   Pause the screen
* END How to Play
*******************************************************************************/
void how_to_play ()
{
    //local constants

    //local variables

    /**************************************************/

    system("cls");

    //TItle
    cout << "\n\n";
    cout << setw(45) << "How to Play" << endl;
    cout << setw(45) << "___________" << endl;
    cout << "\n";

    //Display information to the user
    cout << setw(65) << "Game: The goal here is to proprely guess the phrase" << endl;
    cout << setw(65) << "      before the other players. At the beginning of" << endl;
    cout << setw(65) << "      a round you will have a chance to spin for a " << endl;
    cout << setw(65) << "      monetary value or if unlucky a skip or       " << endl;
    cout << setw(65) << "      bankrupt value. After your spin if possible  " << endl;
    cout << setw(65) << "      you will then guess a consonant that has not " << endl;
    cout << setw(65) << "      been guessed already. If the letter guessed  " << endl;
    cout << setw(65) << "      is in the phrase it will be shown. A player  " << endl;
    cout << setw(65) << "      will be able to continue guessing until they " << endl;
    cout << setw(65) << "      are incorrect or they guess the whole word.  " << endl;
    cout << setw(65) << "      Once a player has a minimum of 250 points an " << endl;
    cout << setw(65) << "      option to purchase a vowel will appear. This " << endl;	
    cout << setw(65) << "      will unlock one vowel for the entire phrase. " << endl;	
    cout << setw(65) << "      At the end of the phrase the overall score   " << endl;	
    cout << setw(65) << "      for all the players will be shown. The player" << endl;	
    cout << setw(65) << "      with the highest score will then be allowed  " << endl;	
    cout << setw(65) << "      to go first in the next round.               " << endl;	
    cout << "\n\n";

    //Pause the screen
    system("pause");

}//END How to Play
