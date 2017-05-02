#ifndef SONG_H
#define SONG_H

#include <map>
#include <string>
#include <iostream>

using namespace std;

class Song{
   public:
      Song (string songName_, string artistName_, string albumName_): songName(songName_), artistName(artistName_), albumName(albumName_) {};

      string getSongName() {return songName;}
      string getArtistName() {return artistName;}
      string getAlbumName() {return albumName;}

   private:
      string songName, artistName, albumName;
};

#endif
