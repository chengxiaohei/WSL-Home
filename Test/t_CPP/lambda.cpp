#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;

ostream &operator<< (ostream &os, const pair<int, string> &P){
    return os << P.first << ":" << P.second;
}

int main(){
    // string str("hello");
    // int num = 88;
    // char x = 'x';
    // auto A = [&num, &x](string &str) mutable -> int{
    //     str.append(" world");
    //     num++;
    //     x++;
    //     return 0;
    // };
    // int result = A(str);
    // cout << str << " " << num << " " << x << endl;

    vector<int> table{1,2,3,4,5,2,4,3,2,3,6,3,2,2,7};
    // int count = count_if(table.begin(), table.end(), [](int num) -> bool {return num >= 5;});
    // cout << count << endl;
    // sort(table.begin(), table.end(), [](int a, int b) -> bool {return a > b;});
    // for(int i : table){
    //     cout << i << " ";
    // }
    // cout << endl;
    auto comp = [](pair<int, string> lhs, pair<int, string> rhs){
        return lhs.first < rhs.first;
    };
    priority_queue<pair<int, string>, vector<pair<int,string>>, decltype(comp)> PQ(comp);

    for(int i: table){
        PQ.push(make_pair(i, "s" + to_string(i)));
    }
    for(; !PQ.empty(); PQ.pop()){
        cout << PQ.top() << " ";
    }
    cout << endl;
    return 0;
}

