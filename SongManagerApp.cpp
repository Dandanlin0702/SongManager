#ifndef SongManagerAPP_CPP
#define SongManagerAPP_CPP

#include "Playlist.h"
#include "SongManagerApp.h"

#include <fstream>
#include <sstream>

void SongManagerApp::loadData(int argc, char *argv[]) {
	ifstream inLibrary, inPlaylist;

	if (argc == 1) {
		cout << "No library file provided. \n"
			  << "No playlists file provided. \n";
	} else if (argc == 2) {
		inLibrary.open(argv[1]);

		if (inLibrary.good()) {
			cout << "Loading library from " << "\"" << argv[1] << "\" \n";

			loadLibrary(argv[1]);
			cout << "No playlists file provided. \n";

			inLibrary.close();
		} else {

			cout << "Could not load library from " << "\"" << argv[1]
				  << "\"" << ". Skipping. \n"
			 	  << "No playlists file provided. \n";
		}
	} else if (argc == 3) {
		inLibrary.open(argv[1]);
		inPlaylist.open(argv[2]);

		if (inLibrary.good() && inPlaylist.good()) {
			cout << "Loading library from " << "\"" << argv[1] << "\" \n";
			loadLibrary(argv[1]);

			cout << "Loading playlist from " << "\"" << argv[2] << "\" \n";

			loadPlaylist(argv[2]);
		} else if ( inLibrary.good() && !inPlaylist.good()) {
			cout << "Loading library from " << "\"" << argv[1] << "\" \n";
			loadLibrary(argv[1]);

			cout << "Could not load playlist from " << "\""
				  << argv[2] << "\"" << ". Skipping. \n";
		} else if ((!inLibrary.good() && !inPlaylist.good()) || (!inLibrary.good() && inPlaylist.good())) {
			cout << "Could not load library from " << "\"" << argv[1] << "\"" << ". Skipping. \n";
			cout << "Could not load playlist from " << "\"" << argv[2] << "\"" << ". Skipping. \n";
		}

		inLibrary.close();
		inPlaylist.close();
	}
}

void SongManagerApp::loadLibrary(string filePath) {
	ifstream inLibrary(filePath);
	// Reads input first by line
	string line, token;

	while (getline(inLibrary, line)) {
		Song* songPointer;

		int numberOfPlays = 0, songID = 0;
		string songName, artistName, albumName;

		istringstream lineStream(line);
		int number = 1;

    	// Reads the current line by pipe character
		while (getline(lineStream, token, '|')) {
			switch (number) {
				case 1: // Song Name
					songName = token;
					break;
				case 2: // Artist Name
					artistName = token;
					break;
				case 3: // Album Name
					albumName = token;
					break;
				case 4: // Number of Plays
					numberOfPlays = atoi(token.c_str());
					break;
				case 5: // Song identifier
					songID = atoi(token.c_str());
					break;
			}
			++number;
		}
		songPointer = new Song(songName, artistName, albumName);
		SongManagerDriver_.loadSongToLibrary(songPointer, songID, numberOfPlays);
	}
	cout << "Library loaded successfully! \n";

	inLibrary.close();
}

