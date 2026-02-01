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
    ChessBoard board;

    void init();

    void emptyBoard();
    void setupInitialPosition();
    void parseFEN(const std::string FEN);

    Bitboard setOccupancy(int index, Bitboard attacksMask);

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

    // Move generation

    std::vector<u_int32_t> generateAllPseudoLegalMoves();
    std::vector<Move> generateAllPseudoLegalMovesAsMoveList();
    void __printMoves(std::vector<Move> moves);

    bool makeMove(Move move);

    bool isSquareUnderAttackBy(Square square, Color color);
    void __printAttackedSquare(Color color);

    long long int perftDriver(const int depth);
    void perfTest(const int depth);

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

    void generatePawnMoves(std::vector<u_int32_t>& moves);
    void generatePawnQuietMoves(Square from, std::vector<u_int32_t>& moves);
    void generatePawnCaptureMoves(Square from, std::vector<u_int32_t>& moves);

    void generateKingMoves(std::vector<u_int32_t>& moves);
    void generateKingCastlingMoves(std::vector<u_int32_t>& moves);
    bool canWhiteCastleKingSide();
    bool canWhiteCastleQueenSide();
    bool canBlackCastleKingSide();
    bool canBlackCastleQueenSide();

    void generateSliderAndLeaperMoves(Piece piece,
                                      std::vector<u_int32_t>& moves);
    Bitboard getAttacksBoard(Piece piece, Square square);
};
