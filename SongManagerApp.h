#ifndef SongManagerAPP_H
#define SongManagerAPP_H

#include <string>
#include <istream>
#include <iostream>

#include "SongManagerDriver.h"

using namespace std;

class SongManagerApp{
   public:
      void loadData(int argc, char *argv[]);
      void loadLibrary(string filePath);
      void loadPlaylist(string filePath);

      void startApp();

   private:
      // Private Helper functions for startApp function;
      void commandIsAS();
      void commandIsRS();
      void commandIsAP();
      void commandIsRP();
      void commandIsRN();
      void commandIsAG();
      void commandIsASP();
      void commandIsRSP();
      void commandIsLB();
      void commandIsPLS();
      void commandIsPL();
      void commandIsRT();
      void commandIsPLY();
      void commandIsEXP();

      string helpMenu() const;
      void toTopper(string& anystring);

      SongManagerDriver SongManagerDriver_;
};

#endif
