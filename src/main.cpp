using namespace std;

#include <bitset>
#include <cstring>
#include <iostream>

#include "bitboard/bitboard.h"
#include "engine/chessboard/chessboard.h"
#include "engine/chessboard/color.h"
#include "engine/engine.h"
#include "lib/args/ command-line-args.h"
#include "lib/logger/logger.h"

int main(int argc, char* argv[]) {
    CommandLineParser parser;
    CommandLineArgs args = parser.parseCommandLine(argc, argv);

    bool uciMode = args.uciMode;

    logger.configure(LoggerProps{
        minLevel : static_cast<LogLevel>(args.logLevel),
        enabled : args.logEnable,
    });

    logger.info("=============================================");
    logger.info("=============================================");
    logger.info("===== Khez Chess Engine - Bitboard Demo =====");
    logger.info("=============================================");
    logger.info("=============================================");

    Engine engine;
    engine.init();

    if (uciMode) {
        logger.info("Starint in UCI mode");
        engine.setupInitialPosition();
        engine.UCI();
    }

    // DEBUG

    // engine.parseFEN("r1b3r1/pppp1k2/2n2p2/2b4Q/4P3/8/P4PPP/1RB2RK1 b - - 1
    // 15");
    engine.parseUCIPosition(
        "position startpos moves e2e3 a7a6 b1c3 a8a7 g1f3 f7f6 d2d4 g7g6 d4d5 "
        "e8f7 d1d4 e7e5 d4a7 f8e7 a7b8 g8h6 e3e4 d8g8 c1h6 g6g5 d5d6 f7g6 d6e7 "
        "g8f8 h6f8 g6h5");

    cout << engine.board.toStringComplete();
    engine.__printMoves(engine.generateAllPseudoLegalMovesAsMoveList());

    while (true) {
        cout << engine.board.toStringComplete();
        Move bestMove = engine.searchBestMove(2);
        cout << "Best move: " << bestMove.toStringUCI() << endl;

        getchar();

        engine.makeMove(bestMove);
    }
}