#ifndef PRUNE_H
#define PRUNE_H

#include "QueryGenerator.h"

/***************************************
 * Route structure
 **************************************/

struct Route
{
    Route():
        route_len(1), cost(0.0), p_cost(0.0), rec(0)
        { }

    Route(int len, vector<int> node_seq):
        route_len(len), route(node_seq)
        { }

    Route(int len, vector<int> node_seq, double cost):
        route_len(len), route(node_seq), cost(cost) 
        { }

    Route(int len, vector<int> node_seq, double cost, bool rec):
        route_len(len), route(node_seq), cost(cost), rec(rec)
        { }

    int route_len;
    vector<int> route;
    double cost;
    double p_cost;
    bool rec;
};

/***************************************
 * Route table class
 **************************************/

class RouteTable
{
    public:
        RouteTable() {};
        // list<vector<Route>> table;
        vector<Route> current_step;
        vector<Route> next_step;
        int step_counter;
        vector<Route> result_set; 

        int table_init(int start_ID, int first_cate);
        int FNN(int source_ID, int kth);
        Route extend_route(Route exam_route, int vq_ID, int neighbor_ID, double cost);
        Route replace_route(Route exam_route, int vl_ID, int neighbor_ID, double cost);

        void print_last_step(bool print);
        void print_route(Route route_to_print, bool print);
        void print_result_set(bool print);
        void print_hash_table(vector<Route> route_table);
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
        Route extract_min(vector<Route> *route_table, int rec_len);
        

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