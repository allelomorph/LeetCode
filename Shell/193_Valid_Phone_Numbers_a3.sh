# Time to complete: 10 mins

# Treated as: study problem (research allowed)

# Needed to research:
# - regex count of match with curly braces

# Notes:

#### Begin solution, results at https://leetcode.com/submissions/detail/760252370/


#!/usr/bin/bash
# Read from the file file.txt and output all valid phone numbers to stdout
# Note:
# - valid phone numbers appear two formats: (xxx) xxx-xxxx or xxx-xxx-xxxx
grep -oE '^(\([0-9]{3}\) |[0-9]{3}-)[0-9]{3}-[0-9]{4}$' file.txt


#### end solution
