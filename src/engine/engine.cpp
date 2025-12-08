#include "engine.h"

#include <bitset>
#include <iostream>

#include "../lib/color.h"
#include "../lib/masks.h"
#include "../lib/sliding-piece.h"
#include "../lib/square.h"

void Engine::init() {
    generatePawnMaskAttacks();
    generateKnightMaskMoves();
    generateKingMaskMoves();
    generateSliderPiecesAttacks(IS_BISHOP);
    generateSliderPiecesAttacks(IS_ROOK);
}

#pragma region pawns

Bitboard whitePawnWestAttack(Bitboard pawn) { return (pawn & notAFile) >> 7; }
Bitboard whitePawnEastAttack(Bitboard pawn) { return (pawn & notHFile) >> 9; }

Bitboard blackPawnWestAttack(Bitboard pawn) { return (pawn & notAFile) << 9; }
Bitboard blackPawnEastAttack(Bitboard pawn) { return (pawn & notHFile) << 7; }

Bitboard Engine::generateSinglePawnMaskAttacks(int square, int color) {
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

void Engine::generatePawnMaskAttacks() {
    for (int square = 0; square < 64; square++) {
        pawnMoveMasks[WHITE][square] =
            generateSinglePawnMaskAttacks(square, WHITE);
        pawnMoveMasks[BLACK][square] =
            generateSinglePawnMaskAttacks(square, BLACK);
    }
}

#pragma endregion pawns

#pragma region knights

Bitboard knightNoNoEa(Bitboard knight) { return (knight & notHFile) >> 17; }
Bitboard knightNoEaEa(Bitboard knight) { return (knight & notGHFile) >> 10; }
Bitboard knightSoEaEa(Bitboard knight) { return (knight & notGHFile) << 6; }
Bitboard knightSoSoEa(Bitboard knight) { return (knight & notHFile) << 15; }
Bitboard knightNoNoWe(Bitboard knight) { return (knight & notAFile) >> 15; }
Bitboard knightNoWeWe(Bitboard knight) { return (knight & notABFile) >> 6; }
Bitboard knightSoWeWe(Bitboard knight) { return (knight & notABFile) << 10; }
Bitboard knightSoSoWe(Bitboard knight) { return (knight & notAFile) << 17; }

Bitboard Engine::generateSingleKnightMaskMoves(int square) {
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

void Engine::generateKnightMaskMoves() {
    for (int square = 0; square < 64; square++) {
        knightMoveMasks[square] = generateSingleKnightMaskMoves(square);
    }
}

#pragma endregion

#pragma region King

Bitboard kingNoWe(Bitboard king) { return (king & notAFile) >> 7; }
Bitboard kingNo(Bitboard king) { return king >> 8; }
Bitboard KingNoEa(Bitboard king) { return (king & notHFile) >> 9; }
Bitboard KingEa(Bitboard king) { return (king & notHFile) >> 1; }
Bitboard kingSoEa(Bitboard king) { return (king & notHFile) << 7; }
Bitboard kingSo(Bitboard king) { return king << 8; }
Bitboard kingSoWe(Bitboard king) { return (king & notAFile) << 9; }
Bitboard kingWe(Bitboard king) { return (king & notAFile) << 1; }

Bitboard Engine::generateSingleKingMaskMoves(int square) {
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

void Engine::generateKingMaskMoves() {
    for (int square = 0; square < 64; square++) {
        kingMoveMasks[square] = generateSingleKingMaskMoves(square);
    }
}

#pragma endregion

#pragma region Bishops

Bitboard northEastRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1, file = pieceFile + 1; rank <= 6 && file <= 6;
         rank++, file++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard southEastRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1, file = pieceFile + 1; rank >= 1 && file <= 6;
         rank--, file++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard northWestRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1, file = pieceFile - 1; rank <= 6 && file >= 1;
         rank++, file--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard southWestRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1, file = pieceFile - 1; rank >= 1 && file >= 1;
         rank--, file--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard Engine::generateSingleBishopRelevantOccupanciesMask(int square) {
    Bitboard mask;
    mask |= northEastRelevantOccupancies(square);
    mask |= southEastRelevantOccupancies(square);
    mask |= northWestRelevantOccupancies(square);
    mask |= southWestRelevantOccupancies(square);

    return mask;
}

Bitboard bishopNorthEastAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1, file = pieceFile + 1; rank < 8 && file < 8;
         rank++, file++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard bishopSouthEastAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1, file = pieceFile + 1; rank >= 0 && file < 8;
         rank--, file++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }

    return mask;
}

Bitboard bishopNorthWestAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1, file = pieceFile - 1; rank < 8 && file >= 0;
         rank++, file--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard bishopSouthWestAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1, file = pieceFile - 1; rank >= 0 && file >= 0;
         rank--, file--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard Engine::generateSingleBishopAttacks(int square, Bitboard blocks) {
    Bitboard attacks;
    attacks |= bishopNorthEastAttacks(square, blocks);
    attacks |= bishopSouthEastAttacks(square, blocks);
    attacks |= bishopNorthWestAttacks(square, blocks);
    attacks |= bishopSouthWestAttacks(square, blocks);

    return attacks;
}

Bitboard Engine::getSingleBishopAttacks(int square, Bitboard occupancies) {
    Bitboard t1 = occupancies & bishopRelevantOccupanciesMasks[square];
    Bitboard t2 = Bitboard(t1.getValue() * bishopMagicNumbers[square]);
    Bitboard t3 = Bitboard(t2.getValue() >>
                           (64 - bishopRelevantOccupanciesCounts[square]));
    return bishopAttacksTable[square][t3.getValue()];
}

#pragma endregion

#pragma region Rooks

Bitboard northRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1; rank < 7; rank++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;
    }
    return mask;
}

