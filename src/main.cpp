# include "string.h"
# include "Partitioner.h"
# include "ctime"

using namespace std;


int main(int argc, char *argv[])
{
    string nodefileName = argv[1];
    string netfileName = argv[2];
    string outfileName = argv[3];

    // Read the benchmark
    std::clock_t c_start_1 = std::clock();
    Database database;
    database.readBm(nodefileName, netfileName);
    std::clock_t c_end_1 = std::clock();
    std::cout<<"IO Time (s): "<<(c_end_1 - c_start_1)*1.0/CLOCKS_PER_SEC<<std::endl;

    // Partitioner
    std::clock_t c_start_2 = std::clock();
    Partitioner partitioner(database);
    partitioner.coarsening();

    partitioner.initPart();

    // Output the partitions
    partitioner.OutputPartitions(outfileName);
    std::clock_t c_end_2 = std::clock();

    std::cout<<"Part Time (s): "<<(c_end_2 - c_start_2)*1.0/CLOCKS_PER_SEC<<std::endl;


    return 0;
}