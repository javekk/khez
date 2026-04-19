#pragma once

#include <cstring>
#include <functional>
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

struct SearchContext {
    static constexpr int MAX_PLY = 64;
    int ply = 0;
    u_int64_t nodes = 0;

    uint32_t killerMoves[MAX_PLY][2] = {};
    int historyMoves[6][64] = {};

    uint32_t pvTable[MAX_PLY][MAX_PLY] = {};
    int pvLength[MAX_PLY] = {};

    bool foundPv = false;  // Found at least one good move
    bool followPv =
        true;  //  Should I bother searching for a PV move at this ply?
    bool scoringPv = false;  // Did I find the PV move in this move list, and
                             // should I boost its score?

    void initFromPreviousContenxt(const SearchContext* previousCtx) {
        if (previousCtx) {
            nodes = previousCtx->nodes;
            memcpy(pvTable, previousCtx->pvTable, sizeof(pvTable));
            memcpy(historyMoves, previousCtx->historyMoves,
                   sizeof(historyMoves));
            memcpy(killerMoves, previousCtx->killerMoves, sizeof(killerMoves));
        }
    }

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

    void updatePVLengthCurrentLevel() { pvLength[ply] = ply; }

    void updatePVTable(Move move) {
        pvTable[ply][ply] = move.toBinary();

        for (int nextPly = ply + 1; nextPly < pvLength[ply + 1]; nextPly++) {
            pvTable[ply][nextPly] = pvTable[ply + 1][nextPly];
        }

        pvLength[ply] = pvLength[ply + 1];
    }

    void resetScoring() { scoringPv = false; }

    void togglePVScoring(std::vector<Move> moves) {
        if (followPv) {
            followPv = false;
            for (Move move : moves) {
                if (pvTable[0][ply] == move.toBinary()) {
                    scoringPv = true;
                    followPv = true;
                }
            }
        }
    }
};

struct SearchResults {
    Move bestMove;
    uint32_t pvTable[64];
    int pvLength;
    int score;
    u_int64_t numberOfNodes;
    SearchContext ctx;
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
    SearchResults negamax(int depth,
                          const SearchContext* previousCtx = nullptr);
    SearchResults searchBestMove(
        int depth,
        std::function<void(const SearchResults&, int)> onIteration = nullptr);
    int evaluatePosition() const;
    int evaluateMaterialScore() const;
    int evaluateMoveScore(Move move, SearchContext& ctx) const;

    std::vector<Move> sortMoves(std::vector<Move> moves, SearchContext& ctx);

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

    int negamax_(int alpha, int beta, int depth, SearchContext& ctx);
    int quiescence_(int alpha, int beta, SearchContext& ctx);
};
