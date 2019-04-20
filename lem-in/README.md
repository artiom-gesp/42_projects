# LEM-IN

LEM-IN is an introduction to **graph theory** and **graph traversal**.

The algorithm takes as *input* a graph and a *number of ants*.  
Each node of the graph (except _start_ and _end_) can only contain one ant at a time.
All ants start at _start_.  

The goal is to move all the ants from _start_ to _end_ with the less amount of moves.

It is equivalent to find the largest amount of node-disjoint paths from _start_ to _end_.

![resized_lem_in_visu](https://user-images.githubusercontent.com/41552833/56457060-b45fa000-6375-11e9-915f-fce6d451d37c.gif)

## Steps of the algorithm :
1. Parsing instructions
2. Creating adjacency matrix representing the graph
3. Finding the **augmented path** from _start_ to _end_.
    1. Change the direction of the links constituting the **augmented path** (-> becomes <- and vice versa)
    2. Traverse the graph from end to start to find associated path(s)
    3. Calculcate the required number of steps and store it in a linked list with the associated path(s)
    4. If all the nodes direclty linked to start were visited : **break**
    5. Else : **repeat**
4. Select the node with the lesser amount of steps
5. Send the ants

## Usage
```
Make
./lem-in < ant-farm   (see examples in the maps directory)
./lem-in -p < ant-farm      => show the selected path
./lem-in -v < ant-farm      => visualize the ant farm and move the ants by hand
```
