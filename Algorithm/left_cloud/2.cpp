#include <iostream>
#include <unordered_set>

//给定一个数组arr,求差值为k的去重数字对
int sub2pair(std::vector<int>& arr){
    std::unordered_set<int> hash();
    hash.insert(arr.begin(), arr.end());
    int count = 0;
    for(int i=0; i<arr.size(); i++){
        if(hash.count(arr[i]+2) != 0){
            count++;
        }
    }
    return count;
}

int main(int argc, char const *argv[]){
    std::vector<int> arr();
    arr.push_back(1)
}