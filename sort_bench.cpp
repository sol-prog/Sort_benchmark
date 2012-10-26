#include <iostream>
#include <vector>
#include <random>
#include <boost/chrono.hpp>
#include <algorithm>
#include <ctime>
#include <cstdlib>

// g++-4.7.2 -O3 -std=c++11 sort_bench.cpp -lboost_chrono -lboost_system -o gcc_test
// clang++ -O3 -std=c++11 -stdlib=libc++ sort_bench.cpp -lboost_chrono -lboost_system -o clang_test

//Fill a vector with random numbers in the range [lower, upper]
void rnd_fill(std::vector<double> &V, const double &lower, const double &upper, const unsigned int &seed) {

    //use the default random engine and an uniform distribution
    std::default_random_engine eng(seed);
    std::uniform_real_distribution<double> distr(lower, upper);

    for( auto &elem : V){
        elem = distr(eng);
    }
}

//Use std::sort
double test_sort(std::vector<double> &V) {    
    auto start = boost::chrono::steady_clock::now();
    std::sort(std::begin(V), std::end(V));
    auto end = boost::chrono::steady_clock::now();

    auto diff = end - start;
    
    return boost::chrono::duration <double, boost::milli> (diff).count();
}

//Use std::stable_sort
double test_stable_sort(std::vector<double> &V) {    
    auto start = boost::chrono::steady_clock::now();
    std::stable_sort(std::begin(V), std::end(V));
    auto end = boost::chrono::steady_clock::now();

    auto diff = end - start;
    
    return boost::chrono::duration <double, boost::milli> (diff).count();
}

//Function that compares two elements
int comp(const void *a, const void *b) {
    double aux = *(double*)a - *(double*)b;
    if(aux < 0) {
        return -1;
    } 
    else if(aux > 0) {
        return 1;
    }
    return 0;
}

//Use std::qsort
double test_qsort(std::vector<double> &V) {    
    auto start = boost::chrono::steady_clock::now();
    std::qsort(&V[0], V.size(), sizeof(double), comp);
    auto end = boost::chrono::steady_clock::now();

    auto diff = end - start;
    
    return boost::chrono::duration <double, boost::milli> (diff).count();
}

#define TEST test_qsort

int main() {
    std::vector<double> V;

    //use the system time to create a random seed
    unsigned int seed = (unsigned int) time(nullptr);

    size_t step = 10;
    size_t nr_elem_max = 1000000;

    for(size_t i = 2; i <= nr_elem_max; i = 2 * step, step *= 1.1) {
        //Ensure that V can store N elements
        V.resize(i);
        //Fill V with random numbers in the range [0,1]:
        rnd_fill(V, 0.0, 1.0, seed);

        // Store a random value for the last test
        double unique_rand_value = V[0];

        // Time std::sort for an unsorted, random vector
        double tt_0 = TEST(V);
        
        // Time std::sort for a sorted (increasing), random vector
        double tt_1 = TEST(V);

        // Time std::sort for a sorted (decreasing), random vector
        std::reverse(std::begin(V), std::end(V));
        double tt_2 = TEST(V);

        // Time std::sort for a vector filled with a unique random value
        std::fill(std::begin(V), std::end(V), unique_rand_value);
        double tt_3 = TEST(V);

        // Print the result
        std::cout << i << "\t" << tt_0 << "\t" << tt_1 << "\t" << tt_2 << "\t" << tt_3 << std::endl;
    }

    return 0;
}
