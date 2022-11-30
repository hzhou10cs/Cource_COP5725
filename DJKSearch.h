#ifndef DJKSearch_H
#define DJKSearch_H

#include "Prune.h"


class DJKSearch
{
    public:
        DJKSearch() {};

        static NodeIDC dijkstra(int NodeID, int TargetID, int kth, int TargetNode);
};

#endif // DJKSearch_H