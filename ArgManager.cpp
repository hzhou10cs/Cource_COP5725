#include "ArgManager.h"

uint ArgumentManager::k = 2;
uint ArgumentManager::totalCate = 3;
uint ArgumentManager::numQueries = 1;
uint ArgumentManager::numCate = 3;
string ArgumentManager::algo = "prune";

double ArgumentManager::EPS = 1e-10;
double ArgumentManager::INF = 1.7e30;

bool ArgumentManager::verbose = 1;

string ArgumentManager::resultDirectory = "result/";

void ArgumentManager::readArguments(int argc, char* argv[])
{
    for(int iArg=1; iArg+1<argc; iArg+=2)
    {
        string argName = string(argv[iArg]);
        istringstream argstream(argv[iArg+1]);
        if (argName == "-k")
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
        else
        {
            cout << "unrecognized argument : " << argName << endl;
            exit(EXIT_SUCCESS);
        }
    }
}

void ArgumentManager::printArguments()
{
    cout << "-------------Printing arguments----------" << endl;
    cout << "k : " << k << endl;
    cout << "numQueries : " << numQueries << endl;
    cout << "algorithm: " << algo << endl;
}

void ArgumentManager::outputExperiment()
{

}