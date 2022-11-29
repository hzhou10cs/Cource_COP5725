#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "ArgManager.h"

/***************************************
 * Point Structure
 **************************************/

struct Point
{
    friend std::istream& operator>>(std::istream&, Point&);
    friend std::ostream& operator<<(std::ostream&, const Point&);

    Point():categoryID(0), dis(0.0) { };

    int categoryID;
    double dis;
};

/***************************************
 * Node Structure
 **************************************/

struct Node
{
    friend std::istream& operator>>(std::istream&, Node&);
    friend std::ostream& operator<<(std::ostream&, const Node&);

    Node(): nodeID(0), cateID (ArgumentManager::INF), longitude(0.0), latitude(0.0) { }

    int nodeID;
    int cateID;
    double longitude;
    double latitude;
};

/***************************************
 * Edge Structure
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
 * Map Structure
 **************************************/

struct Map
{
    friend std::istream& operator>>(std::istream&, Map&);
    friend std::ostream& operator<<(std::ostream&, const Map&);

    Map(): edgeID(0), startNodeID(0), endNodeID(0), numPoints(0), length(0.0) { }

    int edgeID;
    int startNodeID;
    int endNodeID;
    int numPoints;
    double length;
    vector<Point> points;

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
        static int numMaps;
        
        static vector<Node> nodes;
        static vector<Edge> edges;
        static vector<Map> maps;

        static map<int, adj_node> adj_matrix;

        static vector<int> good_nodes;
        static vector<int> good_cates;
        
        void load();
        void constructing();

    protected:

    private:
        void readNodes();
        void readEdges();
        void readCates();
};


#endif // MAPLOADER_H