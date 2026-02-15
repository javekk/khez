using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/color.h"
#include "lib/logger.h"
#include "lib/magic.h"
#include "lib/piece.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    logger.info("=============================================");
    logger.info("=============================================");
    logger.info("===== Khez Chess Engine - Bitboard Demo =====");
    logger.info("=============================================");
    logger.info("=============================================");

    Engine engine;
    engine.init();

    engine.setupInitialPosition();
    engine.parseUCIPosition(
        "position fen 4k3/8/8/8/8/8/6p1/5R1K w - - 0 1 moves f1e1 "
        "e8d8");

    logger.info(engine.board.toString());
    engine.parseFEN("4k3/8/8/8/8/8/6p1/5R1K w - - 0 1");
    logger.info(engine.board.toString());

    logger.info(engine.board.toString());

    while (true) {
        cout << "Waiting form position: ";
        string command;
        getline(cin, command);
        engine.parseUCIPosition(command);
        logger.info(engine.board.toStringComplete());
    }
}