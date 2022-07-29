#include <iostream>
#include <thread>      // thread
#include <functional>  // function
#include <string>
#include <vector>


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

//// Begin solution, results at https://leetcode.com/submissions/detail/759192763/


#include <mutex>               // mutex, unique_lock
#include <condition_variable>  // condition_variable
#include <cstdint>             // uint8_t


class H2O {
private:
    std::condition_variable cv;
    std::mutex cv_m;
    uint8_t H_count {0};
    uint8_t O_count {0};
public:
    H2O() {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(cv_m);
        while (H_count >= 2)
            cv.wait(lock);
        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
        ++H_count;
        if (H_count == 2 && O_count == 1) {
            H_count = 0;
            O_count = 0;
        }
        cv.notify_all();
    }

    void oxygen(std::function<void()> releaseOxygen) {
        std::unique_lock<std::mutex> lock(cv_m);
        while (O_count >= 1)
            cv.wait(lock);
        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        ++O_count;
        if (H_count == 2 && O_count == 1) {
            H_count = 0;
            O_count = 0;
        }
        cv.notify_all();
    }
};


//// end solution


// 3 * n == water.length
// 1 <= n <= 20
// water[i] is either 'H' or 'O'.
// There will be exactly 2 * n 'H' in water.
// There will be exactly n 'O' in water.

void testH2O(const std::string &water) {
    H2O solution;
    std::vector<std::thread> threads;
    std::cout << "H2O(\"" << water << "\"): ";
    // threads run in order of supplied elements
    int water_sz (water.size());
    for (int i {0}; i < water_sz; ++i) {
        if (water[i] == 'H') {
            threads.push_back(
                std::thread(&H2O::hydrogen, &solution, []{ std::cout << 'H'; })
                );
        }
        if (water[i] == 'O') {
            threads.push_back(
                std::thread(&H2O::oxygen, &solution, []{ std::cout << 'O'; })
                );
        }
    }
    for (int i {0}; i < water_sz; ++i)
        threads[i].join();
    std::cout << std::endl;
}


int main() {
    testH2O("HOH");
    testH2O("OOHHHH");
}
