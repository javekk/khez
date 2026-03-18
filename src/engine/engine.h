#pragma once

#include <string>
#include <vector>

#include "../bitboard/bitboard.h"
#include "./chessboard/chessboard-status.h"
#include "./chessboard/chessboard.h"
#include "./chessboard/color.h"
#include "./chessboard/piece.h"
#include "./chessboard/sliding-piece.h"
#include "./chessboard/square.h"
#include "./move/move.h"

struct SearchResults {
    Move bestMove;
    int score;
    u_int64_t numberOfNodes;
};

struct SearchContext {
    static constexpr int MAX_PLY = 64;

    uint32_t killerMoves[MAX_PLY][2] = {};
    int historyMoves[6][64] = {};
    int ply = 0;
    u_int64_t nodes = 0;

    void storeKillerMove(Move move) {
        killerMoves[ply][1] = killerMoves[ply][0];
        killerMoves[ply][0] = move.toBinary();
    }

    void updateHistoryMove(Move move, int depth) {
        historyMoves[static_cast<int>(move.piece)][move.to] += depth * depth;
    }

    bool isKillerMove0(Move move) const {
        return killerMoves[ply][0] == move.toBinary();
    }
    bool isKillerMove1(Move move) const {
        return killerMoves[ply][1] == move.toBinary();
    }
};

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
    void undoMove();

    bool isSquareUnderAttackBy(Square square, Color color);
    void __printAttackedSquare(Color color);

    // Move search
    SearchResults negamax(int depth);
    SearchResults searchBestMove(int depth);
    int evaluatePosition() const;
    int evaluateMaterialScore() const;
    int evaluateMoveScore(Move move, const SearchContext& ctx) const;

    std::vector<Move> sortMoves(std::vector<Move> moves,
                                const SearchContext& ctx);

    // UCI

    bool parseUCIGo(std::string input);
    bool parseUCIPosition(std::string input);
    bool parseUCIMove(std::string input);
    bool UCIok();
    void UCI();

    // perf tests

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

    bool isMyKingInCheck();
    bool isOpponentKingInCheck();

    // Search

    int negamax_(int alpha, int beta, int depth, uint32_t* outBestMove,
                 SearchContext& ctx);
    int quiescence_(int alpha, int beta, SearchContext& ctx);
};
