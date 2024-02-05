# include <iostream>
# include <fstream>
# include "Partitioner.h"
# include <ctime>
# include "utils.h"
# include <algorithm>
# include <queue>
# include <set>
using namespace std;

bool NetCluster::isCutNet(const vector<int> &partitions) const
{
    for(auto pin : pins)
        if(partitions[pins[0]->id] != partitions[pin->id])
            return true;
    return false;
}

bool NetCluster::isCriticalNet()
{
    return ((partitionPinCnt[0] <= 1) || (partitionPinCnt[1] <= 1));  
}

void Partitioner::coarsening()
{
    std::cout<<"===== FM Partitioning ====="<<std::endl;

    // Initialize the clusters
    vector<shared_ptr<NodeCluster>> nodeclusterbase;
    vector<shared_ptr<NetCluster>> netclusterbase;

    totalWeight = 0;
    for(auto &node : database.nodes)
    {
        nodeclusterbase.push_back(make_shared<NodeCluster>(node));
        nodeclusterbase.back()->id = node.getId();
        totalWeight += node.getWeight();
    }

    int calWeight = 0;
    for (auto node: nodeclusterbase)
        calWeight += node->weight;

    for (auto &net : database.nets)
    {
        netclusterbase.push_back(make_shared<NetCluster>());
        for (auto &pin : net.getPins())
        {
            netclusterbase.back()->pins.push_back(nodeclusterbase[pin]);
            nodeclusterbase[pin]->nets.push_back(netclusterbase.back());
        }
        netclusterbase.back() -> id = net.getId();
    }

    NodeClusterLevels.push_back(nodeclusterbase);
    NetClusterLevels.push_back(netclusterbase);
}

void Partitioner::initPart()
{
    // Randomly initialize the cellPartitions (half)
    // According to the weights in order to make this two part more balanced
    int posCnt = 0;
    int posWeight = 0;
    int partid;
    Partitions.resize(2);
    std::cout<<"Total Weight: "<<totalWeight<<std::endl;
    for(int i = 0; i < NodeClusterLevels.back().size(); i++)
    {
        posWeight += NodeClusterLevels.back()[i]->weight;
        partid = (posWeight > (11.0*totalWeight/20.0)) ? 0 : 1;
        cellPartitions.push_back(partid);
        Partitions[partid].addNodes(NodeClusterLevels.back()[i]);
    }
    
    for(auto netcluster : NetClusterLevels.back())
    {
        netcluster->partitionPinCnt.resize(2,0);
        netcluster->partitionPin.resize(2);
        for (auto nodecluster : netcluster->pins)
        {
            partid = cellPartitions[nodecluster->id];
            netcluster->partitionPinCnt[partid]++;
            netcluster->partitionPin[partid].insert(nodecluster);
        }
    }

    // Print the Partitioning results
    std::cout<<"Before Bipartitioning"<<std::endl;
    std::cout<<"Nodes in Partition 1: "<<Partitions[0].getNodesCnt()<<", Nodes in Partition 2: "<<Partitions[1].getNodesCnt()<<std::endl;
    std::cout<<"Weights in Partition 1: "<<Partitions[0].getNodesWeight()<<", Weights in Partition 2: "<<Partitions[1].getNodesWeight()<<std::endl;

    // calculate the cut
    CUT = 0;
    for (auto net : NetClusterLevels.back())
    {
        if(net->isCutNet(cellPartitions))
            CUT += 1;
    }
    std::cout<<"CUT: "<<CUT<<std::endl;

    int level = NodeClusterLevels.size() - 1;
    FMadjust(level);

    std::cout<<"After Bipartitioning"<<std::endl;
    // Print the Partitioning results
    std::cout<<"Nodes in Partition 1: "<<Partitions[0].getNodesCnt()<<", Nodes in Partition 2: "<<Partitions[1].getNodesCnt()<<std::endl;
    std::cout<<"Weights in Partition 1: "<<Partitions[0].getNodesWeight()<<", Weights in Partition 2: "<<Partitions[1].getNodesWeight()<<std::endl;


    // calculate the cut
    CUT = 0;
    for (auto net : NetClusterLevels.back())
    {
        if(net->isCutNet(cellPartitions))
            CUT += 1;
    }
    std::cout<<"CUT: "<<CUT<<std::endl;

}

