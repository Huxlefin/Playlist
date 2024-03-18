/*
Hubert Pilichowski's playlist.h file
Declarations for the playlist class
*/

#include "song.h"
using namespace std;

class Playlist
{
    friend ostream& operator<<(ostream& os, const Playlist& p);

public:
    // constructor and destructor
    Playlist();
    ~Playlist();

    // declarations for the member functions
    void Insert(const Song& s);
    Song LookupByName(const char song[35]) const;
    Playlist LookupByArtist(const char artist[20]) const;
    Playlist LookupByCategory(Style s) const;
    double StorageSize() const;
    void Delete(const char song[35]);
    int showSize() const;

private:
    // private member data
    int currentSize;
    int maxSize;
    Song* songList;

    // private member functions for grow and delete
    void Grow();
    void Shrink();
};
