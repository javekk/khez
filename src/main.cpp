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
        "r1b2rk1/pppp1pbp/2n3p1/4p1q1/2B1Q3/3P4/PPPK1PPP/RN4NR w - - 0 9");
    std::vector<Move> moves = engine.generateAllMovesAsMoveList(&board.status);
    engine.__printMoves(moves);

    for (auto move : moves) {
        cout << board.toStringComplete();

        cout << move.toString() << endl;

        bool isLegal = engine.makeMove(&board, move);

        cout << board.toStringComplete();

        if (!isLegal) {
            cout << "Not a legal move!" << endl;
        } else {
            cout << "Legal move" << endl;
            board.undoLastMove();
        }

        getchar();
    }
}