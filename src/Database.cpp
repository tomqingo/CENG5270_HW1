# include <fstream>
# include <sstream>
# include "Database.h"

using namespace std;

void Database::readNodes(string fileName)
{
    ifstream fin(fileName);
    string line;
    while(getline(fin, line)){
        istringstream iss(line);
        string nodeName;
        string weightStr;
        int weight;
        getline(iss, nodeName, ' ');
        getline(iss, weightStr);
        weight = std::stoi(weightStr);
        nodeName2Id[nodeName] = nodes.size();
        nodes.emplace_back(nodes.size(), nodeName, weight);
    }
}

void Database::readNets(string fileName)
{
    ifstream fin(fileName);
    string line;
    while(getline(fin, line)){
        istringstream iss(line);
        string netsign, netName;
        iss >> netsign;
        // add Nodes
        string pinName;
        if(netsign.find("NET") != netsign.npos)
        {
            iss >> netName;
            nets.emplace_back(nets.size(), netName, 1);
        }
        else
        {
            if (netsign.find("c") != netsign.npos)
            {
                pinName = netsign;
                int nodeid = nodeName2Id[pinName];
                nets.back().addNodes(nodeid);
                nodes[nodeid].addConnectedNets(nets.size() - 1);
            }
        }

        while(getline(iss, pinName, ' '))
        {
            if(pinName.find("c") != pinName.npos)
            {
                int nodeid = nodeName2Id[pinName];
                nets.back().addNodes(nodeid);
                nodes[nodeid].addConnectedNets(nets.size() - 1); 
            }
        }

    }
}

void Database::readBm(string nodefileName, string netfileName)
{
    std::cout<<"===== Read the Netlist ====="<<std::endl;
    std::cout<<"Read the node file"<<std::endl;
    readNodes(nodefileName);
    std::cout<<"Read the net file"<<std::endl;
    readNets(netfileName);
    std::cout<<"#Nodes: "<<nodes.size()<<" #Nets: "<<nets.size()<<std::endl;
}