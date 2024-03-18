/*
Hubert Pilichowski's menu.cpp file
Takes the playlist and song classes and creates a menu 
for a user
*/


#include <iostream>
#include <cstring>
#include "playlist.h"
#include "song.h"

// function declarations
void showMenu();
bool Valid(char choice);
bool checkStyle(char s);
void Insert(Playlist& p);
void Find(Playlist& p);
void Delete(Playlist& p);
void Show(Playlist& p);
void Category(Playlist& p);
void Size(Playlist& p);

int main()
{
    Playlist p;

    showMenu();
    char choice;

    // continuous loop until keyboard monkey breaks it
    while(true)
    {
        cin >> choice;
        // error checking for menu options
        while (!Valid(choice))
        {
            cout << "Invalid Option. Try Again: " << endl;
            cin >> choice;
        }

        // options for menu based on keyboard monkey choice
        switch (choice)
        {
            case 'A': 
            case 'a':
                Insert(p);
                break;
            case 'F':
            case 'f':
                Find(p);
                break;
            case 'D':
            case 'd':
                Delete(p);
                break;
            case 'S':
            case 's':
                Show(p);
                break;
            case 'C':
            case 'c':
                Category(p);
                break;
            case 'Z':
            case 'z':
                Size(p);
                break;
            case 'M':
            case 'm':
                showMenu();
                break;
            case 'X':
            case 'x':
                cout << "Goodbye.";
                return 0;
        }
    }
    return 0;
}

// functions that displays the menu to the screen
void showMenu()
{
    cout << endl << "*** Playlist Menu ***" << endl;
    cout << "A:   Add a song to the playlist " << endl;
    cout << "F:   Find a song on the playlist " << endl;
    cout << "D:   Delete a song from the playlist" << endl;
    cout << "S:   Show the entire playlist" << endl;
    cout << "C:   Category summary" << endl;
    cout << "Z:   Show playlist size" << endl;
    cout << "M:   Show this Menu" << endl;
    cout << "X:   eXit the program" << endl << endl;
}

// functions that determines whether the user's choice is valid and returns the result
bool Valid(char choice)
{
    if (choice == 'A' || choice == 'a' || choice == 'F' || choice == 'f' ||
    choice == 'D' || choice == 'd' || choice == 'S' || choice == 's' || 
    choice == 'C' || choice == 'c' || choice == 'Z' || choice == 'z' ||
    choice == 'M' || choice == 'm' || choice == 'X' || choice == 'x')
    {
        return true;
    }
    else    
        return false;
}

// inserts a new song into the playlist
void Insert(Playlist& p)
{
    // information about the song
    Song song;
    Style style;
    char title[35];
    char artist[20];
    char s;
    int size;
    bool valid;

    // get user's choices
    cin.getline(title, 35);
    cout << "Enter the song name: ";
    cin.getline(title, 35);
    cout << "Enter the artist's name: ";
    cin.getline(artist, 20);
    cout << "Enter the style of music (P, R, A, C, H, and Y - for Pop, Rock, Alternative, Country, HipHop, and Parody)" << endl;
    cin >> s;
    
    // error check the style choice
    while (!checkStyle(s))
    {
    
        cout << "Invalid Input. Try again. " << endl;
        cin >> s;
    }

    // switch the user's choice to the actual style
    switch (s)
    {
        case 'P':
        case 'p':
            style = POP;
            break;
        case 'R':
        case 'r':
            style = ROCK;
            break;
        case 'A':
        case 'a':
            style = ALTERNATIVE;
            break;
        case 'C':
        case 'c':
            style = COUNTRY;
            break;
        case 'H':
        case 'h':
            style = HIPHOP;
            break;
        case 'Y':
        case 'y':
            style = PARODY;
            break;
    }
    
    cout << "Enter the size of the song (in Kilobytes): ";
    cin >> size;

    // put the song into playlist
    song.Set(title, artist, style, size);
    p.Insert(song);
}

void Find(Playlist& p)
{
    char song[35];
    cout << "Enter a song name or artist name: ";
    cin.getline(song, 35);
    cin.getline(song, 35);

    // lookup the song by name
    Song s = p.LookupByName(song);
    // if there is a song, it to the screen and leave the function
    if ((strcmp(s.GetTitle(), "Empty") != 0))
    {
        cout << s << endl;
        return;
    }

    // if the song is not found by name, try by artist
    Playlist artists = p.LookupByArtist(song);
    if (artists.showSize() != 0)
        cout << artists;
    else
    {
        cout << "There was no song name or artist that matched your search." << endl;
        showMenu();
    }
}

// function that deletes a song from the playlist
void Delete(Playlist& p)
{
    char song[35];
    cout << "Enter the song that you would like to delete: ";
    cin.getline(song, 35);
    cin.getline(song, 35);

    // lookup the song by name
    Song s = p.LookupByName(song);
    if (strcmp(s.GetTitle(), "Empty") == 0)
    {
        cout << "Song not found. " << endl;
        return;
    }

    p.Delete(song);
    cout << "Song Removed" << endl;
}

// function that displays the function to the screen
void Show(Playlist& p)
{
    cout << left;
    cout.width(35);
    cout << "* Song Name *";
    cout.width(20);
    cout << "* Artist Name *";
    cout.width(15);
    cout << "* Category *";
    cout.width(10);
    cout << "* Size (MB) *" << endl << endl;
    cout << p << endl;
    cout << "Number of songs in the playlist: " << p.showSize() << endl;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(2);
    cout << "Size of playlist (in megabytes): " << p.StorageSize()/1000 << endl << endl;
}

// function that sorts the playlist by the category and displays it to the screen
void Category(Playlist& p)
{
    char s;
    Style style;
    cout << "Enter the style of music (P, R, A, C, H, and Y - for Pop, Rock, Alternative, Country, HipHop, and Parody): ";
    cin >> s;

    // error checking for style
    while (!checkStyle(s))
    {
        cout << "Invalid Input. Try again." << endl;
        cin >> s;
    }

    switch (s)
    {
        case 'P':
        case 'p':
            style = POP;
            break;
        case 'R':
        case 'r':
            style = ROCK;
            break;
        case 'A':
        case 'a':
            style = ALTERNATIVE;
            break;
        case 'C':
        case 'c':
            style = COUNTRY;
            break;
        case 'H':
        case 'h':
            style = HIPHOP;
            break;
        case 'Y':
        case 'y':
            style = PARODY;
            break;
    }

    // new playlist for only categories
    Playlist category = p.LookupByCategory(style);
    cout << endl << category << endl;
    cout << "The number of songs in this category: " << category.showSize() << endl;
    cout << "The size of this category (in megabytes): " << category.StorageSize()/1000 << endl << endl;
}

// functions that displays the size of the playlist to the screen
void Size(Playlist& p)
{
    cout.unsetf(ios::fixed);
    cout.unsetf(ios::showpoint);
    cout << "Size of playlist (in kilobytes): " << p.StorageSize() << endl << endl;
    cout.precision(2);
}

// error checking functions for style
bool checkStyle(char s)
{
    if (s == 'P' || s == 'p' || s == 'R' || s == 'r' || 
    s == 'A' || s == 'a' || s == 'C' || s == 'c' || 
    s == 'H' || s == 'h' || s == 'Y' || s == 'y')
        return true;
    else 
        return false;
}
