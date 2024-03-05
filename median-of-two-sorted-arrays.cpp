class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int nms1 = nums1.size();
        int nms2 = nums2.size();
        int i = 0, j = 0;
        int current = 0, last = 0;

        // Find median
        for (int count = 0; count <= (nms1 + nms2) / 2; count++) {
            last = current;
            if (i != nms1 && j != nms2) {
                if (nums1[i] > nums2[j]) {
                    current = nums2[j++];
                } else {
                    current = nums1[i++];
                }
            } else if (i < nms1) {
                current = nums1[i++];
            } else {
                current = nums2[j++];
            }
        }

        // Check if the sum of n and m is odd
        if ((nms1 + nms2) % 2 == 1) {
            return static_cast<double>(current);
        } else {
            // Calculate average of two for even arrays
            double ans = static_cast<double>(current) + static_cast<double>(last);
            return ans / 2.0;
        }
    }
};