void SongManagerApp::loadPlaylist(string filePath) {
	ifstream inPlaylist(filePath);

	Song* songPointer;
	Playlist* playlistPointer;
	// Vector of Song* to store the songs
	vector<Song*> seriesOfSongs;
	string line, token, playlistTitle;
	int playlistRating, numberOfSongs;

	// Reads input first by line
	while (getline(inPlaylist, line)) {
		istringstream lineStream(line);
		int number = 1;

		// Reads the current line by pipe character
		while (getline(lineStream, token, '|')) {
			switch (number) {
				case 1: // Playlist Title
					playlistTitle = token;
					break;
				case 2: // Playlist Rating
					playlistRating = atoi(token.c_str());
					break;
				case 3: // Number Of Songs
					numberOfSongs = atoi(token.c_str());
					break;
			}
			++number;

			// After loading the playlistTitle line load songs
			if (number == 4) {

				// Load tempNumberOfSongs from playist
				int  tempNumberOfSongs = numberOfSongs;
				while (tempNumberOfSongs > 0 && getline(inPlaylist, line)) {
					string songName, artistName, albumName;
					int numberSong = 1, songID = 0, numberOfPlays = 0;

					istringstream lineStream2(line);
					while (getline(lineStream2, token, '|')) {
						switch (numberSong) {
							case 1: // Song Name
								songName = token;
								break;
							case 2: // Artist Name
								artistName = token;
								break;
							case 3: // Album Name
								albumName = token;
								break;
						}
						++numberSong;
					}
					songPointer = new Song(songName, artistName, albumName);
					// Check if the song exists in the library, if not output erroe message
					if (SongManagerDriver_.libraryHasSong(songPointer, songID, numberOfPlays)) {
						seriesOfSongs.push_back(songPointer);
					} else {
						// If the song does not exit in the library skipp it and decrement the numberOfSongs
						--numberOfSongs;
						cout << "Could not find song in library: \"" << songName << '|'
							  << artistName << '|' << albumName << "\" \n";
					}
					--tempNumberOfSongs;
				}
				playlistPointer = new Playlist(playlistTitle, playlistRating, numberOfSongs);

				// load playlist and the song to the playlist library
				SongManagerDriver_.loadPlaylistToPlaylist(playlistPointer, seriesOfSongs);
				// Clear teh vector for next time use
				seriesOfSongs.clear();
			}
		}
	}
	// close File
	inPlaylist.close();
}

void SongManagerApp::startApp() {
	string userCommand;
	// Greet to user
	cout << "Welcome to your SongManager! For a full list of userCommand, type \"HELP\".\n";

	do {
		cout << "> ";
		cin >> userCommand;

      toTopper(userCommand);

		if (userCommand == "AS") {
			commandIsAS();
		} else if (userCommand == "RS") {
			commandIsRS();
		} else if (userCommand == "PLY") {
			commandIsPLY();
		} else if (userCommand == "LB") {
			commandIsLB();
		} else if (userCommand == "AP") {
			commandIsAP();
		} else if (userCommand == "RP") {
			commandIsRP();
		} else if (userCommand == "RN") {
			commandIsRN();
		} else if (userCommand == "ASP") {
			commandIsASP();
		} else if (userCommand == "RSP") {
			commandIsRSP();
		} else if (userCommand == "RT") {
			commandIsRT();
		} else if (userCommand == "PL") {
			commandIsPL();
		} else if (userCommand == "PLS") {
			commandIsPLS();
		} else if (userCommand == "AG") {
			commandIsAG();
		} else if (userCommand == "EXP") {
			commandIsEXP();
		} else if (userCommand == "HELP") {
			cout << helpMenu();
		} else if (userCommand == "EXIT") {
			cout << "Thank you for using SongManager! \n \n";
			break;
		} else {
			cout << "Unknown user command (" << userCommand << ") invoked. \n";
		}
		cout << "\n";
	} while (true);
}

