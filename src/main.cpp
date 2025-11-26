using namespace std;

#include <bitset>
#include <iostream>

#include "bitboard/bitboard.h"
#include "chessboard/chessboard.h"
#include "engine/engine.h"
#include "lib/magic.h"
#include "lib/random.h"
#include "lib/square.h"

int main() {
    std::cout << "Khez Chess Engine - Bitboard Demo\n";
    std::cout << "==================================\n\n";

    ChessBoard board;
    board.setupInitialPosition();

    cout << board.toStringFancy() << endl;
    cout << "Side: " << (board.side ? "Black" : "White") << endl;
    cout << "Castling: " << board.availableCastleToString() << endl;
    cout << "Enpassant: "
         << (board.enpassant.has_value() ? squareMap.at(board.enpassant.value())
                                         : " ")
         << endl;

    return 0;
}