#include <iostream>
#include <thread>      // thread
#include <random>
#include <functional>  // function
#include <tuple>


void printNumber(int n) {
    std::cout << n;
}


// Time to complete: 20 mins

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - cppreference for condition_varaible::notify_one() dicusses how it
//     is best practice to unlock the mutex before notifying the condition
//     variable, but in this solution it is difficult to determine whether
//     cv.wait() was ever called, and unlocking an unlocked mutex would
//     throw an exception

//// Begin solution, results at https://leetcode.com/submissions/detail/758751859/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable


class ZeroEvenOdd {
private:
    int n;
    std::condition_variable cv;
    std::mutex cv_m;
    bool print_zero {true};
    bool print_odd {true};
public:
    ZeroEvenOdd(int n) : n(n) {}

    // printNumber(x) outputs "x", where x is an integer.
    void zero(std::function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {0}; i < n; ++i) {
            while (!print_zero)
                cv.wait(lock);
            printNumber(0);
            print_zero = false;
            cv.notify_all();
        }
    }

    void even(std::function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {2}; i <= n; i += 2) {
            while (print_zero || print_odd)
                cv.wait(lock);
            printNumber(i);
            print_odd = true;
            print_zero = true;
            cv.notify_all();
        }
    }

    void odd(std::function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {1}; i <= n; i += 2) {
            while (print_zero || !print_odd)
                cv.wait(lock);
            printNumber(i);
            print_odd = false;
            print_zero = true;
            cv.notify_all();
        }
    }
};


//// end solution


// copied from The_Cpp_Programming_Language_4th_ed/utils/
template<class IntType = int>
class UniformRandIntGen {
public:
    UniformRandIntGen(IntType low, IntType high) :rng{rd()}, dist{low, high} { }
    IntType operator()() { return dist(rng); }
private:
    // The default_random_engine (minstd_rand0 or
    //   std::linear_congruential_engine<std::uint_fast32_t, 16807, 0,
    //   2147483647> in the GNU implementation) seems to not be
    //   seeded/produces the same values at runtime for every compilation;
    //   using Marsenne instead.
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng;          // random-number engine used (Mersenne-Twister)
    std::uniform_int_distribution<IntType> dist;
};


void testZeroEvenOdd(int n) {
    ZeroEvenOdd solution(n);
    using tp_t = void (ZeroEvenOdd::*)(std::function<void (int)>);
    tp_t thread_params[3] { &ZeroEvenOdd::zero,
            &ZeroEvenOdd::even, &ZeroEvenOdd::odd };
    std::thread threads[3];
    std::cout << "ZeroEvenOdd(" << n << "): ";
    // threads run asynchronously in any order
    UniformRandIntGen<> rng_0_to_2(0, 2);
    for (int i {rng_0_to_2()}, j {0}; j < 3; ++i, ++j) {
        threads[i % 3] = std::thread (
            thread_params[i % 3], &solution, printNumber);
    }
    for (int i {rng_0_to_2()}, j {0}; j < 3; ++i, ++j)
        threads[i % 3].join();
    std::cout << std::endl;
}


int main() {
    testZeroEvenOdd(2);
    testZeroEvenOdd(5);
}
