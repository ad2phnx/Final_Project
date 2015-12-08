
// File: word.cpp
// Word class implementation

#include "word.h"

// Member functions
// Constructors
word::word()
{

}

void word::set_name(string Name)
{
    this->Name = Name;
}

string word::get_name()
{
    return Name;
}

void word::set_size(int Size)
{
    this->Size = Size;
}

int word::get_size()
{
    return Size;
}
