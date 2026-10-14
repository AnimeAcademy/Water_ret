#include "water.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <tuple>

long int waterret(char const* filename) {
    std::ifstream file(filename);

    int row, col;

    if (!file.is_open()) {
        printf("File failed to open");
        return -1;
    }

    file >> row >> col;
    
    //READ FILE
    std::vector<std::vector<int>> grid(row, std::vector<int>(col));
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            file >> grid[i][j];
        }
    }

    // DONE WITH FILE SO CLOSE
    file.close();
    //1040889255
    std::vector<std::vector<int>> kill(row, std::vector<int>(col, 1203449));

    typedef std::tuple<int, int, int> T;
    std::priority_queue<T, std::vector<T>, std::greater<T>> pq;

    // Mark cells on the outside off
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (i == 0 || i == row - 1 || j == 0 || j == col - 1) {
                kill[i][j] = grid[i][j];
                pq.push(std::make_tuple(grid[i][j], i, j));
            }
        }
    }

   
    const int temp[] = { -1, 1, 0, 0 };
    const int temp1[] = { 0, 0,-1, 1 };

    while (!pq.empty()) {
        T top = pq.top();
        pq.pop();

        int num = std::get<0>(top);
        int r = std::get<1>(top);
        int c = std::get<2>(top);

        if (num > kill[r][c]) continue;

        for (int d = 0; d < 4; ++d) {
            int numR = r + temp[d];
            int numC = c + temp1[d];
            if (numR < 0 || numR >= row || numC < 0 || numC >= col) continue;

            int finalKill = std::max(grid[numR][numC], num);
            if (finalKill < kill[numR][numC]) {
                kill[numR][numC] = finalKill;
                pq.push(std::make_tuple(finalKill, numR, numC));
            }
        }
    }

    long int total = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            total += kill[i][j] - grid[i][j];
        }
    }
   
    return total;
}