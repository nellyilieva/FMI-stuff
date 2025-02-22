#include <iostream>
#include <vector>
#include <algorithm>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

//using const_iterator = std::vector<int>::const_iterator;
//
//TreeNode* build_from_range(const_iterator begin, const_iterator end) {
//    // When end is before begin std::distance will return
//    // negative number by standard.
//    int distance = std::distance(begin, end);
//
//    if (distance < 0)
//        return nullptr;
//
//    if (distance == 0)
//        return new TreeNode(*begin);
//
//    int mid = distance / 2;
//
//    return new TreeNode(*(begin + mid),
//        build_from_range(begin, begin + mid - 1),
//        build_from_range(begin + mid + 1, end)
//    );
//}
//
//TreeNode* build_from_sorted(const std::vector<int>& v) {
//    return build_from_range(v.begin(), v.end() - 1);
//}

TreeNode* buildFromSorted(std::vector<int>& nums, int left, int right) {
    if (left > right) {
        return nullptr;
    }

    int mid = left + (right - left) / 2;
    TreeNode* root = new TreeNode(nums[mid]);
    root->left = buildFromSorted(nums, left, mid - 1);
    root->right = buildFromSorted(nums, mid + 1, right);
    return root;
}


TreeNode* sortedArrayToBST(std::vector<int>& nums) {
    return buildFromSorted(nums, 0, nums.size() - 1);
}

int main() {
    std::vector<int> nums = { -10, -3, 0, 5, 9 };
    TreeNode* root = sortedArrayToBST(nums);
}
