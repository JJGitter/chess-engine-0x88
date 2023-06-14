//https://www.youtube.com/watch?v=7_QP8Rk9TE8&list=PLmN0neTso3JzhJP35hwPHJi4FZgw5Ior0&index=11

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

    parseFEN(tricky_position);
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
                // white pawn moves
                if(board[square] == P){
                    // init target square
                    int to_square = square - 16;

                    // quiet white pawn moves. Check if target square is on board and empty
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
                            if((square >= a2 && square <= h2) && !board[square - 32])
                                printf("%s%s\n", square_to_coords[square], square_to_coords[square - 32]);
                        }
                    }
                    // white pawn capture moves
                    for (int index = 0; index < 4; index++){
                        int pawn_offset = bishop_offsets[index];

                        // white pawn offsets
                        if (pawn_offset < 0){
                            int to_square = square + pawn_offset;
                            // check if target square is on board
                            if (!(to_square & 0x88)){
                                // capture pawn promotion
                                if (
                                    (square >= a7 && square <= h7) && 
                                    (board[to_square] >= p && board[to_square] <= k)
                                    ){
                                    printf("%s%sq\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sr\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sb\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sn\n", square_to_coords[square], square_to_coords[to_square]);
                                }else{
                                    // casual capture
                                    if ((board[to_square] >= p && board[to_square] <= k)){
                                        printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                    }
                                    // enPassant capture
                                    if(to_square == enPassantSquare)
                                        printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                }
                                
                            }
                        }
                    }
                }
                // white king castling
                if (board[square] == K){
                    // if king side castling is available
                    if (castle & KC){
                        // make sure there are empty squares between king and rook
                        if (board[f1] == 0 && board[g1] == 0) {
                            // make sure king & neighbour square are not under attack
                            if (!isSquareAttacked(e1, black) && !isSquareAttacked(f1, black))
                                printf("%s%s\n", "e1", "g1");

                        }
                    }

                    // if queen side castling is available
                    if (castle & QC){
                        // make sure there are empty squares between king and rook
                        if ( board[b1] == 0 && board[c1] == 0 && board[d1] == 0 ) {
                            // make sure king & neighbour square are not under attack
                            if (!isSquareAttacked(e1, black) && !isSquareAttacked(d1, black))
                                printf("%s%s\n", "e1", "c1");

                        }
                    }
                }
            }
            //black pawn and castling moves
            else{
                // black pawn moves
                if(board[square] == p){
                    // init target square
                    int to_square = square + 16;

                    // quite black pawn moves. check if target square is on board and empty
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
                    // black pawn capture moves
                    for (int index = 0; index < 4; index++){
                        int pawn_offset = bishop_offsets[index];

                        // black pawn offsets
                        if (pawn_offset > 0){
                            int to_square = square + pawn_offset;
                            // check if target square is on board
                            if (!(to_square & 0x88)){
                                // capture pawn promotion
                                if (
                                    (square >= a2 && square <= h2) && 
                                    (board[to_square] >= P && board[to_square] <= K)
                                    ){
                                    printf("%s%sq\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sr\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sb\n", square_to_coords[square], square_to_coords[to_square]);
                                    printf("%s%sn\n", square_to_coords[square], square_to_coords[to_square]);
                                }else{
                                    // casual capture
                                    if ((board[to_square] >= P && board[to_square] <= K)){
                                        printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                    }
                                    // enPassant capture
                                    if(to_square == enPassantSquare)
                                        printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                }
                                
                            }
                        }
                    }
                }
                // black king castling
                if (board[square] == k){
                    // if king side castling is available
                    if (castle & kc){
                        // make sure there are empty squares between king and rook
                        if (board[f8] == 0 && board[g8] == 0) {
                            // make sure king & neighbour square are not under attack
                            if (!isSquareAttacked(e8, white) && !isSquareAttacked(f8, white))
                                printf("%s%s\n", "e8", "g8");

                        }
                    }

                    // if queen side castling is available
                    if (castle & qc){
                        // make sure there are empty squares between king and rook
                        if ( board[b8] == 0 && board[c8] == 0 && board[d8] == 0 ) {
                            // make sure king & neighbour square are not under attack
                            if (!isSquareAttacked(e8, white) && !isSquareAttacked(d8, white))
                                printf("%s%s\n", "e8", "c8");

                        }
                    }
                }
            }
            // knight moves
            if(sideToMove == white ? board[square] == N : board[square] == n){
                // loop over knight move offsets
                for(int index = 0; index < 8; index++){
                    // initialize target square
                    int to_square = square + knight_offsets[index];

                    // initialize target piece
                    int piece = board[to_square];

                    // make sure target square is on board
                    if(!(to_square & 0x88)){
                        //
                        if(
                            sideToMove == white ? 
                            (piece == e || (piece >= p && piece <= k)) : 
                            (piece == e || (piece >= P && piece <= K))
                        ){
                            // on capture
                            if(piece != e){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);

                            // on empty square
                            }else{
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                            }

                        }
                    }
                }
            }

            // king moves
            if(sideToMove == white ? board[square] == K : board[square] == k){
                // loop over king move offsets
                for(int index = 0; index < 8; index++){
                    // initialize target square
                    int to_square = square + king_offsets[index];

                    // initialize target piece
                    int piece = board[to_square];

                    // make sure target square is on board
                    if(!(to_square & 0x88)){
                        //
                        if(
                            sideToMove == white ? 
                            (piece == e || (piece >= p && piece <= k)) : 
                            (piece == e || (piece >= P && piece <= K))
                        ){
                            // on capture
                            if(piece != e){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);

                            // on empty square
                            }else{
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                            }
                        }
                    }
                }
            }

            // bishop and queen moves
            if (
                sideToMove == white ? 
                board[square] == B || board[square] == Q : 
                board[square] == b || board[square] == q
                )
            {
                // loop over bishop & queen offsets
                for (int index = 0; index < 4; index++){
                    // init target square
                    int to_square = square + bishop_offsets[index];

                    // loop over attack ray
                    while (!(to_square & 0x88)){
                        //init target piece
                        int piece = board[to_square];
                        // if hits own piece
                        if (
                            sideToMove == white ? 
                            board[to_square] >=P && board[to_square] <=K : 
                            board[to_square] >=p && board[to_square] <=k
                            ){
                                break;
                            }

                        // if hits opponent's piece
                        if (
                            sideToMove == white ? 
                            board[to_square] >=p && board[to_square] <=k : 
                            board[to_square] >=P && board[to_square] <=K
                            ){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                break;
                            }

                        // if steps into an empty square
                        if (piece == e){
                            printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                        }

                        //increment target square
                        to_square += bishop_offsets[index];
                    }
                }
            }

            // rook and queen moves
            if (
                sideToMove == white ? 
                board[square] == R || board[square] == Q : 
                board[square] == r || board[square] == q
                )
            {
                // loop over rook & queen offsets
                for (int index = 0; index < 4; index++){
                    // init target square
                    int to_square = square + rook_offsets[index];

                    // loop over attack ray
                    while (!(to_square & 0x88)){
                        //init target piece
                        int piece = board[to_square];
                        // if hits own piece
                        if (
                            sideToMove == white ? 
                            board[to_square] >=P && board[to_square] <=K : 
                            board[to_square] >=p && board[to_square] <=k
                            ){
                                break;
                            }

                        // if hits opponent's piece
                        if (
                            sideToMove == white ? 
                            board[to_square] >=p && board[to_square] <=k : 
                            board[to_square] >=P && board[to_square] <=K
                            ){
                                printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                                break;
                            }

                        // if steps into an empty square
                        if (piece == e){
                            printf("%s%s\n", square_to_coords[square], square_to_coords[to_square]);
                        }

                        //increment target square
                        to_square += rook_offsets[index];
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
    printf("    enPassant:    %s\n", (enPassantSquare != no_square ? square_to_coords[enPassantSquare] : "--")  );
    
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