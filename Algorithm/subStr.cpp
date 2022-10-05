#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

string LCS(string s1, string s2) {
    vector<vector<string>> dp(s1.size()+1, vector<string>(s2.size()+1, ""));
    for(int i=1; i<s1.size()+1; i++){
        for(int j=1; j<s2.size()+1; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1] + s1[i-1];
            }else{
                dp[i][j] = dp[i-1][j].size() > dp[i][j-1].size() ? dp[i-1][j] : dp[i][j-1];
            }
        }
    }
    return dp[s1.size()][s2.size()].size() == 0 ? "-1" : dp[s1.size()][s2.size()];
}

int main(){
    string s1 = "1A2C3D4B56";
    string s2 = "B1D23A456A";
    cout << LCS(s1, s2) << endl;
    return 0;
}