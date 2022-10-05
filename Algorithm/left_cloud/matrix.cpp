#include <iostream>
#include <vector>
#include<iomanip>

//打印(r1,c1)到(r2,c2)构成的矩形边框
void printEdge(std::vector< std::vector<int> >& matrix, int r1, int c1, int r2, int c2){
    if(r1 > r2 || c1 > c2){
        return;
    }
    if(r1 == r2){  //矩形是一条横线
        for(int j=c1; j<=c2; j++){
            std::cout << std::setw(4) << matrix[r1][j];
        }
    }else if(c1 == c2){  //矩形是一条竖线
        for(int i=r1; i<=r2; i++){
            std::cout << std::setw(4) << matrix[i][c1];
        }
    }else{
        for(int i=r1, j=c1; j<c2; j++){
            std::cout << std::setw(4) << matrix[i][j];
        }
        for(int i=r1, j=c2; i<r2; i++){
            std::cout << std::setw(4) << matrix[i][j];
        }
        for(int i=r2, j=c2; j>c1; j--){
            std::cout << std::setw(4) << matrix[i][j];
        }
        for(int i=r2, j=c1; i>r1; i--){
            std::cout << std::setw(4) << matrix[i][j];
        }
    }
}

//螺旋打印二维数组
void rotatePrintMatrix(std::vector< std::vector<int> >& matrix){
    int row = matrix.size();
    int col = matrix[0].size();
    int r1 = 0, c1 = 0, r2 = row - 1, c2 = col - 1;
    while(r1 <= r2 && c1 <= c2){
        printEdge(matrix, r1, c1, r2, c2);
        r1++; c1++; r2--; c2--;
    }
    std::cout << std::endl;
}

//旋转(rc1,rc1)到(rc2,rc2)构成的正方形边框
void rotateEdge(std::vector< std::vector<int> >& box, int rc1, int rc2){
    int group = rc2 - rc1;
    for(int g=0; g<group; g++){
        int temp = box[rc1][rc1+g];
        box[rc1][rc1+g] = box[rc2-g][rc1];
        box[rc2-g][rc1] = box[rc2][rc2-g];
        box[rc2][rc2-g] = box[rc1+g][rc2];
        box[rc1+g][rc2] = temp;
    }
}

//原地顺时针旋转一个正方形矩阵
void rotateBox(std::vector< std::vector<int> >& box){
    int row = box.size();
    int col = box[0].size();
    if(row != col){
        std::cout << "error!" << std::endl;
    }
    int rc1 = 0, rc2 = row - 1;
    while(rc1 < rc2){
        rotateEdge(box, rc1, rc2);
        rc1++; rc2--;
    }
}

//打印(r1,c2)与(r2,c2)之间的斜线,falg为true时从1到2,flag为false时从2到1
void printLine(std::vector< std::vector<int> >& matrix, int r1, int c1, int r2, int c2, bool flag){
    if(flag){
        while(r1 >= r2){
            std::cout << std::setw(4) << matrix[r1][c1];
            r1--; c1++;
        }
    }else{
        while(r1 >= r2){
            std::cout << std::setw(4) << matrix[r2][c2];
            r2++; c2--;
        }
    }
}

void printZig(std::vector< std::vector<int> >& matrix){
    int row = matrix.size();
    int col = matrix[0].size();
    int r1 = 0, c1 = 0, r2 = 0, c2 = 0;
    bool flag = true;
    while(r1 + c1 <= row + col - 2){
        printLine(matrix, r1, c1, r2, c2, flag);
        flag = !flag;
        if(r1 == row - 1){
            c1++;
        }else{
            r1++;
        }
        if(c2 == col - 1){
            r2++;
        }else{
            c2++;
        }
    }
    std::cout << std::endl;
}


int main(int argc, char const *argv[]){
    std::vector< std::vector<int> > matrix(4,std::vector<int>());
    matrix[0].push_back(1);matrix[0].push_back(2);matrix[0].push_back(3);matrix[0].push_back(4);
    matrix[1].push_back(5);matrix[1].push_back(6);matrix[1].push_back(7);matrix[1].push_back(8);
    matrix[2].push_back(9);matrix[2].push_back(10);matrix[2].push_back(11);matrix[2].push_back(12);
    matrix[3].push_back(13);matrix[3].push_back(14);matrix[3].push_back(15);matrix[3].push_back(16);

    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << std::endl;
    }
    rotatePrintMatrix(matrix);
    rotateBox(matrix);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            std::cout << std::setw(4) << matrix[i][j];
        }
        std::cout << std::endl;
    }
    printZig(matrix);
    return 0;
}