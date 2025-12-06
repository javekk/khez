#include "chessboard.h"

#include <string.h>

#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include "../lib/masks.h"

ChessBoard::ChessBoard() {
    boards_[WHITE_PAWNS] = Bitboard();
    boards_[BLACK_PAWNS] = Bitboard();
    boards_[WHITE_ROOKS] = Bitboard();
    boards_[BLACK_ROOKS] = Bitboard();
    boards_[WHITE_KNIGHTS] = Bitboard();
    boards_[BLACK_KNIGHTS] = Bitboard();
    boards_[WHITE_BISHOPS] = Bitboard();
    boards_[BLACK_BISHOPS] = Bitboard();
    boards_[WHITE_QUEEN] = Bitboard();
    boards_[BLACK_QUEEN] = Bitboard();
    boards_[WHITE_KING] = Bitboard();
    boards_[BLACK_KING] = Bitboard();
}

void ChessBoard::setupInitialPosition() {
    side = WHITE;

    boards_[WHITE_PAWNS] = whitePawns;
    boards_[BLACK_PAWNS] = blackPawns;
    boards_[WHITE_ROOKS] = whiteRooks;
    boards_[BLACK_ROOKS] = blackRooks;
    boards_[WHITE_KNIGHTS] = whiteKnights;
    boards_[BLACK_KNIGHTS] = blackKnights;
    boards_[WHITE_BISHOPS] = whiteBishops;
    boards_[BLACK_BISHOPS] = blackBishops;
    boards_[WHITE_QUEEN] = whiteQueen;
    boards_[BLACK_QUEEN] = blackQueen;
    boards_[WHITE_KING] = whiteKing;
    boards_[BLACK_KING] = blackKing;

    updateAllOccupancyBoards();

    availableCastle = 0b1111;
}

std::vector<std::string> split(std::string s, const char* delim) {
    std::vector<std::string> result;

    char* token = strtok(s.data(), delim);
    while (token != nullptr) {
        result.push_back(std::string(token));
        token = strtok(nullptr, delim);
    }

    return result;
}

// rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1
// rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2
void ChessBoard::parseFEN(const std::string FEN) {
    std::vector<std::string> result = split(FEN, " ");

    // Parse chessboard
    std::string board = result[0];
    int rankIndex = 7;
    int fileIndex = 0;
    for (auto c : board) {
        if (c == '/') {
            fileIndex = 0;
            rankIndex--;
        } else if (strchr(pieceNames_, c) != NULL) {
            int square = (rankIndex * 8) + fileIndex;
            setPieceAt(square, c);
            fileIndex++;
        } else if (isdigit(c)) {
            fileIndex += (c - '0');
        }
    }

    side = (result[1] == "w") ? WHITE : BLACK;
    parseFENCastling(result[2]);
    if (result[3] != "-") {
        enpassant = inverseSquareMap.at(result[3]);
    }

    halfmoveCounter = result[4][0] - '0';
    fullmoveNumber = result[5][0] - '0';
}

void ChessBoard::setPieceAt(int square, Piece piece, Color color) {
    assert(square >= 0 && square < 64);

    std::map<std::pair<Color, Piece>, int> indexMap = {
        {{WHITE, PAWN}, WHITE_PAWNS},     {{WHITE, BISHOP}, WHITE_BISHOPS},
        {{WHITE, KNIGHT}, WHITE_KNIGHTS}, {{WHITE, ROOK}, WHITE_ROOKS},
        {{WHITE, KING}, WHITE_KING},      {{WHITE, QUEEN}, WHITE_QUEEN},
        {{BLACK, PAWN}, BLACK_PAWNS},     {{BLACK, BISHOP}, BLACK_BISHOPS},
        {{BLACK, KNIGHT}, BLACK_KNIGHTS}, {{BLACK, ROOK}, BLACK_ROOKS},
        {{BLACK, KING}, BLACK_KING},      {{BLACK, QUEEN}, BLACK_QUEEN},
    };

    boards_[indexMap.at({color, piece})].setBit(square);
}

