#include "chessboard.h"

#include <sstream>

#include "../lib/masks.h"

ChessBoard::ChessBoard() {
    boards_[WHITE_PAWNS] = Bitboard();
    boards_[BLACK_PAWNS] = Bitboard();
    boards_[WHITE_ROOKS] = Bitboard();
    boards_[BLACK_ROOKS] = Bitboard();
    boards_[WHITE_KNIGHTS] = Bitboard();
    boards_[BLACK_KNIGHTS] = Bitboard();
    boards_[WHITE_BISHOPS] = Bitboard();
    boards_[BLACK_BISHOPS] = Bitboard();
    boards_[WHITE_QUEEN] = Bitboard();
    boards_[BLACK_QUEEN] = Bitboard();
    boards_[WHITE_KING] = Bitboard();
    boards_[BLACK_KING] = Bitboard();
}

void ChessBoard::setupInitialPosition() {
    boards_[WHITE_PAWNS] = whitePawns;
    boards_[BLACK_PAWNS] = blackPawns;
    boards_[WHITE_ROOKS] = whiteRooks;
    boards_[BLACK_ROOKS] = blackRooks;
    boards_[WHITE_KNIGHTS] = whiteKnights;
    boards_[BLACK_KNIGHTS] = blackKnights;
    boards_[WHITE_BISHOPS] = whiteBishops;
    boards_[BLACK_BISHOPS] = blackBishops;
    boards_[WHITE_QUEEN] = whiteQueen;
    boards_[BLACK_QUEEN] = blackQueen;
    boards_[WHITE_KING] = whiteKing;
    boards_[BLACK_KING] = blackKing;

    updateAllBoards();
}

std::string ChessBoard::toString() const {
    std::ostringstream oss;

    for (int rank = 7; rank >= 0; rank--) {
        oss << (rank + 1) << " | ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << getPieceAt(square) << " ";
        }
        oss << "\n";
    }

    oss << "    ---------------\n";
    oss << "    a b c d e f g h\n";

    return oss.str();
}

char ChessBoard::getPieceAt(int square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (boards_[boardsIndex].getBit(square)) {
            return pieceNames_[boardsIndex];
        }
    }
    return '.';
}

void ChessBoard::updateAllBoards() {
    boards_[WHITE_ALL] = boards_[WHITE_PAWNS] | boards_[WHITE_ROOKS] |
                         boards_[WHITE_KNIGHTS] | boards_[WHITE_BISHOPS] |
                         boards_[WHITE_QUEEN] | boards_[WHITE_KING];

    boards_[BLACK_ALL] = boards_[BLACK_PAWNS] | boards_[BLACK_ROOKS] |
                         boards_[BLACK_KNIGHTS] | boards_[BLACK_BISHOPS] |
                         boards_[BLACK_QUEEN] | boards_[BLACK_KING];

    boards_[ALL] = boards_[WHITE_ALL] | boards_[BLACK_ALL];
}