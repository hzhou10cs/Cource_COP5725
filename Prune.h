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
struct FCNode
{
    FCNode(): 
        father(ArgumentManager::INF), cost(ArgumentManager::INF) {};
    FCNode(int FNode, double cost):
        father(FNode), cost(cost)
        {}

    int father;
    double cost;
};

typedef pair<int, FCNode> FCNodeID;

class RouteTable
{
    public:
        RouteTable() {
            //initialization of global private variables for all FNN queries
            //printf("%s\n","RelaM_init");
            RelaM_init();
            //printf("%s\n","Lin_Lout_init");
            Lin_Lout_init();
            //printf("%s\n","cateVector_init");
            cateVector_init();
            //printf("%s\n","InvertedLabel_init");
            InvertedLabel_init();
        };
        list<vector<Route>> table;
        vector<Route> current_step;
        vector<Route> next_step;
        int step_counter;
        vector<Route> result_set; 

        int table_init(int start_ID, int first_cate);
        
        Route extend_route(Route exam_route, int vq_ID, int neighbor_ID, double cost);
        Route replace_route(Route exam_route, int vl_ID, int neighbor_ID, double cost);

        void print_last_step(bool print);
        void print_route(Route route_to_print, bool print);
        void print_result_set(bool print);
        void print_hash_table(vector<Route> route_table);

        // ************* FNN
        //initilize Forward and Backward Relationship Matrix
        void RelaM_init();
        //Return shortest distance between two nodes
        double Query(int startNodeID,int endNodeID);
        //comparator for priority queue
        //bool PQComparator(const pair<int,double> &a,const pair<int,double> &b);
        //pruned dijkstra algorithm forward for Lin and backward for Lout
        void prunedDijkForward(int start_NodeID);
        void prunedDijkBackward(int start_NodeID);
        //initialization of Lin and Lout in preporcessing
        void Lin_Lout_init();
        //initialization of category vector
        void cateVector_init();
        //initialization of Inverted Label
        void InvertedLabel_init();
        //return nearest xth neighbor NodeID of source node in next category 
        FCNodeID FNN(int source_ID, int next_cate_ID, int xth, int TargetNode);
        
    protected:

    private:
        //forward and backward relationship matrix
        vector<vector<int>> RelaMForward;
        vector<vector<int>> RelaMBackward;
        //vector of hash tables for Lin and Lout
        vector<map<int,double>> Lin;
        vector<map<int,double>> Lout;
        //vector of cateories that group nodes withines each category
        vector<vector<int>> cateVector;
        //inverted label
        vector<map<int,map<int,double>>> InvertedLabel;

        
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

        static int kth_track[0][0];
    
    protected:

    private:
        int current_k;
        
};

#endif // PRUNE_H