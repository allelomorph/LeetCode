#include <stdio.h>


void printNumber(int n) {
    printf("%i", n);
}


// Time to complete: 10 mins (after a1)

// Treated as: study problem (research allowed)

// Needed to research:

// Notes:
// - must be compiled with `-pthread`
// - modified from C++11 in a1

//// Begin solution, results at https://leetcode.com/submissions/detail/758776044/


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
    bool print_zero;
    bool print_odd;
} ZeroEvenOdd;

ZeroEvenOdd *zeroEvenOddCreate(int n) {
    ZeroEvenOdd *obj = malloc(sizeof(ZeroEvenOdd));
    obj->n = n;
    pthread_mutex_init(&(obj->cv_m), NULL);
    pthread_cond_init(&(obj->cv), NULL);
    obj->print_zero = true;
    obj->print_odd = true;
    return obj;
}

// You may call global function `void printNumber(int x)`
// to output "x", where x is an integer.

void zero(ZeroEvenOdd *obj) {
    for (int i = 0; i < obj->n; ++i) {
        pthread_mutex_lock(&(obj->cv_m));
        while (!obj->print_zero)
            pthread_cond_wait(&(obj->cv), &(obj->cv_m));
        printNumber(0);
        obj->print_zero = false;
        pthread_cond_broadcast(&(obj->cv));
        pthread_mutex_unlock(&(obj->cv_m));
    }
}

void even(ZeroEvenOdd *obj) {
    for (int i = 2; i <= obj->n; i += 2) {
        pthread_mutex_lock(&(obj->cv_m));
        while (obj->print_zero || obj->print_odd)
            pthread_cond_wait(&(obj->cv), &(obj->cv_m));
        printNumber(i);
        obj->print_zero = true;
        obj->print_odd = true;
        pthread_cond_broadcast(&(obj->cv));
        pthread_mutex_unlock(&(obj->cv_m));
    }
}

void odd(ZeroEvenOdd *obj) {
    for (int i = 1; i <= obj->n; i += 2) {
        pthread_mutex_lock(&(obj->cv_m));
        while (obj->print_zero || !obj->print_odd)
            pthread_cond_wait(&(obj->cv), &(obj->cv_m));
        printNumber(i);
        obj->print_zero = true;
        obj->print_odd = false;
        pthread_cond_broadcast(&(obj->cv));
        pthread_mutex_unlock(&(obj->cv_m));
    }
}

void zeroEvenOddFree(ZeroEvenOdd *obj) {
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


// Was unable to cast function pointers to make them compatible with
//   pthread_create, so creating wrappers with proper prototype:

typedef void *(*tsrp_t)(void *);  // thread start routine pointer

void *zeroWrapper(void *p) {
    zero((ZeroEvenOdd *)p);
    return NULL;
}

void *evenWrapper(void *p) {
    even((ZeroEvenOdd *)p);
    return NULL;
}

void *oddWrapper(void *p) {
    odd((ZeroEvenOdd *)p);
    return NULL;
}

void testZeroEvenOdd(int n) {
    ZeroEvenOdd *solution = zeroEvenOddCreate(n);
    pthread_t threads[3];
    tsrp_t tsrs[3] = { zeroWrapper, evenWrapper, oddWrapper };

    printf("ZeroEvenOdd(%i): ", n);
    // threads run asynchronously in any order
    for (int i = rangedRNG(2), j = 0; j < 3; ++i, ++j) {
        pthread_create(
            threads + (i % 3), NULL, tsrs[i % 3], solution
            );
    }
    for (int i = rangedRNG(2), j = 0; j < 3; ++i, ++j) {
        pthread_join(threads[i % 3], NULL);
    }
    printf("\n");
    zeroEvenOddFree(solution);
}

int main() {
    testZeroEvenOdd(2);
    testZeroEvenOdd(5);

    return EXIT_SUCCESS;
}
