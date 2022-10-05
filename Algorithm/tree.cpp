#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
using namespace std;

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val, TreeNode *left, TreeNode *right): val(val), left(left), right(right){}
};

vector<vector<int> > levelOrder(TreeNode* root) {
    // write code here
    vector<vector<int>> res;
    if(root == nullptr) return res;
    res.push_back(vector<int>());
    queue<pair<TreeNode *,int>> Q;
    Q.push(make_pair(root, 0));
    while(!Q.empty()){
        auto node = Q.front(); Q.pop();
        if(node.second < res.size()){
            res[node.second].push_back(node.first->val);
        }else if(node.second == res.size()){
            res.push_back(vector<int>());
            res[node.second].push_back(node.first->val);
        }else{
            printf("l");
        }
        cout << node.first->val << " ";
        if(node.first->left != nullptr) Q.push(make_pair(node.first->left, node.second + 1));
        if(node.first->right != nullptr) Q.push(make_pair(node.first->right, node.second + 1));
    }
    return res;
}



//在以head为根节点的的二叉树中，寻找和为target的路径,并打印
void process(TreeNode *head, int target, vector<int> &already){
    if(head == nullptr) return;
    if(head->left == nullptr && head->right == nullptr && head->val == target){
        already.push_back(target);
        for(int &a : already){
            printf("%d ", a);
        }
        cout << endl;
        already.pop_back();
        return;
    }
    if(target - head->val <= 0) return;
    already.push_back(head->val);
    if(head->left != nullptr){
        process(head->left, target - head->val, already);
    }
    if(head->right != nullptr){
        process(head->right, target - head->val, already);
    }
    already.pop_back();
}

// 打印出完全二叉树中路径和等于target的路径中全部节点(路径:根节点到页节点)
void printPath(TreeNode *head, int target){
    vector<int> V;
    process(head, target, V);
}


int main(int argc, char const * argv[]){
    TreeNode *node0 = new TreeNode(0, nullptr, nullptr);
    TreeNode *node1 = new TreeNode(1, nullptr, nullptr);
    TreeNode *node2 = new TreeNode(2, nullptr, nullptr);
    TreeNode *node3 = new TreeNode(3, nullptr, nullptr);
    TreeNode *node4 = new TreeNode(2, nullptr, nullptr);
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

    // levelOrder(Root);
    printPath(Root, atoi(argv[1]));

    return 0;
}