#include <iostream>
#include <vector>

using namespace std;

// 从cur开始，到n结束，寻找所有容量为k的分组
void process(int n, int k, int cur, vector<int> &tmp, vector<vector<int>> &res){
    if(tmp.size() == k){
        res.push_back(tmp);
        return;
    }
    if(cur > n) return;
    tmp.push_back(cur);
    process(n, k, cur + 1, tmp, res);
    tmp.pop_back();
    process(n, k, cur + 1, tmp, res);
}

vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> res;
    vector<int> tmp;
    process(n, k, 1, tmp, res);
    return res;
}


int main(){
    vector<vector<int>> res = combine(4, 2);
    for(auto &r : res){
        for(auto &i : r){
            printf("%d ", i);
        }
        printf("\n");
    }
    return 0;
}