#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "ArgManager.h"


/***************************************
 * Node Structure
 **************************************/

struct Node
{
    friend std::istream& operator>>(std::istream&, Node&);
    friend std::ostream& operator<<(std::ostream&, const Node&);

    Node(): nodeID(0), cateID (0), longitude(0.0), latitude(0.0) { }

    int nodeID;
    int cateID;
    double longitude;
    double latitude;
};

/***************************************
 * Map Structure
 **************************************/

struct Edge
{
    friend std::istream& operator>>(std::istream&, Edge&);
    friend std::ostream& operator<<(std::ostream&, const Edge&);

    Edge(): edgeID(0), startNodeID(0), endNodeID(0), length(0.0) { }

    int edgeID;
    int startNodeID;
    int endNodeID;
    double length;
};

/***************************************
 * Class: DataLoader
 **************************************/

typedef pair<int, double> node_dis;
typedef vector<node_dis> adj_node;

class DataLoader
{
    public:
        DataLoader() {};

        static int numNodes;
        static int numEdges;
        static vector<Node> nodes;
        static vector<Edge> edges;
        static map<int, adj_node> adj_matrix;

        

        static bool test;

        void load();
        void constructing();

    protected:

    private:
        void readNodes();
        void readEdges();
};


#endif // MAPLOADER_H