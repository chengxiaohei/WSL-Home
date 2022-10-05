#include <iostream>
#include <vector>
#include <climits>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

int findSmallestIndex(vector<ListNode*>& lists){
    int smallVal = INT_MAX;
    int smallIndex = 0;
    for(int i = 0; i<lists.size(); i++){
        if(lists[i] == nullptr){
            continue;
        }
        if(lists[i]->val < smallVal){
            smallVal = lists[i]->val;
            smallIndex = i;
        }
    }
    return smallIndex;
}

ListNode* mergeKLists(vector<ListNode*>& lists) {
    int index = findSmallestIndex(lists);
    ListNode *cur = lists[index];
    ListNode *newHead = cur;
    lists[index] = lists[index]->next;
    int K = lists.size();
    while(true){
        bool allNull = true;
        for(int i=0; i<K; i++){
            if(lists[i] != nullptr){
                allNull = false;
                break;
            }
        }
        if(allNull) break;
        //for(int i=0; i<K; i++){
        //    cout << lists[i]->val << "\t";
        //} cout << endl;
        cout << "?" << endl;
        int index = findSmallestIndex(lists);
        cout << "!" << endl;
        cur->next = lists[index];
        cur = cur->next;
        lists[index] = lists[index]->next;
        // cur->next = nullptr;
        cout << "he" << endl;
    }
    return newHead;
}

int main(){
    ListNode *A = new ListNode(5);
    ListNode *B = new ListNode(4, A);
    ListNode *C = new ListNode(1, B);
    std::vector<ListNode *> table;
    table.push_back(C);
    A = new ListNode(4);
    B = new ListNode(3, A);
    C = new ListNode(1, B);
    table.push_back(C);
    A = new ListNode(6);
    B = new ListNode(2, A);
    table.push_back(B);
    C = mergeKLists(table);
    while(C != nullptr){
        cout << C->val << "\t";
        C = C->next;
    }cout << endl;
    return 0;
}