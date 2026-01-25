#include "chessboard.h"

#include <string.h>

#include <bitset>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

#include "../lib/masks.h"

ChessBoard::ChessBoard() { emptyBoard(); }

void ChessBoard::emptyBoard() {
    status.boards[WHITE_PAWNS] = Bitboard();
    status.boards[BLACK_PAWNS] = Bitboard();
    status.boards[WHITE_ROOKS] = Bitboard();
    status.boards[BLACK_ROOKS] = Bitboard();
    status.boards[WHITE_KNIGHTS] = Bitboard();
    status.boards[BLACK_KNIGHTS] = Bitboard();
    status.boards[WHITE_BISHOPS] = Bitboard();
    status.boards[BLACK_BISHOPS] = Bitboard();
    status.boards[WHITE_QUEEN] = Bitboard();
    status.boards[BLACK_QUEEN] = Bitboard();
    status.boards[WHITE_KING] = Bitboard();
    status.boards[BLACK_KING] = Bitboard();

    updateAllOccupancyBoards();

    status.side.reset();
    status.availableCastle = 0b1111;
    status.enpassant.reset();
    status.halfmoveCounter = 0;
    status.fullmoveNumber = 1;
    moveHistory.clear();
    statusHistory.clear();
}

void ChessBoard::setupInitialPosition() {
    emptyBoard();

    status.boards[WHITE_PAWNS] = whitePawns;
    status.boards[BLACK_PAWNS] = blackPawns;
    status.boards[WHITE_ROOKS] = whiteRooks;
    status.boards[BLACK_ROOKS] = blackRooks;
    status.boards[WHITE_KNIGHTS] = whiteKnights;
    status.boards[BLACK_KNIGHTS] = blackKnights;
    status.boards[WHITE_BISHOPS] = whiteBishops;
    status.boards[BLACK_BISHOPS] = blackBishops;
    status.boards[WHITE_QUEEN] = whiteQueen;
    status.boards[BLACK_QUEEN] = blackQueen;
    status.boards[WHITE_KING] = whiteKing;
    status.boards[BLACK_KING] = blackKing;

    updateAllOccupancyBoards();

    status.side = WHITE;
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

void ChessBoard::parseFEN(const std::string FEN) {
    emptyBoard();

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
            setPieceAt(static_cast<Square>(square), c);
            fileIndex++;
        } else if (isdigit(c)) {
            fileIndex += (c - '0');
        }
    }

    status.side = (result[1] == "w" || result[1] == "W") ? WHITE : BLACK;
    parseFENCastling(result[2]);
    if (result[3] != "-") {
        status.enpassant = inverseSquareMap.at(result[3]);
    }

    status.halfmoveCounter = result[4][0] - '0';
    status.fullmoveNumber = result[5][0] - '0';

    updateAllOccupancyBoards();
}

void ChessBoard::makeMove(Move move) {
    // Do not care if the move it's legal, just make it. The Engine::makeMove
    // will take care of that
    moveHistory.push_back(move);
    statusHistory.push_back(status);

    clearPieceAt(move.from);

    if (move.isCapture) {
        makeMoveCapture(move);
    } else {
        makeMoveQuite(move);
    }

    // Promotion
    if (move.promoted != EMPTY) {
        clearPieceAt(move.to);
        setPieceAt(move.to, move.promoted, status.side.value());
    }

    // reset enpassant
    if (move.type != PAWN_DOUBLE_PUSH) {
        status.enpassant.reset();
    }

    if (status.availableCastle) {
        makeMoveCastlingChecks(move);
    }

    // halfmove counter
    if (move.piece == PAWN || move.isCapture) {
        status.halfmoveCounter = 0;
    } else {
        status.halfmoveCounter++;
    }

    // Full move counter
    if (status.side == BLACK) {
        status.fullmoveNumber++;
    }

    // side
    status.side = ((status.side.value() == WHITE) ? BLACK : WHITE);
}

void ChessBoard::makeMoveCastlingChecks(Move& move) {
    if (move.piece == KING) {
        if (status.side == WHITE) {
            status.availableCastle &= (~WHITE_KINGSIDE & ~WHITE_QUEENSIDE);
        } else {
            status.availableCastle &= (~BLACK_KINGSIDE & ~BLACK_QUEENSIDE);
        }
    }
    if (move.piece == ROOK) {
        if (move.from == a1) {
            status.availableCastle &= ~WHITE_QUEENSIDE;
        }
        if (move.from == h1) {
            status.availableCastle &= ~WHITE_KINGSIDE;
        }
        if (move.from == a8) {
            status.availableCastle &= ~BLACK_QUEENSIDE;
        }
        if (move.from == h8) {
            status.availableCastle &= ~BLACK_KINGSIDE;
        }
    }
}