// Adds a new song to the user’s library.
void SongManagerApp::commandIsAS() {
	Song* songPointer;
	int numberOfPlays, songID;
	string songName, artistName, albumName;

	// Obtain general info(songName, artistName, albumName) from user
	cout << "What is the name of the song you’d like to purchase? \n> ";
	cin.ignore();
	getline(cin, songName);

   cout << "Who is its artist? \n> ";
   getline(cin, artistName);

   cout << "Which album does it belong to? \n> ";
   getline(cin, albumName);

	songPointer = new Song(songName, artistName, albumName);

	// Check if the song user wants to purchase already exists
	if (SongManagerDriver_.libraryHasSong(songPointer, songID, numberOfPlays) && songID != -1) {
		cout << "\"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << " ("
		     << songPointer->getAlbumName() << "), identified as #" << songID
			  << ", already exists in your library. \n";
	} else {
		// Add the song to library
		SongManagerDriver_.addSongToLibrary(songPointer, songID);

		cout << "\"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << " ("
		     << songPointer->getAlbumName() << "), identified as #" << songID
			  << ", purchased successfully to your library. \n";
	}
}

// Removes a song from user's library and playlists that that song belongs to
void SongManagerApp::commandIsRS() {
   int songID;
	Song* songPointer;
	string songName, artistName, albumName;
	vector<string> playlistTitleVec;

	if (SongManagerDriver_.numberOfSongs() == 0) {
		cout << "You have no songs in your library. \n";
	} else {
		cout << "What is the identifier of the song you’d like to remove from your library? \n> ";
		cin >> songID;
		// Check if the user provided song identifier is valid
		if (!SongManagerDriver_.isIDValid(songID)) {
			cout << "No song with identifier #" << songID << " exists in your library. \n";
			return;
		} else {
			SongManagerDriver_.getGeneralSongInfo(songPointer, songID);
			// Push all the playlist's, which contains the song, title to a vector
			SongManagerDriver_.getPlaylistContainsSong(songPointer, playlistTitleVec);
			SongManagerDriver_.removeSongFromLibrary(songID);

			if (playlistTitleVec.size() == 0) {
				cout << "\"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << " ("
					  << songPointer->getAlbumName() << "), identified as #" << songID
					  << " removed successfully from your library. \n";
			} else {
				cout << "\"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << " ("
					  << songPointer->getAlbumName() << "), identified as #" << songID
					  << " removed successfully from your library ";

			// Lists all the playlist's, which contains the song, titles
				for (unsigned int i = 0; i < playlistTitleVec.size(); ++i) {
					// Remove a song from playlist
					SongManagerDriver_.removeSongFromPlaylist(playlistTitleVec[i], songPointer);

					if (playlistTitleVec.size() == 1) {
						cout << "and from playlists \"" << playlistTitleVec[i] << "\". \n";
					} else if (playlistTitleVec.size() > 1 && i == playlistTitleVec.size() - 1) {
						cout << " \"" << playlistTitleVec[i] << "\". \n";
					} else {
						cout << "and from playlists \"" << playlistTitleVec[i] << "\", ";
					}
				}
			}
		}
	}
}

// Plays a song in the use's library a certain number of times
void SongManagerApp::commandIsPLY() {
	Song* songPointer;
	string songName, artistName, albumName;
	int songID, numberOfPlays = 0, playTimes = 0, tempPlaytimes = 0;

	if (SongManagerDriver_.numberOfSongs() == 0) {
		cout << "You have no songs in your library. \n";
	} else {
		// Obtain the song identifier from user
		cout << "What is the identifier of the song you’d like to listen to? \n> ";
		cin >> songID;
		// Check if the song identifier is valid
		if (!SongManagerDriver_.isIDValid(songID)) {
			cout << "No song with identifier #" << songID << " exists in your library. \n";
		} else { // Gets play ti,es from user
			cout << "How many times would you like to play this song? \n> ";
			cin >> playTimes;

			if (playTimes <= 0) {
		      playTimes = 0;
		   }

			tempPlaytimes = playTimes;
			// Play the song and update the playTimes
			SongManagerDriver_.playSongs(songID, playTimes, numberOfPlays);
			SongManagerDriver_.getGeneralSongInfo(songPointer, songID);

			cout << "\"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName()
			     << "(" << songPointer->getAlbumName() << "), identified as #"
				  << songID << ", played successfully " << tempPlaytimes
				  << " times (" << numberOfPlays << " plays -> " << playTimes << " plays).\n";
		}
	}
}

// Dispay all songs in the library
void SongManagerApp::commandIsLB() {
	string categoryType;
	// Output warning when there's no songs in the library
	if (SongManagerDriver_.numberOfSongs() == 0) {
		cout << "You have no songs in your library. \n";
	} else {
		// Get the criterion for ordering songs from user
		cout << "What category should the songs be ordered by? (NAME/ARTIST/ALBUM/PLAYS) \n> ";
		cin >> categoryType;

		toTopper(categoryType);

		// Output error messge when user provided an invalid category type
		if (categoryType == "NAME" || categoryType == "ARTIST" ||
		    categoryType == "ALBUM" || categoryType == "PLAYS") {

			SongManagerDriver_.displaySongs(categoryType);
		} else {
			cout << "You entered an invalid category type. \n";
		}
	}
}

// Creates a new playlist
void SongManagerApp::commandIsAP() {
	string playlistTitle;
	// Gets playlist title from user
	cout << "What is the title of the playlist you’d like to create? \n> ";
	cin.ignore();
	getline(cin, playlistTitle);

	// Check if the user provided playlist already exists
	if (SongManagerDriver_.hasPlaylist(playlistTitle)){
		// If it exists putput error message
		cout << "\"" << playlistTitle << "\"" << " playlist already exists. \n ";
	} else {
		// Else create a new playlist
		SongManagerDriver_.createPlaylist(playlistTitle);

		cout << "\"" << playlistTitle << "\"" << "playlist created successfully. \n";
	}
}

// Removes a playlist
void SongManagerApp::commandIsRP(){
	string playlistTitle;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute RP command, there's no playlist exits. \n";
	} else if (SongManagerDriver_.numberOfPlaylist() != 0){
		cin.ignore();
		cout << "What is the title of the playlist you’d like to remove? \n> ";
		getline(cin, playlistTitle);

		// Check if user provided a valid playlistTitle, if yes, remove it. Otherwise, prompt erro message
		if (SongManagerDriver_.hasPlaylist(playlistTitle)){
			SongManagerDriver_.removePlaylist(playlistTitle);
			cout << "\"" << playlistTitle << "\"" << " playlist removed successfully. \n";
		} else {
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		}
	}
}

// Renames an existing playlist
void SongManagerApp::commandIsRN(){
	string playlistTitle, newPlaylistTitle;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute RN command, there's no playlist exits. \n";
	} else {
		// Get the Playlist title that user wants to rename and the new playlistTitle
		cout << "What is the title of the playlist you’d like to rename? \n> ";
		cin.ignore();
		getline(cin, playlistTitle);

		if (SongManagerDriver_.hasPlaylist(playlistTitle)) {
			cout << "What is the new title that you’d like to rename it to? \n> ";
			getline(cin, newPlaylistTitle);

			// If the new title user provided alreday exitst output error message
			if (SongManagerDriver_.hasPlaylist(newPlaylistTitle)) {
				cout << "\"" << newPlaylistTitle << "\"" << " playlist already exists. \n";
			} else {
				SongManagerDriver_.renamePlaylist(playlistTitle, newPlaylistTitle);

				cout << "\"" << playlistTitle << "\"" << " playlist renamed successfully to "
		           << "\"" << newPlaylistTitle << "\" \n" ;
			}
		} else { 	// If the playlist user wants to rename does not exist output error message
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		}
	}
}

// Adds a song from user's library to an existing playlist
void SongManagerApp::commandIsASP() {
	Song* songPointer;
	int songID = 0;
	string songName, artistName, albumName, playlistTitle;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute ASP command, there's no playlist exits. \n";
	} else {
		cout << "What is the title of the playlist you’d like to add a song to? \n> ";
		cin.ignore();
		getline(cin, playlistTitle);

		// Check is the playlist already exists
		if (!SongManagerDriver_.hasPlaylist(playlistTitle)) {
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		} else {
			// If the playlistTitle is valid, obtain the song identifier that user wants to add from user
			cout << "What is identifier of the song to add to the playlist? \n> ";
			cin >> songID;
			// Check is the song identifier is vlid
			if (!(SongManagerDriver_.isIDValid(songID))) {
				cout << "No song with identifier #" << songID << " exists in your library. \n";
			} else {

				SongManagerDriver_.getGeneralSongInfo(songPointer, songID);

				if (SongManagerDriver_.playlistHasSong(playlistTitle, songPointer)) {
					cout << " \"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << "("
					     << songPointer->getAlbumName() << "), identified as #" << songID
						  << " already exists in playlist \"" << playlistTitle << "\".\n" ;
				} else {
					// Add the song to playlist if the song identifier is valid
					SongManagerDriver_.addSongToPlaylist(playlistTitle, songPointer);

					cout << " \"" << songPointer->getSongName() << "\" by " << songPointer->getArtistName() << "("
					     << songPointer->getAlbumName() << "), identified as #" << songID
						  << " added successfully to playlist \"" << playlistTitle << "\".\n" ;
				}
			}
		}
	}
}

// Removes a song from a playlist
void SongManagerApp::commandIsRSP() {
   Song* songPointer;
	int songID;
	string songName, artistName, albumName, playlistTitle;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute RSP command, there's no playlist exits. \n";
	} else {
		cout << "What is the title of the playlist you’d like to remove a song? \n> ";
		cin.ignore();
		getline(cin, playlistTitle);

	   // Check if user provdied valid playlist title
		if (!(SongManagerDriver_.hasPlaylist(playlistTitle))) {
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		} else {
			cout << "What is identifier of the song to be removed from the playlist? \n> ";
			cin >> songID;

	      // Obtain the general info about the target song
			SongManagerDriver_.getGeneralSongInfo(songPointer, songID);

			if (SongManagerDriver_.playlistHasSong(playlistTitle, songPointer)) {
				// Remove the song from the traget playlist
				SongManagerDriver_.removeSongFromPlaylist(playlistTitle, songPointer);

				cout << " \"" << songPointer->getSongName() << " by " << songPointer->getArtistName() << "("
				     << songPointer->getAlbumName() << "), identified as #" << songID
					  << " removed successfully from playlist \"" << playlistTitle << "\".\n" ;
			} else {
				cout << "No song with identifier #" << songID << " exits in playlist "
					  << playlistTitle << ".\n";
			}
		}
	}
}

// Gives a new rating to a playlist
void SongManagerApp::commandIsRT() {
	int rating;
	string playlistTitle;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute RT command, there's no playlist exits. \n";
	} else {
		cout << "What is the title of the playlist you’d like to rate? \n> ";
		cin.ignore();
		getline(cin, playlistTitle);

		if (!SongManagerDriver_.hasPlaylist(playlistTitle)) {
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		} else {
	      // Obtain the rating from user
			cout << "What rating would you like to give this playlist? (1 to 5) \n> ";
			cin >> rating;
	      // Output error message if user entered an invalid rating
			if (rating <= 0 || rating >= 6) {
				cout << "\"" << rating << "\"" << " is not a valid rating. \n";
			} else {
	         // Else rate the playlist with user provided rating
				SongManagerDriver_.ratePlaylist(playlistTitle, rating);
				cout << "\"" << playlistTitle << "\"" << " playlist rated successfully as a " << rating <<  ". \n";
			}
		}
	}
}

