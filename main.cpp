/*******					Notes:***---------------------------------------------------------------------------------***	c_str():	Returns the current value of the string object***	atoi():  	Returns the integer representation of an ascii character***	to_string(): 	Returns a string containing the representation of a number
***	trunc:		Discard the contents of the stream when opening
***	app:		Seek to the end of the stream before each write***---------------------------------------------------------------------------------*******/#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void print_append(string,string);


class treeNode
{
	public:
		string chStr;
		int prob;
		string code;
		treeNode* left;
		treeNode* right;
		treeNode* next;
		treeNode();
		treeNode(string,int,string,treeNode*,treeNode*,treeNode*);
};

treeNode::treeNode()
{
	chStr = "dummy";
	prob  = -999;
	code  = "";
	left  = NULL;
	right = NULL;
	next  = NULL;
}

treeNode::treeNode(string chStr, int prob, string code, treeNode* left, treeNode* right, treeNode* next)
{
	this->chStr = chStr;
	this->prob  = prob;
	this->code  = code;
	this->left  = left;
	this->right = right;
	this->next  = next;;
}

class linkedList
{
	public:
		treeNode* listHead;
		linkedList();
		treeNode* findSpot(treeNode*);
		void insertNewNode(treeNode*,treeNode*);
		void insert(treeNode*,treeNode*);
		string printList();
};

linkedList::linkedList()
{
	listHead = new treeNode();
}

treeNode* linkedList::findSpot(treeNode *newNode)
{
	treeNode* spot = this->listHead;
	while(spot->next != NULL)
	{
		if(spot->next != NULL and spot->next->prob < newNode->prob)
			spot = spot->next;
		else
			return spot;
	}
	return spot;
}

void linkedList::insert(treeNode *spot,treeNode *newNode)
{
	newNode->next = spot->next;
	spot->next = newNode;
}

void linkedList::insertNewNode(treeNode *listHead, treeNode *newNode)
{
	treeNode* temp = findSpot(newNode);
	insert(temp,newNode);
}

string linkedList::printList()
{
	string line = "listHead --> ";
	treeNode* ptr = this->listHead;
	while(ptr->next != NULL)
	{
		line += "(\"" + ptr->chStr + "\", "+ to_string(ptr->prob);
		line += ", \"" + ptr->next->chStr + "\") --> ";
		ptr = ptr->next;
	}
	line += "(\"" + ptr->chStr + "\", ";
	line += to_string (ptr->prob)+ ", NULL) --> NULL\n";

	return line;
}

class HuffmanBinaryTree
{
	public:
		treeNode* Root;
		HuffmanBinaryTree();
		HuffmanBinaryTree(treeNode*);
		linkedList constructHuffmanLList(string, string);
		void constructHuffmanBinTree(linkedList*,string);

		void preOrderTraveral(treeNode*,string);
		void postOrderTraveral(treeNode*,string);
		void inOrderTraveral(treeNode*,string);
};

HuffmanBinaryTree::HuffmanBinaryTree()
{
	Root = new treeNode();
}

HuffmanBinaryTree::HuffmanBinaryTree(treeNode *listHead)
{
	Root = listHead;
}

linkedList HuffmanBinaryTree::constructHuffmanLList(string input_file_name, string output_file_name)
{
	ifstream inFile;
	ofstream outFile(output_file_name);
	inFile.open(input_file_name);

	string word;
	string charIn;
	int prob;
	bool read_str = true; // True/False = reading characters/probabilities

	linkedList L;

	while(inFile >> word)
	{
		if(read_str == true)
		{
			charIn = word;
			read_str = false;
		}
		else
		{
			prob = atoi(word.c_str());
			treeNode* temp = new treeNode(charIn, prob, "", NULL, NULL, NULL);
			L.insertNewNode(L.findSpot(temp), temp);
			read_str = true;
		}	
	}

	// Making the Root point to the linked list(Empty changed to point to somewhere)
	this->Root = L.listHead;

	outFile << L.printList();

	inFile.close();
	outFile.close();

	return L;
}

