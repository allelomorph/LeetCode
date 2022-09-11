#ifndef LC_VECTOR_STREAM_OPS
#define LC_VECTOR_STREAM_OPS


#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>  // move


template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    os << '[';
    for (auto it {v.begin()}, last {--v.end()}; it != v.end(); ++it) {
        os << *it;
        if (it != last)
            os << ',';
    }
    os << ']';
    return os;
}


// using failbit instead of exceptions to mimic STL handling of failed parsing
template<typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    is >> std::ws;  // ensure leading whitespace skipped
    if (is.get() != '[') {
        is.setstate(std::ios_base::failbit);  // expected '[' at start
        return is;
    }
    is >> std::ws;
    std::vector<T> new_v;
    T temp;
    for (char peek(is.peek()); is.good() && peek != ']';) {
        is >> temp;
        if (is.fail() && !is.eof())
            return is;  // could not read element from stream
        new_v.emplace_back(temp);
        is >> std::ws;
        peek = is.peek();
        if (is.eof() || (peek != ',' && peek != ']')) {
            is.setstate(std::ios_base::failbit);  // expected ',' or ']' after element
            return is;
        }
        if (peek == ',')
            is.get();
        is >> std::ws;
    }
    is.get();  // consume ']'
    if (!is.fail() || is.eof())
        v = std::move(new_v);
    return is;
}


#endif  // LC_VECTOR_STREAM_OPS