// Displays all of the songs in a playlist
void SongManagerApp::commandIsPL() {
	string playlistTitle;
	int numberOfPlays, songID;
	vector<Song*> songPointerVector;

	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute PL command, because there's no playlist exits. \n";
	} else {
		cin.ignore();
		cout << "What is the title of the playlist you’d like to display? \n> ";
		getline(cin, playlistTitle);

	   // Output error message if the playlist user wants to display does not exit
		if (!SongManagerDriver_.hasPlaylist(playlistTitle)) {
			cout << "\"" << playlistTitle << "\"" << " playlist does not exist. \n";
		} else {
	      // Check is the Playlist has songs
			if (SongManagerDriver_.numberOfSongsInPlaylist(playlistTitle) == 0) {
				cout << "\"" << playlistTitle << "\" playlist has no songs. \n";

			} else {
				songPointerVector = SongManagerDriver_.getSpecificPlaylist(playlistTitle);

				for (unsigned int i = 0; i < songPointerVector.size(); ++i) {
					SongManagerDriver_.libraryHasSong(songPointerVector[i], songID, numberOfPlays);

					SongManagerDriver_.displaySongsInPlaylist(songPointerVector[i], numberOfPlays,
																	 songID, i);
				}
			}
		}
	}
}

// displays all the playlists, ordered by rating then the alphabeticallyby title
void SongManagerApp::commandIsPLS(){
	if (SongManagerDriver_.numberOfPlaylist() == 0) {
		cout << "Unable to execute PLS command, because no playlist exists. \n";
	} else {
		SongManagerDriver_.displayPlaylists();
	}
}

