#include <iostream>
#include <vector>
long long func(int N){
    std::vector<long long> dp(201, 0);
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 2;
    for(int i=3; i<=N; i++){
        dp[i] = dp[i-1] * i;
    }
    return dp[N];
}

int main(){
    int N;
    std::cin >> N;
    if(N < 1 || N > 200){
        std::cout << "Error" << std::endl;
        return 0;
    }
    std::cout << func(N) << std::endl;
    return 0;
}