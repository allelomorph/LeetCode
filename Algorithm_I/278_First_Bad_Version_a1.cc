#include <iostream>


class APICallIsBadVersion {
public:
    int first_bad_ver;

    bool operator () (int ver) const {
        return (ver >= first_bad_ver);
    }
};

APICallIsBadVersion isBadVersion;


//// Begin solution, results at https://leetcode.com/submissions/detail/736203958/


// The API isBadVersion is defined for you.
// bool isBadVersion(int version);


class Solution {
    // 1 <= bad <= n <= 2^31 - 1  // INT_MAX
    // So, previous binary search calculation of mid = (lo + hi) / 2
    //   can cause int overflow for higher values
public:
    int firstBadVersion(int n) {
        // can be implemented similarly to a binary search (non-recursive)
        int earliest_bad_ver {n};
        for (int lo {0}, hi {n}, mid {lo + ((hi - lo) / 2)};
             lo <= hi; mid = lo + ((hi - lo) / 2)) {
            if (isBadVersion(mid)) {
                if (mid < earliest_bad_ver)
                    earliest_bad_ver = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return earliest_bad_ver;
    }
};


//// end solution


int main() {
    Solution solution;

    isBadVersion.first_bad_ver = 4;
    std::cout << "bad: " << isBadVersion.first_bad_ver <<
        " solution.firstBadVersion(5): " << solution.firstBadVersion(5) << '\n';
    // 4
    isBadVersion.first_bad_ver = 1;
    std::cout << "bad: " << isBadVersion.first_bad_ver <<
        " solution.firstBadVersion(1): " << solution.firstBadVersion(1) << '\n';
    // 1
    isBadVersion.first_bad_ver = 1702766719;
    std::cout << "bad: " << isBadVersion.first_bad_ver <<
        " solution.firstBadVersion(2126753390): " <<
        solution.firstBadVersion(2126753390) << '\n';
    // 4
}
