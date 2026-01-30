#pragma once

#include <string>
#include <vector>

#include "../bitboard/bitboard.h"
#include "../chessboard/chessboard-status.h"
#include "../chessboard/chessboard.h"
#include "../lib/color.h"
#include "../lib/move.h"
#include "../lib/piece.h"
#include "../lib/sliding-piece.h"
#include "../lib/square.h"

class Engine {
   public:
    void init();

    Bitboard setOccupancy(int index, Bitboard attacksMask);

    bool isSquareUnderAttackBy(const ChessboardStatus* const status,
                               Square square, Color color);
    void __printAttackedSquare(const ChessboardStatus* const status,
                               Color color);

    // Masks

    Bitboard generateSinglePawnMaskAttacks(Square square, Color color);
    Bitboard getSinglePawnAttacks(Square square, Color color);

    Bitboard generateSingleKnightAttacksMask(Square square);
    Bitboard getSingleKnightAttacks(Square square);

    Bitboard generateSingleKingAttacksMask(Square square);
    Bitboard getSingleKingAttacks(Square square);

    Bitboard generateSingleBishopRelevantOccupanciesMask(Square square);
    Bitboard generateSingleBishopAttacks(Square square, Bitboard blocks);
    Bitboard getSingleBishopAttacks(Square square, Bitboard occupancies);

    Bitboard generateSingleRookRelevantOccupanciesMask(Square square);
    Bitboard generateSingleRookAttacks(Square square, Bitboard blocks);
    Bitboard getSingleRookAttacks(Square square, Bitboard occupancies);

    Bitboard getSingleQueenAttacks(Square square, Bitboard occupancies);

    void generateSliderPiecesAttacks(SlidingPiece piece);

    // Move generation from status

    std::vector<u_int32_t> generateAllPseudoLegalMoves(
        const ChessboardStatus* const status);
    std::vector<Move> generateAllPseudoLegalMovesAsMoveList(
        const ChessboardStatus* const status);
    void __printMoves(std::vector<Move> moves);

    bool makeMove(ChessBoard* const chessboard, Move move);

    long long int perftDriver(ChessBoard& chessboard, const int depth);
    void perfTest(ChessBoard& chessboard, const int depth);

   private:
    // Masks

    Bitboard pawnAttacksMasks[2][64];

    Bitboard knightAttacksMasks[64];

    Bitboard kingAttacksMasks[64];

    Bitboard bishopRelevantOccupanciesMasks[64];
    Bitboard rookRelevantOccupanciesMasks[64];

    Bitboard bishopAttacksTable[64][512];
    Bitboard rookAttacksTable[64][4096];

    void generatePawnMaskAttacks();
    void generateKnightMaskMoves();
    void generateKingMaskMoves();

    // Move generation from status

    void generatePawnMoves(const ChessboardStatus* const status,
                           std::vector<u_int32_t>& moves);
    void generatePawnQuietMoves(const ChessboardStatus* const status,
                                Square from, std::vector<u_int32_t>& moves);
    void generatePawnCaptureMoves(const ChessboardStatus* const status,
                                  Square from, std::vector<u_int32_t>& moves);

    void generateKingMoves(const ChessboardStatus* const status,
                           std::vector<u_int32_t>& moves);
    void generateKingCastlingMoves(const ChessboardStatus* const status,
                                   std::vector<u_int32_t>& moves);
    bool canWhiteCastleKingSide(const ChessboardStatus* const status);
    bool canWhiteCastleQueenSide(const ChessboardStatus* const status);
    bool canBlackCastleKingSide(const ChessboardStatus* const status);
    bool canBlackCastleQueenSide(const ChessboardStatus* const status);

    void generateSliderAndLeaperMoves(const ChessboardStatus* const status,
                                      Piece piece,
                                      std::vector<u_int32_t>& moves);
    Bitboard getAttacksBoard(const ChessboardStatus* const status, Piece piece,
                             Square square);
};
