class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> table;

        // Build the lookup table
        for (int i = 0; i < nums.size(); i++) {
            table[nums[i]] = i;
        }

        // Find the complement
        for (int i = 0; i < nums.size(); i++) {
            // Because => complement + nums[i] = target
            int complement = target - nums[i];
            if (table.count(complement) && table[complement] != i) {
                return {i, table[complement]};
            }
        }

        return {}; // No solution found
    }
};
