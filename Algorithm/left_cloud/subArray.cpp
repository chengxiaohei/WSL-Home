#include <iostream>
#include <vector>
#include <climits>

//需要保证arr中有数据
int maxSubArraySum(std::vector<int>& arr){
    int curSum = 0;
    int maxValue = INT_MIN;
    for(int i=0; i<arr.size(); i++){
        curSum += arr[i];
        if(curSum > maxValue){
            maxValue = curSum;
        }
        curSum = curSum < 0 ? 0 : curSum;
    }
    return maxValue;
}

//需要保证matrix中有数据,
//通过将矩阵压缩为数组解决问题
int maxSubMatrixSum(std::vector<std::vector<int>>& matrix){
    int row = matrix.size();
    int col = matrix[0].size();
    int maxValue = INT_MIN;
    std::vector<int> sumArray(col, 0);
    for(int i=0; i<row; i++){
        for(int j=i; j<row; j++){
            //构建sumArray数组
            for(int r = i; r<=j; r++){
                for(int k=0; k<col; k++){
                    sumArray[k] += matrix[r][k];
                }
            }
            //对sumArray数组求最大子数组
            maxValue = std::max(maxValue, maxSubArraySum(sumArray));
            //将sumArray数组清零
            for(int c=0; c<col; c++){
                sumArray[c] = 0;
            }
        }
    }
    return maxValue;
}


int main(int argc, char const *argv[]){
    std::vector<int> arr;
    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(-1);
    arr.push_back(-10);
    arr.push_back(11);
    arr.push_back(4);
    arr.push_back(-6);
    arr.push_back(9);
    arr.push_back(20);
    arr.push_back(-10);
    arr.push_back(-2);
    int res1 = maxSubArraySum(arr);
    std::cout << res1 << std::endl;

    std::vector<std::vector<int>> matrix(4, std::vector<int>());
    matrix[0].push_back(1);    matrix[0].push_back(4);    matrix[0].push_back(1);    matrix[0].push_back(1);
    matrix[1].push_back(9);    matrix[1].push_back(1);    matrix[1].push_back(7);    matrix[1].push_back(7);
    matrix[2].push_back(-1);    matrix[2].push_back(0);    matrix[2].push_back(1);    matrix[2].push_back(1);
    matrix[3].push_back(6);    matrix[3].push_back(1);    matrix[3].push_back(-91);    matrix[3].push_back(-10);
    int res2 = maxSubMatrixSum(matrix);
    std::cout << res2 << std::endl;
    return 0;
}