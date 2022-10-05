#include <iostream>
#include <vector>
#include <string>

using namespace std;

void func1(int arg1, int arg2){
    int a = 1;
    printf("a的地址:%p\n", &a);
    vector<int> A {1,2,3,4};
    printf("A的地址:%p\n", &A);
    printf("A[0]的地址:%p,\nA[1]的地址:%p\n \
        ,A[2]的地址:%p\n,A[3]的地址:%p\n"
        ,&A[0],&A[1],&A[2],&A[3]);
    
    int *b = new int[1];
    printf("b指针的地址:%p\n",&b);
    printf("b的地址:%p\n",b);
    vector<int> *B = new vector<int>{1,2,3,4};
    printf("B指针的地址:%p\n", B);
    printf("B的地址:%p\n", &B);
    printf("B[0]的地址:%p,\nB[1]的地址:%p\n \
        ,B[2]的地址:%p\n,B[3]的地址:%p\n"
        ,&(*B)[0],&(*B)[1],&(*B)[2],&(*B)[3]);
    for(auto x : *B){
        printf("x=%d ",x);
    }
}

#include <array>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>



int main(){
    string str("caabeefa");
    func1(1, 2);
    cout << sizeof(string) << "\n";
    cout << sizeof(str) << "\n";
    str += "hioejfoiejo";
    cout << sizeof(str) << "\n";
    cout << sizeof(array<int, 22>) << "\n";
    cout << sizeof(vector<int>) << "\n";
    cout << sizeof(set<int>) << "\n";
    cout << sizeof(map<int,int>) << "\n";
    cout << sizeof(unordered_set<int>) << "\n";
    cout << sizeof(unordered_map<int,int>) << "\n";
    cout << sizeof(multiset<int>) << "\n";
    cout << sizeof(multimap<int,int>) << "\n";
    cout << sizeof(unordered_multiset<int>) << "\n";
    cout << sizeof(unordered_multimap<int,int>) << "\n";
    return 0;
}