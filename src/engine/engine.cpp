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

Bitboard Engine::generateSinglePawnMaskAttacks(Square square, Color color) {
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
        pawnAttacksMasks[WHITE][square] =
            generateSinglePawnMaskAttacks(static_cast<Square>(square), WHITE);
        pawnAttacksMasks[BLACK][square] =
            generateSinglePawnMaskAttacks(static_cast<Square>(square), BLACK);
    }
}

Bitboard Engine::getSinglePawnAttacks(Square square, Color color) {
    return pawnAttacksMasks[color][square];
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

Bitboard Engine::generateSingleKnightAttacksMask(Square square) {
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
        knightAttacksMasks[square] =
            generateSingleKnightAttacksMask(static_cast<Square>(square));
    }
}

Bitboard Engine::getSingleKnightAttacks(Square square) {
    return knightAttacksMasks[square];
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

Bitboard Engine::generateSingleKingAttacksMask(Square square) {
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
        kingAttacksMasks[square] =
            generateSingleKingAttacksMask(static_cast<Square>(square));
    }
}

Bitboard Engine::getSingleKingAttacks(Square square) {
    return kingAttacksMasks[square];
}

#pragma endregion

#pragma region Bishops

Bitboard northEastRelevantOccupancies(Square square) {
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

Bitboard southEastRelevantOccupancies(Square square) {
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

Bitboard northWestRelevantOccupancies(Square square) {
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

Bitboard southWestRelevantOccupancies(Square square) {
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

Bitboard Engine::generateSingleBishopRelevantOccupanciesMask(Square square) {
    Bitboard mask;
    mask |= northEastRelevantOccupancies(square);
    mask |= southEastRelevantOccupancies(square);
    mask |= northWestRelevantOccupancies(square);
    mask |= southWestRelevantOccupancies(square);

    return mask;
}

Bitboard bishopNorthEastAttacks(Square square, Bitboard blocks) {
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

Bitboard bishopSouthEastAttacks(Square square, Bitboard blocks) {
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

Bitboard bishopNorthWestAttacks(Square square, Bitboard blocks) {
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

Bitboard bishopSouthWestAttacks(Square square, Bitboard blocks) {
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

Bitboard Engine::generateSingleBishopAttacks(Square square, Bitboard blocks) {
    Bitboard attacks;
    attacks |= bishopNorthEastAttacks(square, blocks);
    attacks |= bishopSouthEastAttacks(square, blocks);
    attacks |= bishopNorthWestAttacks(square, blocks);
    attacks |= bishopSouthWestAttacks(square, blocks);

    return attacks;
}

Bitboard Engine::getSingleBishopAttacks(Square square, Bitboard occupancies) {
    Bitboard t1 = occupancies & bishopRelevantOccupanciesMasks[square];
    Bitboard t2 = Bitboard(t1.getValue() * bishopMagicNumbers[square]);
    Bitboard t3 = Bitboard(t2.getValue() >>
                           (64 - bishopRelevantOccupanciesCounts[square]));
    return bishopAttacksTable[square][t3.getValue()];
}

#pragma endregion

#pragma region Rooks

Bitboard northRelevantOccupancies(Square square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank + 1; rank < 7; rank++) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;
    }
    return mask;
}

Bitboard southRelevantOccupancies(Square square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int rank = pieceRank - 1; rank > 0; rank--) {
        Bitboard tMask = Bitboard::fromSquare(rank * 8 + pieceFile);
        mask |= tMask;
    }
    return mask;
}

Bitboard westRelevantOccupancies(Square square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int file = pieceFile - 1; file > 0; file--) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard eastRelevantOccupancies(Square square) {
    Bitboard mask;

    int pieceRank = square / 8;
    int pieceFile = square % 8;

    for (int file = pieceFile + 1; file < 7; file++) {
        Bitboard tMask = Bitboard::fromSquare(pieceRank * 8 + file);
        mask |= tMask;
    }
    return mask;
}

Bitboard Engine::generateSingleRookRelevantOccupanciesMask(Square square) {
    Bitboard mask;
    mask |= northRelevantOccupancies(square);
    mask |= southRelevantOccupancies(square);
    mask |= westRelevantOccupancies(square);
    mask |= eastRelevantOccupancies(square);

    return mask;
}

Bitboard rookNorthAttacks(Square square, Bitboard blocks) {
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

Bitboard rookSouthAttacks(Square square, Bitboard blocks) {
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

Bitboard rookWestAttacks(Square square, Bitboard blocks) {
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

Bitboard rookEastAttacks(Square square, Bitboard blocks) {
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

Bitboard Engine::generateSingleRookAttacks(Square square, Bitboard blocks) {
    Bitboard attacks;
    attacks |= rookNorthAttacks(square, blocks);
    attacks |= rookSouthAttacks(square, blocks);
    attacks |= rookWestAttacks(square, blocks);
    attacks |= rookEastAttacks(square, blocks);

    return attacks;
}

Bitboard Engine::getSingleRookAttacks(Square square, Bitboard occupancies) {
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
            generateSingleBishopRelevantOccupanciesMask(
                static_cast<Square>(square));
        rookRelevantOccupanciesMasks[square] =
            generateSingleRookRelevantOccupanciesMask(
                static_cast<Square>(square));

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
                    generateSingleBishopAttacks(static_cast<Square>(square),
                                                occupancy);
            } else {
                Bitboard occupancy = setOccupancy(index, attackMask);
                int magicIndex =
                    (occupancy.getValue() * rookMagicNumbers[square]) >>
                    (64 - rookRelevantOccupanciesCounts[square]);
                rookAttacksTable[square][magicIndex] =
                    generateSingleRookAttacks(static_cast<Square>(square),
                                              occupancy);
            }
        }
    }
}

#pragma endregion

#pragma region Queen

Bitboard Engine::getSingleQueenAttacks(Square square, Bitboard occupancies) {
    Bitboard attacks;
    attacks |= getSingleBishopAttacks(square, occupancies);
    attacks |= getSingleRookAttacks(square, occupancies);

    return attacks;
}

#pragma endregion

#pragma region Attacks

bool Engine::isSquareUnderAttackBy(const ChessboardStatus* const status,
                                   Square square, Color color) {
    if ((color == WHITE) &&
        (getSinglePawnAttacks(square, BLACK) & status->boards[WHITE_PAWNS])
            .getValue()) {
        return true;
    }

    if ((color == BLACK) &&
        (getSinglePawnAttacks(square, WHITE) & status->boards[BLACK_PAWNS])
            .getValue()) {
        return true;
    }

    if ((getSingleKnightAttacks(square) &
         status->boards[color == BLACK ? BLACK_KNIGHTS : WHITE_KNIGHTS])
            .getValue()) {
        return true;
    }

    if ((getSingleKingAttacks(square) &
         status->boards[color == BLACK ? BLACK_KING : WHITE_KING])
            .getValue()) {
        return true;
    }

    if ((getSingleBishopAttacks(square, status->boards[ALL_PIECES]) &
         status->boards[color == BLACK ? BLACK_BISHOPS : WHITE_BISHOPS])
            .getValue()) {
        return true;
    }

    if ((getSingleRookAttacks(square, status->boards[ALL_PIECES]) &
         status->boards[color == BLACK ? BLACK_ROOKS : WHITE_ROOKS])
            .getValue()) {
        return true;
    }

    if ((getSingleQueenAttacks(square, status->boards[ALL_PIECES]) &
         status->boards[color == BLACK ? BLACK_QUEEN : WHITE_QUEEN])
            .getValue()) {
        return true;
    }

    return false;
}

void Engine::__printAttackedSquare(const ChessboardStatus* const status,
                                   Color color) {
    std::string _color = color == WHITE ? "White" : "Black";
    std::cout << _color << " is attacking : [ ";
    for (int square = 0; square < 64; square++) {
        Square _square = static_cast<Square>(square);
        if (isSquareUnderAttackBy(status, _square, color)) {
            std::cout << squareMap.at(_square) << " ";
        }
    }
    std::cout << " ]\n";
}

#pragma endregion

#pragma region Move generation

std::vector<std::tuple<Move, MoveType>> Engine::generateMoves(
    const ChessboardStatus* const status) {
    std::vector<std::tuple<Move, MoveType>> moves;
    Bitboard attacksBoard;

    // Loop over all the bitboard
    for (int piece = 0; piece < 12; piece++) {
        Bitboard pieceBoard = status->boards[piece];

        // Generate white pawns and side castling moves
        if (status->side == WHITE) {
            if (piece == WHITE_PAWNS) {
                while (pieceBoard.getValue()) {
                    Square sourceSquare = static_cast<Square>(
                        pieceBoard.leastSignificantBeatIndex());

                    Square targetSquareCandidate = static_cast<Square>(
                        sourceSquare + 8);  // move forward 1 square

                    // Quite moves
                    if ((targetSquareCandidate < h8) &&
                        !(status->boards[ALL_PIECES].getBit(
                            targetSquareCandidate))) {
                        if (sourceSquare >= a7 && sourceSquare <= h7) {
                            // Pawn promotion
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_BISHOP));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_ROOK));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_KNIGHT));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_QUEEN));
                        } else {
                            // Pawn push
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PUSH));

                            if (sourceSquare >= a2 && sourceSquare <= h2 &&
                                !(status->boards[ALL_PIECES].getBit(
                                    targetSquareCandidate + 8))) {
                                Square targetSquare = static_cast<Square>(
                                    targetSquareCandidate + 8);
                                moves.push_back(std::make_tuple(
                                    Move{sourceSquare, targetSquare},
                                    PAWN_DOUBLE_PUSH));
                            }
                        }
                    }

                    pieceBoard.clearBit(sourceSquare);
                }
            }
        }

        // Generate black pawns and side castling moves
        if (status->side == BLACK) {
            if (piece == BLACK_PAWNS) {
                while (pieceBoard.getValue()) {
                    Square sourceSquare = static_cast<Square>(
                        pieceBoard.leastSignificantBeatIndex());

                    Square targetSquareCandidate = static_cast<Square>(
                        sourceSquare - 8);  // move forward 1 square

                    // Quite moves
                    if ((targetSquareCandidate > a1) &&
                        !(status->boards[ALL_PIECES].getBit(
                            targetSquareCandidate))) {
                        if (sourceSquare >= a2 && sourceSquare <= h2) {
                            // Pawn promotion
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_BISHOP));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_ROOK));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_KNIGHT));
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PROMOTION_TO_QUEEN));
                        } else {
                            // Pawn push
                            moves.push_back(std::make_tuple(
                                Move{sourceSquare, targetSquareCandidate},
                                PAWN_PUSH));

                            if (sourceSquare >= a7 && sourceSquare <= h7 &&
                                !(status->boards[ALL_PIECES].getBit(
                                    targetSquareCandidate - 8))) {
                                Square targetSquare = static_cast<Square>(
                                    targetSquareCandidate - 8);
                                moves.push_back(std::make_tuple(
                                    Move{sourceSquare, targetSquare},
                                    PAWN_DOUBLE_PUSH));
                            }
                        }
                    }

                    pieceBoard.clearBit(sourceSquare);
                }
            }
        }

        // Generate knight moves

        // Generate bishop moves

        // Generate rook moves

        // Generate queen moves

        // Generate king moves
    }

    return moves;
}

void Engine::__printMoves(std::vector<std::tuple<Move, MoveType>> moves) {
    std::cout << "Moves: \n";
    std::map<MoveType, std::string> moveDescriptionMap = {
        {PAWN_PUSH, "Pawn push"},
        {PAWN_DOUBLE_PUSH, "Double pawn push"},
        {PAWN_PROMOTION_TO_BISHOP, "Pawn promotion to Bishop"},
        {PAWN_PROMOTION_TO_ROOK, "Pawn promotion to Rook"},
        {PAWN_PROMOTION_TO_KNIGHT, "Pawn promotion to Knight"},
        {PAWN_PROMOTION_TO_QUEEN, "Pawn promotion to Queen"},
    };
    for (auto [move, moveType] : moves) {
        std::cout << " - " << moveDescriptionMap.at(moveType) << " from "
                  << squareMap.at(move.sourceSquare) << " to "
                  << squareMap.at(move.targetSquare) << std::endl;
    }
}

#pragma endregion