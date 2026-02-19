#include "./ command-line-args.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

void parseSingleInput(char* arg, CommandLineArgs* args) {
    switch (arg[0]) {
        case '-':
            if (strcmp(arg, "--uci") == 0) {
                args->uciMode = true;
            } else if (strcmp(arg, "--log") == 0) {
                args->logEnable = true;
            } else if (strcmp(arg, "--no-log") == 0) {
                args->logEnable = false;
            } else if (strncmp(arg, "--log-level=", 12) == 0) {
                args->logLevel = std::stoi(arg + 12);
            } else {
                std::cout << "Unknown option: " << arg << std::endl;
            }
            break;

        default:
            std::cout << "Unknown argument: " << arg << std::endl;
            break;
    }
}

CommandLineArgs CommandLineParser::parseCommandLine(int argc, char* argv[]) {
    CommandLineArgs args;

    for (int i = 1; i < argc; ++i) {  // Start from 1 to skip program name
        parseSingleInput(argv[i], &args);
    }

    return args;
}
