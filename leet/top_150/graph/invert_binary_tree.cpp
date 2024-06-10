// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

TreeNode *invertTree(TreeNode *root) {
  if (root == nullptr) {
    return root;
  }

  auto* temp = root->right;
  root->right = root->left;
  root->left = temp;
  invertTree(root->left);
  invertTree(root->right);

  return root;
}

int main() {
  TreeNode root(4);
  root.left = new TreeNode(2, new TreeNode(1), new TreeNode(3));
  root.right = new TreeNode(7, new TreeNode(6), new TreeNode(9));

  return 0;
}
