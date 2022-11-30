#include "main.h"

int main(int argc, char* argv[])
{
    cout << endl;
    // read argument
    ArgumentManager argmanager;
    argmanager.readArguments(argc, argv);
    argmanager.printArguments();

    // load data
    DataLoader loader;
    loader.load();
    // construct adjacent map
    loader.constructing();

    // generate query
    QueryGenerator generator;
    generator.generating();

    // prunning KOSR algo
    PruneKOSR PK;
    PK.main();

    // output result
    argmanager.outputExperiment(PK.ave_querytime,
            PK.ave_examinedroute, PK.ave_nnqueries);

    cout << "finish, exit" << endl;
    exit(0);
}
