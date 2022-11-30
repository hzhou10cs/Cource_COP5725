#include "ArgManager.h"

uint ArgumentManager::k = 30;
uint ArgumentManager::totalCate = 63;
uint ArgumentManager::numQueries = 50;
uint ArgumentManager::numCate = 4;
string ArgumentManager::algo = "prunedij";
string ArgumentManager::mapdata = "test";

int ArgumentManager::INF = 2147483646;

bool ArgumentManager::verbose = 0;
bool ArgumentManager::verbose_dijk = 0;
bool ArgumentManager::direct = 0;
int ArgumentManager::randseed = 100;


string ArgumentManager::resultDirectory = "results/";

void ArgumentManager::readArguments(int argc, char* argv[])
{
    for(int iArg=1; iArg+1<argc; iArg+=2)
    {
        string argName = string(argv[iArg]);
        istringstream argstream(argv[iArg+1]);
        if (argName == "-map")
            argstream >> mapdata;
        else if (argName == "-k")
            argstream >> k;
        else if(argName == "-tc")
            argstream >> totalCate;
        else if(argName == "-nq")
            argstream >> numQueries;
        else if(argName == "-nc")
            argstream >> numCate;
        else if(argName == "-algo")
            argstream >> algo;
        else if(argName == "-print")
            argstream >> verbose;
        else if(argName == "-seed")
            argstream >> randseed;
        else
        {
            cout << "unrecognized argument : " << argName << endl;
            exit(EXIT_SUCCESS);
        }
    }
    if(mapdata == "test")
    {
        k = 2;
        totalCate = 5;
        numQueries = 1;
        numCate = 3;
        direct = 1;
    }
    if(mapdata == "cal")
        totalCate = 63;
    if(mapdata == "TG")
        totalCate = 81;
    if(mapdata == "OL")
        totalCate = 40;

}

void ArgumentManager::printArguments()
{
    cout << "-------------Printing arguments----------" << endl;
    cout << "map: " << mapdata << endl;
    cout << "total category" << totalCate << endl;
    cout << "top k : " << k << endl;
    cout << "total Queries : " << numQueries << endl;
    cout << "cate each query: " << numCate << endl;
    if (algo == "prunedij")
        cout << "algorithm: Prune-Dijkstra" << endl;
    else
        cout << "algorithm: Prune-FNN" << endl;
}

void ArgumentManager::outputExperiment(float time, int nquery, int nneigbor)
{
    string filename;
    filename = algo+"_"+mapdata+
                    "_k"+to_string(k)+
                    "_nq"+to_string(numQueries)+
                    "_nc"+to_string(numCate)+
                    "_seed"+to_string(randseed)+".txt";
    ofstream outfile(filename);
    if (outfile.is_open())
    {
        outfile << time << " " << nquery << " " << nneigbor << endl;
        outfile.close();
    }

}