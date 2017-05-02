#ifndef PLAYLISTLIBRARY_CPP
#define PLAYLISTLIBRARY_CPP

#include "PlaylistLibrary.h"

#include <fstream>
#include <iostream>
using namespace std;

void PlaylistLibrary::addToPlaylist(string playlistTitle_, vector<Song*> mySongVector_) {
   int playlistRating_ = 1, numberOfSongs_ = mySongVector_.size();
   Playlist* playlistPointer_;

   playlistPointer_ = new Playlist(playlistTitle_, playlistRating_, numberOfSongs_);

   myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));
}

void PlaylistLibrary::loadPlaylistToPlaylist(Playlist* playlistPointer_, vector<Song*> songPointerVector_) {
   myPlaylistMap.insert(make_pair(playlistPointer_, songPointerVector_));
}

int PlaylistLibrary::numberOfPlaylist() {
   return myPlaylistMap.size();
}

void PlaylistLibrary::OrderPlaylist() {
   vector<pair<Playlist*, vector<Song*>>>myVector(myPlaylistMap.begin(), myPlaylistMap.end());
   sort(myVector.begin(), myVector.end(), PlaylistComparator());

   displayOrderedPlaylists(myVector);
}

void PlaylistLibrary::displayOrderedPlaylists(vector<pair<Playlist*, vector<Song*>>>myVector_) {
   // Iterate through the vector and output each element in the vector
   for (unsigned int i = 0; i < myPlaylistMap.size(); ++i) {
      cout << i+1 << ". \"" <<  myVector_[i].first->getPlaylistTitle()
           << "\" - Rating: " << myVector_[i].first->getPlaylistRating()
           << " - " << myVector_[i].first->getNumberOfSongs() << " songs \n";
   }
}

void PlaylistLibrary::displayPlaylists() {
   OrderPlaylist();
}

bool PlaylistLibrary::hasPlaylist(string playlistTitle_) {
   // Check is the Playlist already exists, if yes, return true, else return false
   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
      if (it->first->getPlaylistTitle() == playlistTitle_) {
         return true;
      }
   }
   return false;
}

void PlaylistLibrary::createPlaylist(string playlistTitle_) {
   vector<Song*> mySongVector_;
   // Initialize the rating to 1 and numberOfSongs in playlist with 0
   int playlistRating_ = 1, numberOfSongs_ = 0;

   Playlist* playlistPointer_ = new Playlist(playlistTitle_, playlistRating_, numberOfSongs_);
   myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));
}

void PlaylistLibrary::removePlaylist(string playlistTitle_) {
   if (numberOfPlaylist() == 1) {
      myPlaylistMap.clear();
   } else {
       for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
         // Iterate through the playlist map, located the target playist and remove it
         if (it->first->getPlaylistTitle() == playlistTitle_) {
            myPlaylistMap.erase(it);

            return;
         }
      }
   }
   return;
}

void PlaylistLibrary::renamePlaylist(string playlistTitle_, string newPlaylistTitle_) {
   Playlist* playlistPointer_;
   vector<Song*> mySongVector_;

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
     // Iterate through the playlist map, located the target playist and remove it
     if (it->first->getPlaylistTitle() == playlistTitle_) {
        mySongVector_ = it->second;
        playlistPointer_ = new Playlist(newPlaylistTitle_, it->first->getPlaylistRating(), it->first->getNumberOfSongs());

        // Remove the Playlist first and then insert it  into the map with new title;
        myPlaylistMap.erase(it);
        myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));

        return;
     }
   }
}

void PlaylistLibrary::addSongToPlaylist(string playlistTitle_, Song* songPointer_) {
   Playlist* playlistPointer_;
   vector<Song*> mySongVector_;

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
     // Iterate through the playlist map, located the target playist and remove it
     if (it->first->getPlaylistTitle() == playlistTitle_) {
        mySongVector_ = it->second;
        mySongVector_.push_back(songPointer_);
        playlistPointer_ = new Playlist(playlistTitle_, it->first->getPlaylistRating(), it->first->getNumberOfSongs()+1);
        // Remove the Playlist first and then insert it  into the map with new title;
        myPlaylistMap.erase(it);
        myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));
        return;
     }
   }
}

