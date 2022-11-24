#include "MapLoader.h"

int DataLoader::numNodes = 0;
int DataLoader::numEdges = 0;
vector<Node> DataLoader::nodes;
vector<Edge> DataLoader::edges;

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
}

/***************************************
 * Dataloader Read Nodes
 ***************************************/

void DataLoader::readNodes()
{
    ifstream nodefile ("data/cal.cnode");
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
    numNodes--;
    cout << numNodes << " vertex has been loaded ... ..." << endl;
}

/***************************************
 * Dataloader Read Map
 ***************************************/

void DataLoader::readEdges()
{
    ifstream edgefile ("data/cal.cedge");
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
    cout << numEdges << " Edges has been loaded ... ..." << endl;
}