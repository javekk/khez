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
        "2kr3r/pQp2p2/5npB/3pp3/2B1P1P1/2b2N2/PPP1NP1P/3R1KR1 b - - 0 20");

    cout << board.toStringComplete();
    engine.__printMoves(engine.generateAllMoves(&board.status));
}
