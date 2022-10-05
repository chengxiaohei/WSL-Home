#include <iostream>
#include <unordered_map>
#include <vector>
#include <cstdlib>

/**
 * 给出n个数字a_1,......,a_n,问最多有多少不重叠的非空区间，
 * 使得每个区间内数字的xor都等于0
 */

//这是左程云上课时展示的代码
int nArea1(std::vector<int> arr){
    int length = arr.size();
    if(length == 0){
        return 0;
    }
    int x = 0;
    std::vector<int> dp(length, 0);
    std::unordered_map<int, int> hash;
    hash[0] = -1;
    for(int i=0; i<length; i++){
        x ^= arr[i];
        if(hash.count(x) != 0){
            int pre = hash[x];
            dp[i] = pre == -1 ? 1 : (dp[pre] + 1);
        }
        if(i > 0){
            dp[i] = std::max(dp[i-1], dp[i]);
        }
        hash[x] = i;
    }
    return dp[length - 1];
}

//这是我自己些的代码
int nArea2(std::vector<int> arr){
    int length = arr.size();
    if(length == 0){
        return 0;
    }
    //生成辅助前缀异或数组
    std::vector<int> xorArr(length, 0);
    xorArr[0] = arr[0];
    for(int i=1; i<length; i++){
        xorArr[i] = arr[i] ^ xorArr[i-1];
    }
    //dp数组,用于存储arr[0~i]中的非空非重叠异或为0的子数组个数
    std::vector<int> dp(length, 0);
    dp[0] = arr[0] == 0 ? 1 : 0;
    for(int i=1; i<length; i++){
        if(arr[i] == 0){
            dp[i] = dp[i-1]+1;
        }else{
            //第一种可能性: arr[i]不属于异或为0的子数组
            int p1 = dp[i-1];
            //第二种可能性: arr[i]与a[0~i-1]的一部分可以构成异或为0的子数组
            int p2 = -1;
            for(int j=i-1; j>=0; j--){
                if(xorArr[j] == xorArr[i]){
                    p2 = dp[j] + 1;
                    break;
                }
            }
            //这部分应该有，但是树枝上与p1相等，所以可以优化掉
            // if(p2 == -1){
            //     p2 = dp[i-1];
            // }
            dp[i] = std::max(p1, p2);
        }
    }
    return dp[length - 1];
}

//在nArea2算法的基础上使用哈希表将时间复杂度优化到O(N)
int nArea3(std::vector<int> arr){
    int length = arr.size();
    if(length == 0){
        return 0;
    }
    int x = arr[0];  //x为第前缀异或值
    //创建哈希表，存储ket:异或值,该异或值在数组中的索引
    std::unordered_map<int, int> hash;
    hash[arr[0]] = 0;
    //dp数组,用于存储arr[0~i]中的非空非重叠异或为0的子数组个数
    std::vector<int> dp(length, 0);
    dp[0] = arr[0] == 0 ? 1 : 0;
    for(int i=1; i<length; i++){
        x ^= arr[i];
        if(arr[i] == 0){
            dp[i] = dp[i-1]+1;
        }else{
            //第一种可能性: arr[i]不属于异或为0的子数组
            int p1 = dp[i-1];
            //第二种可能性: arr[i]与a[0~i-1]的一部分可以构成异或为0的子数组
            int p2 = hash.count(x) ? dp[ hash[x] ] + 1 : -1;
            dp[i] = std::max(p1, p2);
        }
        hash[x] = i;
    }
    return dp[length - 1];
}


int main(int argc, char const *argv[]){
    std::vector<int> arr;
    for(int i=0; i<50; i++){
        int times = rand()%5000;
        for(int j=0; j<times; j++){
            arr.push_back(rand());
        }
        if(nArea1(arr) != nArea3(arr)){
            std::cout << "error!" << std::endl;
            return -1;
        }
        arr.clear();
    }
    std::cout << "success!" << std::endl;
    return 0;
}