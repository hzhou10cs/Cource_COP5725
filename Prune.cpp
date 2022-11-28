#include "Prune.h"
#include "DJKSearch.h"

// int PruneKOSR::kth_track [0][0];

void PruneKOSR::main()
{
    RouteTable RT;
    HashPool HP;
    // kth_track[ArgumentManager::numCate][DataLoader::numNodes];
    map<pair<int,int>,int> kth_track_map;
    current_k = 0;
    bool verbose = ArgumentManager::verbose;
    srand(150);
    for (int q_order = 0; q_order < ArgumentManager::numQueries; q_order ++)
    {
        // resolve the query
        Query query = QueryGenerator::query_set.at(q_order);
        Node s_node = DataLoader::nodes.at(query.sourceID);
        Node t_node = DataLoader::nodes.at(query.destinationID);
        vector<int> cate_seq = query.cate_sequence;
        RT.table.clear();
        HP.Hash_list.clear();
        kth_track_map.clear();

        // initialize the route table
        int second_node_ID = RT.table_init(s_node.nodeID, cate_seq.at(0));
        kth_track_map[{s_node.nodeID, 2}] = 1;  

        // initialize the category track
        int current_cat = cate_seq.at(0);
        int next_cat = cate_seq.at(1);

        // In to the main function
        while (current_k< ArgumentManager::k)
        {
            cout << "current k" << current_k << endl;
            // *** take out the route ***
            auto table_iter = RT.table.rbegin();
            Route *exam_route_p = &table_iter->back(); // To directly change the value: iter->front().route_len += 50;
            Route exam_route(*exam_route_p);
            // cout << "exam size" << exam_route.route_len << endl;
            
            // *** prepare for the next step -- adding a new step ***
            RT.table.push_back(RT.table.back());
            auto new_table_iter = RT.table.rbegin();
            // delete the original route from the route table
            new_table_iter->pop_back();
            

            // *** examine the route ***
            // check if the route reached the target node
            if(exam_route.route_len == ArgumentManager::numCate+2)
            {
                cout << q_order << endl;
                // ** add the target route in the result list
                RT.result_set.push_back(exam_route);
                // ** reconsider the dominated route **
                for (int lenm1=1; lenm1<ArgumentManager::numCate+2;lenm1++)
                {
                    int rec_node_ID = exam_route.route.at(lenm1);
                    int rec_len = lenm1+1;
                    vector<Route> *v_doming = &HP.Hash_list[rec_node_ID].dominating_table;
                    vector<Route> *v_dominated = &HP.Hash_list[rec_node_ID].dominated_table;

                    // show the dominating and dominated table
                    // if (v_doming->size()!=0)
                    // {   
                    //     cout << "dominating table of node: " << rec_node_ID << " -- ";
                    //     vector<Route> doming_table(*v_doming);
                    //     RT.print_hash_table(doming_table);
                    // }
                    // if (v_dominated->size()!=0)
                    // {   
                    //     cout << "dominated table of node: " << rec_node_ID << " -- ";
                    //     vector<Route> dominated_table(*v_dominated);
                    //     RT.print_hash_table(dominated_table);
                    // }

                    for (int doming_order = 0; doming_order<v_doming->size(); doming_order++)
                    {   
                        if (v_doming->at(doming_order).route_len == rec_len)
                        {
                            vector<Route> doming_table(*v_doming);
                            Route print_route(v_doming->at(doming_order));

                            vector<int> wait_route = (v_doming->begin()+doming_order)->route;
                            vector<int> target_route = {exam_route.route.begin(), exam_route.route.begin()+lenm1+1};

                            if (target_route == wait_route)
                            {
                                // extract the min cost route from dominated
                                // if return cost =  INF means no dominated route
                                Route rec_route = HP.extract_min(v_dominated, rec_len);
                                // insert the reconsider root into route table
                                if (rec_route.cost != ArgumentManager::INF)
                                {
                                    rec_route.rec = 1;
                                    new_table_iter->push_back(rec_route);
                                    // erase the route in dominating
                                    v_doming->erase(v_doming->begin()+doming_order);
                                }
                            }
                        }                   
                    }
                }
                RT.print_result_set(verbose);
                current_k ++;
            }
            // havent visited all category, do extend and replace
            else
            {
                
                // ** take out the final and last second node **
                Node vq = DataLoader::nodes.at(exam_route.route.back());
                Node vl = DataLoader::nodes.at(exam_route.route.rbegin()[1]);

                // ** update the category track
                current_cat = vq.cateID;
                if (exam_route.route_len == ArgumentManager::numCate+1)
                    next_cat = t_node.cateID;
                else
                    next_cat = cate_seq.at(exam_route.route_len-1);
                // ** chekc domination **
                bool dominating = HP.check_domination(exam_route, vq.nodeID);
                // if dominating
                if (dominating)
                {   
                    // add the examined route to the dominating hash table
                    kth_track_map[{vq.nodeID, exam_route.route_len+1}] = 1;
                    // kth_track[exam_route.route_len][vq.nodeID] = 1;
                    // cout << "find a dominating route: ";
                    RT.print_route(exam_route,verbose);
                    HP.add_to_dominating(exam_route, vq.nodeID);

                    // extend the route from the final node
                    Route extended_route = exam_route;
                    // int neighborID = RT.FNN(vq.nodeID, extended_route.knn);
                    FCNodeID NN;
                    if (exam_route.route_len == ArgumentManager::numCate+1)
                        NN = DJKSearch::dijkstra(vq.nodeID, next_cat, ArgumentManager::INF, t_node.nodeID);
                    else 
                        NN = DJKSearch::dijkstra(vq.nodeID, next_cat, 1, vq.nodeID);
                    int NNID = NN.first;
                    double NNcost = NN.second.cost;
                    if (NN.second.cost == ArgumentManager::INF)
                    {
                        cout << "break here query #: "<< q_order << endl;
                        break;
                    }
                    extended_route = RT.extend_route(extended_route, vq.nodeID, NNID, NNcost);
                
                    // cout << "node to be extend is: " << NNID << endl;
                    // ** add the extended route to the route table **
                    new_table_iter->push_back(extended_route);
                }
                // else if dominated
                else
                {
                    // add the examined route to the dominated hash table
                    // cout << "find a dominated route: ";
                    RT.print_route(exam_route,verbose);
                    // cout << endl;
                    HP.add_to_dominated(exam_route, vq.nodeID);
                }
                
                // do replace with the second node if it is not reconsidered route
                if (exam_route.rec == 0)
                {
                    Route replaced_route = exam_route;
                    kth_track_map[{vl.nodeID, exam_route.route_len}] += 1;
                    int kth = kth_track_map[{vl.nodeID, exam_route.route_len}];
                    // int kth = kth_track[exam_route.route_len][vl.nodeID];
                    // cout << "in replace operation, kth is: " << kth << endl;
                    FCNodeID kthNN = DJKSearch::dijkstra(vl.nodeID, current_cat, kth, vl.nodeID);
                    // int neighborID = RT.FNN(vl.nodeID, replaced_route.knn);
                    int kthNNID = kthNN.first;
                    double kthNNcost = kthNN.second.cost;

                    if (kthNNcost == ArgumentManager::INF)
                    {
                        cout << "break here query #: "<< q_order << endl;
                        break;
                    }
                    
                    // ** add the replaced route to the route table if a new replaced node is found **
                    if (kthNNID!=vq.nodeID)
                    {
                        // cout << "node to be replaced: " << kthNNID<< endl;
                        replaced_route = RT.replace_route(replaced_route, vl.nodeID, kthNNID, kthNNcost);                 
                        new_table_iter->push_back(replaced_route);
                    }
                    else
                    {
                        // cout << "no need to be replace" << endl;
                    }
                        
                }

            }
        
            // *** sort the route by cost from large to small ***
            sort( new_table_iter->begin( ), new_table_iter->end( ), [ ]( const Route& lhs, const Route& rhs )
            {
            return lhs.cost > rhs.cost;
            });

            // (optional) print out 
            RT.print_last_step(verbose);
        }
        if (current_k == ArgumentManager::k)
            cout << "find top k route" << endl;
    }
}

