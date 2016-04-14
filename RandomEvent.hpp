//=======================================================================
//File:     This is the file containing the declarations for the free functions that will handle the probabilistic functions used
//           in the model.
//
//Date:   Jan. 21, 2016
//=======================================================================


#ifndef RandomEvent
#define RandomEvent
#include<iostream>
#include <stdlib.h>
#include <random>

//std::default_random_engine generator;
//std::uniform_int_distribution<int> distribution(1,100);
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(1,100);

bool IsShipSpawned(int x)
{
    //distribution.reset();

    int r = dis(gen);
    return (r<=x);
}


// Function to randomly pick an integer number in the interval [1,n]
int GetNode(int n){
    std::uniform_int_distribution<int> distribution(0, (n - 1) );
    return distribution(gen);

}


#endif 
