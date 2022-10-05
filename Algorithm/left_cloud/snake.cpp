#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <climits>

/**
    这个题的边界问题很烦，回头再看
 */
struct Info{
    int no; // 未使用能力所达到的最长长度。
    int yes; //使用能力达到的最长长度。
    Info(int no, int yes): no(no), yes(yes){}
};

// 从最左侧出发，到达board[row][col]的最长长度。
Info process(std::vector <std::vector<int> >& board, int row, int col){
    //BaseCase
    if(col == 0){
        return Info(board[row][col], -board[row][col]);
    }
    int preNo = -1;
    int preYes = -1;
    if(row != 0){
        Info leftUP = process(board, row-1, col-1);
        preNo = leftUP.no >= 0 ? leftUP.no : preNo;
        preYes = leftUP.yes >= 0 ? leftUP.yes : preYes;
    }
    if(row != board.size() - 1){
        Info leftDown = process(board, row+1, col-1);
        preNo = leftDown.no >= 0 ? std::max(leftDown.no, preNo) : preNo;
        preYes = leftDown.yes >= 0 ? std::max(leftDown.yes, preYes) : preYes;
    }
    Info left = process(board, row, col - 1);
    preNo = left.no >= 0 ? std::max(left.no, preNo) : preNo;
    preYes = left.yes >= 0 ? std::max(left.yes, preYes) : preYes;

    int curNo = -1;
    int curYes = -1;
    curNo = preNo >= 0 ? preNo + board[row][col] : curNo;
    curYes = preYes >= 0 ? std::max(preNo - board[row][col], preYes + board[row][col]) : curYes;
    return Info(curNo, curYes);
}

int snake(std::vector <std::vector<int> >& board){
    if(board.size() == 0) return 0;
    if(board[0].size() == 0) return 0;
    int result = INT_MIN;
    for(int row = 0; row < board.size(); row++){
        for(int col = 0; col < board[0].size(); col++){
            Info res = process(board, row, col);
            result = std::max(result, std::max(res.no, res.yes));
        }
    }
    return result;
}

int main(int argc, char const *argv[]){
    srand((unsigned int)time(NULL));
    int row = rand()%10 + 1;
    int col = rand()%20 + 1;
    std::vector< std::vector<int> > game(row, std::vector<int>(col, 0));
    for(int i=0; i<row; i++){
        for(int j=0; j<col; j++){
            game[i][j] = rand()%20 - 10;
            std::cout << game[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    std::cout << snake(game) << std::endl;
    return 0;
}