#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<int> dailyTemperatures(vector<int>& temperatures) {
    std::vector<int> res(temperatures.size(), 0);
    stack< stack<int> > S;  //单调栈
    for(int i=0; i<temperatures.size(); i++){
        if(S.empty() || temperatures[i] < temperatures[S.top().top()]){
            S.push(stack<int>({i}));
        }else if(temperatures[i] == temperatures[S.top().top()]){
            S.top().push(i);
        }else{
            while(!S.empty() && temperatures[i] > temperatures[S.top().top()]){
                res[S.top().top()] = i - S.top().top();
                S.top().pop();
                if(S.top().empty()){
                    S.pop();
                }
            }
            i--;
        }
    }
    return res;
}

int main(int argc, const char** argv) {
    vector<int> water={73, 74, 75, 71, 69, 72, 76, 73};
    vector<int> res = dailyTemperatures(water);
    for(auto i : res){
        cout << i << "\t";
    }
    cout << endl;
    return 0;
}