// Autogeneeates a playlist, based on user's selection, NAME, ARTIST, or ALBUM and MAGIC
void SongManagerApp::commandIsAG() {
	string listCategory;

	// Obtain the category type from user
	cout << "What is the category you’d like to autogenerate a playlist with? \n (NAME/ARTIST/ALBUM/MAGIC) \n> ";
	cin >> listCategory;

	toTopper(listCategory);
	// Caes 1, categoryType is NAME
	if (listCategory == "NAME") {
		SongManagerDriver_.autogeneratePlaylist(SongManagerDriver::NAME);

	} else if (listCategory == "ARTIST") { // Caes 2, categoryType is ARTIST
		SongManagerDriver_.autogeneratePlaylist(SongManagerDriver::ARTIST);

	} else if (listCategory == "ALBUM") { // Caes 3, categoryType is ALBUM
		SongManagerDriver_.autogeneratePlaylist(SongManagerDriver::ALBUM);

	} else if (listCategory == "MAGIC") { // Caes 4, categoryType is MAGIC
		SongManagerDriver_.autogeneratePlaylist(SongManagerDriver::MAGIC);
	} else {
		cout << "You entered an invalid criteria. \n";
	}
}

// Exports the song library and playliststo files
void SongManagerApp::commandIsEXP() {
	string libraryPath, playlistPath;

	// Obtain file path from user
	cout << "What is the name of the file you’d like to export your library to? \n> ";
	cin >> libraryPath;

	cout << "What is the name of the file you’d like to export your playlists to? \n> ";
	cin >> playlistPath;

	// Exports both files
	SongManagerDriver_.exportLibrary(libraryPath);
	SongManagerDriver_.exportPlaylist(playlistPath);

	cout << "Library and playlists exported successfully! \n";
}

string SongManagerApp::helpMenu() const {
	stringstream ss;

	ss << "AS: Purchases a new song to your library \n"
      << "RS: Removes a specific song from your library \n"
      << "AP: Creates an empty playlist \n"
      << "RP: Removes a specific playlist \n"
      << "RN: Renames a specific playlist \n"
      << "AG: Autogenerates a playlist based on song name, artist, album, or magic \n"
      << "ASP: Adds a specific song from your library to a playlist \n"
      << "RSP: Removes a specific song from a playlist \n"
      << "LB: Displays all the songs in your library \n"
      << "PLS: Displays all the of the playlists in alphabetical order of title \n"
      << "PL: Displays all the songs in a specific playlist in the order added \n"
      << "RT: Rates a specific playlist from 1 to 5 \n"
      << "PLY: Plays a specific song in your library a specified number of time \n"
      << "EXP: Exports the song library and playlists to files \n"
      << "HELP: Displays this help menu \n"
      << "EXIT: Exits the program \n";

	return ss.str();
}

// Converts any string to uppercase for convenience
void SongManagerApp::toTopper(string& anyString) {
	for (unsigned int i = 0; i < anyString.length(); i++) {
		anyString[i] = toupper(anyString[i]);
	}
}

#endif
