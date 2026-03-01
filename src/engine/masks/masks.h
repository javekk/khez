#pragma once

#include <map>

#include "../../bitboard/bitboard.h"
#include "../chessboard/piece.h"

extern const Bitboard whitePawns;
extern const Bitboard blackPawns;
extern const Bitboard whiteRooks;
extern const Bitboard blackRooks;
extern const Bitboard whiteKnights;
extern const Bitboard blackKnights;
extern const Bitboard whiteBishops;
extern const Bitboard blackBishops;
extern const Bitboard whiteQueen;
extern const Bitboard blackQueen;
extern const Bitboard whiteKing;
extern const Bitboard blackKing;

extern const Bitboard notAFile;
extern const Bitboard notHFile;

extern const Bitboard notABFile;
extern const Bitboard notGHFile;

extern const Bitboard firstRank;
extern const Bitboard eighthRank;

extern const int rookRelevantOccupanciesCounts[64];
extern const int bishopRelevantOccupanciesCounts[64];

extern const u_int64_t bishopMagicNumbers[64];
extern const u_int64_t rookMagicNumbers[64];

extern const int castlingRights[64];

extern const std::map<Piece, int> materialScoreMap;

extern const int pstPawnMg[64];
extern const int pstPawnEg[64];
extern const int pstKnightMg[64];
extern const int pstKnightEg[64];
extern const int pstBishopMg[64];
extern const int pstBishopEg[64];
extern const int pstRookMg[64];
extern const int pstRookEg[64];
extern const int pstQueenMg[64];
extern const int pstQueenEg[64];
extern const int pstKingMg[64];
extern const int pstKingEg[64];