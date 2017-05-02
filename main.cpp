#include "SongManagerApp.h"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	SongManagerApp SongManagerApp_;

	SongManagerApp_.loadData(argc, argv);
	SongManagerApp_.startApp();

	return 0;
}
