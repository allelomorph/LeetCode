#include <iostream>
#include <thread>      // thread
#include <random>
#include <functional>  // function
#include <tuple>


// Time to complete: 30 mins

// Treated as: study problem (research allowed)

// Needed to research:
// - https://en.cppreference.com/w/cpp/thread/condition_variable
// - https://en.cppreference.com/w/cpp/thread/lock_guard
// - https://en.cppreference.com/w/cpp/thread/unique_lock
// - https://en.cppreference.com/w/cpp/thread/mutex
// - https://en.cppreference.com/w/cpp/utility/functional/function
// - Eaxmple credit: Surabhi_Gupta
//   - https://leetcode.com/problems/print-in-order/discuss/2265427/C%2B%2B-using-mutex-and-conditional-variable

// Notes:
// - must be compiled with `-pthread`
// - While building test main, learned that class member functions need to be
//    named with a different syntax from normal function pointers in some cases,
//    here when passed to INVOKE for thread creation - `&Class::Func`:
//    -  https://stackoverflow.com/a/10673671
// - Also, when using this syntax, the `this` arg to INVOKE must be a pointer
//    instead of a reference for sub-C++17:
//    - https://stackoverflow.com/a/36472589

//// Begin solution, results at https://leetcode.com/submissions/detail/753576752/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable


class Foo {
public:
    Foo() {}

    void first(std::function<void()> printFirst) {
        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();
        exec_i = 1;
        cv.notify_all();
    }

    void second(std::function<void()> printSecond) {
        std::unique_lock<std::mutex> lock(cv_m);
        while (exec_i != 1)
            cv.wait(lock);
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();
        exec_i = 2;
        // unlock before notify avoids waking up the waiting thread only to
        //   block again
        lock.unlock();
        cv.notify_all();
    }

    void third(std::function<void()> printThird) {
        std::unique_lock<std::mutex> lock(cv_m);
        // lambda equivalent to while loop in second():
        cv.wait(lock, [this]{return this->exec_i == 2;});
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
        exec_i = 3;
    }

private:
    std::mutex cv_m;
    std::condition_variable cv;
    int exec_i {0};
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
    Foo solution;

    // see Notes section above for thread creation with member functions
    using tp_t = std::tuple<void (Foo::*)(std::function<void ()>),
                        std::function<void ()>>;
    tp_t thread_params[3] {
                          { &Foo::first, []{std::cout << "first";} },
                          { &Foo::second, []{std::cout << "second";} },
                          { &Foo::third, []{std::cout << "third";} }
                      };
    std::thread threads[3];
    // threads run asynchronously in any order
    UniformRandIntGen<> rng_0_to_2(0, 2);
    for (int i {rng_0_to_2()}, j {0}; j < 3; ++i, ++j) {
        threads[i % 3] = std::thread (
            std::get<0>(thread_params[i % 3]), &solution,
            std::get<1>(thread_params[i % 3])
            );
    }
    for (int i {rng_0_to_2()}, j {0}; j < 3; ++i, ++j)
        threads[i % 3].join();
}
