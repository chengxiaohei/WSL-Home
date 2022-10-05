#include <iostream>
#include <vector>

int getWater(std::vector<int> arr){
    int length = arr.size();
    int leftMax = arr[0], rightMax = arr[length-1];
    int lIndex = 1, rIndex = length-2;
    int sumWater = 0;
    while(lIndex <= rIndex){
        if(leftMax <= rightMax){
            sumWater += std::max(leftMax - arr[lIndex], 0);
            leftMax = std::max(leftMax, arr[lIndex]);
            lIndex++;
        }else{
            sumWater += std::max(rightMax - arr[rIndex], 0);
            rightMax = std::max(rightMax, arr[rIndex]);
            rIndex--;
        }
    }
    return sumWater;
}

int main(int argc, char const *argv[]){
    std::vector<int> arr;
    arr.push_back(3);
    arr.push_back(1);
    arr.push_back(2);
    arr.push_back(5);
    arr.push_back(2);
    arr.push_back(4);
    std::cout << getWater(arr) << std::endl;
    return 0;
}