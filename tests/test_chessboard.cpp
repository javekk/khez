#include <cassert>
#include <iostream>

#include "../src/chessboard/chessboard.h"
#include "../src/lib/square.h"

void test_board_initialization() {
    std::cout << "\t\tTesting board initialization...\n";

    ChessBoard board;
    bool has_pieces = false;
    for (int i = 0; i < 64; i++) {
        char c = board.getPieceAt(0);
        if (c >= 'A' && c <= 'Z') {
            has_pieces = true;
            break;
        }
        if (c >= 'a' && c <= 'z') {
            has_pieces = true;
            break;
        }
    }

    assert(!has_pieces);

    std::cout << "\t\tBoard initialization tests passed!\n";
}

void test_to_string() {
    std::cout << "\t\tTesting toString() returning the board...\n";

    ChessBoard board;

    std::string board_str = board.toString();
    assert(!board_str.empty());
    assert(board_str.length() > 50);  // Should be a reasonable size

    std::cout << "\t\tPiece placement tests passed!\n";
}

void test_initial_position() {
    std::cout << "\t\tTesting initial position setup...\n";

    ChessBoard board;
    board.setupInitialPosition();

    std::cout << "\t\t\tTesting white pieces on rank 1...\n";
    assert(board.getPieceAt(a1) == 'R');
    assert(board.getPieceAt(b1) == 'N');
    assert(board.getPieceAt(c1) == 'B');
    assert(board.getPieceAt(d1) == 'Q');
    assert(board.getPieceAt(e1) == 'K');
    assert(board.getPieceAt(f1) == 'B');
    assert(board.getPieceAt(g1) == 'N');
    assert(board.getPieceAt(h1) == 'R');

    std::cout << "\t\t\tTesting white pieces on rank 2...\n";
    assert(board.getPieceAt(a2) == 'P');
    assert(board.getPieceAt(h2) == 'P');

    std::cout << "\t\t\tTesting black pieces on rank 8...\n";
    assert(board.getPieceAt(a8) == 'r');
    assert(board.getPieceAt(e8) == 'k');

    std::cout << "\t\t\tTesting black pieces on rank 7...\n";
    assert(board.getPieceAt(a7) == 'p');
    assert(board.getPieceAt(h7) == 'p');

    std::cout << "\t\t\tTesting empty squares...\n";
    assert(board.getPieceAt(e4) == '.');
    assert(board.getPieceAt(d5) == '.');

    std::cout << "\t\tInitial position tests passed!\n";
}

void test_set_piece_at() {
    std::cout << "\t\tTesting set piece at function...\n";

    ChessBoard board;

    std::cout << "\t\t\tTesting e4...\n";
    assert(board.getPieceAt(e4) == '.');
    board.setPieceAt(e4, PAWN, WHITE);
    assert(board.getPieceAt(e4) == 'P');
    board.clearPieceAt(e4);
    board.setPieceAt(e4, QUEEN, BLACK);
    assert(board.getPieceAt(e4) == 'q');
    board.clearPieceAt(e4);
    assert(board.getPieceAt(e4) == '.');

    std::cout << "\t\t\tTesting a1...\n";
    assert(board.getPieceAt(a1) == '.');
    board.setPieceAt(a1, ROOK, WHITE);
    assert(board.getPieceAt(a1) == 'R');
    board.clearPieceAt(a1);
    board.setPieceAt(a1, KNIGHT, BLACK);
    assert(board.getPieceAt(a1) == 'n');
    board.clearPieceAt(a1);
    assert(board.getPieceAt(a1) == '.');

    std::cout << "\t\tSet piece at function tests passed...\n";
}

