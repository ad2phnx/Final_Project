
// File: word.cpp
// Word class implementation

#include "word.h"

// Member functions
// Constructors
word::word()
{

}

void word::set_name(string name)
{
    this->name = name;
}

string word::get_name()
{
    return this->name;
}
