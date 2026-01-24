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
        "rnb1kbnr/pppp1ppp/8/4p3/4P1q1/8/PPPPQPPP/RNB1KBNR w KQkq "
        "- 0 3");
    std::vector<Move> moves = engine.generateAllMovesAsMoveList(&board.status);
    engine.__printMoves(moves);

    for (auto move : moves) {
        cout << board.toStringComplete();
        cout << move.toString() << endl;
        board.makeMove(move);
        cout << board.toStringComplete();
        board.undoLastMove();
        getchar();
    }
}