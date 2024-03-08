class Solution {
public:
    string longestPalindrome(string s) {
        // Initialize variables to keep track of the maximum length and the corresponding palindrome substring.
        int max = 0;
        string ans = "";

        // Initialize the answer with the first character of the string.
        ans += s[0];

        // Iterate through the string to find palindromes with odd length.
        for (int i = 1; i < s.length() - 1; i++) {
            // Check if the character at the current position is the center of a palindrome with odd length.
            if (s[i - 1] == s[i + 1]) {
                // Expand around the center and find the longest palindrome.
                int start = i - 1, end = i + 1;
                while (start - 1 >= 0 && end + 1 < s.length() && s[start - 1] == s[end + 1]) {
                    start--, end++;
                }

                // Update the maximum length and the corresponding palindrome substring if a longer palindrome is found.
                if (max < end - start + 1) {
                    max = end - start + 1;
                    ans = s.substr(start, max);
                }
            }
        }

        // Iterate through the string to find palindromes with even length.
        for (int i = 1; i < s.length(); i++) {
            // Check if the current and previous characters are the same, indicating the center of a palindrome with even length.
            if (s[i - 1] == s[i]) {
                // Expand around the center and find the longest palindrome.
                int start = i - 1, end = i;
                while (start - 1 >= 0 && end + 1 < s.length() && s[start - 1] == s[end + 1]) {
                    start--, end++;
                }

                // Update the maximum length and the corresponding palindrome substring if a longer palindrome is found.
                if (max < end - start + 1) {
                    max = end - start + 1;
                    ans = s.substr(start, max);
                }
            }
        }

        return ans;
    }
};
