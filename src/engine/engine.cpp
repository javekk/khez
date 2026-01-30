#include "engine.h"

#include <bitset>
#include <chrono>
#include <cstdlib>
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

bool isOnRank(Square square, int rank) {
    return (square >= (rank - 1) * 8) && (square < rank * 8);
}

void addPromotionMoves(Square from, Square to, std::vector<u_int32_t>& moves) {
    bool isCapture = from % 8 != to % 8;

    moves.push_back(Move::createBinary(
        from, to,
        isCapture ? PAWN_CAPTURE_PROMOTION_TO_QUEEN : PAWN_PROMOTION_TO_QUEEN));
    moves.push_back(Move::createBinary(
        from, to,
        isCapture ? PAWN_CAPTURE_PROMOTION_TO_ROOK : PAWN_PROMOTION_TO_ROOK));
    moves.push_back(Move::createBinary(from, to,
                                       isCapture
                                           ? PAWN_CAPTURE_PROMOTION_TO_BISHOP
                                           : PAWN_PROMOTION_TO_BISHOP));
    moves.push_back(Move::createBinary(from, to,
                                       isCapture
                                           ? PAWN_CAPTURE_PROMOTION_TO_KNIGHT
                                           : PAWN_PROMOTION_TO_KNIGHT));
}

void addPawnPushMove(Square from, Square to, std::vector<u_int32_t>& moves) {
    bool isCapture = from % 8 != to % 8;
    bool isDoublePush = (!isCapture) && (abs((to / 8) - (from / 8)) == 2);
    MoveType moveType = isDoublePush ? PAWN_DOUBLE_PUSH
                                     : (isCapture ? PAWN_CAPTURE : PAWN_PUSH);
    moves.push_back(Move::createBinary(from, to, moveType));
}

void generateWhitePawnCaptures(const ChessboardStatus* status, Square from,
                               Square to, std::vector<u_int32_t>& moves) {
    if (to == status->enpassant) {
        moves.push_back(Move::createBinary(from, to, PAWN_CAPTURE_ENPASSANT));
        return;
    }

    if (isOnRank(from, 7)) {
        addPromotionMoves(from, to, moves);
        return;
    }
    addPawnPushMove(from, to, moves);
}

void generateBlackPawnCaptures(const ChessboardStatus* status, Square from,
                               Square to, std::vector<u_int32_t>& moves) {
    if (to == status->enpassant) {
        moves.push_back(Move::createBinary(from, to, PAWN_CAPTURE_ENPASSANT));
        return;
    }

    if (isOnRank(from, 2)) {
        addPromotionMoves(from, to, moves);
        return;
    }

    addPawnPushMove(from, to, moves);
}

void generateWhitePawnQuietMoves(const ChessboardStatus* status, Square from,
                                 std::vector<u_int32_t>& moves) {
    const Bitboard& allPieces = status->boards[ALL_PIECES];
    Square to = static_cast<Square>(from + 8);

    if (to > h8 || allPieces.getBit(to)) {
        return;
    }

    if (isOnRank(from, 7)) {
        addPromotionMoves(from, to, moves);
        return;
    }

    addPawnPushMove(from, to, moves);

    if (isOnRank(from, 2)) {
        Square doublePushTo = static_cast<Square>(to + 8);
        if (!allPieces.getBit(doublePushTo)) {
            addPawnPushMove(from, doublePushTo, moves);
        }
    }
}

void generateBlackPawnQuietMoves(const ChessboardStatus* status, Square from,
                                 std::vector<u_int32_t>& moves) {
    const Bitboard& allPieces = status->boards[ALL_PIECES];
    Square to = static_cast<Square>(from - 8);

    if (to < a1 || allPieces.getBit(to)) {
        return;
    }

    if (isOnRank(from, 2)) {
        addPromotionMoves(from, to, moves);
        return;
    }

    addPawnPushMove(from, to, moves);

    if (isOnRank(from, 7)) {
        Square doublePushTo = static_cast<Square>(to - 8);
        if (!allPieces.getBit(doublePushTo)) {
            addPawnPushMove(from, doublePushTo, moves);
        }
    }
}

