#include <iostream>
#include <string>

// 回溯算法打印字符串中所有字符的全排列
using namespace std;

void process(string &str, string &already){
    if(str.size() == 0){
        cout << already << endl;
        return;
    }
    for(int i=0; i<str.size(); ++i){
        char t = str[i];
        already.push_back(t);
        str.erase(str.begin() + i);
        process(str, already);
        str.insert(str.begin() + i, t);
        already.pop_back();
    }
}

void printSubString(string &str){
    string tmp;
    process(str, tmp);
}

int main(int argc, const char *argv[]){
    string str(argv[1]);
    printSubString(str);
    return 0;
}