void HuffmanBinaryTree::constructHuffmanBinTree(linkedList *L,string outFile)
{
	string new_chStr;
	int new_prob = 0;

	while(L->listHead->next->next != NULL)
	{
		// Concatenating characters
		new_chStr = L->listHead->next->chStr;
		new_chStr += L->listHead->next->next->chStr;

		// Summing probabilities up
		new_prob = L->listHead->next->prob;
		new_prob += L->listHead->next->next->prob;

		// Creating new node
		treeNode* new_node = new treeNode(new_chStr, new_prob, "", NULL, NULL, NULL);
		// Pointing the new node's left and right child to its original nodes
		new_node->left = L->listHead->next;
		new_node->right = L->listHead->next->next;

		// Inserting new node
		L->insertNewNode(L->findSpot(new_node), new_node);

		// Shifting the linked list head to the next next one
		L->listHead->next = L->listHead->next->next->next;
	}

	// Renewing the Root
	this->Root = L->listHead->next;
}

void HuffmanBinaryTree::preOrderTraveral(treeNode *Root,string output_file_name)
{
 	if(Root == NULL)
		return;
	else
	{
		string line = "(\"" + Root->chStr + "\", " + to_string(Root->prob) + ")  "; 
		print_append(line, output_file_name);
		preOrderTraveral(Root->left, output_file_name);
		preOrderTraveral(Root->right, output_file_name);
	}
}

void HuffmanBinaryTree::postOrderTraveral(treeNode *Root,string output_file_name)
{
	if(Root == NULL)
		return;
	else
	{
		postOrderTraveral(Root->left, output_file_name);
		postOrderTraveral(Root->right, output_file_name);
		string line = "(\"" + Root->chStr + "\", " + to_string(Root->prob) + ")  ";
		print_append(line, output_file_name);
	}
}

void HuffmanBinaryTree::inOrderTraveral(treeNode *Root,string output_file_name)
{	
	if(Root == NULL)
		return;
	else
	{
		inOrderTraveral(Root->left, output_file_name);
		string line = "(\"" + Root->chStr + "\", " + to_string(Root->prob) + ")  ";
		print_append(line, output_file_name);
		inOrderTraveral(Root->right, output_file_name);
	}
}


bool isLeaf(treeNode *T)
{
	if(T->left == NULL and T->right == NULL)
		return true;
	else
		return false;
}

void constructCharCode(treeNode *T,string code,string outFile)
{
	if(isLeaf(T))
	{	
		T->code = code;
		// Writing code to output file
		string line = T->chStr + "   " + T->code + "\n";
		print_append(line, outFile);
	}
	else
	{
		if(T->left != NULL)
			constructCharCode(T->left, code + "0", outFile);
		if(T->right != NULL)
			constructCharCode(T->right, code + "1", outFile);
	}
}

void print_append(string content,string file_name)
{
	
	ofstream outFile(file_name, fstream::app);
	outFile << content;
	outFile.flush();
	outFile.close();
}


int main(int argc, char **argv)
{
	string pre_txt	= "The Pre-Order traversal of the Huffman Binary Tree:\n";
	string post_txt = "\n\nThe Post-Order traversal of the Huffman Binary Tree:\n";
	string in_txt	= "\n\nThe In-Order traversal of the Huffman Binary Tree:\n";

	string inFile   = argv[1];// input file
	string outFile1 = argv[2];// Huffman<char code> pairs
	string outFile2 = argv[3];// Huffman Tree Traversals
	string outFile3 = argv[4];// Output for Debugging

	HuffmanBinaryTree T;
	linkedList temp = T.constructHuffmanLList(inFile,outFile3);
	T.constructHuffmanBinTree(&temp,outFile3);
	ofstream traversal(outFile2,ifstream::trunc);
	print_append(pre_txt,outFile2);
	T.preOrderTraveral(T.Root,outFile2);
	print_append(post_txt,outFile2);	T.postOrderTraveral(T.Root,outFile2);	print_append(in_txt,outFile2);	T.inOrderTraveral(T.Root,outFile2);
	

	string fakeCode = "";	ofstream codeList(outFile1,ifstream::trunc);
	constructCharCode(T.Root,fakeCode,outFile1);

	traversal.close();	codeList.close();	
	return 0;
}
