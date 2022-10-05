#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(nullptr), right(nullptr) {
    }
    TreeNode(int val, TreeNode *left, TreeNode *right): val(val), left(left), right(right){}
};

void preList(TreeNode *pRoot, vector<int> &view){
    if(pRoot == nullptr) return;
    view.push_back(pRoot->val);
    preList(pRoot->left, view);
    preList(pRoot->right, view);
}

void postList(TreeNode *pRoot, vector<int> &view){
    if(pRoot == nullptr) return;
    view.push_back(pRoot->val);
    postList(pRoot->right, view);
    postList(pRoot->left, view);
}

bool isSymmetrical(TreeNode* pRoot) {
    if(pRoot == nullptr) return true;
    if(pRoot->left == nullptr && pRoot->right == nullptr) return true;
    if(pRoot->left == nullptr || pRoot->right == nullptr) return false;
    vector<int> preView, postView;
    preList(pRoot->left, preView);
    postList(pRoot->right, postView);
    int length = min(preView.size(), postView.size());
    for(int i=0; i<length; i++){
        if(preView[i] != postView[i]) return false;
    }
    return preView.size() == postView.size();
}


int main(){

    // TreeNode *node0 = new TreeNode(0, nullptr, nullptr);
    // TreeNode *node1 = new TreeNode(1, nullptr, nullptr);
    // TreeNode *node2 = new TreeNode(2, nullptr, nullptr);
    // TreeNode *node3 = new TreeNode(3, nullptr, nullptr);
    // TreeNode *node4 = new TreeNode(4, nullptr, nullptr);
    // TreeNode *node5 = new TreeNode(5, nullptr, nullptr);
    // TreeNode *node6 = new TreeNode(6, nullptr, nullptr);
    // TreeNode *node7 = new TreeNode(7, nullptr, nullptr);

    TreeNode *nodea = new TreeNode(9);
    TreeNode *nodeb = new TreeNode(3);
    TreeNode *nodec = new TreeNode(3);
    TreeNode *noded = new TreeNode(9);

    TreeNode *nodeA = new TreeNode(2, nodea, nodeb);
    TreeNode *nodeB = new TreeNode(2, nodec, noded);

    TreeNode *Root = new TreeNode(10, nodeA, nodeB);
    cout << isSymmetrical(Root) << endl;
}