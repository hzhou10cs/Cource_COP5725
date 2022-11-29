#ifndef DJKSearch_H
#define DJKSearch_H

#include "Prune.h"

// struct FCNode
// {
//     FCNode(): 
//         father(ArgumentManager::INF), cost(ArgumentManager::INF) {};
//     FCNode(int FNode, double cost):
//         father(FNode), cost(cost)
//         {}

//     int father;
//     double cost;
// };

// typedef pair<int, FCNode> FCNodeID;

typedef pair<int, float>  NodeIDC;

class DJKSearch
{
    public:
        DJKSearch() {};

        // static FCNodeID dijkstra(int NodeID, int TargetID, int kth, int TargetNode);
        static NodeIDC dijkstra(int NodeID, int TargetID, int kth, int TargetNode);
};

#endif // DJKSearch_H