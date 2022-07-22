#include <stdio.h>


void printFirst(void) {
    printf("first");
}

void printSecond(void) {
    printf("second");
}

void printThird(void) {
    printf("third");
}


// Time to complete: 40 mins

// Treated as: study problem (research allowed)

// Needed to research:
// - Oracle pthread multithreading guide:
//   - mutexes:
//     - https://docs.oracle.com/cd/E53394_01/html/E54803/sync-110.html
//   - condition variables:
//     - https://docs.oracle.com/cd/E53394_01/html/E54803/sync-21067.html
// - C rng with random(3) and srandom(3) (for test main):
//    - https://stackoverflow.com/a/18254516
//    - https://stackoverflow.com/a/10984975

// Notes:
// - must be compiled with `-pthread`

//// Begin solution, results at https://leetcode.com/submissions/detail/754064588/


#include <pthread.h>
#include <stdlib.h>   // exit, malloc, free

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
    // User defined data may be declared here.
    pthread_mutex_t cv_m;
    pthread_cond_t cv;
    int exec_i;
} Foo;

Foo *fooCreate() {
    Foo *obj = (Foo *) malloc(sizeof(Foo));
    // Initialize user defined data here
    pthread_mutex_init(&(obj->cv_m), NULL);
    pthread_cond_init(&(obj->cv), NULL);
    obj->exec_i = 0;
    return obj;
}

void first(Foo *obj) {
    // printFirst() outputs "first". Do not change or remove this line.
    printFirst();
    obj->exec_i = 1;
    pthread_cond_broadcast(&(obj->cv));
}

void second(Foo *obj) {
    pthread_mutex_lock(&(obj->cv_m));
    while (obj->exec_i != 1) {
        pthread_cond_wait(&(obj->cv), &(obj->cv_m));
    }
    // printSecond() outputs "second". Do not change or remove this line.
    printSecond();
    obj->exec_i = 2;
    pthread_mutex_unlock(&(obj->cv_m));
    pthread_cond_broadcast(&(obj->cv));
}

void third(Foo *obj) {
    pthread_mutex_lock(&(obj->cv_m));
    while (obj->exec_i != 2) {
        pthread_cond_wait(&(obj->cv), &(obj->cv_m));
    }
    // printThird() outputs "third". Do not change or remove this line.
    printThird();
    obj->exec_i = 3;
    pthread_mutex_unlock(&(obj->cv_m));
}

void fooFree(Foo *obj) {
    // User defined data may be cleaned up here.
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


// Was unable to cast function pointers for first, second, third to
//   make them compatible with pthread_create, so creating wrappers
//   with proper prototype:

typedef void *(*tsrp_t)(void *);  // thread start routine pointer

void *first_wrapper(void *p) {
    first((Foo *)p);
    return NULL;
}

void *second_wrapper(void *p) {
    second((Foo *)p);
    return NULL;
}

void *third_wrapper(void *p) {
    third((Foo *)p);
    return NULL;
}


int main() {
    Foo *solution = fooCreate();
    pthread_t threads[3];
    tsrp_t tsrs[3] = { first_wrapper, second_wrapper, third_wrapper };

    // threads run asynchronously in any order
    for (int i = rangedRNG(2), j = 0; j < 3; ++i, ++j) {
        pthread_create(
            threads + (i % 3), NULL, tsrs[i % 3], solution
            );
    }
    for (int i = rangedRNG(2), j = 0; j < 3; ++i, ++j) {
        pthread_join(threads[i % 3], NULL);
    }
    fooFree(solution);
    return EXIT_SUCCESS;
}
