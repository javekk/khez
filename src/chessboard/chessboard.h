#pragma once

#include <optional>
#include <string>
#include <vector>

#include "../bitboard/bitboard.h"
#include "../lib/color.h"
#include "../lib/masks.h"
#include "../lib/move.h"
#include "../lib/piece.h"
#include "../lib/square.h"
#include "chessboard-status.h"

class ChessBoard {
   public:
    ChessBoard();

    ChessboardStatus status;

    std::vector<Move> moveHistory;
    std::vector<ChessboardStatus> statusHistory;

    void emptyBoard();
    void setupInitialPosition();
    void parseFEN(const std::string FEN);

    void makeMove(Move move);
    void undoLastMove();

    void setPieceAt(const Square square, const Piece piece, const Color color);
    void setPieceAt(const Square square, const char piece);
    void clearPieceAt(const Square square);
    char getPieceAt(const Square square) const;

    std::string toString() const;
    std::string getPieceAtFancy(const Square square) const;
    std::string toStringFancy() const;
    std::string availableCastleToString() const;
    std::string toStringComplete() const;

   private:
    char pieceNames_[12] = {'P', 'p', 'R', 'r', 'N', 'n',
                            'B', 'b', 'Q', 'q', 'K', 'k'};

    std::string pieceSymbols_[12] = {"♙", "♟︎", "♖", "♜", "♘", "♞",
                                     "♗", "♝", "♕", "♛", "♔", "♚"};

    void updateAllOccupancyBoards();
    void parseFENCastling(const std::string FEN_castling);

    void makeMoveCapture(Move& move);
    void makeMoveQuite(Move& move);
    void makeMoveCastlingChecks(Move& move);
};