#include "QueryGenerator.h"

/***************************************
 * Generator main
 ***************************************/

vector<Query> QueryGenerator::query_set;

void QueryGenerator::generating()
{
    cout << endl;
    cout << "-------------Generating queries------------" << endl;
    

    if(ArgumentManager::test)
    {
        cout << "Testing the query (s, t, <MA, RE, CI>, 2)" << endl;
        query_set.clear();
        Query test_query(0, 0, 7, 2, {1,2,3});
        query_set.push_back(test_query);
    }
    else
    {
        cout << "Generated " << numQueries << " random queries ... ..." << endl;
        srand(50);
        vector<int> goodnodeID;
        for (int e=0; e<DataLoader::numEdges; e++)
        {
            goodnodeID.push_back(DataLoader::edges.at(e).startNodeID);

        }
        vector<int>::iterator ip;
        ip = std::unique(goodnodeID.begin(), goodnodeID.end());
        goodnodeID.resize(distance(goodnodeID.begin(), ip));
        cout << "good node ID size" << goodnodeID.size() << endl;
        for (int i=0; i<numQueries; i++)
        {
            int source_ID_index = rand()%goodnodeID.size();
            int source_ID = goodnodeID.at(source_ID_index);
            int destination_ID = rand()%DataLoader::numNodes;

            vector<int> category_set;
            for (int i=0; i<numCate; i++)
                { category_set.push_back(rand()%totalCate);}

            Query query(i, source_ID, destination_ID, topk, category_set);
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

/***************************************
 * Dataloader Read Nodes
 ***************************************/
