#include <iostream>
#include <cmath>

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val): val(val), left(nullptr), right(nullptr){}
    TreeNode(int val, TreeNode *left, TreeNode *right): val(val),left(left), right(right){}
};

// 获取完全二叉树的深度
static int getFullTreeDepth(TreeNode *root){
    int count = 0;
    while(root != nullptr){
        count++;
        root = root->left;
    }
    return count;
}

// 获取完全二叉树的节点数
int getFullTreeNodeNum(TreeNode *root){
    if(root == nullptr){
        return 0;
    }
    if(root->right == nullptr){
        return root->left == nullptr ? 1 : 2;
    }
    int leftDepth = getFullTreeDepth(root->left);
    int rightDepth = getFullTreeDepth(root->right);
    if(leftDepth == rightDepth){  //左数为完全二叉树
        return (1 << leftDepth) + getFullTreeNodeNum(root->right);
    }else{ //leftDepth == rightDepth + 1 //右树为完全二叉树,但深度少一
        return (1 << rightDepth) + getFullTreeNodeNum(root->left);
    }
    return -1;
}

int main(int argc, char const *argv[]){
    TreeNode *node0 = new TreeNode(0);
    TreeNode *node1 = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *node4 = new TreeNode(4);
    // TreeNode *node5 = new TreeNode(5);
    // TreeNode *node6 = new TreeNode(6);
    // TreeNode *node7 = new TreeNode(7);

    TreeNode *nodea = new TreeNode(5, node0, node1);
    TreeNode *nodeb = new TreeNode(7, node2, node3);
    TreeNode *nodec = new TreeNode(3, node4, nullptr);
    TreeNode *noded = new TreeNode(9, nullptr, nullptr);

    TreeNode *nodeA = new TreeNode(10, nodea, nodeb);
    TreeNode *nodeB = new TreeNode(11, nodec, noded);

    TreeNode *Root = new TreeNode(10, nodeA, nodeB);
    std::cout << getFullTreeDepth(Root) << std::endl;
    std::cout << getFullTreeNodeNum(Root) << std::endl;
    return 0;
}