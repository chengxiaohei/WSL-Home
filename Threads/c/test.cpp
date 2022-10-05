#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

bool isValid(string& str){
    stack<char> S;
    for(int i=0; i<str.size(); i++){
        if(S.empty()){
            S.push(str[i]);
        }else{
            if(S.top() == '(' && str[i] == ')'){
                S.pop();
            }else{
                S.push(str[i]);
            }
        }
    }
    return S.empty();
}

void process(int n, string curStr, vector<string>& result) {
    if(curStr.size() == n*2){
        if(isValid(curStr)){
            result.push_back(curStr);
        }
        return;
    }
    process(n, curStr + "(", result);
    process(n, curStr + ")", result);
}

vector<string> generateParenthesis(int n) {
    vector<string> result;
    process(n, "(", result);
    return result;
}

int main(){
    vector<string> res = generateParenthesis(2);
    for(int i=0; i<res.size(); i++){
        cout << res[i] << endl;
    }
    return 0;
}