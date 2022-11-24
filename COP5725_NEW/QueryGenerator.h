#ifndef QueryGen_H
#define QueryGen_H

#include "MapLoader.h"

struct Query
{
    Query(int QID, int SID, int DIS, int topk, vector<int> cate):
        queryID(QID), sourceID(SID), destinationID(DIS),
        k(topk), cate_sequence(cate)
        { }

    int queryID;
    int sourceID;
    int destinationID;
    int k;
    vector<int> cate_sequence;
};

/***************************************
 * Class: QueryGenerator
 **************************************/

class QueryGenerator
{
    public:
        QueryGenerator():
            topk(ArgumentManager::k),
            totalCate(ArgumentManager::totalCate),
            numQueries(ArgumentManager::numQueries),
            numCate(ArgumentManager::numCate),
            numNodes(DataLoader::numNodes)
            { };

        static vector<Query> query_set;

        void generating();
    protected:

    private:
        int topk;
        int totalCate;
        int numQueries;
        int numCate;
        int numNodes;

        void delete_query();
};

#endif // QueryGen_H