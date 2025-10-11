#include "chess_board.h"

#include <sstream>

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

void ChessBoard::updateAllBoards() {
    boards_[WHITE_ALL] = boards_[WHITE_PAWNS] | boards_[WHITE_ROOKS] |
                         boards_[WHITE_KNIGHTS] | boards_[WHITE_BISHOPS] |
                         boards_[WHITE_QUEEN] | boards_[WHITE_KING];

    boards_[BLACK_ALL] = boards_[BLACK_PAWNS] | boards_[BLACK_ROOKS] |
                         boards_[BLACK_KNIGHTS] | boards_[BLACK_BISHOPS] |
                         boards_[BLACK_QUEEN] | boards_[BLACK_KING];

    boards_[ALL] = boards_[WHITE_ALL] | boards_[BLACK_ALL];
}

void ChessBoard::setupInitialPosition() {
    boards_[WHITE_PAWNS] = Bitboard(0x00ff000000000000);
    boards_[BLACK_PAWNS] = Bitboard(0x000000000000ff00);
    boards_[WHITE_ROOKS] = Bitboard(0x8100000000000000);
    boards_[BLACK_ROOKS] = Bitboard(0x0000000000000081);
    boards_[WHITE_KNIGHTS] = Bitboard(0x4200000000000000);
    boards_[BLACK_KNIGHTS] = Bitboard(0x0000000000000042);
    boards_[WHITE_BISHOPS] = Bitboard(0x2400000000000000);
    boards_[BLACK_BISHOPS] = Bitboard(0x0000000000000024);
    boards_[WHITE_QUEEN] = Bitboard(0x1000000000000000);
    boards_[BLACK_QUEEN] = Bitboard(0x0000000000000010);
    boards_[WHITE_KING] = Bitboard(0x0800000000000000);
    boards_[BLACK_KING] = Bitboard(0x0000000000000008);

    updateAllBoards();
}

char ChessBoard::getPieceAt(int square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (boards_[boardsIndex].getBit(square)) {
            return pieceNames_[boardsIndex];
        }
    }
    return '.';
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

// section: pawn attacks

Bitboard whitePawnWestAttack(Bitboard pawn) { return (pawn & notAFile) >> 7; }
Bitboard whitePawnEastAttack(Bitboard pawn) { return (pawn & notHFile) >> 9; }

Bitboard blackPawnWestAttack(Bitboard pawn) { return (pawn & notAFile) << 9; }
Bitboard blackPawnEastAttack(Bitboard pawn) { return (pawn & notHFile) << 7; }

Bitboard ChessBoard::generateSinglePawnMaskAttacks(int square, int color) {
    Bitboard squareBitboard;
    squareBitboard.setBit(square);

    Bitboard attacks;

    if (color == WHITE) {
        attacks |= whitePawnWestAttack(squareBitboard);
        attacks |= whitePawnEastAttack(squareBitboard);
    } else {
        attacks |= blackPawnWestAttack(squareBitboard);
        attacks |= blackPawnEastAttack(squareBitboard);
    }

    return attacks;
}

void ChessBoard::generatePawnMaskAttacks() {
    for (int square = 0; square < 64; square++) {
        pawnMoveMasks[WHITE][square] =
            generateSinglePawnMaskAttacks(square, WHITE);
        pawnMoveMasks[BLACK][square] =
            generateSinglePawnMaskAttacks(square, BLACK);
    }
}

// endsection

// section: knights attacks

Bitboard knightNoNoEa(Bitboard knight) { return (knight & notHFile) >> 17; }
Bitboard knightNoEaEa(Bitboard knight) { return (knight & notGHFile) >> 10; }
Bitboard knightSoEaEa(Bitboard knight) { return (knight & notGHFile) << 6; }
Bitboard knightSoSoEa(Bitboard knight) { return (knight & notHFile) << 15; }
Bitboard knightNoNoWe(Bitboard knight) { return (knight & notAFile) >> 15; }
Bitboard knightNoWeWe(Bitboard knight) { return (knight & notABFile) >> 6; }
Bitboard knightSoWeWe(Bitboard knight) { return (knight & notABFile) << 10; }
Bitboard knightSoSoWe(Bitboard knight) { return (knight & notAFile) << 17; }

Bitboard ChessBoard::generateSingleKnightMaskAttacks(int square) {
    Bitboard squareBitboard;
    squareBitboard.setBit(square);

    Bitboard attacks;

    attacks |= knightNoNoEa(squareBitboard);
    attacks |= knightNoEaEa(squareBitboard);
    attacks |= knightSoEaEa(squareBitboard);
    attacks |= knightSoSoEa(squareBitboard);
    attacks |= knightNoNoWe(squareBitboard);
    attacks |= knightNoWeWe(squareBitboard);
    attacks |= knightSoWeWe(squareBitboard);
    attacks |= knightSoSoWe(squareBitboard);

    return attacks;
}

void ChessBoard::generateKnightMaskAttacks() {
    for (int square = 0; square < 64; square++) {
        knightMoveMasks[square] = generateSingleKnightMaskAttacks(square);
    }
}

// endsection