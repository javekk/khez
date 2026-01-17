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
        "2kr3r/ppp2p2/3b1npB/1q1pp3/1QB1P1P1/1n3N2/PPP1NPbP/3RK1R1 w - - 3 17");

    cout << board.toStringComplete();
    engine.__printMoves(engine.generateAllMoves(&board.status));
}
