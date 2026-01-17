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
        "r3k2r/pppq1ppp/2n2n2/2bppb2/2BPP3/2N1BN2/PPPQ1PPP/R3K2R b KQkq - 11 "
        "8");

    cout << board.toStringComplete();
    engine.__printMoves(engine.generateAllMoves(&board.status));
}
