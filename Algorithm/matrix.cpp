#include <iostream>
#include <vector>

using namespace std;

int process(int** matrix, int now, int startRow, int startCol, int endRow, int endCol){
    if(startRow == endRow && startCol == endCol){
        return 0;
    }
    if(startRow == endRow){
        return process(matrix, now+matrix[startRow][startCol], startRow, startCol+1, endRow, endCol);
    }else if(startCol == endCol){
        return process(matrix, now+matrix[startRow][startCol], startRow+1, startCol, endRow, endCol);
    }else{
        return std::max(
            process(matrix, now+matrix[startRow][startCol], startRow, startCol+1, endRow, endCol),
            process(matrix, now+matrix[startRow][startCol], startRow+1, startCol, endRow, endCol)
        );
    }
}

int process(vector<vector<int>>& matrix, int startRow, int startCol, int endRow, int endCol){
    if(startRow == endRow && startCol == endCol){
        return matrix[endRow][endCol];
    }
    if(startRow == endRow){
        return matrix[startRow][startCol] + process(matrix, startRow, startCol+1, endRow, endCol);
    }else if(startCol == endCol){
        return matrix[startRow][startCol] + process(matrix, startRow+1, startCol, endRow, endCol);
    }else{
        return matrix[startRow][startCol]+ std::max(
            process(matrix, startRow, startCol+1, endRow, endCol),
            process(matrix, startRow+1, startCol, endRow, endCol)
        );
    }
}
// int maxValue(vector<vector<int>>& matrix, int matrixRowLen, int matrixColLen) {
//     // write code here
//     return matrix[0][0] + max(process(matrix, 1, 0, matrixRowLen-1, matrixColLen-1),
//         process(matrix, 0, 1, matrixRowLen-1, matrixColLen-1));
// }

int maxValue(vector<vector<int>>& matrix, int matrixRowLen, int matrixColLen) {
    vector<vector<int>> dp(matrixRowLen, vector<int>(matrixColLen, 0));
    dp[matrixRowLen-1][matrixColLen-1] = matrix[matrixRowLen-1][matrixColLen-1];
    for(int i=matrixRowLen-2; i>=0; i--){
        dp[i][matrixColLen-1] = matrix[i][matrixColLen-1] + dp[i+1][matrixColLen-1];
    }
    for(int i=matrixColLen-2; i>=0; i--){
        dp[matrixRowLen-1][i] = matrix[matrixRowLen-1][i] + dp[matrixRowLen-1][i+1];
    }
    for(int i=matrixRowLen-2; i>=0; i--){
        for(int j=matrixColLen-2; j>=0; j--){
            dp[i][j] = matrix[i][j] + max(dp[i+1][j], dp[i][j+1]);
        }
    }
    return dp[0][0];
}


int main(){
    // int matrix[3][3] = {{2,3,1},{2,5,3},{4,2,1}};
    vector<vector<int>> matrix {{2,3,1},{2,5,3},{4,2,1}};
    std::cout << maxValue(matrix, 3, 3) << std::endl;
}