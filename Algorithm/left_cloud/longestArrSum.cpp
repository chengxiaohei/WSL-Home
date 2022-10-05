#include <iostream>
#include <vector>
#include <climits>

int func(std::vector<int> arr, int K){
    int length = arr.size();
    if(length == 0){
        return 0;
    }
    int L = 0, R = 0, sum = arr[0];
    int ans = 0;
    while(L < length){
        if(sum == K){
            ans = std::max(R-L+1, ans);
            sum -= arr[L++];
        }else if(sum > K){
            sum -= arr[L++];
        }else{ //(sum < K)
            sum += arr[++R];
        }
    }
    return ans;
}

int main(){
    std::vector<int> arr;
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(1);
    arr.push_back(8);
    arr.push_back(1);
    std::cout << func(arr, 3) << std::endl;
    return 0;
}