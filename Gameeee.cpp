/* KELOMPOK Game
AKBAR KHALIFA JAYADININGRAT - 2702361280
BENEDIKTUS EVANDY UNAMO - 2702227864
FELIX NATAN LIM - 2702262066 */

#include <stdio.h>
#include <string.h>

// Struktur data pemain
struct Player {
    char name[50];
    int wins;
};

// Fungsi untuk menampilkan papan permainan
void displayBoard(char board[3][3]) {
    printf("\nPapan Permainan:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

// Fungsi untuk memeriksa apakah ada pemenang
int checkWinner(char board[3][3], char player) {
    // Memeriksa baris dan kolom
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) {
            return 1; // Baris
        }
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player) {
            return 1; // Kolom
        }
    }

    // Memeriksa diagonal
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) {
        return 1; // Diagonal kiri atas ke kanan bawah
    }
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) {
        return 1; // Diagonal kanan atas ke kiri bawah
    }

    return 0; // Tidak ada pemenang
}

// Fungsi untuk memeriksa apakah papan penuh (seri)
int isBoardFull(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return 0; // Papan tidak penuh
            }
        }
    }
    return 1; // Papan penuh (seri)
}

// Fungsi untuk menyimpan data kemenangan pemain ke dalam file
void savePlayerWins(struct Player *players) {
    FILE *file = fopen("player_wins.txt", "w");

    if (file != NULL) {
        for (int i = 0; i < 2; i++) {
            fprintf(file, "%s %d\n", players[i].name, players[i].wins);
        }

        fclose(file);
        printf("Data kemenangan pemain berhasil disimpan ke dalam file 'player_wins.txt'.\n");
    } else {
        printf("Gagal membuka file untuk penulisan.\n");
    }
}

// Fungsi untuk memuat data kemenangan pemain dari file
void loadPlayerWins(struct Player *players) {
    FILE *file = fopen("player_wins.txt", "r");

    if (file != NULL) {
        for (int i = 0; i < 2; i++) {
            fscanf(file, "%s %d", players[i].name, &players[i].wins);
        }

        fclose(file);
        printf("Data kemenangan pemain berhasil dimuat dari file 'player_wins.txt'.\n");
    } else {
        printf("Gagal membuka file untuk membaca. Inisialisasi skor pemain ke 0.\n");
        for (int i = 0; i < 2; i++) {
            players[i].wins = 0;
        }
    }
}

// Fungsi untuk mereset papan permainan
void resetGameBoard(char board[3][3]) {
    memset(board, ' ', sizeof(board));
    printf("Papan permainan berhasil direset.\n");
}

// Fungsi untuk menampilkan data kemenangan pemain di dalam program
void displayPlayerWins(struct Player *players) {
    printf("\nSkor Pemain:\n");
    for (int i = 0; i < 2; i++) {
        printf("%s: %d\n", players[i].name, players[i].wins);
    }
}

// Fungsi untuk menjalankan permainan Tic-Tac-Toe
void playTicTacToe(struct Player *players) {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int currentPlayer = 1; // 1 untuk Player1, 2 untuk Player2

    printf("Selamat datang di Game Tic-Tac-Toe!\n");
    
    printf("Masukan posisi kamu seperti dibawah ini\n");
	printf("0 0   0 1   0 2\n");
	printf("1 0   1 1   1 2\n");
	printf("2 0   2 1   2 2\n");

    // Contoh memuat data kemenangan pemain dari file
    loadPlayerWins(players);

    do {
        displayPlayerWins(players);
        displayBoard(board);

        char marker = (currentPlayer == 1) ? 'X' : 'O';
        int row, col;

        // Input posisi langkah dari pemain
        printf("Pemain %c, masukkan baris (0-2): ", marker);
        scanf("%d", &row);
        printf("Pemain %c, masukkan kolom (0-2): ", marker);
        scanf("%d", &col);

        // Memeriksa apakah langkah valid
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            printf("Langkah tidak valid. Coba lagi.\n");
            continue;
        }

        // Menyimpan langkah pemain ke papan
        board[row][col] = marker;

        // Memeriksa apakah ada pemenang
        if (checkWinner(board, marker)) {
            displayBoard(board);
            printf("Pemain %c menang!\n", marker);

            // Update statistik pemain
            int winnerIndex = currentPlayer - 1;
            players[winnerIndex].wins++;

            // Menyimpan data kemenangan pemain ke dalam file
            savePlayerWins(players);

            // Menampilkan skor pemain
            displayPlayerWins(players);

            // Reset papan permainan
            resetGameBoard(board);
        }

        // Memeriksa apakah papan penuh (seri)
        if (isBoardFull(board)) {
            displayBoard(board);
            printf("Permainan seri!\n");

            // Menyimpan data kemenangan pemain ke dalam file
            savePlayerWins(players);

            // Menampilkan skor pemain
            displayPlayerWins(players);

            // Reset papan permainan
            resetGameBoard(board);
        }

        // Ganti pemain
        currentPlayer = (currentPlayer == 1) ? 2 : 1;

    } while (1); // Terus bermain hingga ada pemenang atau seri
}

int main() {
    struct Player players[2] = {{"Player1", 0}, {"Player2", 0}};

    // Main loop permainan Tic-Tac-Toe
    playTicTacToe(players);

    return 0;
}