Bitboard southRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1; rank > 0; rank--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;
    }
    return mask;
}

Bitboard westRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int file = pieceFile - 1; file > 0; file--) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard eastRelevantOccupancies(int square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int file = pieceFile + 1; file < 7; file++) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard Engine::generateSingleRookRelevantOccupanciesMask(int square) {
    Bitboard mask;
    mask |= northRelevantOccupancies(square);
    mask |= southRelevantOccupancies(square);
    mask |= westRelevantOccupancies(square);
    mask |= eastRelevantOccupancies(square);

    return mask;
}

Bitboard rookNorthAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1; rank < 8; rank++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard rookSouthAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1; rank >= 0; rank--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard rookWestAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int file = pieceFile - 1; file >= 0; file--) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard rookEastAttacks(int square, Bitboard blocks) {
    Bitboard mask;

    int pieceFile = square % 8;
    int pieceRank = square / 8;

    for (int file = pieceFile + 1; file < 8; file++) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;

        if (!(blocks & tMask).isEmpty()) {
            break;
        }
    }
    return mask;
}

Bitboard Engine::generateSingleRookAttacks(int square, Bitboard blocks) {
    Bitboard attacks;
    attacks |= rookNorthAttacks(square, blocks);
    attacks |= rookSouthAttacks(square, blocks);
    attacks |= rookWestAttacks(square, blocks);
    attacks |= rookEastAttacks(square, blocks);

    return attacks;
}

Bitboard Engine::getSingleRookAttacks(int square, Bitboard occupancies) {
    Bitboard t1 = occupancies & rookRelevantOccupanciesMasks[square];
    Bitboard t2 = Bitboard(t1.getValue() * rookMagicNumbers[square]);
    Bitboard t3 =
        Bitboard(t2.getValue() >> (64 - rookRelevantOccupanciesCounts[square]));
    return rookAttacksTable[square][t3.getValue()];
}

#pragma endregion

#pragma region Sliding Pieces Logic
Bitboard Engine::setOccupancy(int index, Bitboard attacksMask) {
    Bitboard occupancyMask;
    int attacksMaskPopCount = attacksMask.popCount();

    for (int count = 0; count < attacksMaskPopCount; count++) {
        int square = attacksMask.leastSignificantBeatIndex();
        attacksMask.clearBit(square);

        if (index & (1 << count)) {
            occupancyMask |= Bitboard::fromSquare(square);
        }
    }

    return occupancyMask;
};

void Engine::generateSliderPiecesAttacks(SlidingPiece piece) {
    for (int square = 0; square < 64; square++) {
        bishopRelevantOccupanciesMasks[square] =
            generateSingleBishopRelevantOccupanciesMask(square);
        rookRelevantOccupanciesMasks[square] =
            generateSingleRookRelevantOccupanciesMask(square);

        Bitboard attackMask = piece == IS_BISHOP
                                  ? bishopRelevantOccupanciesMasks[square]
                                  : rookRelevantOccupanciesMasks[square];

        int relevantOccupanciesBits = attackMask.popCount();
        int occupancyIndices = (1 << relevantOccupanciesBits);

        for (int index = 0; index < occupancyIndices; index++) {
            if (piece == IS_BISHOP) {
                Bitboard occupancy = setOccupancy(index, attackMask);
                int magicIndex =
                    (occupancy.getValue() * bishopMagicNumbers[square]) >>
                    (64 - bishopRelevantOccupanciesCounts[square]);
                bishopAttacksTable[square][magicIndex] =
                    generateSingleBishopAttacks(square, occupancy);
            } else {
                Bitboard occupancy = setOccupancy(index, attackMask);
                int magicIndex =
                    (occupancy.getValue() * rookMagicNumbers[square]) >>
                    (64 - rookRelevantOccupanciesCounts[square]);
                rookAttacksTable[square][magicIndex] =
                    generateSingleRookAttacks(square, occupancy);
            }
        }
    }
}

#pragma endregion

#pragma region Queen

Bitboard Engine::getSingleQueenAttacks(int square, Bitboard occupancies) {
    Bitboard attacks;
    attacks |= getSingleBishopAttacks(square, occupancies);
    attacks |= getSingleRookAttacks(square, occupancies);

    return attacks;
}

#pragma endregion