void PlaylistLibrary::removeSongFromPlaylist(string playlistTitle_, Song* songPointer_) {
   Playlist* playlistPointer_;
   vector<Song*> mySongVector_;

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
     // Iterate through the playlist map, located the target playist and remove it
     if (it->first->getPlaylistTitle() == playlistTitle_) {
       playlistPointer_ = new Playlist(playlistTitle_, it->first->getPlaylistRating(), it->first->getNumberOfSongs()-1);

       for (unsigned int i = 0; i < it->second.size(); ++i) {
          if (it->second[i]->getSongName() == songPointer_->getSongName() &&
             it->second[i]->getArtistName() == songPointer_->getArtistName() &&
             it->second[i]->getAlbumName() == songPointer_->getAlbumName()) {
               mySongVector_ = it->second;
               mySongVector_.erase(mySongVector_.begin()+i);

               myPlaylistMap.erase(it);
               myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));

               return;
            }
         }
      }
   }
   return;
}

bool PlaylistLibrary::playlistHasSong(string playlistTitle_, Song* songPointer_) {
   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
      if (it->first->getPlaylistTitle() == playlistTitle_) {
         // Locate the playlsist and check if the song exist in playst
         for (unsigned int i = 0; i < it->second.size(); ++i) {
            if (it->second[i]->getSongName() == songPointer_->getSongName() &&
                it->second[i]->getArtistName() == songPointer_->getArtistName() &&
                it->second[i]->getAlbumName() == songPointer_->getAlbumName()) {

               return true;
            }
         }
      }
   }
   return false;
}

void PlaylistLibrary::ratePlaylist(string playlistTitle_, int playlistRating_) {
   Playlist* playlistPointer_;
   vector<Song*> mySongVector_;

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
     // Iterate through the playlist map, located the target playist and remove it
     if (it->first->getPlaylistTitle() == playlistTitle_) {
        mySongVector_ = it->second;
        playlistPointer_ = new Playlist(playlistTitle_, playlistRating_,
                                        it->first->getNumberOfSongs());

        myPlaylistMap.erase(it);
        myPlaylistMap.insert(make_pair(playlistPointer_, mySongVector_));

        return;
     }
   }
}

// Display all the songs in a specific playlist
void PlaylistLibrary::displaySongsInPlaylist(Song* songPointer_,
                                             int numberOfPlays_, int songID_,
                                             int counter_) {
   // Get the Song identifier and numberOfPlays in the library
   cout << counter_+1 << ". \"" << songPointer_->getSongName() << "\" by "
        << songPointer_->getArtistName() << "("
        << songPointer_->getAlbumName() << ") - "
        << numberOfPlays_ << " plays [#"
        << songID_ << "]\n";
}

int PlaylistLibrary::numberOfSongsInPlaylist(string playlistTitle_) {
   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
     // Iterate through the playlist map, located the target playist and remove it
     if (it->first->getPlaylistTitle() == playlistTitle_) {
        return it->first->getNumberOfSongs();
     }
   }

   return -1;
}

vector<string> PlaylistLibrary::getPlaylistContainsSong(Song* songPointer_) {
   vector<string> playlistContainsSong_;

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
      for (unsigned int i = 0; i < it->second.size(); ++i) {
         if (it->second[i]->getSongName() == songPointer_->getSongName() &&
             it->second[i]->getArtistName() == songPointer_->getArtistName() &&
             it->second[i]->getAlbumName() == songPointer_->getAlbumName()) {
            // Push back the playlist's title which contains target song
            playlistContainsSong_.push_back(it->first->getPlaylistTitle());
         }
      }
   }
   return playlistContainsSong_;
}

void PlaylistLibrary::exportPlaylist(string filePath_) {
   ofstream outPlaylist(filePath_);

   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
      // Export playlist title, rating and number of songs
      outPlaylist << it->first->getPlaylistTitle() << '|'
                  << it->first->getPlaylistRating() << '|'
                  << it->first->getNumberOfSongs() << "\n";
      // Export songs in the playlist
      for (unsigned int i = 0; i < it->second.size(); ++i) {
         outPlaylist << it->second[i]->getSongName() << '|'
                     << it->second[i]->getArtistName() << '|'
                     << it->second[i]->getAlbumName() << "\n";
      }
   }
   return;
}

vector<Song*> PlaylistLibrary::getSpecificPlaylist(string playlistTitle_) {
   vector<Song*> songPointerVector_;
   // Get songs in a specific playlist
   for (it = myPlaylistMap.begin(); it != myPlaylistMap.end(); ++it) {
      if (it->first->getPlaylistTitle() == playlistTitle_) {
         songPointerVector_ = it->second;
      }
   }
   return songPointerVector_;
}

#endif
