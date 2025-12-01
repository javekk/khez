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
    std::cout << "==================================\n\n";

    ChessBoard board;
    board.setupInitialPosition();
    board.setPieceAt(e4, QUEEN, WHITE);

    board.parseFEN(
        "rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1");

    cout << board.toStringFancy() << endl;
    cout << "Side: " << (board.side ? "Black" : "White") << endl;
    cout << "Castling: " << board.availableCastleToString() << endl;
    cout << "Enpassant: "
         << (board.enpassant.has_value() ? squareMap.at(board.enpassant.value())
                                         : " ")
         << endl;

    return 0;
}