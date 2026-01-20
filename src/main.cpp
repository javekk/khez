using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/color.h"
#include "lib/magic.h"
#include "lib/piece.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "=================================\n\n";

    Engine engine;
    engine.init();

    ChessBoard board;
    board.parseFEN(
        "r3k2r/pPppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/"
        "R3K2R b KQkq - 0 0");

    cout << board.toStringComplete();
    engine.__printMoves(engine.generateAllMoves(&board.status));
}
