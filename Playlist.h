#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <map>
#include <string>
#include <iostream>
#include <unordered_map>

#include "Song.h"
#include "SongLibrary.h"

using namespace std;

class Playlist{
   public:
      Playlist();
      Playlist(string playlistTitle_, int playlistRating_, int numberOfSongs_)
      : playlistTitle(playlistTitle_), playlistRating(playlistRating_), numberOfSongs(numberOfSongs_) {};

      void setPlaylistTitle(string playlistTitle_) {
         playlistTitle = playlistTitle_;
      }
      void setPlaylistRating(int playlistRating_) {
         playlistRating = playlistRating_;
      }
      void setnumberOfSongs(int numberOfSongs_) {
         numberOfSongs = numberOfSongs_;
      }

      string getPlaylistTitle() {return playlistTitle;}
      int getPlaylistRating() {return playlistRating;}
      int getNumberOfSongs() {return numberOfSongs;}

   private:
      string playlistTitle;
      int playlistRating, numberOfSongs;
};

#endif
