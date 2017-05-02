#ifndef SONGLIBRARY_CPP
#define SONGLIBRARY_CPP

#include "SongLibrary.h"

#include <fstream>
#include <iostream>
using namespace std;

void SongLibrary::loadSongToLibrary(Song* songPointer_, int songID_, int numberOfPlays_) {
   // Add the song to the songlibrary using insert function
   myLibraryMap.insert(make_pair(songPointer_, make_pair(songID_, numberOfPlays_)));
}

void SongLibrary::displaySongs(SongDisplayType Type) {
   switch (Type) {
      case NAME:
         displayByName();
         break;
      case ARTIST:
         displayByArtist();
         break;
      case ALBUM:
         displayByAlbum();
         break;
      case PLAYS:
         displayByPlays();
         break;
   }
}

// Used to ensure we do not have duplicate Song Identifiers
void SongLibrary::uniqueIDAssi(int& songID_) {
   int uniqueID = 1;
   // Generate an ID and check it's uniqueness
   Object myObject(uniqueID);
   // If generated ID already exists increment it
   while (isIDValid(uniqueID)) {
      uniqueID++;
   }
   songID_ = uniqueID;
}

// Check if user's library alreday contain the song and update the song identifier for later use
bool SongLibrary::libraryHasSong(Song* songPointer_, int& songID_, int& numberOfPlays_) {
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      if (it->first->getSongName() == songPointer_->getSongName() &&
          it->first->getArtistName() == songPointer_->getArtistName() &&
          it->first->getAlbumName() == songPointer_->getAlbumName()) {
             songID_ = it->second.first;
             numberOfPlays_ = it->second.second;
             return true;
      }
   }
   songID_ = -1;
   return false;
}

void SongLibrary::addSongToLibrary(Song* songPointer_, int& songID_) {
   // Create a unique song identifier
   uniqueIDAssi(songID_);
   // Insert the song to the library
   myLibraryMap.insert(make_pair(songPointer_, make_pair(songID_, 0)));
}

// Check if user provided Song Identifier is vaild, if yes, return true, Otherwise, return false
bool SongLibrary::isIDValid(int songID_) {
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      if (it->second.first == songID_) {
         return true;
      }
   }
   return false; // The Song Identifier does not exist
}

// Obtain the detailed song's info
void SongLibrary::getGeneralSongInfo(Song*& songPointer_, int songID_) {
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      // Locate the song based on the song identifier
      if (it->second.first == songID_) {
         songPointer_ = it->first;
         return;
      }
   }
}

// Removes a song based on the identifier
void SongLibrary::removeSongFromLibrary(int songID_) {
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      // Locate the target song in the library
      if (it->second.first == songID_) {
         // Remove the song in it position
         myLibraryMap.erase(it);
         return; // The target song found and removed
      }
   }
}

void SongLibrary::playSongs(int songID_, int& playTimes_, int& numberOfPlays_) {
   // Play the song in the library
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      if (it->second.first == songID_) {
         numberOfPlays_ = it->second.second;
         // update the totalPlay times
         playTimes_ = playTimes_ + it->second.second;
         it->second.second = playTimes_;
         return;
      }
   }
}

void SongLibrary::displayByName() {
   vector<pair<Song*, pair<int, int>>>myVector(myLibraryMap.begin(), myLibraryMap.end());
   // Sort the library vector by Name
   sort(myVector.begin(), myVector.end(),
        SongPointerComparatorNAME());

   displaySongsOrdered(myVector);
}


void SongLibrary::displayByArtist() {
   vector<pair<Song*, pair<int, int>>>myVector(myLibraryMap.begin(), myLibraryMap.end());
   // Sort the library vector by Artist
   sort(myVector.begin(), myVector.end(),
        SongPointerComparatorARTIST());

   displaySongsOrdered(myVector);
}

void SongLibrary::displayByAlbum() {
   vector<pair<Song*, pair<int, int>>>myVector(myLibraryMap.begin(), myLibraryMap.end());
   // Sort the library vector by Album
   sort(myVector.begin(), myVector.end(),
        SongPointerComparatorALBUM());
   // Display songs in library in certain order
   displaySongsOrdered(myVector);
}


void SongLibrary::displayByPlays() {
   vector<pair<Song*, pair<int, int>>>myVector(myLibraryMap.begin(), myLibraryMap.end());
   // Sort the vector by the number of plays
   sort(myVector.begin(), myVector.end(),
        SongPointerComparatorPLAYS());
   // Display songs in library in certain order
   displaySongsOrdered(myVector);
}

void SongLibrary::displaySongsOrdered(vector<pair<Song*, pair<int, int>>> myVector_) {
   // Iterate through the vector and output each element in the vector
   for (unsigned int i = 0; i < myVector_.size(); ++i) {
      cout << i+1 << ". \"" << myVector_[i].first->getSongName() << "\" by "
           << myVector_[i].first->getArtistName() << "("
           << myVector_[i].first->getAlbumName() << ") - "
           << myVector_[i].second.second << " plays [#"
           << myVector_[i].second.first << "] \n";
   }
}

