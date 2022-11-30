#include "QueryGenerator.h"

/***************************************
 * Generator main
 ***************************************/

vector<Query> QueryGenerator::query_set;

void QueryGenerator::generating()
{
    cout << endl;
    cout << "-------------Generating queries------------" << endl;
    

    if(ArgumentManager::mapdata=="test")
    {
        cout << "Testing the query (s, t, <MA, RE, CI>, 2)" << endl;
        query_set.clear();
        Query test_query(0, 0, 7, 2, {1,2,3});
        query_set.push_back(test_query);
    }
    else
    {
        cout << "Generated " << numQueries << " random queries ... ..." << endl;
        srand(ArgumentManager::randseed);
        for (int i=0; i<numQueries; i++)
        {
            int source_ID = rand()%numNodes;
            int destin_ID = min(source_ID +rand()%1000,numNodes-1);

            vector<int> category_set;
            for (int i=0; i<numCate; i++)
            { 
                int cate_index = rand()%totalCate;
                category_set.push_back(cate_index);
            }

            Query query(i, source_ID, destin_ID, topk, category_set);
            query_set.push_back(query);

            cout << query_set.at(i).queryID << ": ["  
                << query_set.at(i).sourceID << ", " 
                << query_set.at(i).destinationID << ", <" ;
                for (int j=0; j<numCate; j++)
                    cout << query_set.at(i).cate_sequence.at(j) << ' ';
            cout << "> ," << topk << "]"<< endl;
        }
    }
}
