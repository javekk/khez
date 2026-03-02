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

    engine.parseFEN(
        "r3kb1r/pbqp1ppp/1pn1pn2/8/2B1P3/2N2N2/PPPP1PPP/R1BQ1RK1 w kq - 0 1");
    engine.parseUCIPosition(
        "position startpos moves g1f3 a7a6 d2d4 f7f6 e2e4 e8f7 f1c4 e7e6 f3d2 "
        "f8e7 b1c3 d8f8 d1h5 g7g6 h5a5 e7d8 d4d5 b8c6 d5c6 f7e7 c6b7 e7f7 "
        "b7a8q g8h6 a8c8 f7g7 c8d7 h6f7 c4e6 g7h6 e6f7 f8g8 f7g8 f6f5 d7d8 "
        "c7c6 d2b1");

    cout << engine.board.toStringFancy();
    engine.__printMoves(engine.generateAllPseudoLegalMovesAsMoveList());
    cout << engine.evaluatePosition() << endl;
    cout << engine.searchBestMove(4).toStringUCI() << endl;

    engine.parseFEN(
        "r1bq1rk1/pppp1ppp/2n2n2/2b1p3/8/1PN1PN2/PBQP1PPP/R3KB1R b KQ - 0 1");
    cout << engine.board.toStringFancy();
    cout << engine.evaluatePosition() << endl;
    cout << engine.searchBestMove(4).toStringUCI() << endl;

    // Move bestMove = engine.searchBestMove(4);
    // cout << "Best move: " << bestMove.toStringUCI() << endl;

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