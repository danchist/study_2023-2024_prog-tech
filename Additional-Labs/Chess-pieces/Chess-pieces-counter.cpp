// Условие (Task)
// Реализовать оптимальные алгоритмы расчёта достпуного хода для каждого типа фигуры
// из каждой начальной точки шахматной доски. При условии что фигура 1 на доске.
// а так же вывести по запросу достпуный ход. Функция вывода содержит в качестве аргументов
// функции 3 переменные: коллекция в которой хранится ходы, позиция из которой производится
// ход, и тип фигуры.
// Вcего 6 типов фигур:
// Rook, Pawn, Bishop, Knight, Queen, King

// Увидеть требуемый вывод можно в файле "Условие (Task).md"

// Решение начинается тут.

#include <iostream>

const int n = 8;

void pawnMoves(int x, int y, int board[n][n]){
    if (x + 1 < n) {
        board[x + 1][y] = 1;
        board[x][y] = 2;
    }
}

void rookMoves(int x, int y, int board[n][n]){
    for (int i=0; i < n; i++){
        board[x][i] = 1;
        board[i][y] = 1;
    }
    board[x][y] = 2;
}

void bishopMoves(int x, int y, int board[n][n]){
    for (int i=1; i < n + 1; i++){
        if (x + i <= n and y + i <= n){
            board[x + i][y + i] = 1;

        }
        if (x - i >= 0 and y + i >= 0){
            board[x - i][y + i] = 1;
        }
        if (x + i >= 0 and y - i >= 0){
            board[x + i][y - i] = 1;
        }
        if (x - i >= 0 and y - i >= 0){
            board[x - i][y - i] = 1;
        }
    }
    board[x][y] = 2;
}

void knightMoves(int x, int y, int board[n][n]){
    for (int i; i < 9; i++){
        if (0 < x+1 < n and 0 < y+2 < n){
            board[x+1][y+2] = 1;
        }
        if (0 < x-1 < n and 0 < y+2 < n){
            board[x-1][y+2] = 1;
        }
        if (0 < x+1 < n and 0 < y-2 < n){
            board[x+1][y-2] = 1;
        }
        if (0 < x-1 < n and 0 < y-2 < n){
            board[x-1][y-2] = 1;
        }

        if (0 < x+2 < n and 0 < y+1 < n){
            board[x+2][y+1] = 1;
        }
        if (0 < x-2 < n and 0 < y+1 < n){
            board[x-2][y+1] = 1;
        }
        if (0 < x+2 < n and 0 < y-1 < n){
            board[x+2][y-1] = 1;
        }
        if (0 < x-2 < n and 0 < y-1 < n){
            board[x-2][y-1] = 1;
        }
        board[x][y] = 2;
    }
}

void kingMoves(int x, int y, int board[n][n]){
    if (0<x+1<n){
        board[x+1][y] = 1;
        if (0<y+1<n){
            board[x+1][y+1] = 1;
            board[x][y+1] = 1;
        }
        if (0<y-1<n){
            board[x+1][y-1] = 1;
            board[x][y-1] = 1;
        }
    }
    if (0<x-1<n){
        board[x-1][y] = 1;
        if (0<y+1<n){
            board[x-1][y+1] = 1;
            board[x][y+1] = 1;
        }
        if (0<y-1<n){
            board[x-1][y-1] = 1;
            board[x][y-1] = 1;
        }

    }
    board[x][y] = 2;
}

void queenMoves(int x, int y, int board[n][n]){
    bishopMoves(x, y, board);
    rookMoves(x, y, board);
}

int main(){
    int board[n][n] = {0};
    int x;
    int y;
    std::string name;

    std::cout << "Enter coordinates \n";
    std:: cin >> x >> y;
    x -= 1;
    y -= 1;

//    std:: cout << x << " " << y;
    std::cout << "Enter the name of the chess piece \n";
    std::cin >> name;
//    std::cout << name;



    if (name == "pawn" or name == "Pawn"){
        pawnMoves(x, y, board);
    }
    else if (name == "rook" or name == "Rook"){
        rookMoves(x, y, board);
    }
    else if (name == "knight" or name == "Knight"){
        knightMoves(x, y, board);
    }
    else if (name == "king" or name == "King"){
        kingMoves(x, y, board);
    }
    else if (name == "bishop" or name == "Bishop"){
        bishopMoves(x, y, board);
    }
    else if (name == "queen" or name == "Queen"){
        queenMoves(x, y, board);
    }
    else{
        std::cout<< "wrong name \n";
    }

// печать доски

    for (int i=0; i < n; i++){
        std::cout << "[";
        for (int j=0; j < n; j++){
            std::cout << board[i][j] << ",";
        }
        std::cout << "]";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