void ChessBoard::makeMoveQuite(Move& move) {
    setPieceAt(move.to, move.piece, status.side.value());

    if (move.promoted != EMPTY) {
        clearPieceAt(move.to);
        setPieceAt(move.to, move.promoted, status.side.value());
    }

    if (move.isCastling) {
        if (status.side == WHITE) {
            if (move.to == g1) {  // White kingside
                clearPieceAt(h1);
                setPieceAt(f1, 'R');
            }

            if (move.to == c1) {  // White queenside
                clearPieceAt(a1);
                setPieceAt(d1, 'R');
            }
        } else {
            if (move.to == g8) {  // Black kingside
                clearPieceAt(h8);
                setPieceAt(f8, 'r');
            }

            if (move.to == c8) {  // Black queenside
                clearPieceAt(a8);
                setPieceAt(d8, 'r');
            }
        }
    }

    if (move.isDoublePush) {
        int file = status.side.value() == WHITE ? -8 : +8;
        status.enpassant = static_cast<Square>(move.to + file);
    }
}

void ChessBoard::makeMoveCapture(Move& move) {
    if (move.isEnpassant) {
        int file = status.side.value() == WHITE ? -8 : +8;
        clearPieceAt(static_cast<Square>(status.enpassant.value() + file));
        setPieceAt(move.to, move.piece, status.side.value());
    } else {
        clearPieceAt(move.to);
        setPieceAt(move.to, move.piece, status.side.value());
    }
}

void ChessBoard::undoLastMove() {
    ChessboardStatus previuousStatus = statusHistory.back();
    status = previuousStatus;

    statusHistory.pop_back();
    moveHistory.pop_back();
}

void ChessBoard::setPieceAt(const Square square, const Piece piece,
                            const Color color) {
    assert(square >= 0 && square < 64);

    status.boards[sideColorToPieceBoardMap.at({color, piece})].setBit(square);
    updateAllOccupancyBoards();
}

void ChessBoard::setPieceAt(const Square square, const char p) {
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

void ChessBoard::clearPieceAt(const Square square) {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (status.boards[boardsIndex].getBit(square)) {
            status.boards[boardsIndex].clearBit(square);
            break;
        }
    }
    updateAllOccupancyBoards();
}

std::string ChessBoard::toString() const {
    std::ostringstream oss;

    for (int rank = 7; rank >= 0; rank--) {
        oss << (rank + 1) << " | ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            oss << getPieceAt(static_cast<Square>(square)) << " ";
        }
        oss << "\n";
    }

    oss << "    ---------------\n";
    oss << "    a b c d e f g h\n";

    return oss.str();
}

char ChessBoard::getPieceAt(const Square square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (status.boards[boardsIndex].getBit(square)) {
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
            oss << getPieceAtFancy(static_cast<Square>(square)) << " ";
        }
        oss << "\n";
    }

    oss << "    ---------------\n";
    oss << "    a b c d e f g h\n";

    return oss.str();
}

std::string ChessBoard::getPieceAtFancy(const Square square) const {
    for (int boardsIndex = 0; boardsIndex < 12; boardsIndex++) {
        if (status.boards[boardsIndex].getBit(square)) {
            return pieceSymbols_[boardsIndex];
        }
    }
    return ".";
}

std::string ChessBoard::availableCastleToString() const {
    std::ostringstream oss;

    if (status.availableCastle & WHITE_KINGSIDE) oss << "<WK>";
    if (status.availableCastle & WHITE_QUEENSIDE) oss << "<WQ>";
    if (status.availableCastle & BLACK_KINGSIDE) oss << "<bk>";
    if (status.availableCastle & BLACK_QUEENSIDE) oss << "<bq>";

    return oss.str();
}

std::string ChessBoard::toStringComplete() const {
    std::ostringstream oss;
    oss << "===========================" << std::endl;
    oss << toString() << std::endl;
    oss << "Side: " << (*status.side == Color::BLACK ? "Black" : "White")
        << std::endl;
    oss << "Castling: " << availableCastleToString() << std::endl;
    oss << "Enpassant: "
        << (status.enpassant.has_value()
                ? squareMap.at(status.enpassant.value())
                : " ")
        << std::endl;
    oss << "===========================" << std::endl;

    return oss.str();
}

void ChessBoard::updateAllOccupancyBoards() {
    status.boards[WHITE_ALL] =
        status.boards[WHITE_PAWNS] | status.boards[WHITE_ROOKS] |
        status.boards[WHITE_KNIGHTS] | status.boards[WHITE_BISHOPS] |
        status.boards[WHITE_QUEEN] | status.boards[WHITE_KING];

    status.boards[BLACK_ALL] =
        status.boards[BLACK_PAWNS] | status.boards[BLACK_ROOKS] |
        status.boards[BLACK_KNIGHTS] | status.boards[BLACK_BISHOPS] |
        status.boards[BLACK_QUEEN] | status.boards[BLACK_KING];

    status.boards[ALL_PIECES] =
        status.boards[WHITE_ALL] | status.boards[BLACK_ALL];
}

void ChessBoard::parseFENCastling(const std::string FEN_castling) {
    status.availableCastle = 0;
    if (FEN_castling == "-") {
        return;
    }
    if (strchr(FEN_castling.c_str(), 'K') != NULL) {
        status.availableCastle |= WHITE_KINGSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'Q') != NULL) {
        status.availableCastle |= WHITE_QUEENSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'k') != NULL) {
        status.availableCastle |= BLACK_KINGSIDE;
    }
    if (strchr(FEN_castling.c_str(), 'q') != NULL) {
        status.availableCastle |= BLACK_QUEENSIDE;
    }
}
