#include <iostream>
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *reverseList(ListNode *head){
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *newHead = reverseList(head->next);
    head->next->next = head;
    head->next = nullptr;
    return newHead;
}

ListNode *reverseList2(ListNode *head){
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode *pre = nullptr;
    ListNode *cur = head;
    ListNode *next= head->next;
    while(next != nullptr){
        cur->next = pre;
        pre = cur;
        cur = next;
        next = next->next;
    }
    cur->next = pre;
    return cur;
}

void reorderList(ListNode* head) {
    if(head == nullptr){
        return;
    }
    ListNode *slow = head;
    ListNode *fast = head;
    while(fast->next != nullptr && fast->next->next != nullptr){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *slownext = slow->next;
    slow->next = nullptr;
    slow = reverseList2(slownext);
    while(head != nullptr && slow != nullptr){
        ListNode *temp1 = head->next;
        ListNode *temp2 = slow->next;
        head->next = slow;
        slow->next = temp1;
        head = temp1;
        slow = temp2;
    }
}

ListNode* rotateRight(ListNode* head, int k) {
    if(head == nullptr){
        return nullptr;
    }
    ListNode *node = head;
    int length = 1;
    while(node->next != nullptr){
        length++;
        node = node->next;
    }
    node->next = head;
    k %= length;
    int step = length - (k % length);
    ListNode *newHead = head;
    while(step > 0){
        newHead = newHead->next;
        node = node->next;
        step--;
    }
    node->next = nullptr;
    return newHead;
}


int main(){
    ListNode *N10 = new ListNode(10);
    ListNode *N9 = new ListNode(9, N10);
    ListNode *N8 = new ListNode(8, N9);
    ListNode *N7 = new ListNode(7, N8);
    ListNode *N6 = new ListNode(6, N7);
    ListNode *N5 = new ListNode(5, N6);
    ListNode *N4 = new ListNode(4, N5);
    ListNode *N3 = new ListNode(3, N4);
    ListNode *N2 = new ListNode(2, N3);
    ListNode *N1 = new ListNode(1, N2);
    ListNode *N0 = new ListNode(0, N1);
    N0 = rotateRight(N0, 2);
    while(N0 != nullptr){
        std::cout << N0->val << "\t";
        N0 = N0->next;
    }std::cout << std::endl;
}