# include <iostream>
# include <vector>
# include <memory>
# include <set>
# include "Database.h"

using namespace std;

class NodeCluster;
class NetCluster;
class Partitioner;
class Partition;
class Move;

class NodeCluster
{
    public:
        NodeCluster() {weight = 0; size = 0;}
        NodeCluster(Node &node)
        {
            leafnodecol.push_back(node.getName());
            weight = node.getWeight();
            size = 1;
        }

        void addNode(shared_ptr<NodeCluster> node)
        {
            nodes.push_back(node);
            for (int i = 0; i < leafnodecol.size(); i++)
            {
                leafnodecol.push_back(node->leafnodecol[i]);
            }
            weight += node->weight;
            size += node->size;
        }

        vector<shared_ptr<NodeCluster>> nodes;
        vector<shared_ptr<NetCluster>> nets;
        vector<string> leafnodecol;

        int id;
        int weight;
        int size;
        bool locked = false;

    private:
        int dbNode = -1;
};

class NetCluster
{
    public:
        NetCluster() {}

        bool isCriticalNet ();
        bool isCutNet (const vector<int> &partiitons) const;
        vector<shared_ptr<NodeCluster>> pins;
        vector<int> partitionPinCnt;
        vector<set<shared_ptr<NodeCluster>>> partitionPin;
        int weight;
        int id;
};


class Partition
{
    public:
        Partition() {nodeWeight = 0;}
        int getNodesCnt() {return nodes.size();}
        int getNodesWeight() {return nodeWeight;}
        void addNodes(shared_ptr<NodeCluster> node) 
        {  
            nodes.insert(node);
            nodeWeight += node->weight;
        }
        void deleteNodes(shared_ptr<NodeCluster> node) 
        {
            nodes.erase(node);
            nodeWeight -= node->weight;
        }
        void clearNodes()
        {
            nodes.clear();
            nodeWeight = 0;
        }
        set<shared_ptr<NodeCluster>> nodes;
        int nodeWeight;
};

class Move
{
    public:
        Move(int _gain): gain(_gain) {}
        void addCandidateNodes(shared_ptr<NodeCluster> node) {candidateNodes.insert(node);}
        void deleteCandidateNodes(shared_ptr<NodeCluster> node) {candidateNodes.erase(node);}
        int NodeSetSize() {return candidateNodes.size();}
        set<shared_ptr<NodeCluster>> candidateNodes;
        int gain;        
};

class Partitioner
{
    public:
        Partitioner(Database _database): database(_database) {}
        void coarsening();
        void initPart();
        vector<vector<int>> genClusters(vector<shared_ptr<NodeCluster>> &nodecluster);
        vector<shared_ptr<NodeCluster>> genClusters(vector<vector<int>> &clusterIds, int level);
        vector<shared_ptr<NetCluster>> genClusterNets(int level);
        void FMadjust(int level);
        void initializeGain(vector<int>& gain, shared_ptr<NodeCluster> node);
        void updateGain(vector<int>& gain, shared_ptr<NodeCluster> node, vector<Move>& move);
        bool checkAllLocked(vector<shared_ptr<NodeCluster>> nodecluster);
        bool checkBalance();
        void OutputPartitions(string filename);

        vector<vector<shared_ptr<NodeCluster>>> NodeClusterLevels;
        vector<vector<shared_ptr<NetCluster>>> NetClusterLevels;
        vector<Partition> Partitions;
        vector<vector<int>> clusterSize;
        vector<int> cellPartitions;
        Database database;
        int totalWeight;
        int CUT;
};