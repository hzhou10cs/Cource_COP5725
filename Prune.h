#ifndef PRUNE_H
#define PRUNE_H

#include "QueryGenerator.h"

/***************************************
 * Route structure
 **************************************/

struct Route
{
    Route():
        route_len(1), cost(0.0), knn(1)
        { }

    Route(int key, vector<int> value):
        route_len(key), candidate(value)  
        { }

    Route(int key, vector<int> value, int sec_value):
        route_len(key), candidate(value),cost(sec_value) 
        { }

    Route(int len, vector<int> node_seq, float cost, int k):
        route_len(len), candidate(node_seq), cost(cost), knn(k)
        { }

    int route_len;
    vector<int> candidate;
    float cost;
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
        int FNN(int source_ID, int kth);
        Route extend_route(Route exam_route, int vq_ID, int neighbor_ID);
        Route replace_route(Route exam_route, int vl_ID, int neighbor_ID);

        void print_last_step();
    protected:

    private:
        
        
};

/***************************************
 * Vertex Hash Pair struct
 **************************************/

struct Hash_table
{
    Hash_table() {};

    vector<Route> dominating_table;
    vector<Route> dominated_table;
};

/***************************************
 * Vertex Hash Table class
 **************************************/

class HashPool
{
    public:
        HashPool() {};

        unordered_map<int, Hash_table> Hash_list;

        void insert_pair();
        void delete_pair();

        bool check_domination(Route exam_route, int vq_ID);
        void add_to_dominating(Route exam_route, int vq_ID);
        void add_to_dominated(Route exam_route, int vq_ID);
        Route extract_min(vector<Route> *route_table);
        

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