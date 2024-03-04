class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int right, left = 0;
        int ans = 0; // Longest substring length
        vector<int> charIndex(128, -1);
        for (right = 0; right < s.length(); right++) {
            if (charIndex[s[right]] >= left) {
                left = charIndex[s[right]] + 1;
            }
            charIndex[s[right]] = right;
            ans = max(ans, right - left + 1);
        }
        return ans;
    }
};
