#include "DJKSearch.h"

FCNodeID DJKSearch::dijkstra(int s, int TID, int kth, int t)
{
    map<int, FCNode> open_node;
    map<int, FCNode> close_node;
    map<int, FCNode> target_node;
    adj_node near_nodes_set;

    int target_cate_num = 0;
    // Generate open node table
    for (int i=0; i<DataLoader::numNodes; i++)
    {   
        FCNode init_node;
        open_node[i] = init_node;
    }
    // Initial the source node
    int exam_nodeID = s;
    FCNode exam_node(s, 0);
    open_node[s] = exam_node;
    
    // while loop for main algorithm
    while (open_node.size()!=0)
    {   
        // get the iterator of the node with minimum cost in open node set
        auto pr = min_element
        (
            open_node.begin(), open_node.end(),
            [] (const pair<int, FCNode>& p1, const pair<int, FCNode> & p2) {
                return p1.second.cost < p2.second.cost;
            }
        );
        // assign the iterator address to the exame node
        exam_nodeID = pr->first;
        exam_node = pr->second;

        // cout << "the min node ID: " << exam_nodeID << ", its cost to source node: " << exam_node.cost <<endl; 
        // move it from open to close node
        open_node.erase(exam_nodeID);
        close_node.insert({exam_nodeID, exam_node});

        // cout << endl <<  "--------- open node table (" << open_node.size() << ") ----------" << endl;
        // for (auto open_it = open_node.begin(); open_it!= open_node.end(); open_it++)
        // {
        //     cout << "[ " << open_it->first << ", {f: " << open_it->second.father << ", c; " << open_it->second.cost << "} ] "; 
        // }

        // cout << endl <<  "--------- close node table (" << close_node.size() << ") ----------" << endl;
        // for (auto close_it = close_node.begin(); close_it!= close_node.end(); close_it++)
        // {
        //     cout << "[ " << close_it->first << ", {f: " << close_it->second.father << ", c; " << close_it->second.cost << "} ] "; 
        // }

        // count the accessed nodes with target category


        if (DataLoader::nodes.at(exam_nodeID).cateID == TID)
        {
            target_cate_num ++;
            target_node[exam_nodeID] = exam_node;
            if (exam_nodeID == t || target_cate_num == kth)
                break;
        }

        // cout << endl << "already found: " << target_cate_num << " points with target categories" << endl;
        // cout <<  "--------- target node table (" << target_node.size() << ") ----------" << endl;
        // for (auto target_it = target_node.begin(); target_it!= target_node.end(); target_it++)
        // {
        //     cout << "[ " << target_it->first << ", f: " << target_it->second.father << ", c; " << target_it->second.cost << "] "; 
        // }

        // extract the adjacent nodes from map (type: vector<node_dis> adj_node)
        near_nodes_set = DataLoader::adj_matrix.at(exam_nodeID);
        int num_near_nodes = near_nodes_set.size();

        // cout << "node " << exam_nodeID << " has " << num_near_nodes << " neighbors" << endl;
        // for (auto neighbor_it = near_nodes_set.begin(); neighbor_it!= near_nodes_set.end(); neighbor_it++)
        // {
        //     cout << "[ ID: " << neighbor_it->first << ", DIS: " << neighbor_it->second << " ] "; 
        // }
        // cout << endl << endl;

        if (num_near_nodes == 0)
            continue; // no adjacent nodes, examine the next smalled cost node
        for (int n = 0; n<num_near_nodes; n++)
        {
            node_dis near_node = near_nodes_set.at(n);
            int near_nodeID = near_node.first;
            // check whether the adjacent node is in the open set
            if (open_node.count(near_nodeID))
            {
                double cost_eton = exam_node.cost + near_node.second;
                // if found a smaller cost, replace the father and cost
                if (cost_eton < open_node[near_nodeID].cost)
                {
                    open_node[near_nodeID].cost = cost_eton;
                    open_node[near_nodeID].father = exam_nodeID;
                }
            }
        }
    }

    if (kth != ArgumentManager::INF)
    {
        auto kth_it = max_element
        (
            target_node.begin(), target_node.end(),
            [] (const pair<int, FCNode>& p1, const pair<int, FCNode> & p2) {
                return p1.second.cost < p2.second.cost;
            }
        );
        return FCNodeID {kth_it->first, kth_it->second};
    }
    else
    {
        return {t, target_node[t]};
    }
        
}