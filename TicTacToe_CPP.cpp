#include <bits/stdc++.h>
using namespace std;

#define COMPUTER 1
#define HUMAN 2

#define SIDE 3

#define COMPUTERMOVE 'O'
#define HUMANMOVE 'X'

void showBoard(char board[][SIDE]) {
    printf("\t\t\t %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("\t\t\t-----------\n");
    printf("\t\t\t %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
}

void showInstructions() {
    printf("\nChoose a cell numbered from 1 to 9 as below and play\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n\n");
}

void initialise(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = '*';
    }
}

void declareWinner(int whoseTurn, string playerName) {
    if (whoseTurn == COMPUTER)
        cout<<"\n\nYay! I won the game... \n\nThat was amazing playing with you "<<playerName<<"!";
    else
        cout <<"Congrats "<< playerName << "! You won the game!\n";
}

bool rowCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[i][0] == board[i][1] &&
            board[i][1] == board[i][2] &&
            board[i][0] != '*')
            return true;
    }
    return false;
}

bool columnCrossed(char board[][SIDE]) {
    for (int i = 0; i < SIDE; i++) {
        if (board[0][i] == board[1][i] &&
            board[1][i] == board[2][i] &&
            board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE]) {
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '*') ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*'))
        return true;
    return false;
}

bool gameOver(char board[][SIDE]) {
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI) {
    if (gameOver(board)) {
        return isAI ? -10 : 10;
    }
    if (depth == SIDE * SIDE) {
        return 0;
    }

    int bestScore = isAI ? -999 : 999;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = isAI ? COMPUTERMOVE : HUMANMOVE;
                int score = minimax(board, depth + 1, !isAI);
                board[i][j] = '*';

                bestScore = isAI ? max(bestScore, score) : min(bestScore, score);
            }
        }
    }
    return bestScore;
}

int bestMove(char board[][SIDE], int moveIndex) {
    int bestScore = -999, x = -1, y = -1;
    for (int i = 0; i < SIDE; i++) {
        for (int j = 0; j < SIDE; j++) {
            if (board[i][j] == '*') {
                board[i][j] = COMPUTERMOVE;
                int score = minimax(board, moveIndex + 1, false);
                board[i][j] = '*';

                if (score > bestScore) {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

void playTicTacToe(int whoseTurn, string playerName) {
    char board[SIDE][SIDE];
    int moveIndex = 0, x = 0, y = 0;

    initialise(board);
    showInstructions();

    while (!gameOver(board) && moveIndex != SIDE * SIDE) {
        int n;
        if (whoseTurn == COMPUTER) {
            n = bestMove(board, moveIndex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = COMPUTERMOVE;
            printf("\nI have put a %c in cell %d\n\n", COMPUTERMOVE, n + 1);
            showBoard(board);
            moveIndex++;
            whoseTurn = HUMAN;
        } else {
            printf("\nYou can insert in the following positions: ");
            for (int i = 0; i < SIDE; i++)
                for (int j = 0; j < SIDE; j++)
                    if (board[i][j] == '*')
                        printf("%d ", (i * 3 + j) + 1);
            printf("\n\nEnter the position: ");
            cin >> n;
            n--;
            x = n / SIDE;
            y = n % SIDE;
            if (board[x][y] == '*' && n >= 0 && n < 9) {
                board[x][y] = HUMANMOVE;
                cout << "\nYou have put an " << HUMANMOVE << " in cell " << n + 1 << "\n\n";
                showBoard(board);
                moveIndex++;
                whoseTurn = COMPUTER;
            } else {
                printf("\nInvalid move! Try again.\n\n");
            }
        }
    }

    if (!gameOver(board) && moveIndex == SIDE * SIDE)
        cout<<"\n\nIt's a draw match "<<playerName<<"!\n\nYou are challenging indeed!";
    else
        declareWinner(whoseTurn == COMPUTER ? HUMAN : COMPUTER, playerName);
}

int main() {
    printf("\n---------------------------------------------------------------\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n---------------------------------------------------------------\n\n");

    string playerName;
    cout << "\n\nHello there! \n\nPlease tell me your name: ";
    getline(cin, playerName);

    cout<<"\n\n\nWelcome "<<playerName<<"! Let's play TicTacToe together.";
    char cont = 'y';
    do {
        char choice;
        cout<<"\n\n\n\n"<<playerName<<", do you want to start first? (y/n): ";
        cin >> choice;

        if (choice == 'n')
            playTicTacToe(COMPUTER, playerName);
        else
            playTicTacToe(HUMAN, playerName);

        printf("\n\nDo you want to quit? (y/n): ");
        cin >> cont;

        if (cont == 'n') cout<<"\n\nGreat "<<playerName<<"! Let's play again...";

        if (cont == 'y') cout<<"\n\nThat was amazing to play with you "<<playerName<<"! Hoping to see you soon...";
    } while (cont == 'n');

    return 0;
}