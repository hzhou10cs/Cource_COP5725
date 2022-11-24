#include "QueryGenerator.h"

/***************************************
 * Generator main
 ***************************************/

vector<Query> QueryGenerator::query_set;

void QueryGenerator::generating()
{
    cout << endl;
    cout << "-------------Generating queries------------" << endl;

    for (int i=0; i<numQueries; i++)
        {
            int source_ID = rand()%numNodes;
            int destination_ID = rand()%numNodes;

            vector<int> category_set;
            for (int i=0; i<numCate; i++)
                { category_set.push_back(rand()%totalCate);}

            Query Query(i, source_ID, destination_ID, topk, category_set);
            query_set.push_back(Query);

            // cout << query_set.at(i).queryID << ": "  
            //     << query_set.at(i).sourceID << " "
            //     << query_set.at(i).destinationID << " C: <" ;
            //     for (int j=0; j<numCate; j++)
            //         cout << query_set.at(i).cate_sequence.at(j) << ' ';
            // cout << "> " << topk << endl;
        }

    cout << "Generated " << totalCate << " random queries ... ..." << endl;
}

/***************************************
 * Dataloader Read Nodes
 ***************************************/