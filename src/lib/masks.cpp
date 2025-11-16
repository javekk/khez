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
*/
const u_int64_t bishopMagicNumbers[64] = {
    0x40040822862081,   0xa168041010224880, 0x8010141024304420,
    0x850000c804208209, 0x2400115284c20a00, 0x100420c021080800,
    0x100310402010480,  0x22010108410402,   0x1010300200425028,
    0x4044408022444,    0x18200202820010,   0x81001082022481,
    0x20804202a080080,  0x40004200908000,   0x4885a80d100080,
    0x860990400200,     0x802024046000100,  0xd48010802018090,
    0x10200080201400,   0x400812000041,     0x204018a11000,
    0x2001202a12000,    0x101044300a004001, 0x8904411402080,
    0x4c49404200008202, 0x2240400004200,    0x10020042024c0082,
    0x100480114400,     0x1000040c00803000, 0x20808240900010,
    0x4066020280200040, 0x50902500001800,   0x8001002041008800,
    0x220018400544c00,  0x400802008040400,  0x420a0402088,
    0x2000441000400000, 0x1280430006000000, 0xa140900000410b1a,
    0xc200802008010,    0x1002008042020104, 0x8002000308110c30,
    0x420b001601052912, 0x1001112801400220, 0x88000082080080,
    0x4000806008044040, 0x26a000100001012,  0x1060200020680,
    0x408814206106208,  0x40201108904,      0x460640109400044,
    0x80441004000008,   0x70202904100900,   0x8200049400110000,
    0x8004008048810044, 0xc008340002102c04, 0x4202110101085,
    0x8002013002120036, 0x8022080406205124, 0x80a09a0404000,
    0x4008280001401680, 0x240c320100040020, 0x810250008720800,
    0x301004504022000};

const u_int64_t rookinMagicNumbers[64] = {
    0x205081040a,       0x8400008130020804, 0x8012004824011022,
    0x9202002005881002, 0x8010210408100101, 0x820040081022,
    0x804012400081a103, 0x8004852200104502, 0x10040a41200,
    0x1404308802014400, 0x402000408100200,  0x8001040080280280,
    0x408081000210100,  0x4200200100401100, 0xa820200040008080,
    0x2000210050800100, 0x200204846c020009, 0x88084102840010,
    0x8000040002008080, 0x202000890060020,  0x1001000090020,
    0x2020004021010012, 0x9150500020084000, 0x8002400080018028,
    0x209000041001082,  0xa000080144003002, 0x8004040080800200,
    0x18002004040040,   0x801002009001000,  0x802000801000,
    0x1000442002c01000, 0x2080004001402000, 0x4200008421,
    0x41000100020004,   0x9024008080040200, 0x100080080040080,
    0x4080100100082101, 0x1101004700200110, 0x400400080200080,
    0x8c40400080208000, 0x44008600010882c4, 0x280808002000100,
    0x184808004010200,  0x122020008100520,  0x848010000802,
    0x8810820010420820, 0x100808020004000,  0x800228004804000,
    0x40280018022d300,  0x8029010402000100, 0x62000408020010,
    0x800400800800,     0x200808010000800,  0x2004200108024,
    0x1000400020100048, 0xd000800020804010, 0x200010200402894,
    0x280008001000200,  0x100010008040002,  0x4200201008040200,
    0x2200104200080420, 0x2080081000200080, 0x40100020004004,
    0x80042018804000};