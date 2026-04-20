#pragma once

#include <cstring>
#include <optional>

#include "../../bitboard/bitboard.h"
#include "./color.h"
#include "./piece.h"
#include "./square.h"

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

    ALL_PIECES,
    BOARDS_COUNTER,  // Must be last - used only for size
};

struct SideColorToPieceBoardMap {
    constexpr PieceBoard at(std::pair<Color, Piece> k) const {
        constexpr PieceBoard t[2][6] = {
            {WHITE_PAWNS, WHITE_ROOKS, WHITE_KNIGHTS, WHITE_BISHOPS,
             WHITE_QUEEN, WHITE_KING},
            {BLACK_PAWNS, BLACK_ROOKS, BLACK_KNIGHTS, BLACK_BISHOPS,
             BLACK_QUEEN, BLACK_KING},
        };
        return t[k.first][k.second];
    }
};
extern const SideColorToPieceBoardMap sideColorToPieceBoardMap;

struct PieceBoardToSideColorMap {
    std::pair<Color, Piece> at(PieceBoard b) const {
        constexpr std::pair<Color, Piece> t[12] = {
            {WHITE, PAWN},   {BLACK, PAWN},   {WHITE, ROOK},   {BLACK, ROOK},
            {WHITE, KNIGHT}, {BLACK, KNIGHT}, {WHITE, BISHOP}, {BLACK, BISHOP},
            {WHITE, QUEEN},  {BLACK, QUEEN},  {WHITE, KING},   {BLACK, KING},
        };
        return t[b];
    }
};
extern const PieceBoardToSideColorMap pieceBoardToSideColorMap;

struct CharToColorPieceMap {
    std::pair<Color, Piece> at(char c) const {
        switch (c) {
            case 'P':
                return {WHITE, PAWN};
            case 'R':
                return {WHITE, ROOK};
            case 'N':
                return {WHITE, KNIGHT};
            case 'B':
                return {WHITE, BISHOP};
            case 'Q':
                return {WHITE, QUEEN};
            case 'K':
                return {WHITE, KING};
            case 'p':
                return {BLACK, PAWN};
            case 'r':
                return {BLACK, ROOK};
            case 'n':
                return {BLACK, KNIGHT};
            case 'b':
                return {BLACK, BISHOP};
            case 'q':
                return {BLACK, QUEEN};
            case 'k':
                return {BLACK, KING};
        }
        __builtin_unreachable();
    }
    bool contains(char c) const { return strchr("PRNBQKprnbqk", c); }
};
extern const CharToColorPieceMap charToColorPieceMap;

enum Castle {
    WHITE_KINGSIDE = 0b0001,
    WHITE_QUEENSIDE = 0b0010,
    BLACK_KINGSIDE = 0b0100,
    BLACK_QUEENSIDE = 0b1000,
};

struct ChessboardStatus {
    Bitboard boards[BOARDS_COUNTER];

    std::optional<Color> side;
    std::optional<Square> enpassant;
    int8_t availableCastle;

    int halfmoveCounter;
    int fullmoveNumber;
};