void Engine::generatePawnMoves(const ChessboardStatus* const status,
                               std::vector<u_int32_t>& moves) {
    Color sideToMove = status->side.value();
    PieceBoard pawnPiece = (sideToMove == WHITE) ? WHITE_PAWNS : BLACK_PAWNS;
    Bitboard pawns = status->boards[pawnPiece];

    while (pawns.getValue()) {
        Square from = static_cast<Square>(pawns.leastSignificantBeatIndex());

        generatePawnQuietMoves(status, from, moves);
        generatePawnCaptureMoves(status, from, moves);
        pawns.clearBit(from);
    }
}

void Engine::generatePawnQuietMoves(const ChessboardStatus* const status,
                                    Square from,
                                    std::vector<u_int32_t>& moves) {
    Color sideToMove = status->side.value();
    if (sideToMove == WHITE) {
        generateWhitePawnQuietMoves(status, from, moves);
    } else {
        generateBlackPawnQuietMoves(status, from, moves);
    }
}

void Engine::generatePawnCaptureMoves(const ChessboardStatus* const status,
                                      Square from,
                                      std::vector<u_int32_t>& moves) {
    Color sideToMove = status->side.value();
    PieceBoard attackedSide = (sideToMove == WHITE) ? BLACK_ALL : WHITE_ALL;
    Bitboard attacks =
        pawnAttacksMasks[sideToMove][from] & status->boards[attackedSide];

    Bitboard enpassantAttacks;
    if (status->enpassant.has_value()) {
        enpassantAttacks = pawnAttacksMasks[sideToMove][from] &
                           Bitboard::fromSquare(status->enpassant.value());
    }

    Bitboard allCapture = attacks | enpassantAttacks;

    while (allCapture.getValue()) {
        Square to = static_cast<Square>(allCapture.leastSignificantBeatIndex());
        if (sideToMove == WHITE) {
            generateWhitePawnCaptures(status, from, to, moves);
        } else {
            generateBlackPawnCaptures(status, from, to, moves);
        }
        allCapture.clearBit(to);
    }
}

void Engine::generateKingMoves(const ChessboardStatus* const status,
                               std::vector<u_int32_t>& moves) {
    generateSliderAndLeaperMoves(status, KING, moves);
    generateKingCastlingMoves(status, moves);
}

bool Engine::canWhiteCastleKingSide(const ChessboardStatus* const status) {
    if (!(status->availableCastle & WHITE_KINGSIDE)) {
        return false;
    }

    bool emptyRank = !status->boards[ALL_PIECES].getBit(f1) &&
                     !status->boards[ALL_PIECES].getBit(g1);
    bool noAttacks = !isSquareUnderAttackBy(status, e1, BLACK) &&
                     !isSquareUnderAttackBy(status, f1, BLACK);
    // I do not check g1 (where the king lands) that is
    // resposability of the makeMove function

    return (emptyRank && noAttacks);
}

bool Engine::canWhiteCastleQueenSide(const ChessboardStatus* const status) {
    if (!(status->availableCastle & WHITE_QUEENSIDE)) {
        return false;
    }

    bool emptyRank = !status->boards[ALL_PIECES].getBit(d1) &&
                     !status->boards[ALL_PIECES].getBit(c1) &&
                     !status->boards[ALL_PIECES].getBit(b1);
    bool noAttacks = !isSquareUnderAttackBy(status, e1, BLACK) &&
                     !isSquareUnderAttackBy(status, d1, BLACK);
    // I do not check c1 (where the king lands) that is
    // resposability of the makeMove function

    return (emptyRank && noAttacks);
}

bool Engine::canBlackCastleKingSide(const ChessboardStatus* const status) {
    if (!(status->availableCastle & BLACK_KINGSIDE)) {
        return false;
    }

    bool emptyRank = !status->boards[ALL_PIECES].getBit(f8) &&
                     !status->boards[ALL_PIECES].getBit(g8);
    bool noAttacks = !isSquareUnderAttackBy(status, e8, WHITE) &&
                     !isSquareUnderAttackBy(status, f8, WHITE);
    // I do not check g8 (where the king lands) that is
    // resposability of the makeMove function

    return (emptyRank && noAttacks);
}

