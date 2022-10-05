// 大疆笔记第二题
// 给一个数组，搭建完全二叉树，打印输出和为target的路径

#include <iostream>
#include <vector>
using namespace std;

void process(const vector<int> &data, int index, int target, vector<int> &already){
    if(index >= data.size()) return;
    if(2*index+1 >= data.size() && 2*index+2 >= data.size() && data[index] == target){
        already.push_back(target);
        for(int &a : already){
            cout << a << " ";
        }
        cout << endl;
        already.pop_back();
        return;
    }
    already.push_back(data[index]);
    if(2 * index + 1 < data.size()){
        process(data, 2 * index + 1, target - data[index], already);
    }
    if(2 * index + 2 < data.size()){
        process(data, 2 * index + 2, target - data[index], already);
    }
    already.pop_back();
}

int main(int argc, const char *argv[]){
    int d;
    vector<int> data({1,2,3,6,3,7,3,6,3,6,8,3,5,6,8,1});
    // while(cin >> d){
    //     if(d == '\n') break;
    //     data.push_back(d);
    // }
    
    // int target;
    // cin >> target;
    vector<int> temp;
    process(data, 0, atoi(argv[1]), temp);
    return 0;
}