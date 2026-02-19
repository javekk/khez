using namespace std;

#include <bitset>
#include <cstring>
#include <iostream>

#include "bitboard/bitboard.h"
#include "engine/chessboard/chessboard.h"
#include "engine/chessboard/color.h"
#include "engine/engine.h"
#include "lib/logger/logger.h"

int main(int argc, char* argv[]) {
    logger.info("=============================================");
    logger.info("=============================================");
    logger.info("===== Khez Chess Engine - Bitboard Demo =====");
    logger.info("=============================================");
    logger.info("=============================================");

    bool uciMode = false;

    if (argc > 2) {
        for (int i = 0; i < argc; ++i) {
            if (strcmp(argv[i], "--uci") == 0) {
                uciMode = true;
            }
        }
    }

    Engine engine;
    engine.init();
    engine.setupInitialPosition();
    engine.parseFEN("r2k2Q1/ppp4p/2n5/4P3/3Pp3/N1P5/PP4PP/R1B1K2R b KQ - 0 16");
    cout << engine.board.toStringComplete();

    cout << "Material score: " << engine.evaluatePosition() << std::endl;

    if (uciMode) {
        engine.UCI();
    }
}