bool Engine::canBlackCastleQueenSide(const ChessboardStatus* const status) {
    if (!(status->availableCastle & BLACK_QUEENSIDE)) {
        return false;
    }

    bool emptyRank = !status->boards[ALL_PIECES].getBit(d8) &&
                     !status->boards[ALL_PIECES].getBit(c8) &&
                     !status->boards[ALL_PIECES].getBit(b8);
    bool noAttacks = !isSquareUnderAttackBy(status, e8, WHITE) &&
                     !isSquareUnderAttackBy(status, d8, WHITE);
    // I do not check c1 (where the king lands) that is
    // resposability of the makeMove function

    return (emptyRank && noAttacks);
}

void Engine::generateKingCastlingMoves(const ChessboardStatus* const status,
                                       std::vector<u_int32_t>& moves) {
    Color sideToMove = status->side.value();

    if (sideToMove == WHITE) {
        if (canWhiteCastleKingSide(status)) {
            moves.push_back(Move::createBinary(e1, g1, CASTLE_KINGSIDE));
        }
        if (canWhiteCastleQueenSide(status)) {
            moves.push_back(Move::createBinary(e1, c1, CASTLE_QUEENSIDE));
        }
    } else {
        if (canBlackCastleKingSide(status)) {
            moves.push_back(Move::createBinary(e8, g8, CASTLE_KINGSIDE));
        }
        if (canBlackCastleQueenSide(status)) {
            moves.push_back(Move::createBinary(e8, c8, CASTLE_QUEENSIDE));
        }
    }
}

Bitboard Engine::getAttacksBoard(const ChessboardStatus* const status,
                                 Piece piece, Square square) {
    switch (piece) {
        case KNIGHT:
            return getSingleKnightAttacks(square);
        case BISHOP:
            return getSingleBishopAttacks(square, status->boards[ALL_PIECES]);
        case ROOK:
            return getSingleRookAttacks(square, status->boards[ALL_PIECES]);
        case QUEEN:
            return getSingleQueenAttacks(square, status->boards[ALL_PIECES]);
        case KING:
            return getSingleKingAttacks(square);

        default:
            return Bitboard();
    }
}

MoveType getMoveType(Piece piece, bool isQuiet) {
    const std::map<Piece, MoveType> captureMoveMap = {
        {KNIGHT, KNIGHT_CAPTURE}, {KING, KING_CAPTURE},
        {ROOK, ROOK_CAPTURE},     {QUEEN, QUEEN_CAPTURE},
        {BISHOP, BISHOP_CAPTURE},
    };

    const std::map<Piece, MoveType> quietMoveMap = {
        {KNIGHT, KNIGHT_QUIET}, {KING, KING_QUIET},     {ROOK, ROOK_QUIET},
        {QUEEN, QUEEN_QUIET},   {BISHOP, BISHOP_QUIET},
    };

    return isQuiet ? quietMoveMap.at(piece) : captureMoveMap.at(piece);
}

void Engine::generateSliderAndLeaperMoves(const ChessboardStatus* const status,
                                          Piece piece,
                                          std::vector<u_int32_t>& moves) {
    Color sideToMove = status->side.value();

    Bitboard pieceBoard =
        status->boards[sideColorToPieceBoardMap.at({sideToMove, piece})];
    PieceBoard sideBoard = (sideToMove == WHITE) ? WHITE_ALL : BLACK_ALL;
    PieceBoard opponentBoard = (sideToMove == WHITE) ? BLACK_ALL : WHITE_ALL;

    while (pieceBoard.getValue()) {
        Square from =
            static_cast<Square>(pieceBoard.leastSignificantBeatIndex());
        Bitboard attacks =
            getAttacksBoard(status, piece, from) & ~(status->boards[sideBoard]);

        while (attacks.getValue()) {
            Square to =
                static_cast<Square>(attacks.leastSignificantBeatIndex());

            if (status->boards[opponentBoard].getBit(to)) {
                moves.push_back(
                    Move::createBinary(from, to, getMoveType(piece, false)));
            } else {
                moves.push_back(
                    Move::createBinary(from, to, getMoveType(piece, true)));
            }

            attacks.clearBit(to);
        }

        pieceBoard.clearBit(from);
    }
}

