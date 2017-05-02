#ifndef SongManagerDRIVER_H
#define SongManagerDRIVER_H

#include <string>
#include <iostream>

#include "Song.h"
#include "SongLibrary.h"
#include "PlaylistLibrary.h"

using namespace std;

class SongManagerDriver{
   public:
      enum AutogenerateType { NAME, ARTIST, ALBUM, MAGIC };
      void autogeneratePlaylist(AutogenerateType Type);

      void exportLibrary(string filePath_) {
         SongLibrary_.exportLibrary(filePath_);
      }

      void exportPlaylist(string filePath_) {
         PlaylistLibrary_.exportPlaylist(filePath_);
      }
      // Song Library related functions
      void loadSongToLibrary(Song* songPointer_, int songID_, int numberOfPlays_);
      void loadPlaylistToPlaylist(Playlist* playlistPointer_, vector<Song*> songPointerVector_);

      int numberOfSongs() {
         return SongLibrary_.numberOfSongs();
      }
      bool libraryHasSong(Song* songPointer_, int& songID_, int& numberOfPlays_) {
         return SongLibrary_.libraryHasSong(songPointer_, songID_, numberOfPlays_);
      }

      void addSongToLibrary(Song* songPointer_, int& songID_);
      bool isIDValid(int songID_);

      void getSongInfo(Song*& songPointer_, int songID_);
      void removeSongFromLibrary(int songID_);
      void playSongs(int songID_, int& playTimes_, int&numberOfPlays_);
      void displaySongs(string categoryType_);

      void getGeneralSongInfo(Song*& songPointer_, int songID_);

      // Playlist related functions
      bool hasPlaylist(string playlistTitle_);
      // Crates a new playlist
      void createPlaylist(string playlistTitle_);
      void removePlaylist(string playlistTitle_);
      void renamePlaylist(string playlistTitle_, string newPlaylistTitle_);
      void addSongToPlaylist(string playlistTitle_, Song* songPointer_);
      void removeSongFromPlaylist(string playlistTitle_, Song* songPointer_);
      // Check if a specific exists in the playlsist
      bool playlistHasSong(string playlistTitle_, Song* songPointer_);
      // Rate a specific playlist with rating playlistRating_
      void ratePlaylist(string playlistTitle_, int playlistRating_);
      void displaySongsInPlaylist(Song* songPointer_, int numberOfPlays_,
                                  int songID_, int counter_);
      int numberOfSongsInPlaylist(string playlistTitle_);

      void getPlaylistContainsSong(Song* songPointer_, vector<string>& playlistTitleVec_) {
         playlistTitleVec_ = PlaylistLibrary_.getPlaylistContainsSong(songPointer_);
      }

      int numberOfPlaylist() {
         return PlaylistLibrary_.numberOfPlaylist();
      }
      void displayPlaylists() {
         PlaylistLibrary_.displayPlaylists();
      }
      vector<Song*> getSpecificPlaylist(string playlistTitle_) {
         return PlaylistLibrary_.getSpecificPlaylist(playlistTitle_);
      }
      void autoGeneratePlaylist(string listCategory_, string detailed);

   private:
      SongLibrary SongLibrary_;
      PlaylistLibrary PlaylistLibrary_;
};

#endif