// FM algorithm
void Partitioner::FMadjust(int level)
{
    auto &clusters = NodeClusterLevels[level];
    auto &netclusters = NetClusterLevels[level];

    // The best FM iterations
    vector<int> bestcellPartitions;
    int bestgain;
    int gainsum = 0;
    vector<int> gaincol;
    vector<int> gainsuffixcol;
    vector<string> movenode;

    // The net clusters
    vector<int> gain(clusters.size(), 0);

    // The bucket list
    vector<Move> MoveCol;
    int Pmax = 0;
    for (auto node : clusters)
    {
        if (node->nets.size() > Pmax)
            Pmax = node->nets.size();
    }
    bestgain = -1000000;

    for (int i = 0; i < 2*Pmax + 1; i++)
    {
        int gain_per = -Pmax + i;
        MoveCol.emplace_back(gain_per);
    }

    // Set all the nodes unlocked, initialize the move gains
    for (auto node : clusters)
    {
        node->locked = false;
        initializeGain(gain, node);
        MoveCol[Pmax+gain[node->id]].addCandidateNodes(node);
    }

    // Choose the node with the best gain, and then move and update the Gains
    int NumNodesMove = 0;

    while(NumNodesMove < clusters.size())
    {
        // Find the largest Gain from the bucket list
        shared_ptr<NodeCluster> nodewithlargsetGain;
        int largestGain;
        int partid;

        // Find the largest Gain From the top to the end
        for(int i = 2*Pmax; i >= 0; i--)
        {
            if(MoveCol[i].NodeSetSize() != 0)
            {
                auto candidate =  *(MoveCol[i].candidateNodes.begin());
                partid = cellPartitions[candidate->id];
                nodewithlargsetGain = candidate;
                largestGain = -Pmax + i;
                break;
            }
        }

        // update the node locations
        MoveCol[largestGain+Pmax].deleteCandidateNodes(nodewithlargsetGain);
        nodewithlargsetGain->locked = true;
        NumNodesMove++;

        // update the gains
        updateGain(gain, nodewithlargsetGain, MoveCol);
        Partitions[partid].deleteNodes(nodewithlargsetGain);
        Partitions[1-partid].addNodes(nodewithlargsetGain);
        cellPartitions[nodewithlargsetGain->id] = 1 - cellPartitions[nodewithlargsetGain->id];

        // update the best partitions
        gainsum += largestGain;

        if (checkBalance() && gainsum >= bestgain)
        {
            bestgain = gainsum;
            bestcellPartitions.assign(cellPartitions.begin(), cellPartitions.end());
        }

        gaincol.push_back(largestGain);
        gainsuffixcol.push_back(gainsum);
        movenode.push_back(nodewithlargsetGain->leafnodecol[0]);
    }

    // update the best results to the cellPartitions
    cellPartitions.assign(bestcellPartitions.begin(), bestcellPartitions.end());
    for (int i = 0; i < Partitions.size(); i++)
        Partitions[i].clearNodes();
    for (int i = 0; i < cellPartitions.size(); i++)
        Partitions[cellPartitions[i]].addNodes(clusters[i]);
}


bool Partitioner::checkBalance()
{
    // calculate the TotalWeight of the clusters
    int SrcPartWeight = Partitions[0].getNodesWeight();
    int dstPartWeight = Partitions[1].getNodesWeight();
    int totalWeight = SrcPartWeight + dstPartWeight;
    return (abs(SrcPartWeight - dstPartWeight) < (totalWeight/10));
}

