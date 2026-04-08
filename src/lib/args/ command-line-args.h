#pragma once

#include <string>
#include <vector>

struct CommandLineArgs {
    bool uciMode = false;
    int logLevel = 0;
    bool logEnable = true;
    int depthSearch = 4;
};

class CommandLineParser {
   public:
    CommandLineArgs parseCommandLine(int argc, char* argv[]);
};
