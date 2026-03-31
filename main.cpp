#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>

using namespace std;

// Binary Tree Node structure
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build binary tree from level-order traversal array
TreeNode* buildTree(const vector<int>& levelOrder) {
    if (levelOrder.empty() || levelOrder[0] == -1) {
        return nullptr;
    }

    TreeNode* root = new TreeNode(levelOrder[0]);
    queue<TreeNode*> q;
    q.push(root);

    int i = 1;
    while (!q.empty() && i < levelOrder.size()) {
        TreeNode* node = q.front();
        q.pop();

        // Left child
        if (i < levelOrder.size() && levelOrder[i] != -1) {
            node->left = new TreeNode(levelOrder[i]);
            q.push(node->left);
        }
        i++;

        // Right child
        if (i < levelOrder.size() && levelOrder[i] != -1) {
            node->right = new TreeNode(levelOrder[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}

// Find k-th largest element using reverse in-order traversal
int kthLargest(TreeNode* root, int& k) {
    if (root == nullptr) {
        return -1;
    }

    // Traverse right subtree first (larger values)
    int result = kthLargest(root->right, k);
    if (k == 0) {
        return result;
    }

    // Process current node
    k--;
    if (k == 0) {
        return root->val;
    }

    // Traverse left subtree
    return kthLargest(root->left, k);
}

int findKthLargest(TreeNode* root, int cnt) {
    int k = cnt;
    return kthLargest(root, k);
}

// Free memory
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    int n, cnt;

    // Read number of nodes and cnt
    cin >> n >> cnt;

    vector<int> levelOrder(n);

    // Read all node values
    for (int i = 0; i < n; i++) {
        cin >> levelOrder[i];
    }

    // Build tree and find result
    TreeNode* root = buildTree(levelOrder);
    int result = findKthLargest(root, cnt);

    cout << result << endl;

    // Clean up
    deleteTree(root);

    return 0;
}
