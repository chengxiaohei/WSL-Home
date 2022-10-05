#include <iostream>
#include <string>
#include <deque>
using namespace std;


void printNumDQ(deque<int> &DQ){
    if(!DQ.empty()){
        int tmp = DQ.front();
        printf("%d ", tmp);
        DQ.pop_front();
        printNumDQ(DQ);
        DQ.push_front(tmp);
    }else{
        printf("\n");
    }
}
void printOpDQ(deque<char> &DQ){
    if(!DQ.empty()){
        char tmp = DQ.front();
        printf("%c ", tmp);
        DQ.pop_front();
        printOpDQ(DQ);
        DQ.push_front(tmp);
    }else{
        printf("\n");
    }
}

// 计算L到R表达式的值
int cal(string &s, int L, int R){
    deque<int> numDQ;
    deque<char> opDQ;
    int index = L;
    while(index <= R){
        // 如果是运算符
        if(s[index] == '+' || s[index] == '*'){
            opDQ.push_back(s[index++]);
            continue;
        }
        if(s[index] == '-'){
            int tmpNum = 0;
            index++;
            if(s[index] >= '0' && s[index] <= '9'){
                while(index <= R && s[index] >= '0' && s[index] <= '9'){
                    tmpNum = 10 * tmpNum + s[index] - '0';
                    index++;
                }
            }else if(s[index] == '('){
                int count = 1;
                int left = ++index;
                while(count != 0){
                    if(s[index] == '('){
                        count++;
                        index++;
                    }else if(s[index] == ')'){
                        count--;
                        index++;
                    }else{
                        index++;
                    }
                }
                // 此时index指向右括号的下一个位置
                tmpNum = cal(s, left, index - 2);
            }
            numDQ.push_back(-tmpNum);
            opDQ.push_back('+');
        }
        // 如果是数字
        else if(s[index] >= '0' && s[index] <= '9'){
            int tmpNum = 0;
            while(index <= R && s[index] >= '0' && s[index] <= '9'){
                tmpNum = 10 * tmpNum + s[index] - '0';
                index++;
            }
            numDQ.push_back(tmpNum);
        }
        // 如果是左括号
        else if(s[index] == '('){
            int count = 1;
            int left = ++index;
            while(count != 0){
                if(s[index] == '('){
                    count++;
                    index++;
                }else if(s[index] == ')'){
                    count--;
                    index++;
                }else{
                    index++;
                }
            }
            // 此时index指向右括号的下一个位置
            numDQ.push_back(cal(s, left, index - 2));
        }
        if(!opDQ.empty() && opDQ.back() == '*'){
            int a = numDQ.back(); numDQ.pop_back();
            int b = numDQ.back(); numDQ.pop_back();
            opDQ.pop_back();
            numDQ.push_back(a * b);
        }
    }

    // 此时只需要针对numDQ与opDQ进行加减运算即可
    while(!opDQ.empty() && numDQ.size() >= 2){
        char op = opDQ.front(); opDQ.pop_front();
        int a = numDQ.front(); numDQ.pop_front();
        int b = numDQ.front(); numDQ.pop_front();
        if(op == '+'){
            numDQ.push_front(a + b);
        }else{ // op == '-'
            numDQ.push_front(a - b);
        }
    }
    return numDQ.front();
}

/*
* 返回表达式的值
* @param s string字符串 待计算的表达式
* @return int整型
*/
int solve(string s) {
    // write code here
    return cal(s, 0, s.size() - 1);
}


int main(int argc, const char *argv[]){
    string str = argv[1];
    cout << solve(str) << endl;
    return 0;
}