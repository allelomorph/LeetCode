#include <iostream>
#include <thread>      // thread
#include <random>
#include <functional>  // function
#include <tuple>


// Time to complete: 30 mins

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - cppreference for condition_varaible::notify_one() dicusses how it
//     is best practice to unlock the mutex before notifying the condition
//     variable, but in this solution it is difficult to determine whether
//     cv.wait() was ever called, and unlocking an unlocked mutex would
//     throw an exception
// - simplified from a1 to use bool for condition variable
// - spinlock is not appropriate here, as we need a way to force the first
//     thread to call printFoo() to print first, rather than just guarantee
//     alternating calls of printFoo() and printBar(); however while researching
//     spinlocks, found this useful guide to optimizing them in C++:
//     - https://rigtorp.se/spinlock/
// - also, while spinlocking on one atomic bool would not work, there are
//     solutions with two:
//     - https://leetcode.com/problems/print-foobar-alternately/discuss/2091119/C%2B%2B-solution-with-2-atomics-(with-cache-line)

//// Begin solution, results at https://leetcode.com/submissions/detail/757677920/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable


class FooBar {
private:
    int n;
    std::condition_variable cv;
    std::mutex cv_m;
    bool print_bar_next {false};
public:
    FooBar(int n) : n(n) {}

    void foo(std::function<void()> printFoo) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {0}; i < n; ++i) {
            while (print_bar_next) {
                cv.wait(lock);
            }
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            print_bar_next = true;
            cv.notify_all();
        }
    }

    void bar(std::function<void()> printBar) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {0}; i < n; ++i) {
            while (!print_bar_next) {
                cv.wait(lock);
            }
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            print_bar_next = false;
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



int main() {
    FooBar solution(5);

    // see Notes section above for thread creation with member functions
    using tp_t = std::tuple<void (FooBar::*)(std::function<void ()>),
                        std::function<void ()>>;
    tp_t thread_params[2] {
                          { &FooBar::foo, []{std::cout << "foo";} },
                          { &FooBar::bar, []{std::cout << "bar";} }
                      };
    std::thread threads[2];
    // threads run asynchronously in any order
    UniformRandIntGen<> rng_0_to_1(0, 1);
    for (int i {rng_0_to_1()}, j {0}; j < 2; ++i, ++j) {
        threads[i % 2] = std::thread (
            std::get<0>(thread_params[i % 2]), &solution,
            std::get<1>(thread_params[i % 2])
            );
    }
    for (int i {rng_0_to_1()}, j {0}; j < 2; ++i, ++j)
        threads[i % 2].join();
}
