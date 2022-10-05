#include <iostream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


TreeNode *subFlatten(TreeNode *root){
    if(root == nullptr){
        return nullptr;
    }
    if(root->left == nullptr && root->right == nullptr){
        return root;
    }
    TreeNode *leftEndNode = subFlatten(root->left);
    TreeNode *rightEndNode = subFlatten(root->right);
    if(leftEndNode == nullptr){
        return rightEndNode;
    }else if(rightEndNode == nullptr){
        root->right = root->left;
        root->left = nullptr;
        return leftEndNode;
    }else{
        TreeNode *temp = root->right;
        root->right = root->left;
        root->left = nullptr;
        leftEndNode->right = temp;
        return rightEndNode;
    }
}
void flatten(TreeNode* root) {
    subFlatten(root);
}

int main(){
    TreeNode *node0 = new TreeNode(0, nullptr, nullptr);
    TreeNode *node1 = new TreeNode(1, nullptr, nullptr);
    TreeNode *node2 = new TreeNode(2, nullptr, nullptr);
    TreeNode *node3 = new TreeNode(3, nullptr, nullptr);
    TreeNode *node4 = new TreeNode(4, nullptr, nullptr);
    TreeNode *node5 = new TreeNode(5, nullptr, nullptr);
    TreeNode *node6 = new TreeNode(6, nullptr, nullptr);
    TreeNode *node7 = new TreeNode(7, nullptr, nullptr);

    TreeNode *nodea = new TreeNode(5, node0, node1);
    TreeNode *nodeb = new TreeNode(7, node2, node3);
    TreeNode *nodec = new TreeNode(3, node4, node5);
    TreeNode *noded = new TreeNode(9, node6, node7);

    TreeNode *nodeA = new TreeNode(10, nodea, nodeb);
    TreeNode *nodeB = new TreeNode(11, nodec, noded);

    TreeNode *Root = new TreeNode(10, nodeA, nodeB);
    flatten(Root);
    while(Root != nullptr){
        std::cout << Root->val << "\t";
        Root = Root->right;
    }
    std::cout << std::endl;
    return 0;
}