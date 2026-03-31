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
    getline(cin, line);

    // Parse input
    size_t rootPos = line.find("root = [");
    size_t cntPos = line.find("cnt = ");

    if (rootPos == string::npos || cntPos == string::npos) {
        return 1;
    }

    // Extract root array
    size_t startBracket = line.find('[', rootPos);
    size_t endBracket = line.find(']', startBracket);
    string rootStr = line.substr(startBracket + 1, endBracket - startBracket - 1);

    vector<int> levelOrder;
    stringstream ss(rootStr);
    string token;
    while (getline(ss, token, ',')) {
        // Trim whitespace
        size_t start = token.find_first_not_of(" \t");
        size_t end = token.find_last_not_of(" \t");
        if (start != string::npos && end != string::npos) {
            token = token.substr(start, end - start + 1);
            if (token == "null") {
                levelOrder.push_back(-1);
            } else {
                levelOrder.push_back(stoi(token));
            }
        }
    }

    // Extract cnt
    size_t cntStart = cntPos + 6;
    string cntStr;
    for (size_t i = cntStart; i < line.length(); i++) {
        if (isdigit(line[i])) {
            cntStr += line[i];
        } else if (!cntStr.empty()) {
            break;
        }
    }
    int cnt = stoi(cntStr);

    // Build tree and find result
    TreeNode* root = buildTree(levelOrder);
    int result = findKthLargest(root, cnt);

    cout << result << endl;

    // Clean up
    deleteTree(root);

    return 0;
}
