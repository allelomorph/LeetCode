# Time to complete: 2.5 hrs

# Treated as: study problem (research allowed)

# Needed to research:
# - regex non-whitespace \S
# - bash C-like for loops with ((;;))
# - count of bash array members with ${#[@]}
# - converting to bash integer values with $(())

# Notes:
# - attempted originally to use 2D arrays, but abandoned the idea when
#   discovering difficulty in using C-like [][] notation, see:
#   - https://stackoverflow.com/a/44831174
#   - https://www.baeldung.com/linux/bash-2d-arrays
# - found detailed efficiency analysis of int ranges in bash:
#   - https://stackoverflow.com/questions/169511/how-do-i-iterate-over-a-range-of-numbers-defined-by-variables-in-bash

#### Begin solution, results at https://leetcode.com/submissions/detail/760853659/


#!/usr/bin/bash
# Read from the file file.txt and print its transposed content to stdout
# Notes:
# - each row has the same number of columns
# - each field is separated by the ' ' character

_ROW=(`head -n1 file2.txt`)
ROW_CT="${#_ROW[@]}"
# wc output is text, not integer - need to convert
COL_CT=$((`wc -l < file2.txt`))
# flattening file into array of tokens, \S captures all non-whitespace
TOKENS=(`grep -oE '\S+' file2.txt`)
TOKEN_CT="${#TOKENS[@]}"

for ((i = 0; i < ROW_CT; ++i)); do
    LINE=()
    for ((j = i; j < TOKEN_CT; j += ROW_CT)); do
        LINE+=("${TOKENS[$j]}")
    done
    echo "${LINE[@]}"
done


#### end solution
