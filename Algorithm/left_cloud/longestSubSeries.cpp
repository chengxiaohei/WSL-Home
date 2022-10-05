#include <iostream>
#include <vector>

//数组的最长递增子序列问题
//注意子序列可以不连续，但是需要保持顺序不变
//子数组必须连续顺序不变
//子集可以不连续，可以随意变化顺序

// 普通的动态规划，时间复杂度O(N^2)
int longestSubSeries(std::vector<int>& arr){
    int length = arr.size();
    if(length <= 1) return length;
    int dp[length] = {1};  //dp[i]表示表示arr[0~i]数组中的最长递增子序列
    for(int i=1; i<length; i++){
        int maxLengthIndex = -1;
        int maxLength = 0;
        for(int j=i-1; j>=0; j--){
            //在0~j之间寻找所有arr[j] < arr[i]中dp[j]最大的那个
            if(arr[i] >= arr[j] && dp[j] > maxLength){
                //在dp[0]~dp[j]之间最大值的索引
                maxLength = dp[j];
                maxLengthIndex = j;
            }
        }
        dp[i] = maxLengthIndex == -1 ? 1 : dp[maxLengthIndex]+1;
    }
    //打印dp数组看一下
    for(int i=0; i<length; i++){
        std::cout << dp[i] << "\t";
    }std::cout << std::endl;
    //dp数组中的最大值就是答案
    int maxLength = 0;
    for(int i=0; i<length; i++){
        maxLength = dp[i] > maxLength ? dp[i] : maxLength;
    }
    return maxLength;
}

//优化后的动态规划，时间复杂度O(NlogN)
int longestSubSeries2(std::vector<int>& arr){
    int length = arr.size();
    if(length <= 1) return length;
    int dp[length] = {1};  //dp[i]表示表示arr[0~i]数组中的最长递增子序列
    for(int i=1; i<length; i++){
        //优化dp[i]的填写过程，可以使用空间换时间的思路，构造一个辅助数组，创造单调性，尝试将N复杂度过程降低为logN复杂度
        /*暂时不会做*/
    }
    //打印dp数组看一下
    for(int i=0; i<length; i++){
        std::cout << dp[i] << "\t";
    }std::cout << std::endl;
    //dp数组中的最大值就是答案
    int maxLength = 0;
    for(int i=0; i<length; i++){
        maxLength = dp[i] > maxLength ? dp[i] : maxLength;
    }
    return maxLength;
}


int main(int argc, char const *argv[]){
    std::vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(2);
    arr.push_back(4);
    arr.push_back(3);
    arr.push_back(7);
    arr.push_back(3);
    arr.push_back(5);
    arr.push_back(1);
    arr.push_back(7);
    arr.push_back(-1);
    arr.push_back(8);
    arr.push_back(2);
    for(int i : arr){
        std::cout << i << "\t";
    }std::cout << std::endl;
    std::cout << longestSubSeries(arr) << std::endl;
    return 0;
}