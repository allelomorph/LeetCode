#ifndef LC_STRINGFROMVECTOR_HH
#define LC_STRINGFROMVECTOR_HH


#include <vector>
#include <string>
#include <sstream>


namespace LeetCodeUtils {


template<typename T>
const std::string stringFromVector(std::vector<T> v) {
    std::ostringstream oss;
    oss << '[';
    for (auto it {v.begin()}, last {--v.end()}; it != v.end(); ++it) {
        oss << *it;
        if (it != last)
            oss << ',';
    }
    oss << ']';
    return oss.str();
}


template<typename T>
const std::string stringFromNestedVector(const std::vector<std::vector<T>> &nv) {
    std::ostringstream oss;
    oss << '[';
    for (auto it {nv.begin()}, last {--nv.end()}; it != nv.end(); ++it) {
        oss << stringFromVector(*it);
        if (it != last)
            oss << ',';
    }
    oss << ']';
    return oss.str();
}


}  // namespace LeetCodeUtils


#endif  // LC_STRINGFROMVECTOR_HH
