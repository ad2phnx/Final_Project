// File: word.h
// Word class definition

#ifndef WORD_H
#define WORD_H

#include <iostream>

using namespace std;

class word
{
    public:
        // Member Functions
        // Constructors
        word();

        //get and set name
        void set_name(string);
        string get_name();

        //get and set size
        void set_size(int);
        int get_size();

        // phrase in characters
        char phrase[99];

    private:
        string Name;                // name of words category
        int Size;                   // size of phrase in chars

};//end word

#endif // WORD_H
