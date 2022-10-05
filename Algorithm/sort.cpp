#include <iostream>
#include <ctime>
#include <vector>
#include <climits>

static void swap(std::vector<int>& nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void bubbleSort(std::vector<int>& nums){
    if(nums.size() < 2) return;
    for(int i=0; i<nums.size(); i++){
        for(int j=i+1; j<nums.size(); j++){
            if(nums[i] > nums[j]){
                swap(nums, i, j);
            }
        }
    }
}

void insertSort(std::vector<int>& nums){
    if(nums.size() < 2) return;
    for(int i=1; i<nums.size(); i++){
        for(int j=i; j>0 && nums[j-1] > nums[j]; j--){
            swap(nums, j-1, j);
        }
    }
}

void subMergeSort(std::vector<int>& nums, int L, int R){
    if(L >= R) return;
    if(R-L == 1){
        if(nums[L] > nums[R]){
            swap(nums, L, R);
        }
        return;
    }
    int mid = L + (R - L) / 2;
    subMergeSort(nums, L, mid);
    subMergeSort(nums, mid+1, R);
    std::vector<int> temp(R-L+1, -1);
    int left = L, right = mid+1;
    int index = 0;
    while(left <= mid && right <= R){
        temp[index++] = nums[left] <= nums[right] ? nums[left++] : nums[right++];
    }
    while(left <= mid){
        temp[index++] = nums[left++];
    }
    while(right <= R){
        temp[index++] = nums[right++];
    }
    for(int i=0; i<R-L+1; i++){
        nums[L+i] = temp[i];
        // std::cout << temp[i] << "\t";
    }
    // std::cout << std::endl;
}

void mergeSort(std::vector<int>& nums){
    if(nums.size() < 2) return;
    subMergeSort(nums, 0, nums.size()-1);
}

void selectSort(std::vector<int>& nums){
    if(nums.size() < 2) return;
    for(int i=0; i<nums.size(); i++){
        int minNum = nums[i];
        int minIndex = i;
        for(int j=i+1; j<nums.size(); j++){
            if(nums[j] < minNum){
                minNum = nums[j];
                minIndex = j;
            }
        }
        swap(nums, i, minIndex);
    }
}


void partition(std::vector<int>& nums, int L, int R){
    int length = R - L + 1;
    if(length <= 1) return;
    int index = rand()%length;
    swap(nums, L + index, R);
    int left = L, right = R-1;
    index = L;
    while(index <= right){
        if(nums[index] == nums[R]){
            index++;
        }else if(nums[index] < nums[R]){
            swap(nums, left++, index++);
        }else{ //nums[index] > nums[R]
            swap(nums, index, right--);
        }
    }
    swap(nums, ++right, R);
    std::cout << "hello" << std::endl;
    partition(nums, L, left - 1);
    partition(nums, right + 1, R);
}

void quickSort(std::vector<int>& nums){
    if(nums.size() < 2){
        return;
    }
    partition(nums, 0, nums.size() - 1);
}

void shellSort(std::vector<int>& nums){
    if(nums.size() < 2){
        return;
    }
    for(int g = nums.size()/2; g > 0; g /=2){
        //插入排序
        for(int i=g; i<nums.size(); i+=g){
            for(int j=i; j>0 && nums[j-g] > nums[j]; j-=g){
                swap(nums, j-g, j);
            }
        }
    }
}

int main(){
    std::vector<int> nums({3,6,8,2,56,98,2,56,9,3,56,95,3,70,1,3,26});
    // bubbleSort(nums);
    // insertSort(nums);
    // mergeSort(nums);
    // selectSort(nums);
    // quickSort(nums);
    shellSort(nums);
    for(int& i : nums){
        std::cout << i << "\t";
    }
    std::cout << std::endl;
}