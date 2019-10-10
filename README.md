# Project-3

Project 3:  This project is a continuation of your project 2 to include step 3 and step 4 of the Huffman coding algorithm steps (there are four algorithm steps, see below, will be asked in exam-1).  Re-use your codes in your project 2; however, in order to implement steps 3 and 4, the list nodes in your project 2 will need to be modified to become tree nodes.
  
Step 1: Compute probabilities of a given text file.  (Done in project 1, use character counts as prob.)
Step 2: Construct Huffman ordered linked list using insertion sort.  (Done in project 2.)
	Step 3: Construct Huffman binary tree  (this project).
	After the tree construction, you are to traverse the Huffman binary tree in the order of:
			a) pre-order 
			b) in-order
			c) post-order
	
	Step 4: construct Huffman code, from the binary tree  (this project).
	
Note:  Huffman encoding and decoding will be our project 4.

********************************
I.  Language: C++ 
********************************
Points : 10 pts
Due Date:  Soft copy: 9/16/2019 Monday before midnight
      Hard copy: 9/17/2018 Tuesday in class 

    1 day late: -1 pt 9/17/2019  Tuesday before midnight
Hard copy: 9/19/2018 Thursday in class // no late hard copy!

   2 days late: -3pts 9/18/2019 Wednesday before midnight
Hard copy: 9/19/2018 Thursday in class // no late hard copy!

-10 pts after 9/18/2019  

**** All projects without hard copy after 9/19/2019 will receive 0 pts even you have submit soft copy on time and even if it works.

********************************
I. Input (argv[1] ):  A file contains a list of <char prob> pairs with the  following format. The input prob are integer, has been multiplied by 100, i.e., a prob equal to .40 will be given as 40, char should be treated as string. 
********************************
	char1  prob1  
	char2  prob2
	char3  prob3
:
:
charn  probn  




********************************
II. Outputs: 
********************************
- outFile1 (argv[2]): A text file contain the Huffman <char	code> pairs 
- outFile2 (argv[3]): A text file contain the pre-order, in-order, and
post-order  traversals of the Huffman binary tree
- outFile3 (argv[4]):  for your debugging outputs. See output format below for detail.

********************************
III. Data structure: You MUST include all the object classes as given below.
********************************   
  - A treeNode class  // required
- chStr (string)
- prob (int)
- code (string) 
- left (treeNode *)
- right (treeNode *)
- next (treeNode *)
-  constructor (chStr, prob, code, left, right, next) 
- printNode (T)
// given a node, T, print T’s chStr, T’s prob, T’s next chStr, T’s left’s chStr, T ‘s right’s chStr 
// one print per text line

-  linkedList class // required
- listHead (treeNode *)
- constructor (..)
- insertNewNode (listHead ,  newNode)  
// As taught in class; this method calls findSpot (…) and call insert(…)
- findSpot (…)  // algorithm steps taught in class.
- insert(Spot, newNode) // insert newNode after Spot, taught in class
- printList (…)
// print the list  from listHead to the end of the list in the following format:
listHead -->(“dummy”, -99, next’s chStr1)-->( chStr1, prob1, next’s chStr2)...... --> (chStrj, probi, NULL)--> NULL

	For example: 
listHead -->(“dummy”, -99, “b”)-->( “b”, 5, “a”) -->( “a”, 7, “d”)............ --> (“x”, 45, NULL)--> NULL

- A HuffmanBinaryTree class    // required
	- Root (treeNode *)
- constructor(s)
- constructHuffmanLList (inFile, outFile)
- constructHuffmanBinTree (listHead)  
	- preOrderTraversal (Root, outFile)
	- inOrderTraversal (Root, outFile)
	- postOrderTraversal (Root, outFile)
	- constructCharCode (T, code, outFile)
	- isLeaf (node)// a given node is a leaf if both left and right are null.


******************************************
IV.  Main (….)
******************************************
Step 0: inFile ← open input  file from argv[1]
outFile1, outFile2, …, outFile5 ← open from argv[2], argv[3], argv[4]

Step 1: constructHuffmanLList  (inFile, outFile3) // see below
Step 2:  constructHuffmanBinTree (listHead, outFile3) // see below
Step 3: write: “the pre-order traversal of the constructed Huffman Binary tree: \n”
preOrderTraversal (Root, outFile2)  // see below

Step 4: write: “the in-order  traversal of the constructed Huffman Binary tree: \n”
inOrderTraversal (Root, outFile2)  // see below

Step 5: write: “the post-order traversal of the constructed Huffman Binary tree: \n”
postOrderTraversal (Root, outFile2)  // see below

Step 6:  constructCharCode (Root, ‘’, outFile1) // ‘’ is an empty string
Step 7: close all files
******************************************
V.  constructHuffmanLList (inFile, outFile)
******************************************
Step 1:  listHead ← get a newNode as the dummy treeNode with (“dummy” ,0),  listHead to point to.  

Step 2: chr  ← get  from inFile
            prob  ← get  from inFile
	newNode ← get a new listNode (chr, prob, ‘’,  null, null, null) // ‘’ is an empty string 
      
Step 3: insertNewNode (listHead, newNode) // use algorithm steps given in class
           
Step 4: printList (listHead, outFile) // debug print
// print the list to outFile, from listHead to the end of the list 
// using the format given in the above.
Step 5: repeat step 2 – step 4 until the end of inFile .
			
******************************************
VI. constructHuffmanBinTree (listHead, outFile) 
******************************************
 Step 1: newNode ← create a treeNode  // the following five assignments may be done in the constructor.
        newNode’s prob ← the sum of prob of the first and second node of the list // first is the node after dummy
        newNode’s chStr ← concatenate chStr of the first node and chStr of the second node in the list
        newNode’s left ← the first node of the list
        newNode’s right ← the second node of the list
        newNode’s next ← null

 Step 2: insertNewNode (listHead, newNode)
 Step 3: listHead’s next ← listHead .next.next.next   // third node after dummy node
 Step 4: printList (listHead, outFile)  // debug print
 Step 5: repeat step 1 – step 4 until the list only has one node left after the dummy node
 Step 6:  Root ← listHead’s next
******************************************
VII.  bool isLeaf (T) 
******************************************
if  T’s left is null and T’s right is null
	return true
else return false

******************************************
VIII.  constructCharCode (T, code, outFile) 
******************************************
if  isLeaf (T)   // T’s left and T’s right are null
 	T’s code =  code;
	 output   T’s  chStr  and T’s code to outFile   // one per text line 
	else 
	      constructCharCode (T’s left, code + “0”, outFile) //string concatenation
	      constructCharCode (T’s right, code + “1”, outFile) //string concatenation

******************************************
IV.  preOrderTraveral (T, outFile)  // In recursion
******************************************
  
if  isLeaf (T)
     printNode (T) // output to outFile,  see printing format in treeNode in above
else
      printNode (T) 
      preOrderTraveral (T’s left, outFile)
                  preOrderTraveral (T’s right, outFile)

******************************************
X. inOrderTraversal (Root, outFile)  // In recursion
******************************************

You should know how to write this method.


******************************************
XI. postOrderTraveral (Root, outFile)  // In recursion
******************************************

You should know how to write this method.

