#include <iostream>
#include <string>
#include <vector>
//编辑距离问题



int editLength(std::string& str1, std::string& str2, int ic, int dc, int rc){
    int length1 = str1.size();
    int length2 = str2.size();
    std::vector<std::vector<int>> dp(length1+1, std::vector<int>(length2+1, 0));
    for(int i=0; i<length1+1; i++){
        dp[i][0] = i * dc;
    }
    for(int j=0; j<length2+1; j++){
        dp[0][j] = j * ic;
    }
    for(int i=1; i<=length1; i++){
        for(int j=1; j<=length2; j++){
            if(str1[i-1] == str2[j-1]){ //注意这里i,j是从1开始的,所以word中的索引为i-1,j-1
                dp[i][j] = dp[i-1][j-1];
            }else{
                int res1 = dc + dp[i-1][j];
                int res2 = ic + dp[i][j-1];
                int res3 = rc + dp[i-1][j-1];
                dp[i][j] = std::min(res1, std::min(res2, res3));
            }
        }
    }
    return dp[length1][length2];
}

int editLength2(std::string& str1, std::string& str2){
    int length1 = str1.size();
    int length2 = str2.size();
    std::vector<std::vector<int>> dp(length1+1, std::vector<int>(length2+1, 0));
    for(int i=0; i<length1+1; i++){
        dp[i][0] = i;
    }
    for(int j=0; j<length2+1; j++){
        dp[0][j] = j;
    }
    for(int i=1; i<=length1; i++){
        for(int j=1; j<=length2; j++){
            if(str1[i-1] == str2[j-1]){ //注意这里i,j是从1开始的,所以word中的索引为i-1,j-1
                dp[i][j] = dp[i-1][j-1];
            }else{
                dp[i][j] = 1 + std::min(dp[i-1][j-1], std::min(dp[i-1][j], dp[i][j-1]));
            }
        }
    }
    return dp[length1][length2];
}

int main(){
    std::string str1("fhioeshaogij");
    std::string str2("fhifoeshaogijx");
    std::cout << editLength(str1, str2, 1, 1, 1) << std::endl;
    std::cout << editLength2(str1, str2) << std::endl;
    return 0;
}