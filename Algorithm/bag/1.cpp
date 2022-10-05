//《背包九讲》第一讲

//有N件物品和一个容量为V的背包。
//第i件物品的费用是c[i]，价值是w[i]。
//求解将哪些物品装入背包可使这些物品的费用总和不超过背包容量，且价值总和最大。

// 思路应该是比较简单的，因为每件物品只有一件，可以选择要或者不要。
#include <iostream>
#include <vector>

using namespace std;

void displayDP(vector<vector<int>> &dp){
    for(int i=0; i<dp.size(); i++){
        for(int j=0; j<dp[0].size(); j++){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

vector<int> func(vector<int> &c, vector<int> &w, int bagSize){
    int N = c.size();
    vector<vector<int>> dp(N+1, vector<int>(bagSize+1, 0));
    for(int i=1; i<=N; i++){
        for(int j=1; j<=bagSize; j++){
            if(c[i-1] > j){
                // 放不下
                dp[i][j] = dp[i-1][j];
            }else{
                dp[i][j] = max(dp[i-1][j], w[i-1] + dp[i-1][j-c[i-1]]);
            }
        }
    }
    displayDP(dp);
    return vector<int>();
}

int main(){
    vector<int> c({2,3,4,5});
    vector<int> w({3,4,5,6});
    vector<int> res = func(c,w,8);
    for(int &i : res){
        cout << i << " ";
    }cout << endl;
    return 0;
}