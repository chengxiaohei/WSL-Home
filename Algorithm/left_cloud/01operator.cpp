#include <iostream>
#include <string>
#include <vector>
//编辑距离问题


bool isValid(std::string& str){
    if((str.size() & 1) == 0){
        return false;
    }
    for(int i=0; i<str.size(); i++){
        if((i & 1) == 0){ //偶数位
            if(!(str[i] == '0' || str[i] == '1')){
                return false;
            }
        }else{  //奇数位
            if(!(str[i] == '&' || str[i] == '|' || str[i] == '^')){
                return false;
            }
        }
    }
    return true;
}


int operator01(std::string& str, int L, int R, bool desired){
    int length = str.size();
    if(length == 0 || !isValid(str) || L > R){
        return 0;
    }
    if(L == R){
        if(desired){
            return (str[L] == '1') ? 1 : 0;
        }else{
            return (str[L] == '0') ? 1 : 0;
        }
    }
    int ans = 0;
    for(int i=L+1; i<R; i+=2){
        if(desired){ //期望为true
            if(str[i] == '&'){
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, true);
            }else if(str[i] == '|'){
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, true);
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, false);
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, true);
            }else{ //str[i] == '^'
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, false);
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, true);
            }
        }else{ //期望为false
            if(str[i] == '&'){
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, false);
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, true);
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, false);
            }else if(str[i] == '|'){
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, false);
            }else{ //str[i] == '^'
                ans += operator01(str, L, i-1, true) * operator01(str, i+1, R, true);
                ans += operator01(str, L, i-1, false) * operator01(str, i+1, R, false);
            }
        }
    }
    return ans;
}

// 暴力递归改动态规划
int operator01(std::string& str, bool desired){
    int length = str.size();
    if(length == 0 || !isValid(str)){
        return 0;
    }
    std::vector< std::vector<int> >  trueDP(length, std::vector<int>(length, 0));
    std::vector< std::vector<int> > falseDP(length, std::vector<int>(length, 0));
    for(int i=0; i<length; i+=2){
        trueDP[i][i] = (str[i] == '1') ? 1 : 0;
        falseDP[i][i] = (str[i] == '0') ? 1 : 0;
    }
    for(int row=length-3; row >=0; row-=2){
        for(int col=row+2; col<length; col+=2){
            for(int i=row+1; i<col; i+=2){
                if(str[i] == '&'){
                    trueDP[row][col] += trueDP[row][i-1] * trueDP[i+1][col];
                    falseDP[row][col]+= trueDP[row][i-1] * falseDP[i+1][col];
                    falseDP[row][col]+= falseDP[row][i-1] * trueDP[i+1][col];
                    falseDP[row][col]+= falseDP[row][i-1] * falseDP[i+1][col];
                }else if(str[i] == '|'){
                    trueDP[row][col] += trueDP[row][i-1] * trueDP[i+1][col];
                    trueDP[row][col] += trueDP[row][i-1] * falseDP[i+1][col];
                    trueDP[row][col] += falseDP[row][i-1] * trueDP[i+1][col];
                    falseDP[row][col]+= falseDP[row][i-1] * falseDP[i+1][col];
                }else{
                    trueDP[row][col] += trueDP[row][i-1] * falseDP[i+1][col];
                    trueDP[row][col] += falseDP[row][i-1] * trueDP[i+1][col];
                    falseDP[row][col] += trueDP[row][i-1] * trueDP[i+1][col];
                    falseDP[row][col] += falseDP[row][i-1] * falseDP[i+1][col];
                }
            }
        }
    }
    return desired ? trueDP[0][length-1] : falseDP[0][length-1];
}


int main(){
    std::string str("1^0|0|1^1^0|1|0&1");
    std::cout << operator01(str, 0, str.size()-1, false) << std::endl;
    std::cout << operator01(str, false) << std::endl;
    std::vector<int> V;
    return 0;
}