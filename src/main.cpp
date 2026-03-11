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

    // engine.parseFEN("4k3/q7/4K3/8/8/8/8/8 w - - 0 1 ");
    // cout << engine.board.toStringFancy();
    // engine.__printMoves(engine.generateAllPseudoLegalMovesAsMoveList());
    // cout << engine.evaluatePosition() << endl;
    //  cout << engine.searchBestMove(4).first.toStringUCI() << endl

    engine.setupInitialPosition();
    engine.parseUCIPosition(
        "position startpos moves g1f3 g8f6 d2d4 d7d5 b1c3 b8c6 c1g5 c8g4 h2h3 "
        "g4e6 h1g1 h7h6 g5e3 h8g8 b2b3 b7b6 g2g4 g7g5");
    while (true) {
        cout << engine.board.toStringComplete();

        auto searchResult = engine.searchBestMove(1);
        Move bestMove = searchResult.bestMove;
        int score = searchResult.score;
        u_int64_t nodes = searchResult.numberOfNodes;

        cout << "score: " << score << endl;
        cout << "Best move: " << bestMove.toStringComplete() << endl;
        cout << "Searched Node: " << nodes << endl;
        getchar();

        engine.makeMove(bestMove);
    }
}