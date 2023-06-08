#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// piece encoding
enum { e, P, N, B, R, Q, K, p, n, b, r, q, k, o };

// square encoding
enum squares {
    a8 = 0,   b8, c8, d8, e8, f8, g8, h8,
    a7 = 16,  b7, c7, d7, e7, f7, g7, h7,
    a6 = 32,  b6, c6, d6, e6, f6, g6, h6,
    a5 = 48,  b5, c5, d5, e5, f5, g5, h5,
    a4 = 64,  b4, c4, d4, e4, f4, g4, h4,
    a3 = 80,  b3, c3, d3, e3, f3, g3, h3,
    a2 = 96,  b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1, no_square
    };

// file and rank encoding
enum {RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};

// castling binary represantation
// binary   dec
//  0001     1   white king can castle king side
//  0010     2   white king can castle queen side
//  0100     4   black king can castle king side
//  1000     8   black king can castle queen side
//
// examples
// 1111   both sides can castle both directions
// 1001   black king can castle queen side && white king can castle king side

// castling rights
enum castling { KC = 1, QC = 2, kc = 4, qc = 8};

// sides to move
enum sides { white, black };

// ascii pieces
char ascii_pieces[] = ".PNBRQKpnbrqko";

// encode ascii pieces
int char_pieces[] = {
    ['P'] = P,
    ['N'] = N,
    ['B'] = B,
    ['R'] = R,
    ['Q'] = Q,
    ['K'] = K,
    ['p'] = p,
    ['n'] = n,
    ['b'] = b,
    ['r'] = r,
    ['q'] = q,
    ['k'] = k
};

// chess board representation
int board[128] = {
    r, n, b, q, k, b, n, r,   o, o, o, o, o, o, o, o,
    p, p, p, p, p, p, p, p,   o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,   o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,   o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,   o, o, o, o, o, o, o, o,
    e, e, e, e, e, e, e, e,   o, o, o, o, o, o, o, o,
    P, P, P, P, P, P, P, P,   o, o, o, o, o, o, o, o,
    R, N, B, Q, K, B, N, R,   o, o, o, o, o, o, o, o
};

// side to move
int sideToMove = white;

// enPassant square
int enPassantSquare = no_square;

// castling rights (dec 15 == bin 1111 == both kings can castle to both directions)
int castle = 15;

// convert board square indexes to coordinates
char *square_to_coords[] = {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8", "i8", "j8", "k8", "l8", "m8", "n8", "o8", "p8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7", "i7", "j7", "k7", "l7", "m7", "n7", "o7", "p7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6", "i6", "j6", "k6", "l6", "m6", "n6", "o6", "p6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5", "i5", "j5", "k5", "l5", "m5", "n5", "o5", "p5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4", "i4", "j4", "k4", "l4", "m4", "n4", "o4", "p4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3", "i3", "j3", "k3", "l3", "m3", "n3", "o3", "p3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2", "i2", "j2", "k2", "l2", "m2", "n2", "o2", "p2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1", "i1", "j1", "k1", "l1", "m1", "n1", "o1", "p1",

};

// piece move offsets
int knight_offsets[8] = { 33, 31, 18, 14, -33, -31, -18, -14 };
int bishop_offsets[4] = { 15, 17, -15, -17 };
int rook_offsets[4] = { 16, -16, 1, -1 };
int king_offsets[8] = { 16, -16, 1, -1, 15, 17, -15, -17};

#endif // DEFINITIONS_H