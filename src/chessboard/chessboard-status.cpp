#include "chessboard-status.h"

const std::map<std::pair<Color, Piece>, PieceBoard> sideColorToPieceBoardMap = {
    {{WHITE, PAWN}, WHITE_PAWNS},     {{WHITE, BISHOP}, WHITE_BISHOPS},
    {{WHITE, KNIGHT}, WHITE_KNIGHTS}, {{WHITE, ROOK}, WHITE_ROOKS},
    {{WHITE, KING}, WHITE_KING},      {{WHITE, QUEEN}, WHITE_QUEEN},
    {{BLACK, PAWN}, BLACK_PAWNS},     {{BLACK, BISHOP}, BLACK_BISHOPS},
    {{BLACK, KNIGHT}, BLACK_KNIGHTS}, {{BLACK, ROOK}, BLACK_ROOKS},
    {{BLACK, KING}, BLACK_KING},      {{BLACK, QUEEN}, BLACK_QUEEN},
};
