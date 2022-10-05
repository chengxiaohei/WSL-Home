#include <iostream>

//暴力方法  O(n)
std::pair<int,int> func(int *nums, int length, int s){
    for(int i=0; i<length; i++){
        int d = s - nums[i];
        for(int j=i+1; j<length; j++){
            if(nums[j] == d){
                return std::pair<int,int>(nums[i], nums[j]);
            }
        }
    }
    return std::pair<int,int>(-1,-1);
}

//返回数字d在数组nums[start, end]中的索引,如果没有返回-1
int process(int *nums, int length, int start, int end, int d){
    if(start < 0 || end >=length || start > end) return -1;
    int midIndex = (start + end)/2;
    if(nums[midIndex] == d) return midIndex;
    return d > nums[midIndex] ? process(nums, length, midIndex+1, end, d) : process(nums, length, start, midIndex-1, d);
}

//二分法 O(nlogn)
std::pair<int,int> func2(int *nums, int length, int s){
    for(int i=0; i<length; i++){
        int d = s - nums[i];
        int index = -1;
        if(d > nums[i]){
            index = process(nums, length, i+1, length-1, d);
        }else{
            index = process(nums, length, 0, i-1, d);
        }
        if(index != -1) return std::pair<int,int>(nums[i], nums[index]);
    }
    return std::pair<int,int>(-1,-1);
}

//非递归二分法 O(nlogn)
int process2(int *nums, int length, int start, int end, int d){
    int front = start, last = end;
    while(front < last){
        int mid = (front + last) / 2;
        if(nums[mid] == d){
            return mid;
        }else if(nums[mid] > d){
            last = mid - 1;
        }else{
            front = mid + 1;
        }
    }
    return -1;
}

std::pair<int,int> func2_2(int *nums, int length, int s){
    for(int i=0; i<length; i++){
        int d = s - nums[i];
        int index = -1;
        if(d > nums[i]){
            index = process(nums, length, i+1, length-1, d);
        }else{
            index = process(nums, length, 0, i-1, d);
        }
        if(index != -1) return std::pair<int,int>(nums[i], nums[index]);
    }
    return std::pair<int,int>(-1,-1);
}

//双指针法 O{n}
std::pair<int,int> func3(int *nums, int length, int s){
    if(nums == nullptr || length < 2)
        return std::pair<int,int> (-1,-1);
    int *p1 = nums, *p2 = nums + length - 1;
    while(p1 < p2){
        if(*p1 + *p2 > s){
            p2--;
        }else if(*p1 + *p2 < s){
            p1++;
        }else{
            return std::pair<int,int>(*p1, *p2);
        }
    }
    return std::pair<int,int>(-1,-1);
}

void printInt(int start, int end){
    for(int i=start; i<=end; i++){
        printf("%d,",i);
    }printf("\n");
}

void printSeq(int s){
    int start = 1, end = 2;
    int sum = start + end;
    while(start < end){
        if(sum == s){
            printInt(start, end);
            sum += (++end);
        }else if(sum < s){
            sum += (++end);
        }else{ // sum > s
            sum -= start++;
        }
    }
}

void printInt(int *nums, int start, int end){
    for(int i=start; i<=end; i++){
        printf("%d,", nums[i]);
    }printf("\n");
}

void printSeq(int *nums, int length, int s){
    int start = 0, end = 1;
    int sum = nums[start] + nums[end];
    while(nums[start] < (s+1)/2){  //终止条件是start指针处的数值达到期望总和的一半
        if(sum == s){
            printInt(nums, start, end);
            sum += nums[++end];
        }else if(sum < s){
            sum += nums[++end];
        }else{ // sum > s
            sum -= nums[start++];
        }
    }
}

int main(int argc, char const *argv[]){
    int nums[] = {1,4,5,6,7,8,9,10,12,17,27,30};
    int length = sizeof(nums)/sizeof(int);
    std::pair<int,int> result = func2_2(nums, length, 20);
    printf("%d,%d\n", result.first, result.second);
    printSeq(nums, length, 31);
    return 0;
}