void ChessBoard::setPieceAt(int square, char p) {
    assert(strchr(pieceNames_, p));

    std::map<char, std::pair<Color, Piece>> indexMap = {{
        {'P', {WHITE, PAWN}},
        {'B', {WHITE, BISHOP}},
        {'N', {WHITE, KNIGHT}},
        {'R', {WHITE, ROOK}},
        {'K', {WHITE, KING}},
        {'Q', {WHITE, QUEEN}},
        {'p', {BLACK, PAWN}},
        {'b', {BLACK, BISHOP}},
        {'n', {BLACK, KNIGHT}},
        {'r', {BLACK, ROOK}},
        {'k', {BLACK, KING}},
        {'q', {BLACK, QUEEN}},
    }};
    Color color = indexMap.at(p).first;
    Piece piece = indexMap.at(p).second;
    setPieceAt(square, piece, color);
}

void ChessBoard::clearPieceAt(int square) {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (boards_[boardsIndex].getBit(square)) {
            boards_[boardsIndex].clearBit(square);
            break;
        }
    }
}

std::string ChessBoard::toString() const {
    std::ostringstream oss;

    for (int rank = 7; rank >= 0; rank--) {
        oss << (rank + 1) << " | ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << getPieceAt(square) << " ";
        }
        oss << "\n";
    }

    oss << "    ---------------\n";
    oss << "    a b c d e f g h\n";

    return oss.str();
}

char ChessBoard::getPieceAt(int square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (boards_[boardsIndex].getBit(square)) {
            return pieceNames_[boardsIndex];
        }
    }
    return '.';
}

std::string ChessBoard::toStringFancy() const {
    std::ostringstream oss;

    for (int rank = 7; rank >= 0; rank--) {
        oss << (rank + 1) << " | ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << getPieceAtFancy(square) << " ";
        }
        oss << "\n";
    }

    oss << "    ---------------\n";
    oss << "    a b c d e f g h\n";

    return oss.str();
}

std::string ChessBoard::getPieceAtFancy(int square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (boards_[boardsIndex].getBit(square)) {
            return pieceSymbols_[boardsIndex];
        }
    }
    return ".";
}

std::string ChessBoard::availableCastleToString() const {
    std::ostringstream oss;

    if (this->availableCastle & WHITE_KINGSIDE) oss << "<WK>";
    if (this->availableCastle & WHITE_QUEENSIDE) oss << "<WQ>";
    if (this->availableCastle & BLACK_KINGSIDE) oss << "<bk>";
    if (this->availableCastle & BLACK_QUEENSIDE) oss << "<bq>";

    return oss.str();
}

std::string ChessBoard::toStringComplete() const {
    std::ostringstream oss;

    oss << toString() << std::endl;
    oss << "Side: " << (side ? "Black" : "White") << std::endl;
    oss << "Castling: " << availableCastleToString() << std::endl;
    oss << "Enpassant: "
        << (enpassant.has_value() ? squareMap.at(enpassant.value()) : " ")
        << std::endl;

    return oss.str();
}

void ChessBoard::updateAllOccupancyBoards() {
    boards_[WHITE_ALL] = boards_[WHITE_PAWNS] | boards_[WHITE_ROOKS] |
                         boards_[WHITE_KNIGHTS] | boards_[WHITE_BISHOPS] |
                         boards_[WHITE_QUEEN] | boards_[WHITE_KING];

    boards_[BLACK_ALL] = boards_[BLACK_PAWNS] | boards_[BLACK_ROOKS] |
                         boards_[BLACK_KNIGHTS] | boards_[BLACK_BISHOPS] |
                         boards_[BLACK_QUEEN] | boards_[BLACK_KING];

    boards_[ALL] = boards_[WHITE_ALL] | boards_[BLACK_ALL];
}

void ChessBoard::parseFENCastling(std::string FEN_castling) {
    if (FEN_castling == "-") {
        availableCastle = 0;
    }
    if (strchr(FEN_castling.c_str(), 'K') != NULL) {
        availableCastle |= WHITE_KINGSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'Q') != NULL) {
        availableCastle |= WHITE_QUEENSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'k') != NULL) {
        availableCastle |= BLACK_KINGSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'q') != NULL) {
        availableCastle |= BLACK_QUEENSIDE;
    }
}