bool HashPool::check_domination(Route exam_route, int vq_ID)
{
    // Case 1: the hash table of vertex VQ has never been generated
    if (Hash_list.count(vq_ID)==0 ) 
    {
        // Generate the hash table
        Hash_table hash;
        Hash_list[vq_ID] = hash;
        return true;
    }
    
    // Case 2: vertex hash exist and already contain this route_len
    vector<Route> domi_table = Hash_list[vq_ID].dominating_table;
    for (auto iter = domi_table.rbegin() ; iter != domi_table.rend(); --iter)
    {
        if (iter->route_len == exam_route.route_len)
        {
            return false;
        }
    }
    // Case 3: hash of VQ exists checked
    //         no such route_len chekced
    return true;      
}

void HashPool::add_to_dominating(Route exam_route, int vq_ID)
{
    Route hash_route(exam_route.route_len, exam_route.route, exam_route.cost);
    Hash_list[vq_ID].dominating_table.push_back(hash_route);
}

void HashPool::add_to_dominated(Route exam_route, int vq_ID)
{
    Route hash_route(exam_route.route_len, exam_route.route, exam_route.cost);
    Hash_list[vq_ID].dominated_table.push_back(hash_route);
}

Route HashPool::extract_min(vector<Route> *route_table, int target_len)
{
    Route min_route(target_len, {}, ArgumentManager::INF, 0);
    for(auto it = route_table->begin(); it != route_table->end(); ++it)
    {
        if (it->route_len == target_len && it->cost < min_route.cost)
        {
            min_route.route = it->route;
            min_route.cost = it->cost;
        }
    }
    return min_route;
}

