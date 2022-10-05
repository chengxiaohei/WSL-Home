#include <iostream>
#include <memory>
#include <vector>
using namespace std;

class Test
{
public:
    Test(){
        cout << "构造函数" << endl;
    }
    ~Test(){
        cout << "析构函数" << endl;
    }
private:
    vector<int>* data;
};

int main(){
    {
    unique_ptr<Test> p1 = make_unique<Test>();
    }
    return 0;
}