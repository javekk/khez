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
        "rnbqkbnr/1p1p1ppp/8/4p3/pPp1P3/5NP1/P1PPQPBP/RNB1K2R b "
        "KQkq b3 0 6");

    cout << board.toStringComplete();
    engine.__printMoves(engine.generateAllMoves(&board.status));
}
