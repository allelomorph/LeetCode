# Time to complete: n/a (documenting peer answer)

# Treated as: study problem (research allowed)

# Needed to research:

# Notes:
# - credit to user cqdx:
#   - https://leetcode.com/problems/transpose-file/discuss/2236632/Very-obvious-and-simple-solution-with-awk
# - did not consider this approach originally, having forgotten that cut can
#   can operate on a whole file, plus getting obsessed with 2 dimensional
#   arrays in bash
# - seq mentioned in this efficiency analysis of int ranges in bash:
#   - https://stackoverflow.com/questions/169511/how-do-i-iterate-over-a-range-of-numbers-defined-by-variables-in-bash

#### Begin solution, results at https://leetcode.com/submissions/detail/761692466/


#!/usr/bin/bash
# Read from the file file.txt and print its transposed content to stdout
# Notes:
# - each row has the same number of columns
# - each field is separated by the ' ' character

for i in $(seq $(head -n1 file.txt | wc -w) ); do
    echo $(cut -d' ' -f$i file.txt);
done


#### end solution
