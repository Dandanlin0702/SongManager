### Project Name
   SongManager

### Description:
   This program is an interactive console program that implemented using unsorted map and sorted vector that allows users to manually manage their song library and playlists efficiently.
   They can perform some simple actions such as add, remove, rename, sort music from their existed library. They can also create, rate, autogenerate playlists.

### Compiling & Executing
   User should have a command interface installed before compiling and executing
   To Compile:
      make all

   To execute:
      $ ./SongManager

### Classes
   * Song Library:
         a library is essentially a master list of all the songs owned by a user. It does not contain any duplicate songs.

         With Library users can:
            * Add a new song and add it to the library by specifying the song's name, artist and album name through AS command
            * Remove a specific song from his/her song library through RS command
            * Play an exiting song in the library and track its total number of plays through PLY command
            * Display his/her library, with every song's name, artist name and album name, by specific order, NAME/ARTIST/ALBUM/PLAYS through LB command
            * Auto generate a playlist by specifying the category to auto-generate by, NAME/ARTIST/ALBUM/MAGIC, through AG command
            * Export the song library to a file through command EXP
            Play/Load local song library's file to SongManager, simply by providing the correct file path when he/she runs SongManager

   * Playlist:
         a playlist has a unique title, is assigned a rating from 1 to 5, and contains a series of songs from library

         With Playlist users can:
            * Create a new playlist by providing a unique playlist's title through AP command
            * Remove an existing playlist though RP command
            * Add a new song from his/her library to any existing playlist through ASP command
            * Remove a specific song from a playlist by providing the target song's ID
            * Assign a new rating, from 1 to 5, to a playlist based on how much he/she likes the playlist through RT command
            * Display all of the songs in a playlist, by default songs will be displayed in a numbered list in the order that they were added to the playlist through PL command
            * Display all of the playlists, be default, playlists will be displayed in a numbered list ordered first by rating then alphabetically by title through PLS command
            * Export all of the playlists along with its songs to a file through command EXP
            Play/Load local playlists' file to SongManager, simply by providing the correct file path when he/she runs SongManager


## Relationships Between Some Classes:
   * Song   
      It wraps over the general information related to a song, such as: name, artist, album
   * SongLibrary
      Provides an interface over a map of a songPointer and two ints that stores a group of songs
   * Playlist
      Wraps over the general information about a playlists, such as: title, rating, and number of songs in a playlist
   * PlaylistLibrary
      Provides an interface over Song and Playlist. It take a map of Song* and Playlist* to store varies numbers of playlists
   * SongManagerApp
      It serves as main interaction point with the user. This class contains an instance of SongLibrary, PlaylistLibrary and SongManagerDriver that gets manipulated based on user's commands. This class will keep tracking command and controlling most part of the inputs and outputs.
   * SongManagerDriver
      Represents as the underlying driver for SongLibrary and PlaylistLibrary

### Files Included
   Files Created For Completion
       * main.cpp
       * Playlist.h
       * Playlist.cpp
       * PlaylistLibrary.h
       * PlaylistLibrary.cpp
       * Song.h
       * Song.cpp
       * SongLibrary.h
       * SongLibrary.cpp
       * SongManagerApp.h
       * SongManagerApp.cpp
       * SongManagerDriver.h
       * SongManagerDriver.cpp
   Documentation & Compilation Files
       * README.md
       * makefile
   Testing Files Provided by Instructor
       * library_complete.data
       * playlists_problematic.data
       * playlists_complete.data
       * playlists_problematic.data

### Implemented By
   Dandan Lin
