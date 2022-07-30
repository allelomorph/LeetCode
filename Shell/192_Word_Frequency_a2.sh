# Time to complete: 20 mins

# Treated as: study problem (research allowed)

# Needed to research:
# - grep -o
# - awk printf
# - read -a

# Notes:
# - identical to a1, but added read -a directly into array

#### Begin solution, results at https://leetcode.com/submissions/detail/760256321/


#!/usr/bin/bash
# Read from the file words.txt and output the word frequency list to stdout
# Note:
#  - it is guaranteed that each word's frequency count is unique.
#  - words.txt contains only lowercase characters and space ' ' characters.
#  - Each word must consist of lowercase characters only.
#  - Words are separated by one or more whitespace characters.

# one line:
# grep -oE '[a-z]+' words.txt | sort | uniq -c | sort -r | awk '{printf "%s %s\n", $2, $1}'

# multi-line not requiring awk:
grep -oE '[a-z]+' words.txt | sort | uniq -c | sort -r | while read -a LINE;
do
    echo ${LINE[1]} ${LINE[0]};
done


#### end solution