std::vector<u_int32_t> Engine::generateAllPseudoLegalMoves(
    const ChessboardStatus* const status) {
    std::vector<u_int32_t> moves;

    generatePawnMoves(status, moves);
    generateKingMoves(status, moves);
    generateSliderAndLeaperMoves(status, KNIGHT, moves);
    generateSliderAndLeaperMoves(status, BISHOP, moves);
    generateSliderAndLeaperMoves(status, ROOK, moves);
    generateSliderAndLeaperMoves(status, QUEEN, moves);

    return moves;
}

std::vector<Move> Engine::generateAllPseudoLegalMovesAsMoveList(
    const ChessboardStatus* const status) {
    std::vector<u_int32_t> binaryMoves = generateAllPseudoLegalMoves(status);
    std::vector<Move> moves;
    moves.reserve(binaryMoves.size());
    for (u_int32_t binary : binaryMoves) {
        moves.push_back(Move(binary));
    }
    return moves;
}

void Engine::__printMoves(std::vector<Move> moves) {
    std::cout << "Moves: \n";

    for (auto move : moves) {
        std::cout << move.toString() << std::endl;
    }

    std::cout << "Total moves " << moves.size() << std::endl;
}

bool Engine::makeMove(ChessBoard* const chessboard, Move move) {
    Color sideBeforeMove = chessboard->status.side.value();

    // Save status before making move (no history tracking)
    ChessboardStatus savedStatus = chessboard->status;

    chessboard->makeMove(move, false);  // Don't track history

    int king =
        (sideBeforeMove == WHITE)
            ? chessboard->status.boards[WHITE_KING].leastSignificantBeatIndex()
            : chessboard->status.boards[BLACK_KING].leastSignificantBeatIndex();

    bool isLegalMove = !isSquareUnderAttackBy(
        &chessboard->status, static_cast<Square>(king),
        chessboard->status.side.value());  // Side after move

    if (!isLegalMove) {
        // Restore status instead of undoLastMove
        chessboard->status = savedStatus;
    } else {
        // For legal moves, manually add to history (since we skipped it)
        chessboard->moveHistory.push_back(move);
        chessboard->statusHistory.push_back(savedStatus);
    }
    return isLegalMove;
}

long long int Engine::perftDriver(ChessBoard& chessboard,
                                  const int depth) {
    if (depth == 0) {
        return 1;
    }

    std::vector<u_int32_t> moves =
        generateAllPseudoLegalMoves(&chessboard.status);
    long long int nodes = 0;

    for (const auto& move : moves) {
        if (makeMove(&chessboard, move)) {
            nodes += perftDriver(chessboard, depth - 1);
            chessboard.undoLastMove();
        }
    }
    return nodes;
}

void Engine::perfTest(ChessBoard& chessboard, const int depth) {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<Move> rootMoves =
        generateAllPseudoLegalMovesAsMoveList(&chessboard.status);

    long long int totalNodes = 0;
    for (auto move : rootMoves) {
        if (makeMove(&chessboard, move)) {
            long long int moveCount = perftDriver(chessboard, depth - 1);
            Move m(move);
            std::cout << m.toString() << ": " << moveCount << std::endl;
            totalNodes += moveCount;
            chessboard.undoLastMove();
        }
    }

    auto endTime = std::chrono::high_resolution_clock::now();

    std::cout << std::endl
              << "Depth: " << depth << std::endl
              << "Total nodes: " << totalNodes << std::endl
              << "Time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     endTime - startTime)
                     .count()
              << "ms" << std::endl;
}

#pragma endregion