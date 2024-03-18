/*
Hubert Pilichowski's song.cpp file
Creates a song class to then later use for the playlist class
*/

#include "song.h"
#include <cstring>
using namespace std;

// default constructor that creates an empty song object
Song::Song()
{
    strcpy(title, "Empty");
    strcpy(artist, "Empty");

    size = 0;
}

// sets a song object to a user inputted option
void Song::Set(const char* t, const char* a, Style st, int sz)
{
    for (int i = 0; i < 36; i++)
        title[i] = t[i];
    for (int i = 0; i < 21; i++)
        artist[i] = a[i];

    category = st;
    size = sz;
}

// function that returns the title of the song
const char* Song::GetTitle() const
{
    return title;
}

// function that returns the artist of a song
const char* Song::GetArtist() const
{
    return artist;
}

// function that return the size of the song
int Song::GetSize() const
{
    return size;
}

// functions that returns the category of a song
Style Song::GetCategory() const
{
    return category;
}

// operator overload for a song
ostream& operator<<(ostream& os, const Song& s)
{
    // stream manipulation
    os << left;
    os.width(35);
    os << s.title;
    os.width(20);
    os << s.artist;
    os.width(15);

    // options for categories
    switch(s.category)
    {
        case POP:
            os << "Pop";
            break;
        case ROCK:
            os << "Rock";
            break;
        case ALTERNATIVE:
            os << "Alt";
            break;
        case COUNTRY:
            os << "Ctry";
            break;
        case HIPHOP:
            os << "HH";
            break;
        case PARODY:
            os << "Par";
            break;
    }

    // more stream manipulation
    os.width(10);
    double size = s.size;
    double result = size/1000;
    os.setf(ios::fixed);
    os.setf(ios::showpoint);
    os.precision(2);
    os << result;

    return os;
}
