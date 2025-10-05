#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char **board;                                      // the game board using pointer to 2D array
int N;                                             // board size
char players[3] = {'X','O','Z'};                   // for 3 player game mode

void makeBoard() {                                 // make the board using malloc
    board = (char **)malloc(N * sizeof(char *));   // allocate rows
    for (int i = 0; i < N; i++) {
        board[i] = (char *)malloc(N * sizeof(char));  // allocate each row
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = ' ';                       // for space
}


void showBoard() {                                   // show board on screen with row and column numbers
    printf("\n   ");  
    for (int j = 0; j < N; j++) {
        printf(" %d  ", j);                          // column numbers
    }
    printf("\n");

    for (int i = 0; i < N; i++) {
        printf(" %d ", i);                           // row numbers
        for (int j = 0; j < N; j++) {
            printf(" %c ", board[i][j]);
            if (j < N - 1) printf("|");              // seperating with line
        }
        printf("\n");

        if (i < N - 1) {
            printf("   ");                          // align lines 
            for (int k = 0; k < N; k++) {
                printf("---");
                if (k < N - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int win(char s) {                                   // check win
    int i,j;
    for (i = 0; i < N; i++) {                            //  check all row
        int check=1;
        for (j = 0; j < N; j++) 
        if (board[i][j]!=s) check=0;
        if (check) 
        return 1;
    }

    for (j = 0; j < N; j++) {                            // check all column
        int check=1;
        for (i = 0; i < N; i++) 
        if (board[i][j]!=s) check=0;
        if (check) 
        return 1;
    }

    int check=1;                                      // check diagonal left to right
    for (i = 0; i < N; i++) 
    if (board[i][i]!=s) check=0;
    if (check) 
    return 1;
    check=1;                                          //  check diagonal right to left
    for (i = 0; i < N; i++) 
    if (board[i][N-1-i]!=s) check=0;
    if (check) 
    return 1;

    return 0;                                     // if no win
}

int draw() {                                      // check draw
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (board[i][j]==' ') 
            return 0;                             // still empty box
                                         
    return 1;                                     // board is full
}

void computerMove() {                                 // computer makes move
    int r,c; // row and column
    do {
        r = rand()%N;                             // pick random row
        c = rand()%N;                             // pick random column
    } while (board[r][c] != ' ');                 // repeat if cell is not empt
    board[r][c] = 'O';                            // computer symbol 'O'                  
    printf("Computer moves to %d %d\n",r,c);
}

// Output
int main() {
    printf("TIC TAC TOE GAME\n");

    printf("Enter board size N (3 <= N <= 10): ");   // get board size from user
    scanf("%d",&N);

    makeBoard();                                     // create board

    int mode;                                        // choose game mode
    printf("Select Game Mode: \n");
    printf("1. Two players (User vs User)\n");
    printf("2. User vs computer\n");
    printf("3. Three players\n");
    printf("Enter choice (1-3): ");
    scanf("%d",&mode);

    srand(time(0));                                 // for computer random

    FILE *f;                                        // open file for saving moves
    f = fopen("logfile.txt","w");

    int turn=0;                                     // 0=X,1=O,2=Z
    int row,col;

    while (1) {
        showBoard();                                // display board at each turn
        char now;

        if (mode==1) {                              // user vs user game mode
            now = (turn==0)?'X':'O';                // pick current player symbol
            printf("Player %c enter row and col: ",now);
            scanf("%d %d",&row,&col);               // get move from user

            if (row<0 || row>=N || col<0 || col>=N || board[row][col]!=' ') {           // check if move is valid
                printf("wrong move\n");
                continue; 
            }

            board[row][col]=now;                      // make the move
            fprintf(f,"Player %c moves (row and col): %d %d\n",now,row,col);    //saves in file

            if (win(now)) {                           //check win and save it
                showBoard();
                printf("Player %c Is The Winner\n",now); 
                fprintf(f,"Player %c Is The Winner \n",now);
                break; 
            }

            if (draw()) {                             // check draw and save it
                showBoard(); 
                printf("Draw\n"); 
                fprintf(f,"Draw\n"); 
                break; 
            }

            turn = 1-turn;                           // swap turns

        } else if (mode==2) {                        // user vs computer game mode
            
            printf("You are X Enter row and col: ");   // X is user
            scanf("%d %d",&row,&col);

            if (row<0 || row>=N  || col<0 || col>=N || board[row][col]!=' ') {  // check if move is valid
                printf("wrong move\n"); 
                continue; 
            }
            board[row][col]='X';                                               // make the move
            fprintf(f,"Player X moves (row and col): %d %d\n",row,col);

            if (win('X')) {                                                   //check win and save it
                showBoard(); 
                printf("Player X Is The Winner\n"); 
                fprintf(f,"X Is The Winner\n"); 
                break; 
            }
            if (draw()) {                                                     // check draw and save it
                showBoard(); 
                printf("Draw\n"); 
                fprintf(f,"Draw\n"); 
                break; 
            }

            
            computerMove();                                                       // computer turn

            for (int i = 0; i < N; i++)                                                // make the computer move
            for (int j = 0; j < N; j++) 
            if (board[i][j]=='O') 
            {row=i;col=j;} 
            fprintf(f,"Computer 'O' moves (row and col): %d %d\n",row,col);

            if (win('O')) {                             // check if computer wins
                showBoard(); 
                printf("COMPUTER Is The Winner\n"); 
                fprintf(f,"Computer Wins\n"); 
                break; 
            }
            if (draw()) {                              // check if computer draw
                showBoard(); 
                printf("Draw\n"); 
                fprintf(f,"Draw\n"); 
                break; 
            }

        } else if (mode==3) {                     // Three players game mode
            now = players[turn];                  // pick player's symbol

            printf("Player %c enter row and col: ",now);                                 // get move
            scanf("%d %d",&row,&col);

            if (row<0 || row>=N || col<0 || col>=N || board[row][col]!=' ') {            // check if move is valid
                printf("wrong move\n"); 
                continue; 
            }

            board[row][col]=now;                                                          // make move
            fprintf(f,"Player %c moves (row and col):  %d %d\n",now,row,col);

            if (win(now)) {                                                               //check win and save it
                showBoard(); 
                printf("Player %c Is The Winner\n",now); 
                fprintf(f,"Player %c Is The Winner\n",now); 
                break; 
            }
            if (draw()) {                                                                  //check draw and save it
                showBoard(); 
                printf("Draw\n"); 
                fprintf(f,"Draw\n"); 
                break; 
            }

            turn = (turn+1)%3;                     // move to the next player
        }
    }

    fclose(f);                                    // close logfile
    printf("\nGame saved in logfile.txt\n");

for (int i = 0; i < N; i++) {                     // free allocated memory
    free(board[i]);
}
free(board);

    return 0;
}
