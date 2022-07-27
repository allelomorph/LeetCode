#include <stdio.h>


void printFoo(void) {
    printf("foo");
}

void printBar(void) {
    printf("bar");
}


// Time to complete: 10 mins (after a2)

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - modified from C++11 in a2

//// Begin solution, results at https://leetcode.com/submissions/detail/757711429/


#include <pthread.h>
#include <stdlib.h>   // exit, malloc, free
#include <stdbool.h>  // true, false

// For brevity's sake, there is no error checking of pthread_* functions, but
//   in production code, we could check each call with the following (all
//   researched pthread funcs return errno.h macro values instead of setting
//   errno):
//
// retval = <pthread_func>(<params>);
// if (retval != 0) {
//     fprintf(stderr, "<enclosing func>: <pthread_func>: %s\n",
//             strerror(retval));
//     exit(retval);
// }


typedef struct {
    int n;
    pthread_mutex_t cv_m;
    pthread_cond_t cv;
    bool print_bar_next;
} FooBar;

FooBar *fooBarCreate(int n) {
    FooBar *obj = malloc(sizeof(FooBar));
    obj->n = n;
    // init mutex to default attributes
    pthread_mutex_init(&(obj->cv_m), NULL);
    // init condition variable to default attributes
    pthread_cond_init(&(obj->cv), NULL);
    obj->print_bar_next = false;
    return obj;
}

void foo(FooBar *obj) {
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&(obj->cv_m));
        while (obj->print_bar_next) {
            pthread_cond_wait(&(obj->cv), &(obj->cv_m));
        }
        // printFoo() outputs "foo". Do not change or remove this line.
        printFoo();
        obj->print_bar_next = true;
        pthread_cond_broadcast(&(obj->cv));
        pthread_mutex_unlock(&(obj->cv_m));
    }
}

void bar(FooBar *obj) {
    for (int i = 0; i < obj->n; i++) {
        pthread_mutex_lock(&(obj->cv_m));
        while (!obj->print_bar_next) {
            pthread_cond_wait(&(obj->cv), &(obj->cv_m));
        }
        // printBar() outputs "bar". Do not change or remove this line.
        printBar();
        obj->print_bar_next = false;
        pthread_cond_broadcast(&(obj->cv));
        pthread_mutex_unlock(&(obj->cv_m));
    }
}

void fooBarFree(FooBar *obj) {
    pthread_mutex_destroy(&(obj->cv_m));
    pthread_cond_destroy(&(obj->cv));
    free(obj);
}


//// end solution


#include <sys/time.h>  // struct timeval, gettimeofday
#include <limits.h>    // INT_MAX
#include <stdlib.h>    // random, srandom

// random() is guaranteed to return a number in the range [0 ... 2 ** 31)
#define MAX_RANDOM INT_MAX


int rangedRNG(int hi) {
    struct timeval tm;
    gettimeofday(&tm, NULL);
    srandom(tm.tv_sec + tm.tv_usec * 1000000ul);

    // using the modulo operator for generating a random number is not a good
    //   solution (it severely decreases entropy, see Notes)
    long n;
    do {
        n = random();
    } while (n > (MAX_RANDOM - ((MAX_RANDOM % (hi + 1)) + 1) % (hi + 1)));
    n %= (hi + 1);

    return (int)n;
}


// Was unable to cast function pointers for pritnFoo, printBar to
//   make them compatible with pthread_create, so creating wrappers
//   with proper prototype:

typedef void *(*tsrp_t)(void *);  // thread start routine pointer

void *fooWrapper(void *p) {
    foo((FooBar *)p);
    return NULL;
}

void *barWrapper(void *p) {
    bar((FooBar *)p);
    return NULL;
}


int main() {
    FooBar *solution = fooBarCreate(4);
    pthread_t threads[2];
    tsrp_t tsrs[2] = { fooWrapper, barWrapper };

    // threads run asynchronously in any order
    for (int i = rangedRNG(1), j = 0; j < 2; ++i, ++j) {
        pthread_create(
            threads + (i % 2), NULL, tsrs[i % 2], solution
            );
    }
    for (int i = rangedRNG(1), j = 0; j < 2; ++i, ++j) {
        pthread_join(threads[i % 2], NULL);
    }
    fooBarFree(solution);
    return EXIT_SUCCESS;
}
