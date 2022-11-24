#ifndef PRUNE_H
#define PRUNE_H

#include "QueryGenerator.h"

/***************************************
 * Route structure
 **************************************/

struct Route
{
    Route():
        route_len(1), route_cost(0), knn(1)
        { }

    Route(int len, vector<int> node_seq, int cost, int k):
        route_len(len), node_sequence(node_seq), route_cost(cost), knn(k)
        { }

    int route_len;
    vector<int> node_sequence;
    int route_cost;
    int knn;
};

/***************************************
 * Route table class
 **************************************/

class RouteTable
{
    public:
        RouteTable() {};
        list<vector<Route>> table; 

        void table_init(int start_ID);

        int FNN(int source_ID);

    protected:

    private:
        
        
};

/***************************************
 * Pruning KOSR algorithm
 **************************************/

class PruneKOSR
{
    public:
        PruneKOSR() {};
        void main();
    
    protected:

    private:
        int current_k;
};

#endif // PRUNE_H