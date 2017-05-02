#ifndef SONGLIBRARY_H
#define SONGLIBRARY_H

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

#include "Song.h"

using namespace std;

class SongLibrary{
   public:
      SongLibrary() {}
      // Default constructor initialize the data member
      SongLibrary(int numberOfPlays_, int songID_): numberOfPlays(numberOfPlays_), songID(songID_) {};

      void loadSongToLibrary(Song* songPointer_, int songID_, int numberOfPlays_);

      int getNumberOfPlays() { return numberOfPlays; };
      int getSongID() { return songID; };

      // Obtain the Song's name, artist, album based on the song identifier
      void getGeneralSongInfo(Song*& songPointer_, int songID_);

      // Enum for displying songs
      enum SongDisplayType { NAME, ARTIST, ALBUM, PLAYS };

      void displaySongs(SongDisplayType Type);

      // Struct to generate unique IDs
      struct Object{
         Object(int uniqueID) {
            static int id = 1;
            uniqueID = id++;
         }
      };

      int numberOfSongs() {
         return myLibraryMap.size();
      }

      bool isIDValid(int songID_);
      // Function for creating and assigning song identifiers
      void uniqueIDAssi(int& songID_);

      void removeSongFromLibrary(int songID_);

      void addSongToLibrary(Song* songPointer_, int& songID_);
      void playSongs(int songID_, int& playTimes_, int& numberOfPlays_);

      // Check if a song exists in library, if yes update the song id with it's identifier,
      // Otherwise, update the songID_ with value -1;
      bool libraryHasSong(Song* songPointer_, int& songID_, int& numberOfPlays_);

      // Struct for comparing Songs by song name
      struct SongPointerComparatorNAME {
         bool operator()(pair<Song*, pair<int, int>> const&left,
              pair<Song*, pair<int, int>> const&right) const{
                 return (left.first->getSongName() <  right.first->getSongName());
         }
      };

      // Struct for comparing Songs by artist name
      struct SongPointerComparatorARTIST {
         // Overload operator
         bool operator()(pair<Song*, pair<int, int>> const&left,
              pair<Song*, pair<int, int>> const&right) const{
                 return (left.first->getArtistName() < right.first->getArtistName());
         }
      };

      // Struct for comparing Songs by album name
      struct SongPointerComparatorALBUM {
         bool operator()(pair<Song*, pair<int, int>> const&left,
              pair<Song*, pair<int, int>> const&right) const{
                 return (left.first->getAlbumName() < right.first->getAlbumName());
         }
      };

      // Struct for comparing Songs by number of plays
      struct SongPointerComparatorPLAYS {
         bool operator()(pair<Song*, pair<int, int>> const&left,
            pair<Song*, pair<int, int>> const&right) const{
               return (left.second.second > right.second.second);
            }
      };

      // Function for displaying library in sorted order
      void displaySongsOrdered(vector<pair<Song*, pair<int, int>>> myVector_);

      // Functions for displaying songs in a specific criteria: NAME, ARTIST, ALBUM or PLAYS
      void displayByName();
      void displayByArtist();
      void displayByAlbum();
      void displayByPlays();

      void exportLibrary(string filePath_);

      // Functions for autogenerate songs
      vector<Song*> findSongByNAME(string songName_);
      vector<Song*> findSongByARTIST(string artistName_);
      vector<Song*> findSongByALBUM(string albumName_);
      void findSongByMAGIC(vector<Song*>& tempSongVector_);

      void outputSongs(Song* songPointer_);
      void displaySongsInVector(vector<Song*> mySongVector_, Song* songPointer_,
                                vector<Song*>& tempSongVector_);
   private:
      int numberOfPlays, songID;

      map<Song*, pair<int, int>> myLibraryMap;
      map<Song*, pair<int, int>> ::iterator it;
};

#endif
