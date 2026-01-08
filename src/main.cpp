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
    board.parseFEN("8/2p3/8/8/2P5/8/1q6/8 w KQkq - 0 0");

    cout << board.toStringComplete();
    engine.__printAttackedSquare(&board.status, WHITE);
    engine.__printAttackedSquare(&board.status, BLACK);
}
