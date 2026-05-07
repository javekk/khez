#pragma once

#include <string>
#include <vector>

struct CommandLineArgs {
    bool uciMode = false;
    bool benchMode = false;
    int logLevel = 4;
    bool logEnable = true;
    int depthSearch = 4;
    int benchDepth = 7;
};

class CommandLineParser {
   public:
    CommandLineArgs parseCommandLine(int argc, char* argv[]);
};
