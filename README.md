# Course_COP5725
The code for "Finding KOSR" -- Course COP5727

We have 3 available RoadNetwork dataset:

California
City of San Joaquin County (TG) 
City of Oldenburg (OL)

The information of the map will be shown if you run the program

There argument are shwon as follow:

    static uint k; // .............. top-k optimal solution
    static uint totalCate; // ...... total number of categories
    static uint numQueries; // ..... number of queries
    static uint numCate; // ........ number of categories each query
    static string algo; // ......... which version of algorithm to be used

    // algo can be "prunedij" or "prunefnn"
    
    static string mapdata;
    static bool direct;

    /// mathematic parameter
    static int INF;

    /// for read arguments
    static void readArguments(int argc, char* argv[]);
    static void printArguments();

    /// for immediate result print
    static bool verbose; // ....... For debug
    static bool verbose_dijk;
    static int randseed; // ....... Control the query generating

You can change the following argument manually:

k, numQueris, numCate, algo, mapdata and print

Ther are 4 available input of mapdata:

-map test (tiny map in the paper)
-map cal 
-map TG
-map OL

Remember delete all files in the /obj folder the first time you run the program.

The program can be run in the following command:

make
./DATALOADER -map cal -print 0 -k 30 -nq 50 -nc $c -seed 100 -algo "prunefnn"

The output file will be saved in the current folder