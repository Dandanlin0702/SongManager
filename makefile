CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall

SOURCES = SongManagerApp.cpp SongManagerDriver.cpp Playlist.cpp PlaylistLibrary.cpp Song.cpp SongLibrary.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = SongManager

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
