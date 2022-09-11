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


template<typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    is >> std::ws;  // ensure leading whitespace skipped
    std::vector<T> new_v;
    if (is.peek() != '[')
        throw std::invalid_argument("expected '[' at start of vector");
    is.get();  // consume '['
    T temp;
    for (char peek(is.peek()); is.good() && peek != ']';) {
        is >> std::ws;
        is >> temp;
        if (!is.good() && !is.eof())
            throw std::invalid_argument("could not read element from stream");
        new_v.emplace_back(temp);
        is >> std::ws;
        peek = is.peek();
        if (is.eof() || (peek != ',' && peek != ']'))
            throw std::invalid_argument("expected ',' or ']' after element");
        if (peek == ',')
            is.get();
    }
    is.get();
    v = std::move(new_v);
    return is;
}


#endif  // LC_VECTOR_STREAM_OPS