// Partitioner
void Partitioner::initializeGain(vector<int>& gain, shared_ptr<NodeCluster> node)
{
    int partid = cellPartitions[node->id];
    for(auto net : node->nets)
    {
        if(net->isCriticalNet())
        {
            int Fn = net->partitionPinCnt[partid];
            int Tn = net->partitionPinCnt[1-partid];
            if (Fn == 1)
                gain[node->id]++;
            if (Tn == 0)
                gain[node->id]--;
        }
    }
}

// update the calculated gain
void Partitioner::updateGain(vector<int>& gain, shared_ptr<NodeCluster> node, vector<Move>& move)
{
    int partid = cellPartitions[node->id];
    int Pmax = move.size() / 2;
    // update the gains before moving the nodes (Simply consider the connected critical nets)
    for (auto net : node->nets)
    {
        int Fn;
        int Tn;


        // Get the number of the nodes of both sides
        Fn = net->partitionPinCnt[partid];
        Tn = net->partitionPinCnt[1-partid];

        // Update the Gain before the Move
        if (Tn == 0)
        {
            for(auto pin : net->pins)
            {
                if (!pin->locked)
                {
                    move[gain[pin->id] + Pmax].deleteCandidateNodes(pin);
                    gain[pin->id]++;
                    move[gain[pin->id] + Pmax].addCandidateNodes(pin);
                }
            }
        }
        else
        {
            if (Tn == 1)
            {
                // There are some problems here
                auto node = *(net->partitionPin[1-partid].begin());
                if (!node->locked)
                {
                    int nodeid = node->id;
                    move[gain[nodeid] + Pmax].deleteCandidateNodes(node);
                    gain[nodeid]--;
                    move[gain[nodeid] + Pmax].addCandidateNodes(node);
                }
            }
        }

        // Change the Fn and Tn after the move
        Fn -= 1;
        Tn += 1;

        net->partitionPinCnt[partid]--;
        net->partitionPinCnt[1-partid]++;
        net->partitionPin[partid].erase(node);
        net->partitionPin[1-partid].insert(node);


        // Update the Gain after the Move
        if (Fn == 0)
        {
            for(auto pin : net->pins)
            {
                if(!pin->locked)
                {  
                    move[gain[pin->id]+Pmax].deleteCandidateNodes(pin);
                    gain[pin->id]--;
                    move[gain[pin->id]+Pmax].addCandidateNodes(pin);
                }
            }
        }
        else
        {
            if(Fn == 1)
            {                    
                auto node = *(net->partitionPin[partid].begin());
                if(!node->locked)
                {
                    int nodeid = node->id;
                    move[gain[nodeid] + Pmax].deleteCandidateNodes(node);
                    gain[nodeid]++;
                    move[gain[nodeid] + Pmax].addCandidateNodes(node);
                }
            }
        }
    }
}

vector<vector<int>> Partitioner::genClusters(vector<shared_ptr<NodeCluster>> &nodecluster)
{
    vector<vector<int>> nodeidclustercol;

    vector<int> nodeid2newclusterid(nodecluster.size(), -1); // node id to the new cluster id;

    // Coarsen with the neighbors with the largest connectivity
    for(auto cluster : nodecluster)
    {
        int clusterid = cluster->id;
        if(nodeid2newclusterid[clusterid] != -1)
            continue;

        vector<vector<int>> connectedNetInfo; //<net_weight, net_degree>
        auto netcluster = cluster->nets;
        int pinid = 0;
        
        for(auto net : netcluster)
        {
            vector<int> connectedNetInfoSub;
            connectedNetInfoSub.push_back(pinid);
            connectedNetInfoSub.push_back(net->weight);
            connectedNetInfoSub.push_back(net->pins.size());
            connectedNetInfo.push_back(connectedNetInfoSub);
            pinid++;
        }

        if (connectedNetInfo.size() == 0)
        {
            nodeidclustercol.push_back(vector<int>(1,clusterid));
            continue;
        }

        auto cmp = [](const vector<int> a, const vector<int> b)
        {
            return ((a[1] > b[1]) || ((a[1] == b[1]) && (a[2] < b[2])));
        };

        sort(connectedNetInfo.begin(), connectedNetInfo.end(), cmp);


        // Obtain the connected pins with the largest weight connections
        
        int netid_largest_id = connectedNetInfo[0][0];
        auto pins_largest = netcluster[netid_largest_id]->pins;

        vector<int> nodeidclusternew;

        for(auto pin : pins_largest)
        {
            if (nodeid2newclusterid[pin->id] == -1)
            {
                nodeidclusternew.push_back(pin->id);
                nodeid2newclusterid[pin->id] = nodeidclustercol.size();
            }
        }

        nodeidclustercol.push_back(nodeidclusternew);
    }

    return nodeidclustercol;
}

