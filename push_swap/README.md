# PUSH_SWAP

PUSH_SWAP is a stack sorting algorithm.  
It receives as input a stack of integers and returns a list of instructions to sort it.

To sort the stack, the algorithm can only use the provided stack A and an empty stack on equal size B.  

Here is the list of all possible moves :

![Screen Shot 2019-04-20 at 11 20 35 AM](https://user-images.githubusercontent.com/41552833/56455457-d00b7c00-635e-11e9-9895-d9682f93f56a.png)

Usage :
```
Make
./push_swap STACK     =>    list of moves to sort the stack
./checker < list_of_moves STACK     =>    verify that the list sorts the stack correclty
./push_swap STACK | ./checker STACK     (STACK can be for example : "1 2 5 6 -43 4")
./checker -w STACK    => OUTPUTS the number of moves
./checker -v STACK    => To visualize the sorting
```
  
![GIF_VISU_PUSH_SWAP](https://user-images.githubusercontent.com/41552833/56455917-4f9c4980-6365-11e9-8373-4b06f391b561.gif)
