## Minimum Weight Maximum Entropy Problem
Implementation for the paper [Data Graph Formulation as the Minimum-Weight Maximum-Entropy Problem](http://link.springer.com/chapter/10.1007%2F978-3-319-18224-7_2 "Minimum-Weight Maximum Entropy Problem")

##### Dependencies

This code has been written and tested on Ubuntu and it has the following dependencies:

- [Google Logging:](https://github.com/google/glog) sudo apt-get install libgoogle-glog-dev
- [Google Flags](https://github.com/gflags/gflags) sudo apt-get install libgflags-dev
- [iGraph library](igraph.org)

##### Instructions

Compilation

```
cd minweight-maxentropy/
mkdir build
cd build
cmake ..
```

Execution

```
./n1graph_demo ../data/hat_00.csv ../data/hat_01.csv
```