#include <iostream>
#include <set>
#include <random>
#include <cmath>
#include <vector>
#include <algorithm>

#include "BST.hpp"
#include "util.hpp"

using namespace std;

int main() {
    // This is an example of runtime benchmarking
    // TODO (final): Replace the following with a benchmarking comparison
    // of two data structures, as described in the project instructions
    BST<double> tree;
    std::set<double> rbt;

    int numTrials = 10;
    int dataSize = 10000;

    vector<long long> times(numTrials, 0);

    Timer t;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(-10.0, 10.0);
    for(int i = 0; i < 10; i++){
    // Run benchmarks and time each trial
    vector<double> insertVals(dataSize, 0);
    for (int trialIndex = 0; trialIndex < numTrials; trialIndex++) {
        // Set a new random seed
        generator.seed(1 + trialIndex);

        /* //test worst case insert BST
        t.begin_timer();
        for(int i = 0; i < dataSize; i++)
           tree.insert(i); */
        
        /* //test worst case find BST
        t.begin_timer();
        for(int i = 0; i < dataSize; i++)
            tree.find(i); */

        /* //test average insert BST
        //t.begin_timer();
        for(int i = 0; i < dataSize; i++){
            double x = distribution(generator);
            tree.insert(x);
            insertVals[i] = x;
        } 
        std::random_shuffle(insertVals.begin(), insertVals.end()); */
        

        /* //test average find BST
        t.begin_timer();
        for(int i = 0; i < dataSize; i++)
            tree.find(insertVals[i]); */

        t.begin_timer();
        for(int i = 0; i < dataSize; i++)
            rbt.insert(i);
        


        //double total = 0.0;
        //for (int dataIndex = 0; dataIndex < dataSize; dataIndex++) {
        //    double currentRandom = distribution(generator);
        //    total += currentRandom;
        //}

        times[trialIndex] = t.end_timer();
    }

    // Compute statistics from trial times
    double totalTime = 0.0;
    for (int i = 0; i < numTrials; i++) {
        totalTime += times[i];
    }
    double meanTime = totalTime / ((double) numTrials) / dataSize;

    //cout << "Elapsed time: " << totalTime << " nanoseconds ("
    //    << (totalTime / 1.0e9) << " seconds)" << endl;
    //cout << "Mean: " << meanTime << " nanoseconds per trial" << endl;
    cout << dataSize << "     " << (meanTime / 1.0e9) << endl;
    dataSize += 10000;
    }
    return 0;
}
