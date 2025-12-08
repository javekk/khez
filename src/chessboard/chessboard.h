#pragma once

#include <optional>
#include <string>

#include "../bitboard/bitboard.h"
#include "../lib/color.h"
#include "../lib/piece.h"
#include "../lib/square.h"

enum PieceBoard {
    WHITE_PAWNS,
    BLACK_PAWNS,
    WHITE_ROOKS,
    BLACK_ROOKS,
    WHITE_KNIGHTS,
    BLACK_KNIGHTS,
    WHITE_BISHOPS,
    BLACK_BISHOPS,
    WHITE_QUEEN,
    BLACK_QUEEN,
    WHITE_KING,
    BLACK_KING,

    WHITE_ALL,
    BLACK_ALL,

    ALL,
};

enum Castle {
    WHITE_KINGSIDE = 0b0001,
    WHITE_QUEENSIDE = 0b0010,
    BLACK_KINGSIDE = 0b0100,
    BLACK_QUEENSIDE = 0b1000,
};

class ChessBoard {
   public:
    ChessBoard();

    std::optional<Color> side;
    std::optional<Square> enpassant;
    int8_t availableCastle;

    int halfmoveCounter;
    int fullmoveNumber;

    void emptyBoard();
    void setupInitialPosition();
    void parseFEN(const std::string FEN);

    void setPieceAt(const int square, const Piece piece, const Color color);
    void setPieceAt(const int square, const char piece);
    void clearPieceAt(const int square);

    char getPieceAt(const int square) const;
    std::string toString() const;
    std::string getPieceAtFancy(const int square) const;
    std::string toStringFancy() const;
    std::string availableCastleToString() const;
    std::string toStringComplete() const;

   private:
    Bitboard boards_[15];

    char pieceNames_[12] = {'P', 'p', 'R', 'r', 'N', 'n',
                            'B', 'b', 'Q', 'q', 'K', 'k'};

    std::string pieceSymbols_[12] = {"♙", "♟︎", "♖", "♜", "♘", "♞",
                                     "♗", "♝", "♕", "♛", "♔", "♚"};

    void updateAllOccupancyBoards();
    void parseFENCastling(const std::string FEN_castling);
};