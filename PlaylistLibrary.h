#ifndef PLAYLISTLIBRARY_H
#define PLAYLISTLIBRARY_H

#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "Song.h"
#include "Playlist.h"
#include "SongLibrary.h"

using namespace std;

class PlaylistLibrary{
   public:
      void addToPlaylist(string playlistTitle_, vector<Song*> mySongVector_);
      void loadPlaylistToPlaylist(Playlist* playlistPointer_, vector<Song*> songPointerVector_);
      int numberOfPlaylist();
      void displayPlaylists();

      bool hasPlaylist(string playlistTitle_);

      void createPlaylist(string playlistTitle_);
      // Remove an existing playlist
      void removePlaylist(string playlistTitle_);
      // Rename an existing playlist
      void renamePlaylist(string playlistTitle_, string newPlaylistTitle_);
      // Add a new song from library to playlist
      void addSongToPlaylist(string playlistTitle_, Song* songPointer_);
      // Remove songs from playlist
      void removeSongFromPlaylist(string playlistTitle_, Song* songPointer_);
      // Check if a specific song exists in playlsit
      bool playlistHasSong(string playlistTitle_, Song* songPointer_);

      void ratePlaylist(string playlistTitle_, int playlistRating_);
      void displaySongsInPlaylist(Song* songPointer_, int numberOfPlays_,
                                  int songID_, int counter_);

      int numberOfSongsInPlaylist(string playlistTitle_);

      vector<string> getPlaylistContainsSong(Song* songPointer_);
      void exportPlaylist(string filePath_);

      // Struct for playlsit by rating
      struct PlaylistComparator {
         bool operator()(pair<Playlist*, vector<Song*>> const&left,
            pair<Playlist*, vector<Song*>> const&right) const{
               return ((left.first->getPlaylistRating() > right.first->getPlaylistRating())
                      || (left.first->getPlaylistRating() == right.first->getPlaylistRating()
                      && left.first->getPlaylistTitle() < right.first->getPlaylistTitle()));
            }
      };
      void OrderPlaylist();
      void displayOrderedPlaylists(vector<pair<Playlist*, vector<Song*>>>myVector);

      vector<Song*> getSpecificPlaylist(string playlistTitle_);

   private:
      SongLibrary SongLibrary_;
      // Use vector of type Song* to mainatin varies of songs
      map<Playlist*, vector<Song*>> myPlaylistMap;
      map<Playlist*, vector<Song*>> ::iterator it;
};
#endif