vector<shared_ptr<NodeCluster>> Partitioner::genClusters(vector<vector<int>> &clusterIds, int level)
{

    const vector<shared_ptr<NodeCluster>> &oldClusters = NodeClusterLevels[level - 1];
    vector<shared_ptr<NodeCluster>> newClusters;
    for (auto &cluster : clusterIds)
    {
        shared_ptr<NodeCluster> newCluster = make_shared<NodeCluster>();
        for (auto node : cluster)
            newCluster->addNode(oldClusters[node]);

        newClusters.push_back(newCluster);
    }

    for(int j = 0; j < newClusters.size(); j++)
        newClusters[j]->id = j;
    return newClusters;
}

vector<shared_ptr<NetCluster>> Partitioner::genClusterNets(int level)
{
    const vector<shared_ptr<NodeCluster>> &oldClusters = NodeClusterLevels[level-1];
    const vector<shared_ptr<NodeCluster>> &newClusters = NodeClusterLevels[level];
    const vector<shared_ptr<NetCluster>> &oldNets = NetClusterLevels[level - 1];
    vector<int> newClusterIdx(oldClusters.size());
    for (auto cluster : newClusters)
    {
        for(auto childCluster : cluster->nodes)
            newClusterIdx[childCluster->id] = cluster->id;
    }

    vector<shared_ptr<NetCluster>> newNets(oldNets.size());
    for(int i = 0; i < oldNets.size(); i++)
    {
        shared_ptr<NetCluster> newNet = make_shared<NetCluster>();
        set<int> newPins;
        for (auto cluster : oldNets[i]->pins)
            newPins.insert(newClusterIdx[cluster->id]);
        if (newPins.size() == 1)
            continue;
        for (auto id : newPins)
            newNet->pins.push_back(newClusters[id]);
        newNet->weight = oldNets[i]->weight;
        newNets[i] = newNet;
    }

    vector<shared_ptr<NetCluster>> tmpNewNets;
    for (auto ptr : newNets)
    {
        if(ptr) tmpNewNets.push_back(ptr);
    }

    newNets.assign(tmpNewNets.begin(), tmpNewNets.end());

    for(int i = 0; i < newNets.size(); i++)
    {
        auto net = newNets[i];
        for (auto pin : net->pins)
        {
            pin->nets.push_back(net);
        }
        net->id = i;
    }

    return newNets;
}

void Partitioner::OutputPartitions(string filename)
{
    ofstream outfile;
    outfile.open(filename);
    outfile << "cut_size "<<CUT<<std::endl;
    outfile << "A " << Partitions[0].getNodesCnt() <<std::endl;
    for (auto node : Partitions[0].nodes)
        outfile << node->leafnodecol[0] << std::endl;
    outfile << "B " << Partitions[1].getNodesCnt() <<std::endl;
    for (auto node : Partitions[1].nodes)
        outfile << node->leafnodecol[0] << std::endl;
    outfile << std::endl;
}