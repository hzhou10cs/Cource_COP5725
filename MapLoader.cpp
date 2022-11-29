#include "MapLoader.h"

int DataLoader::numNodes = 0;
int DataLoader::numEdges = 0;
int DataLoader::numMaps = 0;

vector<Node> DataLoader::nodes;
vector<Edge> DataLoader::edges;
vector<Map> DataLoader::maps;

map<int, adj_node> DataLoader::adj_matrix;

vector<int> DataLoader::good_nodes;
vector<int> DataLoader::good_cates;

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
 * Reading Edge stream
 ***************************************/

std::istream&
operator>>(std::istream& in, Map& e)
{
    in >> e.startNodeID >> e.endNodeID >> e.length >> e.numPoints;
    // check that the inputs succeeded
    if (!in)
        e = Map();
    e.points.resize(e.numPoints);
    for(int i=0; i<e.numPoints; i++)
    {
        e.points.push_back(Point());
        in >> e.points.at(i).categoryID >> e.points.at(i).dis;
        // check that the inputs succeeded
        if (!in)
            e = Map();
    }
    return in;
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

    if(ArgumentManager::test)// test only -->
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
    else
        // readCates();
        {}

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
    cout << numEdges << " Edges has been loaded ... ..." << endl;
}

/***************************************
 * Dataloader Read Map
 ***************************************/

void DataLoader::readCates()
{
    string filename = "data/calmap.txt";
    ifstream mapfile(filename);
    if(mapfile.is_open())
    {
        while(mapfile.good())
        {
            Map map;
            mapfile >> map;
            maps.push_back(map);
            numMaps++;
            if (map.points.size()!=0)
            {
                if (map.points.at(0).categoryID!=ArgumentManager::INF)
                    nodes.at(map.startNodeID).cateID = map.points.at(0).categoryID;
            }

        }
        mapfile.close();
    }
    else
    {
        cout << "cal.edge is not open" << endl;
    }
    numMaps--;
    cout << numMaps << " Edges has been loaded ... ..." << endl;


    vector<int> good_start;
    vector<int> good_end;
    vector<int> reachable_node;
    for (int i=0; i<DataLoader::numEdges; i++)
    {
        good_start.push_back(edges.at(i).startNodeID);
        good_end.push_back(edges.at(i).endNodeID);
    }
    sort(good_start.begin(), good_start.end());
    sort(good_end.begin(), good_end.end());
    set_intersection(good_start.begin(), good_start.end(),
                    good_end.begin(), good_end.end(),
                    back_inserter(reachable_node));
    
    int cate_counter[ArgumentManager::totalCate] = {};
    for (int i=0; i<reachable_node.size(); i++)
    {   
        if (nodes.at(reachable_node.at(i)).cateID != ArgumentManager::INF)
            cate_counter [nodes.at(reachable_node.at(i)).cateID ] += 1;
        //     cout<<nodes.at(i).cateID << endl;
    }
    // filter out the category #>=6 to avoid cycle search
    for (int i =0; i<ArgumentManager::totalCate; i++)
    {
        if (cate_counter[i]>=6)
            good_cates.push_back(i);       
    }
    // select out the nodes with the filtered category to avoid ultimate search
    for (int i=0; i<reachable_node.size(); i++)
    {
        if (count(good_cates.begin(), good_cates.end(),nodes.at(reachable_node.at(i)).cateID))
            good_nodes.push_back(i);
    }
    // for (int i=0; i<good_cates.size(); i++)
    //     cout << "i: " << i << " -- "<<good_cates.at(i) << endl;
    cout <<"total good cate: " << good_cates.size() << endl; 
    cout <<"num of good nodes" << good_nodes.size() << endl;
        
}

/***************************************
 * Dataloader Generating Related matrix
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