#include "chessboard-status.h"

const std::map<std::pair<Color, Piece>, PieceBoard> sideColorToPieceBoardMap = {
    {{WHITE, PAWN}, WHITE_PAWNS},     {{WHITE, BISHOP}, WHITE_BISHOPS},
    {{WHITE, KNIGHT}, WHITE_KNIGHTS}, {{WHITE, ROOK}, WHITE_ROOKS},
    {{WHITE, KING}, WHITE_KING},      {{WHITE, QUEEN}, WHITE_QUEEN},
    {{BLACK, PAWN}, BLACK_PAWNS},     {{BLACK, BISHOP}, BLACK_BISHOPS},
    {{BLACK, KNIGHT}, BLACK_KNIGHTS}, {{BLACK, ROOK}, BLACK_ROOKS},
    {{BLACK, KING}, BLACK_KING},      {{BLACK, QUEEN}, BLACK_QUEEN},
};

const std::map<PieceBoard, std::pair<Color, Piece>> pieceBoardToSideColorMap = {
    {WHITE_PAWNS, {WHITE, PAWN}},     {WHITE_BISHOPS, {WHITE, BISHOP}},
    {WHITE_KNIGHTS, {WHITE, KNIGHT}}, {WHITE_ROOKS, {WHITE, ROOK}},
    {WHITE_KING, {WHITE, KING}},      {WHITE_QUEEN, {WHITE, QUEEN}},
    {BLACK_PAWNS, {BLACK, PAWN}},     {BLACK_BISHOPS, {BLACK, BISHOP}},
    {BLACK_KNIGHTS, {BLACK, KNIGHT}}, {BLACK_ROOKS, {BLACK, ROOK}},
    {BLACK_KING, {BLACK, KING}},      {BLACK_QUEEN, {BLACK, QUEEN}},
};
