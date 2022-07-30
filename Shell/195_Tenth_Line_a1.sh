# Time to complete: 10 mins

# Treated as: study problem (research allowed)

# Needed to research:

# Notes:
# - Great comparative exploration of methods with sed, awk, perl, etc:
#   - https://stackoverflow.com/a/39217130

#### Begin solution, results at https://leetcode.com/submissions/detail/760263533/


#!/usr/bin/bash
# Read from the file file.txt and output the tenth line to stdout
# Notes:
# - If the file contains less than 10 lines, what should you output?
# - There's at least three different solutions. Try to explore all possibilities.

# first solution to come to mind, but prints last line if less than 10
# head -n10 file2.txt | tail -n1

# apparently better performance
tail -n+10 file2.txt | head -n1

# sed pipeless
# sed '10q;d' file2.txt


#### end solution