void test_parseFEN() {
    std::cout << "\t\tTesting parseFEN...\n";

    ChessBoard board;

    std::cout << "\t\t\tTesting rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w "
                 "KQkq - 0 1 (Initial position)...\n";

    board.parseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    std::cout << "\t\t\t\tTesting white pieces on rank 1...\n";
    assert(board.getPieceAt(a1) == 'R');
    assert(board.getPieceAt(b1) == 'N');
    assert(board.getPieceAt(c1) == 'B');
    assert(board.getPieceAt(d1) == 'Q');
    assert(board.getPieceAt(e1) == 'K');
    assert(board.getPieceAt(f1) == 'B');
    assert(board.getPieceAt(g1) == 'N');
    assert(board.getPieceAt(h1) == 'R');

    std::cout << "\t\t\t\tTesting white pieces on rank 2...\n";
    assert(board.getPieceAt(a2) == 'P');
    assert(board.getPieceAt(h2) == 'P');

    std::cout << "\t\t\t\tTesting black pieces on rank 8...\n";
    assert(board.getPieceAt(a8) == 'r');
    assert(board.getPieceAt(e8) == 'k');

    std::cout << "\t\t\t\tTesting black pieces on rank 7...\n";
    assert(board.getPieceAt(a7) == 'p');
    assert(board.getPieceAt(h7) == 'p');

    std::cout << "\t\t\t\tTesting empty squares...\n";
    assert(board.getPieceAt(e4) == '.');
    assert(board.getPieceAt(d5) == '.');
    assert(board.getPieceAt(c5) == '.');

    std::cout << "\t\t\t\tTesting extra info...\n";
    assert(board.status.side == WHITE);
    assert(!board.status.enpassant.has_value());
    assert(board.status.availableCastle == 0b1111);
    assert(board.status.halfmoveCounter == 0);
    assert(board.status.fullmoveNumber == 1);

    std::cout << "\t\t\t parseFEN (init position) tests passed!\n";

    std::cout << "\t\t\tTesting FEN; "
                 "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b "
                 "KQkq - 1 2 (Init pos after a couple of moves)...\n";

    board.emptyBoard();
    board.parseFEN(
        "rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

    std::cout << "\t\t\t\tTesting rank 1...\n";
    assert(board.getPieceAt(a1) == 'R');
    assert(board.getPieceAt(b1) == 'N');
    assert(board.getPieceAt(c1) == 'B');
    assert(board.getPieceAt(d1) == 'Q');
    assert(board.getPieceAt(e1) == 'K');
    assert(board.getPieceAt(f1) == 'B');
    assert(board.getPieceAt(g1) == '.');
    assert(board.getPieceAt(h1) == 'R');

    std::cout << "\t\t\t\tTesting rank 2...\n";
    assert(board.getPieceAt(a2) == 'P');
    assert(board.getPieceAt(h2) == 'P');
    assert(board.getPieceAt(e2) == '.');

    std::cout << "\t\t\t\tTesting rank 3...\n";
    assert(board.getPieceAt(f3) == 'N');
    assert(board.getPieceAt(h3) == '.');
    assert(board.getPieceAt(e3) == '.');

    std::cout << "\t\t\t\tTesting rank 8...\n";
    assert(board.getPieceAt(a8) == 'r');
    assert(board.getPieceAt(e8) == 'k');

    std::cout << "\t\t\t\tTesting rank 7...\n";
    assert(board.getPieceAt(a7) == 'p');
    assert(board.getPieceAt(h7) == 'p');
    assert(board.getPieceAt(c7) == '.');

    std::cout << "\t\t\t\tTesting  rank 5...\n";
    assert(board.getPieceAt(a5) == '.');
    assert(board.getPieceAt(h5) == '.');
    assert(board.getPieceAt(c5) == 'p');

    std::cout << "\t\t\t\tTesting empty squares...\n";
    assert(board.getPieceAt(b4) == '.');
    assert(board.getPieceAt(d5) == '.');
    assert(board.getPieceAt(g5) == '.');

    std::cout << "\t\t\t\tTesting extra info...\n";
    assert(board.status.side == BLACK);
    assert(!board.status.enpassant.has_value());
    assert(board.status.availableCastle == 0b1111);
    assert(board.status.halfmoveCounter == 1);
    assert(board.status.fullmoveNumber == 2);

    std::cout << "\t\t\t parseFEN (after a couple of moves) tests passed!\n";

    std::cout << "\t\tParseFEN function tests passed...\n";
}

int run_chessboard_tests() {
    std::cout << "\t Testing chessboard...\n";
    test_board_initialization();
    test_to_string();
    test_initial_position();
    test_set_piece_at();
    test_parseFEN();

    std::cout << "\tAll chessboard tests passed!\n";
    return 0;
}