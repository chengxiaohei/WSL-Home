#include <iostream>
#include <string>
#include <stack>
#include <cstdlib>
#include <ctime>

static bool isNum(char c){
    return c >= '0' && c <= '9';
}

// static bool isSymbol(char c){
//     return c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')';
// }

// 如果没有括号,使用两个栈实现功能
// 确保Q是一个合法的公式
int calculate1(std::string& Q){
    std::stack<std::string> S1;  // S1存放数字
    std::stack<char> S2;    // S2存放符号
    std::string tempNum;
    for(int i=0; i<Q.size(); i++){
        if( isNum(Q[i]) ){
            tempNum.push_back(Q[i]);
        }else{
            S1.push(tempNum);
            tempNum.clear();
            if(!S2.empty() && (S2.top() == '*' || S2.top() == '/')){
                int second = std::stoi(S1.top()); S1.pop();
                int first = std::stoi(S1.top()); S1.pop();
                S1.push( S2.top() == '*' ? std::to_string(first * second) : std::to_string(first / second));
                S2.pop();
            }
            S2.push(Q[i]);
        }
    }
    S1.push(tempNum);

    //打印栈中信息看看
    // while(!S1.empty()){
    //     std::cout << S1.top() << "\t";
    //     S1.pop();
    // }
    // std::cout << std::endl;

    // while(!S2.empty()){
    //     std::cout << S2.top() << "\t";
    //     S2.pop();
    // }
    // std::cout << std::endl;

    int sum = 0;
    while(!S1.empty() && !S2.empty()){
        int num = std::stoi(S1.top()); S1.pop();
        char op = S2.top(); S2.pop();
        sum += op == '-' ? -num : num;
    }
    return sum + std::stoi(S1.top());
}

// 如果没有括号，使用一个栈实现功能，确保Q是一个合法的公式
int calculate2(std::string& Q){
    std::stack<std::string> Stack;
    std::string tempNum;
    char op = -1;  //相当于一个标志位，
    for(int i=0; i<Q.size(); i++){
        if( isNum(Q[i]) ){
            tempNum.push_back(Q[i]);
        }else{
            Stack.push(tempNum);
            tempNum.clear();
            if(op != -1){
                int second = std::stoi(Stack.top()); Stack.pop();
                int first = std::stoi(Stack.top()); Stack.pop();
                Stack.push(op == '*' ? std::to_string(first * second) : std::to_string(first/second));
                op = -1;
            }
            if(Q[i] == '*' || Q[i] == '/'){
                op = Q[i];
            }else{ //Q[i] == '+' || Q[i] == '-'
                Stack.push(std::string(1, Q[i]));
            }
        }
    }
    Stack.push(tempNum);
    //打印栈中信息看看
    // while(!Stack.empty()){
    //     std::cout << Stack.top() << "\t";
    //     Stack.pop();
    // }
    // std::cout << std::endl;

    int sum = 0;
    while(Stack.size() > 1){
        int num = std::stoi(Stack.top()); Stack.pop();
        char symbol = Stack.top()[0]; Stack.pop();
        sum += symbol == '-' ? -num : num;
    }
    return sum + std::stoi(Stack.top());
}

struct Info{
    int result; //计算结果
    int index;  //计算结束后,右括号的索引值
    Info(int r, int n): result(r), index(n){}
};

// process的功能是: 计算index位置起始的子字符串计算结果,以右括号或字符串结尾为结束,
// 返回结构体Info.
static Info process(std::string& Q, int index){
    //BaseCase:
    // ....
    std::stack<std::string> Stack;
    std::string tempNum = Q[index] == '-' ? "-" : "";
    char op = -1;  //相当于一个标志位，
    while(index < Q.size() && Q[index] != ')'){
        if( isNum(Q[index]) ){
            tempNum.push_back(Q[index]);
        }else if(Q[index] != '('){
            Stack.push(tempNum);
            tempNum.clear();
            if(op != -1){ //说明此时有乘除法需要操作
                int second = std::stoi(Stack.top()); Stack.pop();
                int first = std::stoi(Stack.top()); Stack.pop();
                Stack.push(op == '*' ? std::to_string(first * second) : std::to_string(first/second));
                op = -1;
            }
            if(Q[index] == '*' || Q[index] == '/'){
                op = Q[index];
            }else if(Q[index] == '+' || Q[index] == '-'){
                Stack.push(std::string(1, Q[index]));
            }
        }else{
            Info info = process(Q, index + 1);
            Stack.push(std::to_string(info.result));
            index = info.index;
        }
        index++;
    }
    Stack.push(tempNum);
    // while(!Stack.empty()){
    //     std::cout << Stack.top() << "\t";
    //     Stack.pop();
    // }
    // std::cout << std::endl;
    int sum = 0;
    while(Stack.size() > 1){
        int num = std::stoi(Stack.top()); Stack.pop();
        char symbol = Stack.top()[0]; Stack.pop();
        sum += symbol == '-' ? -num : num;
    }
    // return sum + std::stoi(Stack.top());
    return Info(sum + std::stoi(Stack.top()), index);
}

//如果公式中存在括号,采用递归计算
int calculate3(std::string& Q){
    std::cout << process(Q,0).result << std::endl;
    std::cout << process(Q,0).index << std::endl;
    // return process(Q, 3).result;
    return 0;
}

int main(int argc, char const *argv[]){
    // std::string Q = std::string("1*2+3*2*3-4-10*1+3");
    // std::cout << calculate1(Q) << std::endl;
    // std::cout << calculate2(Q) << std::endl;
    // std::string Q = std::string("8*10-57+(7*9-10)-2-(3-1)-2");
    std::string Q = std::string("8*10-57*2*2-235");
    std::cout << calculate3(Q) << std::endl;
    return 0;
}