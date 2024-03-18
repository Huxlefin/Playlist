/*
Hubert Pilichowski's playlist.cpp file
Creates a playlist class that has an array of Songs
*/

#include "playlist.h"
#include <cstring>
using namespace std;

// default constructor, builds an empty song array
Playlist::Playlist()
{
    maxSize = 5;
    currentSize = 0;
    // dynamicall allocate the song array
    songList = new Song[maxSize];
}

// destructor that deallocates the array
Playlist::~Playlist()
{
    delete[] songList;
}

// fucntion that inserts a song into the playlist
void Playlist::Insert(const Song& s)
{
    if (currentSize == maxSize)
        Grow();
    
    songList[currentSize] = s;
    currentSize += 1;
}

// function that looks up a song in the playlist by name and returns it
Song Playlist::LookupByName(const char song[35]) const
{
    // look through whole playlist for song title
    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(song, (songList[i]).GetTitle()) == 0)
        // return the song if the song in playlist
            return songList[i];
    }
    // else return empty song if song not in playlist
    Song s;
    return s;
}

// function that looks up songs based on the artist and returns a Playlist with those songs
Playlist Playlist::LookupByArtist(const char artist[20]) const
{
    // new playlist
    Playlist p;
    // search by artist
    for (int i = 0; i <= currentSize; i++)
    {
        if (strcmp(artist, songList[i].GetArtist()) == 0)
            p.Insert(songList[i]);
    }
    return p;
}

// function that looks up songs based on the category and returns a Playlist with those songs
Playlist Playlist::LookupByCategory(Style s) const
{
    // nnew playlist
    Playlist p;
    // search by category
    for (int i = 0; i < currentSize; i++)
    {
        if (s == (songList[i]).GetCategory())
            p.Insert(songList[i]);
    }
    return p;
}

// functions that returns the storage size
double Playlist::StorageSize() const
{
    double storage = 0;
    for (int i = 0; i < showSize(); i++)
        storage += songList[i].GetSize();

    return storage;
}

// function that deletes a song from the playlist
void Playlist::Delete(const char song[35])
{
    Song s = LookupByName(song);
    int index = 0;

    // find index to start at
    for (int i = 0; i < currentSize; i++)
    {
        if (strcmp(s.GetTitle(), songList[i].GetTitle()) == 0)
            index = i;
    }

    // move songs down a slot beginning at the index
    for (int i = index; i < currentSize; i++)
    {
        if (currentSize > 0)
            songList[i] = songList[i + 1];
    }

    // shrink playlist if too big
    if (maxSize - currentSize == 5)
        Shrink();

    currentSize--;
}

// returns the size of the playlist
int Playlist::showSize() const
{
    return currentSize;
}

// grows the playlist
void Playlist::Grow()
{
    maxSize += 5;
    // create new dynamically allocated array
    Song * newList = new Song[maxSize];

    // copy old array into new array
    for (int i = 0; i < currentSize; i++)
        newList[i] = songList[i];
    
    // delete old array
    delete [] songList;
    // point old name to new array
    songList = newList;
    cout << "Array has expanded by five slots." << endl;
}

// shrinks the playlist
void Playlist::Shrink()
{
    maxSize -= 5;
    // create new dynamically allocated array
    Song * newList = new Song[maxSize];

    // copy old array into new array
    for (int i = 0; i < currentSize; i++)
        newList[i] = songList[i];

    // delete old array
    delete [] songList;
    // point old name to new array
    songList = newList;
    cout << "Array has shrunk by five slots." << endl;
}

// operator overload for the output operator
ostream& operator<<(ostream& os, const Playlist& p)
{
    int length = p.currentSize;
    for (int i = 0; i < length; i++)
    {
        os << p.songList[i] << endl;
    }

    return os;
}
