#include "MapLoader.h"

int DataLoader::numNodes = 0;
int DataLoader::numEdges = 0;
vector<Node> DataLoader::nodes;
vector<Edge> DataLoader::edges;
map<int, adj_node> DataLoader::adj_matrix;

/***************************************
 * Reading Node stream
 ***************************************/

istream& operator>>(istream& in, Node& n)
{
    in >> n.nodeID >> n.longitude >> n.latitude;
    if (!in) n = Node();
    return in;
}

ostream& operator<<(ostream& out, const Node& n)
{
    out << n.nodeID << " " << n.longitude << " "
        << n.latitude << endl;
    return out;
}

/***************************************
 * Reading Edge stream
 ***************************************/

istream& operator>>(istream& in, Edge& e)
{
    in >> e.edgeID >> e.startNodeID >> e.endNodeID >> e.length;
    if (!in) e = Edge();
    return in;
}

ostream& operator<<(ostream& out, const Edge& e)
{
    out << e.edgeID << " " << e.startNodeID << " " << e.endNodeID << " "
        << e.length << endl;
    return out;
}

/***************************************
 * Dataloader Scheduler
 ***************************************/

void DataLoader::load()
{
    cout << endl;
    cout << "-------------Loading Road Map------------" << endl;

    srand(150);
    readNodes();
    readEdges();

    // test only -->
    if(ArgumentManager::test)
    {
        nodes.at(0).cateID = 0;
        nodes.at(1).cateID = 1;
        nodes.at(2).cateID = 2;
        nodes.at(3).cateID = 1;
        nodes.at(4).cateID = 3;
        nodes.at(5).cateID = 2;
        nodes.at(6).cateID = 3;
        nodes.at(7).cateID = 4;
    }

}

/***************************************
 * Dataloader Read Nodes
 ***************************************/

void DataLoader::readNodes()
{
    string filename;
    if(ArgumentManager::test)
        filename = "data/test.cnode";
    else
        filename = "data/cal.cnode";
    ifstream nodefile(filename);
    if(nodefile.is_open())
    {
        while(nodefile.good())
        {
            Node node;
            nodefile >> node;
            node.cateID = rand()%ArgumentManager::totalCate;
            nodes.push_back(node);
            numNodes++;
        }
        nodefile.close();
    }
    else
    {
        cout << "cal.cnode is not open" << endl;
    }
    // numNodes--;
    cout << numNodes << " vertex has been loaded ... ..." << endl;
}

/***************************************
 * Dataloader Read Edge
 ***************************************/

void DataLoader::readEdges()
{
    string filename;
    if(ArgumentManager::test)
        filename = "data/test.cedge";
    else
        filename = "data/cal.cedge";
    ifstream edgefile(filename);
    if(edgefile.is_open())
    {
        while(edgefile.good())
        {
            Edge edge;
            edgefile >> edge;
            edges.push_back(edge);
            numEdges++;
        }
        edgefile.close();
        
    }
    else
    {
        cout << "cal.edge is not open" << endl;
    }
    numEdges--;
    
    int total_edges = numEdges;
    if (ArgumentManager::direct==0)
    {
        for (int e = 0; e<total_edges; e++)
        {
            Edge reversed_edge;
            reversed_edge.edgeID = edges.at(e).edgeID +total_edges;
            reversed_edge.startNodeID = edges.at(e).endNodeID;
            reversed_edge.endNodeID = edges.at(e).startNodeID;
            reversed_edge.length= edges.at(e).length;
            edges.push_back(reversed_edge);
            numEdges++;
        }
    }
    
    cout << numEdges << " Edges has been loaded ... ..." << endl;
}

/***************************************
 * Dataloader Read Edge
 ***************************************/

void DataLoader::constructing()
{
    int startID;
    node_dis nd_pair;
    for (int i=0; i<numEdges; i++)
    {
        startID = edges.at(i).startNodeID;
        nd_pair.first = edges.at(i).endNodeID;
        nd_pair.second = edges.at(i).length;
        adj_matrix[startID].push_back(nd_pair);
    }
    if (ArgumentManager::direct==0)
    {
        for (int i=0; i<numEdges; i++)
        {
            startID = edges.at(i).endNodeID;
            nd_pair.first = edges.at(i).startNodeID;
            nd_pair.second = edges.at(i).length;
            adj_matrix[startID].push_back(nd_pair);
        }
    }
}