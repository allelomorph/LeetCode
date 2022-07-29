#include <iostream>
#include <thread>      // thread
#include <random>
#include <functional>  // function
#include <tuple>


void printFizz() {
    std::cout << "fizz";
}

void printBuzz() {
    std::cout << "buzz";
}

void printFizzBuzz() {
    printFizz();
    printBuzz();
}

void printNumber(int n) {
    std::cout << n;
}


// Time to complete: 45 mins

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - cppreference for condition_varaible::notify_one() dicusses how it
//     is best practice to unlock the mutex before notifying the condition
//     variable, but in this solution it is difficult to determine whether
//     cv.wait() was ever called, and unlocking an unlocked mutex would
//     throw an exception
// - in researching how to make an array of different function pointer types in
//     test main, discovered C++17's std::variant as an upgrade to `union`

//// Begin solution, results at https://leetcode.com/submissions/detail/759474137/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable


class FizzBuzz {
private:
    int n;
    std::condition_variable cv;
    std::mutex cv_m;
    int exec_i {1};  // execution index
public:
    FizzBuzz(int n) : n(n) {}

    // printFizz() outputs "fizz".
    void fizz(std::function<void()> printFizz) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {3}; i <= n; i += 3) {
            if (i % 5 == 0)
                continue;
            while (exec_i % 3 != 0 || exec_i % 5 == 0)
                cv.wait(lock);
            printFizz();
            ++exec_i;
            cv.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(std::function<void()> printBuzz) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {5}; i <= n; i += 5) {
            if (i % 3 == 0)
                continue;
            while (exec_i % 5 != 0 || exec_i % 3 == 0)
                cv.wait(lock);
            printBuzz();
            ++exec_i;
            cv.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
    void fizzbuzz(std::function<void()> printFizzBuzz) {
        std::unique_lock<std::mutex> lock(cv_m);
        for (int i {15}; i <= n; i += 15) {
            while (exec_i % 3 != 0 || exec_i % 5 != 0)
                cv.wait(lock);
            printFizzBuzz();
            ++exec_i;
            cv.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(std::function<void(int)> printNumber) {
        std::unique_lock<std::mutex> lock(cv_m);
        while (exec_i <= n) {
            printNumber(exec_i);
            ++exec_i;
            cv.notify_all();
            while (exec_i <= n && (exec_i % 3 == 0 || exec_i % 5 == 0))
               cv.wait(lock);
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


void testFizzBuzz(int n) {
    FizzBuzz solution(n);
    using tp_t = std::tuple<
            void (FizzBuzz::*)(std::function<void ()>),
            std::function<void ()>
        >;
    // separate treatment for printNumber fp type
    tp_t thread_params[3] {
                          { &FizzBuzz::fizz, printFizz },
                          { &FizzBuzz::buzz, printBuzz },
                          { &FizzBuzz::fizzbuzz, printFizzBuzz }
                      };
    std::thread threads[4];
    std::cout << "FizzBuzz(" << n << "): ";
    // threads run asynchronously in any order

    UniformRandIntGen<> rng_0_to_3(0, 3);
    for (int i {rng_0_to_3()}, j {0}, mod_i; j < 4; ++i, ++j) {
        mod_i = i % 4;
        if (mod_i == 3) {
            threads[mod_i] = std::thread (
                &FizzBuzz::number, &solution, printNumber);
        } else {
            threads[mod_i] = std::thread (
                std::get<0>(thread_params[mod_i]), &solution,
                std::get<1>(thread_params[mod_i]));
        }
    }
    for (int i {rng_0_to_3()}, j {0}; j < 4; ++i, ++j)
        threads[i % 4].join();
    std::cout << std::endl;

}


int main() {
    testFizzBuzz(15);
    testFizzBuzz(5);
}
