# include <iostream>
# include <vector>
# include <unordered_map>
# include "string.h"

using namespace std;


class Node
{
    public:
        Node(int _id, string _name, int _weight): id(_id), name(_name), weight(_weight) {}
        void addConnectedNets(int netId)
        {
            connectednets.push_back(netId);
        }

        int getId() {return id;}
        string getName() {return name;}
        int getWeight() {return weight;}
        vector<int> getConnectedNets() {return connectednets;}

    private:
        int id;
        string name;
        int weight;
        vector<int> connectednets;
};

class Net
{
    public:
        Net(int _id, string _name, int _weight): id(_id), name(_name), weight(_weight) {}
        void addNodes(int nodeId)
        {
            pins.push_back(nodeId);
        }

        int getId() {return id;}
        string getName() {return name;}
        int getWeight() {return weight;}
        vector<int> getPins() {return pins;}

    private:
        int id;
        string name;
        int weight;
        vector<int> pins;

};

class Database
{
    public:
        void readNodes(string fileName);
        void readNets(string fileName);
        void readBm(string nodefileName, string netfileName);
    
        vector<Node> nodes;
        unordered_map<string, int> nodeName2Id;
        vector<Net> nets;
};