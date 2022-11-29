#include "DJKSearch.h"

NodeIDC DJKSearch::dijkstra(int s, int TID, int kth, int t)
{
    // map<int, FCNode> open_node;
    // map<int, FCNode> close_node;
    // map<int, FCNode> target_node;
    map<int, float> open_node;
    map<int, float> close_node;
    map<int, float> target_node;
    adj_node near_nodes_set;

    int target_cate_num = 0;

    int closeprint = 0;
    int time_counter = 0;
    // Generate open node table
    for (int i=0; i<DataLoader::numNodes; i++)
    {   
        // FCNode init_node;
        // open_node[i] = init_node;
        open_node[i] = ArgumentManager::INF;

    }

    // Initial the source node
    int exam_nodeID = s;
    // FCNode exam_node(s, 0);
    // open_node[s] = exam_node;
    open_node[s] = 0;

    // while loop for main algorithm
    while (open_node.size()!=0)
    {   
        // get the iterator of the node with minimum cost in open node set
        // auto pr = min_element
        // (
        //     open_node.begin(), open_node.end(),
        //     [] (const pair<int, FCNode>& p1, const pair<int, FCNode> & p2) {
        //         return p1.second.cost < p2.second.cost;
        //     }
        // );
        auto pr = min_element
        (
            open_node.begin(), open_node.end(),
            [] (const pair<int, float>& p1, const pair<int, float> & p2) {
                return p1.second < p2.second;
            }
        );

        // assign the iterator address to the exame node
        exam_nodeID = pr->first;
        // exam_node = pr->second;
        float cost = pr->second;

        // move it from open to close node
        open_node.erase(exam_nodeID);
        // close_node.insert({exam_nodeID, exam_node});
        close_node.insert({exam_nodeID, cost});
  
        if (ArgumentManager::verbose_dijk)
        {
            cout << endl <<  "--------- open node table (" << open_node.size() << ") ----------" << endl;
            for (auto open_it = open_node.begin(); open_it!= open_node.end(); open_it++)
            {
                // cout << "[ " << open_it->first << ", {f: " << open_it->second.father << ", c; " << open_it->second.cost << "} ] "; 
                cout << "[ " << open_it->first << ", c; " << open_it->second<< " ] "; 
            }

            cout << endl <<  "--------- close node table (" << close_node.size() << ") ----------" << endl;
            for (auto close_it = close_node.begin(); close_it!= close_node.end(); close_it++)
            {
                // cout << "[ " << close_it->first << ", {f: " << close_it->second.father << ", c; " << close_it->second.cost << "} ] "; 
                cout << "[ " << close_it->first << ", c; " << close_it->second<< " ] "; 
            }
        }

        // count the accessed nodes with target category
        // if (DataLoader::nodes.at(exam_nodeID).cateID == TID && exam_node.cost!=ArgumentManager::INF)
        if (DataLoader::nodes.at(exam_nodeID).cateID == TID && cost!=ArgumentManager::INF)
        {
            target_cate_num ++;
            // target_node[exam_nodeID] = exam_node;
            target_node[exam_nodeID] = cost;

            if (ArgumentManager::verbose_dijk)
            {
                cout << endl<< "after "<< time_counter << " iteration, already found: " << target_cate_num << " points with target categories" << endl;
                cout <<  "--------- target node table (" << target_node.size() << ") ----------" << endl;
                for (auto target_it = target_node.begin(); target_it!= target_node.end(); target_it++)
                {
                    // cout << "[ " << target_it->first << ", f: " << target_it->second.father << ", c; " << target_it->second.cost << "] "; 
                    cout << "[ " << target_it->first << ", c; " << target_it->second<< " ] "; 
                }
            }

            if (exam_nodeID == t || target_cate_num == kth)
                // cout << "break here " << exam_nodeID << ","<< t << ","<< kth <<endl;
                break;
        }

        // extract the adjacent nodes from map (type: vector<node_dis> adj_node)
        near_nodes_set = DataLoader::adj_matrix[exam_nodeID];
        int num_near_nodes = near_nodes_set.size();

        if (ArgumentManager::verbose_dijk)
        {
            cout << "node " << exam_nodeID << " has " << num_near_nodes << " neighbors" << endl;
            for (auto neighbor_it = near_nodes_set.begin(); neighbor_it!= near_nodes_set.end(); neighbor_it++)
                cout << "[ ID: " << neighbor_it->first << ", DIS: " << neighbor_it->second << " ] "; 
            cout << endl << endl;
        }

        if (num_near_nodes == 0)
        {
            if (ArgumentManager::verbose_dijk)
                cout << "for node "<< exam_nodeID << ", it has no near nodes" << endl;
            continue; // no adjacent nodes, examine the next smalled cost node
        }
            
        for (int n = 0; n<num_near_nodes; n++)
        {
            node_dis near_node = near_nodes_set.at(n);
            int near_nodeID = near_node.first;
            // check whether the adjacent node is in the open set
            if (open_node.count(near_nodeID))
            {
                // double cost_eton = exam_node.cost + near_node.second;
                float cost_eton = cost + near_node.second;
                // if found a smaller cost, replace the father and cost
                // if (cost_eton < open_node[near_nodeID].cost)
                // {
                //     open_node[near_nodeID].cost = cost_eton;
                //     open_node[near_nodeID].father = exam_nodeID;
                // }
                if (cost_eton < open_node[near_nodeID])
                {
                    open_node[near_nodeID]= cost_eton;
                }
            }
        }
        time_counter ++;
    }

    if (kth != ArgumentManager::INF)
    {
        // auto kth_it = max_element
        // (
        //     target_node.begin(), target_node.end(),
        //     [] (const pair<int, FCNode>& p1, const pair<int, FCNode> & p2) {
        //         return p1.second.cost < p2.second.cost;
        //     }
        // );
        // return FCNodeID {kth_it->first, kth_it->second};
        auto kth_it = max_element
        (
            target_node.begin(), target_node.end(),
            [] (const pair<int, float>& p1, const pair<int, float> & p2) {
                return p1.second < p2.second;
            }
        );
        return NodeIDC {kth_it->first, kth_it->second};
    }
    else
    {
        return {t, target_node[t]};
    }
        
}