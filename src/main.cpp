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

    logger.info(engine.board.toStringComplete());

    while (true) {
        cout << "Waiting form move: ";
        string move;
        cin >> move;
        engine.parseMove(move);
        logger.info(engine.board.toStringComplete());
    }
}