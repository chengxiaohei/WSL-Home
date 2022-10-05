#include <iostream>
#include <functional>
#include <string>
#include <vector>
using namespace std;

int main(){
    std::hash<string*> fn;
    string str = "hello";
    // auto fn = std::hash<vector<char>>();
    size_t res = fn(&str);
    // unsigned long long res = fn("hello_world");
    cout << res << endl;
    return 0;
}