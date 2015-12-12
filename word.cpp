// File: word.cpp
// Word class implementation

#include "word.h"

// Member functions
// Constructors
word::word()
{
}

// set name (category) of word
void word::set_name(string Name)
{
    this->Name = Name;
}


// get name (category) of word
string word::get_name()
{
    return Name;
}

// set size of word
void word::set_size(int Size)
{
    this->Size = Size;
}

// get size of word
int word::get_size()
{
    return Size;
}
