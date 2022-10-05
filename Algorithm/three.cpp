#include <iostream>

struct ListNode {
    int val;
    ListNode *pre;
    ListNode *next;
};

// 获取链表中剩余的最后一个值
int func(ListNode *head){
    int count = 1;
    while(head->next != head){
        if(count != 3){
            head = head->next;
            count++;
        }else{
            head->pre->next = head->next;
            head->next->pre = head->pre;
            ListNode *node = head;
            head = head->next;
            delete node;
            count = 1;
        }
    }
    return head->val;
}

#include <string>
using namespace std;

void exchange(char &c){
    if(c >= 'a' && c <= 'z'){
        c += 'A'-'a';
    }else if(c >= 'A' && c <= 'Z'){
        c -= 'A'-'a';
    }
}

string trans(string s, int n) {
    // write code here
    for(int i=0; i<n/2; i++){
        swap(s[i], s[n-1-i]);
    }
    for(int i=0; i<n; i++){
        exchange(s[i]);
    }
    cout << s << endl;
    int L = 0, R = 0;
    while(R < n){
        L = R;
        while(L < n && s[L] == ' '){
            L++; R++;
        }
        cout << L <<" " << R << endl;
        while(R < n && s[R] != ' '){
            R++;
        }
        int l=L, r=R-1;
        cout << L <<" " << R << endl;
        while(l < r){
            swap(s[l++], s[r--]);
        }
    }
    return s;
}

int main(){
    cout << trans("NowCoder", 8) << endl;
    // int N;
    // std::cin >> N;
    // ListNode *head = new ListNode{1, nullptr, nullptr};
    // head->pre = head;
    // head->next = head;
    // ListNode *preNode = head;
    // for(int i=2; i<=N; i++){
    //     ListNode *node = new ListNode{i, preNode, preNode->next};
    //     preNode->next->pre = node;
    //     preNode->next = node;
    //     preNode = node;
    // }
    
    // std::cout << func(head) << std::endl;
    return 0;
}