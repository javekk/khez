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

    engine.parseFEN("4k3/Q7/4K3/8/8/8/8/8 w - - 0 1 ");
    cout << engine.board.toStringFancy();
    engine.__printMoves(engine.generateAllPseudoLegalMovesAsMoveList());
    cout << engine.evaluatePosition() << endl;
    cout << engine.searchBestMove(4).toStringUCI() << endl;

    // while (true) {
    //     cout << engine.board.toStringComplete();
    //     Move bestMove = engine.searchBestMove(2);
    //     cout << "Best move: " << bestMove.toStringUCI() << endl;
    //
    //    getchar();
    //
    //    engine.makeMove(bestMove);
    //}
}