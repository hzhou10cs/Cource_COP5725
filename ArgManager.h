#ifndef ARGMANAGERH
#define ARGMANAGER_H

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <limits>
#include <chrono>

#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>

using namespace std;
typedef unsigned int uint;
typedef pair<int, float>  NodeIDC;
#define doublemax std::numeric_limits<double>::max()

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
    
    static string mapdata;
    static bool direct;

    /// mathematic parameter
    static int INF;

    /// for read arguments
    static void readArguments(int argc, char* argv[]);
    static void printArguments();

    /// for immediate result print
    static bool verbose;
    static bool verbose_dijk;
    static int randseed;

    /// for output files
    static string resultDirectory;
    static void outputExperiment(float time, int nquery, int nneigbor);
};

#endif // ARGMANAGER_H