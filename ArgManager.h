#ifndef ARGMANAGERH
#define ARGMANAGER_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include <vector>
#include <map>
#include <set>
#include <list>

using namespace std;
typedef unsigned int uint;

/***************************************
 * Argument manager
 **************************************/

struct ArgumentManager
{
    ArgumentManager() { };

    /// input arguments
    static uint k; // .............. top-k optimal solution
    static uint totalCate; // ...... total number of categories
    static uint numQueries; // ..... number of queries
    static uint numCate; // ........ number of categories each query
    static string algo; // ......... which version of algorithm to be used

    /// mathematic parameter
    static double EPS;
    static double INF;

    /// for read arguments
    static void readArguments(int argc, char* argv[]);
    static void printArguments();

    /// for output files
    static string resultDirectory;
    static void outputExperiment();
};

#endif // ARGMANAGER_H