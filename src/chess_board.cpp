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

// section: pawns

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

// section: knights

Bitboard knightNoNoEa(Bitboard knight) { return (knight & notHFile) >> 17; }
Bitboard knightNoEaEa(Bitboard knight) { return (knight & notGHFile) >> 10; }
Bitboard knightSoEaEa(Bitboard knight) { return (knight & notGHFile) << 6; }
Bitboard knightSoSoEa(Bitboard knight) { return (knight & notHFile) << 15; }
Bitboard knightNoNoWe(Bitboard knight) { return (knight & notAFile) >> 15; }
Bitboard knightNoWeWe(Bitboard knight) { return (knight & notABFile) >> 6; }
Bitboard knightSoWeWe(Bitboard knight) { return (knight & notABFile) << 10; }
Bitboard knightSoSoWe(Bitboard knight) { return (knight & notAFile) << 17; }

Bitboard ChessBoard::generateSingleKnightMaskMoves(int square) {
    Bitboard squareBitboard;
    squareBitboard.setBit(square);

    Bitboard moves;

    moves |= knightNoNoEa(squareBitboard);
    moves |= knightNoEaEa(squareBitboard);
    moves |= knightSoEaEa(squareBitboard);
    moves |= knightSoSoEa(squareBitboard);
    moves |= knightNoNoWe(squareBitboard);
    moves |= knightNoWeWe(squareBitboard);
    moves |= knightSoWeWe(squareBitboard);
    moves |= knightSoSoWe(squareBitboard);

    return moves;
}

void ChessBoard::generateKnightMaskMoves() {
    for (int square = 0; square < 64; square++) {
        knightMoveMasks[square] = generateSingleKnightMaskMoves(square);
    }
}

// endsection

// section: King

Bitboard kingNoWe(Bitboard king) { return (king & notAFile) >> 7; }
Bitboard kingNo(Bitboard king) { return king >> 8; }
Bitboard KingNoEa(Bitboard king) { return (king & notHFile) >> 9; }
Bitboard KingEa(Bitboard king) { return (king & notHFile) >> 1; }
Bitboard kingSoEa(Bitboard king) { return (king & notHFile) << 7; }
Bitboard kingSo(Bitboard king) { return king << 8; }
Bitboard kingSoWe(Bitboard king) { return (king & notAFile) << 9; }
Bitboard kingWe(Bitboard king) { return (king & notAFile) << 1; }

Bitboard ChessBoard::generateSingleKingMaskMoves(int square) {
    Bitboard squareBitboard;
    squareBitboard.setBit(square);

    Bitboard moves;
    moves |= kingNoWe(squareBitboard);
    moves |= kingNo(squareBitboard);
    moves |= KingNoEa(squareBitboard);
    moves |= KingEa(squareBitboard);
    moves |= kingSoEa(squareBitboard);
    moves |= kingSo(squareBitboard);
    moves |= kingSoWe(squareBitboard);
    moves |= kingWe(squareBitboard);

    return moves;
}

void ChessBoard::generateKingMaskMoves() {
    for (int square = 0; square < 64; square++) {
        kingMoveMasks[square] = generateSingleKingMaskMoves(square);
    }
}

// endsection

// section: Bishops

Bitboard ChessBoard::generateSingleBishopRelevantOccupanciesMask(int square) {
    Bitboard mask;

    int targetRank = square / 8;
    int targetFile = square % 8;

    for (int rank = targetRank + 1, file = targetFile + 1;
         rank <= 6 && file <= 6; rank++, file++) {
        Bitboard tMask;
        tMask.setBit(rank * 8 + file);
        mask |= tMask;
    }

    for (int rank = targetRank - 1, file = targetFile + 1;
         rank >= 1 && file <= 6; rank--, file++) {
        Bitboard tMask;
        tMask.setBit(rank * 8 + file);
        mask |= tMask;
    }

    for (int rank = targetRank + 1, file = targetFile - 1;
         rank <= 6 && file >= 1; rank++, file--) {
        Bitboard tMask;
        tMask.setBit(rank * 8 + file);
        mask |= tMask;
    }

    for (int rank = targetRank - 1, file = targetFile - 1;
         rank >= 1 && file >= 1; rank--, file--) {
        Bitboard tMask;
        tMask.setBit(rank * 8 + file);
        mask |= tMask;
    }

    return mask;
};

void ChessBoard::generateBishopRelevantOccupancies() {
    for (int square = 0; square < 64; square++) {
        bishopRelevantOccupanciesMasks[square] =
            generateSingleBishopRelevantOccupanciesMask(square);
    }
}

// endsection