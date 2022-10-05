#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> result;
    if(nums.size() < 3){
        return result;
    }
    std::sort(nums.begin(), nums.end());
    for(int i=0; i<nums.size(); i++){
        if(nums[i] > 0){
            return result;
        }
        if (i > 0 && nums[i] == nums[i-1]){
            continue;
        }
        int left = i+1, right = nums.size()-1;
        while(left < right){
            if(nums[left] + nums[i] + nums[right] == 0){
                vector<int> v{nums[left], nums[i], nums[right]};
                result.push_back(v);
                while (right > left && nums[right] == nums[right - 1]) right--;
                while (right > left && nums[left] == nums[left + 1]) left++;
                right--;
                left++;
            }else if(nums[left] + nums[i] + nums[right] > 0){
                right--;
            }else{
                left++;
            }
        }
    }
    return result;
}

int main(){
    vector<int> nums;
    nums.push_back(1);
    nums.push_back(1);
    nums.push_back(-2);
    vector<vector<int>> result = threeSum(nums);
    for(int i=0; i<result.size(); i++){
        for(int j=0; j<result[0].size(); j++){
            std::cout << result[i][j] << "\t";
        }
        std::cout << std::endl;
    }
    return 0;
}