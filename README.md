# CENG5270_HW1
FM_algorithm Implementation

In our implementation, we use CMake to compile the overall program. I write the python script $build.py$ in the scripts folder to help with the compilation as:
~~~
$./scripts/build.py -o release
~~~

Then the executable file $hw1$ would be generated in the $bin$ folder. Then we could run the executable file with the following command as:
~~~
$cd bin
$time -p ./hw1 <node_file> <net_file>  <out_file>
~~~

For example, if we want to run the FM partitioner on the p2-1.cells and p2-1.nets file, we could run:
~~~
$time -p ./hw1 ../testcases/p2-1.cells ../testcases/p2-1.nets ../output/p2-1.out
~~~

The partitioning result for the case would be generated at ../output/p2-1.out file.