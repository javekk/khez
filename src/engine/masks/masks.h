#pragma once

#include <map>

#include "../../bitboard/bitboard.h"
#include "../chessboard/piece.h"

// ============================================================
// Starting-position bitboards
// ============================================================
// Each board has its piece set on the standard starting squares.
// Used by ChessBoard::setupInitialPosition().

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

// ============================================================
// File / rank masks
// ============================================================
// Used to clip attack masks at board edges (e.g. a knight on a-file
// can't jump west) and to detect promotions / pawn double-pushes.
//
// To generate file bitboards you can use this simple script,
// this one is for notAFile:
//
//   Bitboard not_a_file;
//   for (int rank = 0; rank < 8; rank++) {
//       for (int file = 0; file < 8; file++) {
//           if (file > 0) not_a_file.setBit(file + (8 * rank));
//       }
//   }
//   std::cout << not_a_file.toString() << std::endl;
//   std::cout << std::hex << not_a_file.getValue() << std::endl;

extern const Bitboard notAFile;
extern const Bitboard notHFile;
extern const Bitboard notABFile;  ///< Two leftmost files; for knight wrap.
extern const Bitboard notGHFile;  ///< Two rightmost files; for knight wrap.

extern const Bitboard firstRank;
extern const Bitboard eighthRank;

// ============================================================
// Magic bitboards (sliding-piece attacks)
// ============================================================
// For each square: number of relevant occupancy bits (so the magic
// index has the right width) and the magic multiplier itself.
// Together they hash an occupancy bitboard into a small index for
// the attack table lookup.
//
// Counts can be regenerated with:
//   for (int sq = 0; sq < 64; sq++)
//     counts[sq] =
//       engine.generateSingleRookRelevantOccupanciesMask(sq).popCount();
//
// Magic numbers are produced by the routine in magic.h using the
// random seed 1804289383.

extern const int rookRelevantOccupanciesCounts[64];
extern const int bishopRelevantOccupanciesCounts[64];

extern const u_int64_t bishopMagicNumbers[64];
extern const u_int64_t rookMagicNumbers[64];

// ============================================================
// Castling rights mask
// ============================================================
// Indexed by square. AND-ed with the current castling rights after
// every move/capture: any piece moving from or onto a square that
// belongs to a rook / king starting square clears the matching
// right (e.g. moving the white king clears both white rights;
// capturing on h8 clears black king-side).

extern const int castlingRights[64];

// ============================================================
// Evaluation tables
// ============================================================

extern const std::map<Piece, int> materialScoreMap;

// Piece-Square Tables: per-piece, per-square positional bonus.
// Two phases blended via tapered eval (see Engine::evaluatePosition):
//   Mg = middlegame, Eg = endgame.
// Tables are oriented from white's POV; black squares are mirrored
// at lookup time via XOR 56 (flip rank, keep file).
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

// MVV/LVA: Most Valuable Victim / Least Valuable Attacker.
//
// Used to order capture moves during search: capturing a more
// valuable piece is searched first, ties broken by preferring the
// cheapest attacker (it risks less if recaptured). Example: PxQ
// ranks above QxP: same queen won, but if defended PxQ keeps the
// queen while QxP loses it for a pawn.
//
// Score layout: tens digit = victim value, units digit = (6 -
// attacker value), so victim dominates and the cheaper attacker
// wins on ties.
//
//   (Victims) Pawn Knight Bishop   Rook  Queen   King
// (Attackers)
//      Pawn   105    205    305    405    505    605
//    Knight   104    204    304    404    504    604
//    Bishop   103    203    303    403    503    603
//      Rook   102    202    302    402    502    602
//     Queen   101    201    301    401    501    601
//      King   100    200    300    400    500    600
//
// Indexed [attacker][victim].
extern const std::map<std::pair<Piece, Piece>, int> mvvLva;
