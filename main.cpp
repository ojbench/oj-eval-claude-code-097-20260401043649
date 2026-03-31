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
    string line;
    vector<int> levelOrder;
    int cnt = 0;

    // Read first line
    if (!getline(cin, line)) {
        return 1;
    }

    // Parse the tree array
    // Remove any brackets and parse numbers
    string cleanLine;
    for (char c : line) {
        if (c == '[' || c == ']' || c == ',') {
            cleanLine += ' ';
        } else {
            cleanLine += c;
        }
    }

    stringstream ss(cleanLine);
    string token;
    while (ss >> token) {
        if (token == "root" || token == "=" || token == "cnt") {
            continue;
        }
        if (token == "null") {
            levelOrder.push_back(-1);
        } else {
            try {
                int val = stoi(token);
                levelOrder.push_back(val);
            } catch (...) {
                // Skip invalid tokens
            }
        }
    }

    // Read second line if it exists (might contain cnt)
    if (getline(cin, line)) {
        // Extract cnt from second line
        stringstream ss2(line);
        string token2;
        while (ss2 >> token2) {
            if (token2 == "cnt" || token2 == "=") {
                continue;
            }
            try {
                cnt = stoi(token2);
                break;
            } catch (...) {
                // Skip invalid tokens
            }
        }
    } else if (!levelOrder.empty()) {
        // If no second line, assume cnt is the last number in levelOrder
        cnt = levelOrder.back();
        levelOrder.pop_back();
    }

    // Build tree and find result
    TreeNode* root = buildTree(levelOrder);
    int result = findKthLargest(root, cnt);

    cout << result << endl;

    // Clean up
    deleteTree(root);

    return 0;
}
