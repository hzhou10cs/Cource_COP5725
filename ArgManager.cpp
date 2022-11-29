#include "ArgManager.h"

uint ArgumentManager::k = 30;
uint ArgumentManager::totalCate = 136;
uint ArgumentManager::numQueries = 1;
uint ArgumentManager::numCate = 4;
string ArgumentManager::algo = "prunedij";

int ArgumentManager::INF = 2147483646;

bool ArgumentManager::verbose = 1;
bool ArgumentManager::verbose_dijk = 0;
bool ArgumentManager::test = 1;
bool ArgumentManager::direct = 0;


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
        else if(argName == "-test")
            argstream >> test;
        else
        {
            cout << "unrecognized argument : " << argName << endl;
            exit(EXIT_SUCCESS);
        }
    }
    if(test)
    {
        k = 2;
        totalCate = 5;
        numQueries = 1;
        numCate = 3;
        direct = 1;
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