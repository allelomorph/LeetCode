#include <iostream>
#include <thread>      // thread
#include <random>
#include <functional>  // function


// Time to complete: 25 mins

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - cppreference for condition_varaible::notify_one() dicusses how it
//     is best practice to unlock the mutex before notifying the condition
//     variable, but in this solution it is difficult to determine whether
//     cv.wait() was ever called, and unlocking an unlocked mutex would
//     throw an exception
// - tests not fully implemented (this file will not compile): could not
//     understand how pickLeftFork, pickRightFork, eat, putLeftFork,
//     putRightFork would track fork use without taking parameters (at least
//     checking philosopher)
// - only test was for single call of each philosopher per thread, whereas
//     problem mentions that each may be called multiple times
// - multiple solution suggestions in one post, illustrating some more STL
//     concurrency concepts:
//     - https://leetcode.com/problems/the-dining-philosophers/discuss/2205538/C%2B%2B-Three-Solutions-or-Detailed-Explanation-or-One-Liner-or-Follow-Up-Questions

/// Begin solution, results at https://leetcode.com/submissions/detail/760017500/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable


class DiningPhilosophers {
private:
    std::condition_variable cv;
    std::mutex cv_m;
    static constexpr int TABLE_POSITIONS {5};
    bool forks_in_use[TABLE_POSITIONS] {};
public:
    DiningPhilosophers() {}

    void wantsToEat(int philosopher,
                    std::function<void()> pickLeftFork,
                    std::function<void()> pickRightFork,
                    std::function<void()> eat,
                    std::function<void()> putLeftFork,
                    std::function<void()> putRightFork) {
        // philosopher < TABLE_POSITIONS
        int l_fork {philosopher};
        int r_fork {(philosopher == 0) ? 4 : philosopher - 1};
        std::unique_lock<std::mutex> lock(cv_m);

        while (forks_in_use[r_fork])
            cv.wait(lock);
        pickRightFork();
        forks_in_use[r_fork] = true;
        cv.notify_all();

        while (forks_in_use[l_fork])
            cv.wait(lock);
        pickLeftFork();
        forks_in_use[l_fork] = true;
        cv.notify_all();

        eat();

        putLeftFork();
        forks_in_use[l_fork] = false;
        cv.notify_all();

        putRightFork();
        forks_in_use[r_fork] = false;
        cv.notify_all();
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


void testDiningPhilosophers() {
    DiningPhilosophers solution;
    std::thread threads[5];
    std::cout << "DiningPhilosophers(): ";
    // threads run asynchronously in any order
    UniformRandIntGen<> rng_0_to_4(0, 4);
    for (int i {rng_0_to_4()}, j {0}, mod_i; j < 5; ++i, ++j) {
        threads[i % 5] = std::thread (
            &DiningPhilosophers::wantsToEat, &solution,
            i % 5,
            pickLeftFork,
            pickRightFork,
            eat,
            putLeftFork,
            putRightFork
            );
    }
    for (int i {rng_0_to_4()}, j {0}; j < 5; ++i, ++j)
        threads[i % 5].join();
    std::cout << std::endl;
}


int main() {
    testDiningPhilosophers();
}
