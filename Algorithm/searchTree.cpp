#include <iostream>
#include <unordered_map>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 从L~R，共R-L+1个数字，组成一个二叉搜索树，有多少种可能
int process(int L, int R){
    if(L >= R) return 1;
    int ans = 0;
    for(int i=L; i<=R; i++){
        ans += process(L, i-1) * process(i+1, R);
    }
    return ans;
}
int numTrees(int n){
    return process(1, n);
}

// struct LR{
//     int L;
//     int R;
//     LR(int l, int r): L(l), R(r){}
// };

struct CMP{
    size_t operator()(const std::pair<int,int> &a) const {
        return a.first ^ a.second;
    }
};

std::unordered_map<std::pair<int, int>, int, CMP>& hash;

int process2(int L, int R){
    if(L >= R) return 1;
    if(hash.count(std::make_pair(L, R)) != 0){
        return hash[std::make_pair(L, R)];
    }
    int ans = 0;
    for(int i=L; i<=R; i++){
        ans += process2(L, i-1) * process2(i+1, R);
    }
    hash[std::make_pair(L, R)] = ans;
    return ans;
}

int numTrees2(int n){
    // std::unordered_map<std::pair<int, int>, int, CMP> hash;
    process2(1, n);
}

// 动态规划
// int numTree2(int n){
//     std::vector< std::vector<int> > dp(n+2, std::vector<int>(n+2, 1));
//     for(int i=n-1; i>0; i--){
//         for(int j=i+1; j<n; j++){
//             for(int k=i; k<=j; k++){
//                 dp[i][j] += dp[i][k-1] * dp[k+1][j];
//             }
//         }
//     }
//     return dp[1][n];
// }


int main(){
    std::cout << numTrees(3) << std::endl;
    std::cout << numTrees2(3) << std::endl;
}