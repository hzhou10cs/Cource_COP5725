#include "Prune.h"

void PruneKOSR::main()
{
    RouteTable CT;
    current_k = 0;
    for (int q_order = 1; q_order < ArgumentManager::numQueries; q_order ++)
    {
        // resolve the query
        Query query = QueryGenerator::query_set.at(q_order);
        Node s_node = DataLoader::nodes.at(query.sourceID);
        Node t_node = DataLoader::nodes.at(query.destinationID);
        vector<int> cate_seq = query.cate_sequence;

        // initialize the route table
        CT.table_init(s_node.nodeID);
        cout << "the size of the table is" << CT.table.size() << endl; 

        // In to the main function
        while (current_k<ArgumentManager::k)
        {
            // *** take out the route ***
            auto table_iter = CT.table.rbegin();
            // iter->front().route_len += 50;
            Route *exam_route = &table_iter->front();
            // vector<Route> v_route = CT.table.back();

            // *** examine the route ***
                // ** take out the final and last second node **
                Node vq = DataLoader::nodes.at(exam_route->node_sequence.back());
                Node vl = DataLoader::nodes.at(exam_route->node_sequence.rbegin()[1]);
                // ** if dominating **

                // add to the dominating hash table

                // extend the route from the final node

                // else if dominated

                // add to the dominated hash table

            // do replace with the second node

            // add the replaced route to the table

            // delete the route

            // sort the route

            // jump out if the k reaches the targetss
            // cout << "table is" << CT.table.size() << endl;
            current_k ++ ;
            // cout <<" length of first one" << v_route.at(0).route_len << endl;
        }


    }
    

}

void RouteTable::table_init(int start_id)
{
    table.clear();
    // insert the first route
    Route init_route;
    init_route.node_sequence.push_back(start_id);
    vector<Route> init_route_vec;
    init_route_vec.push_back(init_route);
    table.push_back(init_route_vec);

    // insert the second route
    Route second_route = init_route;
    int second_id = FNN (start_id);
    second_route.node_sequence.push_back(second_id);
    vector<Route> second_route_vec;
    second_route_vec.push_back(second_route);
    table.push_back(second_route_vec);
}

int RouteTable::FNN(int source_id)
{
    return 5;
}
