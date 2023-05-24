

//headers
#include <stdio.h>

// FEN debug positions
char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char tricky_position[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";


//piece encoding
enum { e, P, N, B, R, Q, K, p, n, b, r, q, k, o };

//square encoding
enum squares {
    a8 = 0, b8, c8, d8, e8, f8, g8, h8,
    a7 = 16, b7, c7, d7, e7, f7, g7, h7,
    a6 = 32, b6, c6, d6, e6, f6, g6, h6,
    a5 = 48, b5, c5, d5, e5, f5, g5, h5,
    a4 = 64, b4, c4, d4, e4, f4, g4, h4,
    a3 = 80, b3, c3, d3, e3, f3, g3, h3,
    a2 = 96, b2, c2, d2, e2, f2, g2, h2,
    a1 = 112, b1, c1, d1, e1, f1, g1, h1};

//file and rank encoding
enum {RANK_8, RANK_7, RANK_6, RANK_5, RANK_4, RANK_3, RANK_2, RANK_1};
enum {FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H};

//ascii pieces
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

void printBoard();
void resetBoard();
void parseFEN(char *FEN);

//main driver
int main() {

    parseFEN(start_position);
    printBoard();

    return 0;
}

void printBoard(){
    printf("\n");
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 16; file++){
            int squareIndex = rank * 16 + file;

            //print ranks
            if(file == 0){
                printf("  %d  ", 8-rank);
            }

            //if square is on board
            if(!(squareIndex & 0x88)){
                printf("%c ", ascii_pieces[board[squareIndex]]);
            }

        }
        printf("\n");
    }
    printf("\n     a b c d e f g h\n");
    
    printf("\n\n");
}

void resetBoard() {
    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 16; file++){
            int squareIndex = rank * 16 + file;

            //if square is on board
            if(!(squareIndex & 0x88)){
                //reset current board square
                board[squareIndex] = e;
            }

        }
    }
}

void parseFEN(char *fen){

    resetBoard();

    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 16; file++){
            int squareIndex = rank * 16 + file;

            //if square is on board
            if(!(squareIndex & 0x88)){
                //match pieces
                if ((*fen >= 'a' && *fen <= 'z') || (*fen >= 'A' && *fen <= 'Z'))
                {
                    printf("square: %s | current FEN char: %c \n", square_to_coords[squareIndex], *fen);
                    // set the piece on board
                    board[squareIndex] = char_pieces[*fen];
                    // increment FEN pointer
                    fen++;
                }

                // match empty squares
                if(*fen >= '0' && *fen <= '9'){
                    //calculate offset
                    int offset = *fen - '0';

                    // decrement file on empty squares
                    if(board[squareIndex] == e){
                        file--;
                    }

                    //skip empty squares
                    file += offset;

                    fen++;
                }
                
                //match end of rank
                if(*fen == '/'){
                    fen++;
                }
                
            }

        }
    }
}