void SongLibrary::exportLibrary(string filePath_) {
   ofstream outLibrary(filePath_);
   // Iterate through the map and exports all the songs to file
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {
      outLibrary << it->first->getSongName() << '|'
                 << it->first->getArtistName() << '|'
                 << it->first->getAlbumName() << '|'
                 << it->second.second << '|'
                 << it->second.first << "\n";
   }
   outLibrary.close();
}

vector<Song*> SongLibrary::findSongByNAME(string songName_) {
   vector<Song*> mySongVector_;
   // Find has the same or similar song name and add to playlist
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {

      if (songName_ == it->first->getSongName()) {
         mySongVector_.push_back(it->first);
      }
   }
   return mySongVector_;
}

vector<Song*> SongLibrary::findSongByARTIST(string artistName_) {
   vector<Song*> mySongVector_;
   // Find has the same or similar artsit name and add to playlist
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {

      if (artistName_ == it->first->getArtistName()) {
         mySongVector_.push_back(it->first);
      }
   }
   return mySongVector_;
}

vector<Song*> SongLibrary::findSongByALBUM(string albumName_) {
   vector<Song*> mySongVector_;
   // Find has the same or similar album name and add to playlist
   for (it = myLibraryMap.begin(); it != myLibraryMap.end(); ++it) {

      if (albumName_ == it->first->getAlbumName()) {
         mySongVector_.push_back(it->first);
      }
   }
   return mySongVector_;
}

void SongLibrary::findSongByMAGIC(vector<Song*>& tempSongVector_) {
   vector<Song*> mySongVector_;

   vector<pair<Song*, pair<int, int>>>myVector(myLibraryMap.begin(), myLibraryMap.end());
   // Sort the vector by the number of plays
   sort(myVector.begin(), myVector.end(),
        SongPointerComparatorPLAYS());

   if (myVector.size() >= 5) {
      for (int i = 0; i < 5; ++i) {
         if (i == 0 || i == 1) {
            outputSongs(myVector[i].first);
            // Push songs into vector
            mySongVector_ = (findSongByNAME(myVector[i].first->getSongName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);

         } else if (i == 2 || i == 3) {
            outputSongs(myVector[i].first);

            mySongVector_ = (findSongByARTIST(myVector[i].first->getArtistName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);

         } else if (i == 4) {
            outputSongs(myVector[i].first);

            mySongVector_ = (findSongByALBUM(myVector[i].first->getAlbumName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);
         }
      }
      return;
   } else { // If library does not have enough song
      for (unsigned int i = 0; i < myVector.size(); ++i) {
         if (i == 0 || i == 1) {
            outputSongs(myVector[i].first);
            // Push songs into vector
            mySongVector_ = (findSongByNAME(myVector[i].first->getSongName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);

         } else if (i == 2 || i == 3) {
            outputSongs(myVector[i].first);

            mySongVector_ = (findSongByARTIST(myVector[i].first->getArtistName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);

         } else if (i == 4) {
            outputSongs(myVector[i].first);

            mySongVector_ = (findSongByALBUM(myVector[i].first->getAlbumName()));
            displaySongsInVector(mySongVector_, myVector[i].first, tempSongVector_);
         }
      }
   }
}

// Helper functionf ro displays songs
void SongLibrary::outputSongs(Song* songPointer_) {
   cout << "Autogenerating based on the following songs: \n "
        << "\"" << songPointer_->getSongName() << "\" by "
        << songPointer_->getArtistName() << " ("
        << songPointer_->getAlbumName() << "). \n" ;
}

void SongLibrary::displaySongsInVector(vector<Song*> mySongVector_, Song* songPointer_,
                                       vector<Song*>& tempSongVector_) {
   if (mySongVector_.size() == 0) { // Check if any similar songs found in the library
      cout << "  (No similar songs founds). \n";
   } else if (mySongVector_.size() <= 3){
      for (unsigned int i = 1; i < mySongVector_.size(); ++i) {
         tempSongVector_.push_back(mySongVector_[i]);

         // Output the similar songs found in library
         cout << "    \"" << mySongVector_[i]->getSongName() << "\" by "
              << mySongVector_[i]->getArtistName() << " ("
              << mySongVector_[i]->getAlbumName() << ")\n";
      }
   } else {
      for (unsigned int i = 1; i < 3; ++i) {
         tempSongVector_.push_back(mySongVector_[i]);

         // Output the similar songs found in library
         cout << "    \"" << mySongVector_[i]->getSongName() << "\" by "
              << mySongVector_[i]->getArtistName() << " ("
              << mySongVector_[i]->getAlbumName() << ")\n";
      }
   }
}

#endif