int RouteTable::table_init(int start_id, int first_cate)
{
    cout << "start ID is " << start_id << endl;
    cout << "first category is " <<  first_cate << endl;

    table.clear();
    // insert the first route
    Route init_route;
    init_route.route.push_back(start_id);
    vector<Route> init_route_vec;
    init_route_vec.push_back(init_route);
    table.push_back(init_route_vec);

    print_last_step(ArgumentManager::verbose);

    // insert the second route
    Route second_route = init_route;
    FCNodeID NN= DJKSearch::dijkstra(start_id,first_cate,1,start_id);
    // FCNodeID second_id = FNN (start_id, 2, kth);
    int NNID = NN.first;
    double NNcost = NN.second.cost;
    // cout << "return ID: " <<  NNID <<endl <<"return cost: " << NNcost << endl;

    second_route = this->extend_route(second_route, start_id, NNID, NNcost);
    vector<Route> second_route_vec;
    second_route_vec.push_back(second_route);
    table.push_back(second_route_vec);

    print_last_step(ArgumentManager::verbose);

    return NNID;
}

int RouteTable::FNN(int source_id, int kth)
{
    return rand()%DataLoader::numNodes;
}

Route RouteTable::extend_route(Route extended_route, int vqID, int neigborID, double cost)
{
    extended_route.route.push_back(neigborID);
    extended_route.route_len ++;
    extended_route.p_cost = extended_route.cost;
    extended_route.cost += cost;
    return extended_route;
}

Route RouteTable::replace_route(Route replaced_route, int vlID, int neigborID, double cost)
{
    replaced_route.route.back()=neigborID;
    replaced_route.cost = replaced_route.p_cost + cost;
    return replaced_route;
}


void RouteTable::print_route(Route route_to_print, bool verbose)
{
    if (verbose)
    {
        cout << "  [" << route_to_print.route_len << ": <";
        vector<int> current_vector = route_to_print.route;
        for (int i = 0; i<current_vector.size(); i++)
            cout << current_vector.at(i) << ",";
        cout << "> (" << route_to_print.cost << ")]  | ";
    }
}

void RouteTable::print_last_step(bool verbose)
{
    // print out the current step
    if (verbose)
    {
        cout << "----------------------------------------" << endl;
        cout << "current step:" << table.size() << endl;
        vector<Route> current_step_v = table.back();
        for (int n_route = 0; n_route<current_step_v.size(); n_route++)
        {
            print_route(current_step_v.at(n_route), 1);
        }
        cout << endl << "*********----------------***************" << endl;
        
    }
}

void RouteTable::print_result_set(bool verbose)
{
    if (verbose)
    {
        cout << "Obatain a new result, reconsider the dominated route" << endl;
        cout << "Result set: ";
        for(auto it=result_set.begin(); it!=result_set.end(); it++)
            print_route(*it, 1);
        cout << endl;
    }

}

void RouteTable::print_hash_table(vector<Route> hashing_table)
{
    for (int m = 0; m < hashing_table.size(); m++)
        this->print_route(hashing_table.at(m), 1);
    cout << endl;
}