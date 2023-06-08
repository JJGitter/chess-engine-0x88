//https://www.youtube.com/watch?v=lgq2dD26MjQ&list=PLmN0neTso3JzhJP35hwPHJi4FZgw5Ior0&index=7

//headers
#include <stdio.h>
#include "defs.h"

// FEN debug positions
char start_position[] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
char tricky_position[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
char test_position[] = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w kq c6 0 1";
char work_position[] = "r7/8/8/8/8/4r3/8/8 w KQkq - 0 1";

void printBoard();
void resetBoard();
void parseFEN(char *FEN);
void printAttackedSquares();
int isSquareAttacked();
void generateMoves();

//main driver
int main() {

    parseFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPpP/R3K2R b KQkq - 0 1");
    printBoard();
    generateMoves();

    return 0;
}

void generateMoves(){
    // loop over all board squares
    for(int square = 0; square < 128; square++){
        // is square on board?
        if(!(square & 0x88)){
            // white pawn and castling moves
            if(!sideToMove){
                // quite white pawn moves
                if(board[square] == P){
                    // init target square
                    int to_square = square - 16;

                    // check if target square is on board and empty
                    if(!(to_square & 0x88) && !board[to_square]){
                        // pawn promotions
                        if(square >= a7 && square <= h7){
                            printf("%s%sq\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sr\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sb\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sn\n", square_to_coords[square], square_to_coords[to_square]);
                        }else{
                            // one square ahead pawn move
                            printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);

                            // two squares ahead pawn move
                            if((square >= a2 && square <= h2) && !board[square - 32]){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[square - 32]);
                            }
                        }
                    }
                }
            }
            //black pawn and castling moves
            else{
                // quite black pawn moves
                if(board[square] == p){
                    // init target square
                    int to_square = square + 16;

                    // check if target square is on board and empty
                    if(!(to_square & 0x88) && !board[to_square]){
                        // pawn promotions
                        if(square >= a2 && square <= h2){
                            printf("%s%sq\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sr\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sb\n", square_to_coords[square], square_to_coords[to_square]);
                            printf("%s%sn\n", square_to_coords[square], square_to_coords[to_square]);
                        }else{
                            // one square ahead pawn move
                            printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);

                            // two squares ahead pawn move
                            if((square >= a7 && square <= h7) && !board[square + 32]){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[square + 32]);
                            }
                        }
                    }
                }

            }
        }
    }
}

int isSquareAttacked(int square, int side){

    // pawn attacks
    if (!side){
        // if target square is on board and is white pawn
        if(!((square + 17) & 0x88) && board[square + 17] == P)
            return 1;
        if(!((square + 15) & 0x88) && board[square + 15] == P)
            return 1;
    }else{
        // if target square is on board and is black pawn
        if(!((square - 17) & 0x88) && board[square - 17] == p)
            return 1;
        if(!((square - 15) & 0x88) && board[square - 15] == p)
            return 1;
    }

    // knight attacks
    for(int index = 0; index < 8; index++){
        // initialize target square
        int target_square = square + knight_offsets[index];

        // lookup target piece
        int target_piece = board[target_square];

        // is target square on board and a knight?
        if(!(target_square & 0x88)){
            if(!side ? target_piece == N : target_piece == n){
                return 1;
            }
        }
    }

    // king attacks
    for(int index = 0; index < 8; index++){
        // initialize target square
        int target_square = square + king_offsets[index];

        // lookup target piece
        int target_piece = board[target_square];

        // is target square on board and a king?
        if(!(target_square & 0x88)){
            // if target piece is either white or black king
            if(!side ? target_piece == K : target_piece == k){
                return 1;
            }
        }
    }

    // bishop & queen attacks
    for(int index = 0; index < 4; index++){
        // initialize target square
        int target_square = square + bishop_offsets[index];

        // loop over attack ray
        while(!(target_square & 0x88)){
            // target piece
            int target_piece = board[target_square];

            // if target piece is either white or black bishop/queen
            if(!side ? (target_piece == B || target_piece == Q) : (target_piece == b || target_piece == q))
                return 1;

            // break if hit a piece
            if(target_piece != 0)
                break;

            // increment target square by move offset
            target_square += bishop_offsets[index];
        }
        
    }

    // rook & queen attacks
    for(int index = 0; index < 4; index++){
        // initialize target square
        int target_square = square + rook_offsets[index];

        // loop over attack ray
        while(!(target_square & 0x88)){
            // target piece
            int target_piece = board[target_square];

            // if target piece is either white or black rook/queen
            if(!side ? (target_piece == R || target_piece == Q) : (target_piece == r || target_piece == q))
                return 1;

            // break if hit a piece
            if(target_piece != 0)
                break;

            // increment target square by move offset
            target_square += rook_offsets[index];
        }
        
    }

    return 0;
}

void printAttackedSquares(int side){
    printf("\n");
    printf("  Attacking side: %s\n\n", side ? "black" : "white");

    for(int rank = 0; rank < 8; rank++){
        for(int file = 0; file < 16; file++){
            int squareIndex = rank * 16 + file;

            //print ranks
            if(file == 0){
                printf("  %d  ", 8-rank);
            }

            //if square is on board
            if(!(squareIndex & 0x88)){
                printf("%c ", isSquareAttacked(squareIndex, side) ? 'x' : '.');
            }

        }
        printf("\n");
    }
    //print files
    printf("\n     a b c d e f g h\n");
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

    //print files
    printf("\n     a b c d e f g h\n");

    //print board stats
    printf("    ----------------\n");
    printf("    Side:      %s\n", (sideToMove == white) ? "white" : "black");
    printf("    Castling:   %c%c%c%c\n", (castle & KC) ? 'K' : '-', 
                                    (castle & QC) ? 'Q' : '-', 
                                    (castle & kc) ? 'k' : '-', 
                                    (castle & qc) ? 'q' : '-');
    printf("    enPassant:    %s\n", square_to_coords[enPassantSquare]);
    
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
    //reset stats
    sideToMove = -1;
    castle = 0;
    enPassantSquare = no_square;
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
                    // set the piece on board
                    board[squareIndex] = char_pieces[*fen];
                    // increment FEN pointer
                    fen++;
                }
                
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

    //increment fen pointer to side parsing
    fen++;
    // parse side to move
    if(*fen == 'w'){
        sideToMove = white;
    }else{
        sideToMove = black;
    }

    //increment fen pointer to castle parsing
    fen += 2;

    // parse castling rights
    while (*fen != ' '){
        switch(*fen) {
            case 'K':
                castle = castle | KC;
                break;
            case 'Q':
                castle = castle | QC;
                break;
            case 'k':
                castle = castle | kc;
                break;
            case 'q':
                castle = castle | qc;
                break;
            case '-':
                break;
        }
        fen++;
    }
    
    //incremet  fen pointer to enPassant square
    fen++;

    //parse enPassant square
    if(*fen != '-'){
        //parse enpassant square's file and rank
        int file = fen[0] - 'a';
        int rank = 8 - (fen[1] - '0');

        // set up en passant square
        enPassantSquare = rank * 16 + file;
    }else {
        enPassantSquare = no_square;
    }


}