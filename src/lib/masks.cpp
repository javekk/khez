#include "masks.h"

const Bitboard whitePawns = Bitboard(0x00ff000000000000);
const Bitboard blackPawns = Bitboard(0x000000000000ff00);
const Bitboard whiteRooks = Bitboard(0x8100000000000000);
const Bitboard blackRooks = Bitboard(0x0000000000000081);
const Bitboard whiteKnights = Bitboard(0x4200000000000000);
const Bitboard blackKnights = Bitboard(0x0000000000000042);
const Bitboard whiteBishops = Bitboard(0x2400000000000000);
const Bitboard blackBishops = Bitboard(0x0000000000000024);
const Bitboard whiteQueen = Bitboard(0x1000000000000000);
const Bitboard blackQueen = Bitboard(0x0000000000000010);
const Bitboard whiteKing = Bitboard(0x0800000000000000);
const Bitboard blackKing = Bitboard(0x0000000000000008);

/*
  To generate file bitboards you can use this simple script,
  this one in the example is for generate the mask for notAFile

    Bitboard not_a_file;
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            if (file > 0) {
                not_a_file.setBit(file + (8 * rank));
            }
        }
    }
    std::cout << not_a_file.toString() << std::endl;
    std::cout << std::hex << not_a_file.getValue() << std::endl;
*/

const Bitboard notAFile = Bitboard(0x7f7f7f7f7f7f7f7f);
const Bitboard notHFile = Bitboard(0xfefefefefefefefe);

const Bitboard notABFile = Bitboard(0x3f3f3f3f3f3f3f3f);
const Bitboard notGHFile = Bitboard(0xfcfcfcfcfcfcfcfc);

const Bitboard firstRank = Bitboard(0xFF00000000000000);
const Bitboard eighthRank = Bitboard(0x00000000000000FF);

/*
  To generate file bitboards you can use this simple script,
  this one in the example is for Rook Relevant Occupancies count per square

    int rook_relevant_occupancies_counts[64];
    for (int rank = 0; rank < 8; rank++) {
        for (int file = 0; file < 8; file++) {
            int square = file + (8 * rank);
            rook_relevant_occupancies_counts[square] =
                engine.generateSingleRookRelevantOccupanciesMask(square)
                    .popCount();
        }
    }
    for (int i = 0; i < 64; i++) {
        std::cout << rook_relevant_occupancies_counts[i] << ", ";
    }
*/
const int rookRelevantOccupanciesCounts[64] = {
    12, 11, 11, 11, 11, 11, 11, 12, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 11, 10, 10, 10, 10, 10, 10, 11,
    11, 10, 10, 10, 10, 10, 10, 11, 12, 11, 11, 11, 11, 11, 11, 12};

const int bishopRelevantOccupanciesCounts[64] = {
    6, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 7, 7, 7, 7,
    5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 9, 9, 7, 5, 5, 5, 5, 7, 7,
    7, 7, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6, 5, 5, 5, 5, 5, 5, 6};

/*
  The logic to generate this numbers is inside the magic.h class
  Those random number were generate using this seed = 1804289383
*/
const u_int64_t bishopMagicNumbers[64] = {
    0x40040822862081,   0xa168041010224880, 0x8010141024304420,
    0x850000c804208209, 0x2400115284c20a00, 0x100420c021080800,
    0x100310402010480,  0x22010108410402,   0x1010300200425028,
    0x4044408022444,    0x18200202820010,   0x81001082022481,
    0x20804202a080080,  0x40004200908000,   0x4885a80d100080,
    0x860990400200,     0x802024046000100,  0xd48010802018090,
    0x4402600040802100, 0x160401008803101,  0x800062011004800,
    0x4082090001800,    0x8028a1002201100,  0x418110084500a100,
    0x19450020010c00,   0x2008222040048818, 0x20010040160800,
    0x810048200082200,  0x2285400808008200, 0x8804229000080024,
    0x80822000080800,   0x1004442200403a20, 0xc0010440120a0084,
    0x404140008410400,  0x4010108001004128, 0x85010002104014,
    0x480a040008010820, 0x822050040010,     0x10102004440080,
    0x260310584041800,  0x2210811050441020, 0x1208401011009,
    0x8084210068c004,   0x829400a0000c,     0x40042008042100c0,
    0x4190000220220022, 0x9008020202d80201, 0xeac0c0020c0400,
    0xc10082412010,     0x104008208224020,  0x2100008211400024,
    0x2324240420008040, 0x820a02000400,     0x2118104030101,
    0xc0287000828104,   0x400484108601,     0x182008400821080,
    0x7009084130080800, 0x84240440c00008,   0x161104180402002,
    0x20a80a002100c04a, 0xc08008408801000,  0x2820010421004828,
    0x40502008025080a8,
};

const u_int64_t rookMagicNumbers[64] = {
    0x8044010084004022, 0x2103010208100084, 0x4100080400020b,
    0x200089020a40e,    0x2121010904201001, 0x300340a001001019,
    0x880220900401082,  0x840210810408001,  0x84004401008200,
    0x1400820110280400, 0x8021000208040100, 0x6080004110100,
    0x4000090010002100, 0x2a00802004100880, 0x1200884c00880,
    0x80002006400840,   0x9482c10080420004, 0x86000174020088,
    0x40002008080,      0x2801000800050010, 0x200220100a020040,
    0x120001008004040,  0x80002010024a4001, 0x8c40400080208000,
    0x40021008200004c,  0x1000880104001002, 0x10040080800200,
    0x8000080081802400, 0x1040100080800800, 0x801002802000,
    0x2a05104001002480, 0x844003800020,     0x84600008401,
    0xc480020400108148, 0x20080800400,      0x4000480800800,
    0x1800080080100080, 0x2100100880200081, 0x2040002120081000,
    0x8040002080004084, 0x4042020010990044, 0x40030410208,
    0x1302010100040008, 0x48808004000800,   0x2400828008001000,
    0x4110008080200010, 0x1001828040002003, 0x8000c000600049,
    0xa0801041000880,   0x9042008804014200, 0x5002804010016,
    0x1271001185000800, 0x440801000080084,  0x4002001200402084,
    0x4b01400140201000, 0x104800440008021,  0x200120024810044,
    0x5080020001000080, 0x1a00100801220004, 0x4600020004081020,
    0x100201000080500,  0x2080081000200080, 0x40100020004004,
    0x80042018804000,
};