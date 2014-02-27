//Node of Singly Linked List
#include<vector>
struct Node{
	int data;
	Node * next;
	Node(int d, Node * ne){ 
		data = d;
		next = ne;
	}
};

//Node of Binary Tree
typedef struct treeNode{
	int data;
	treeNode * left;
	treeNode * right;
	treeNode(int d, treeNode * l, treeNode * r):data(0),left(NULL),right(NULL){
		data = d;
		left = l;
		right = r;
	}
}treeNode;

//Ajacent List of direct graph
enum visitStatus {unVisited, Visiting, Visited};
typedef struct DGNode{
	int data;
	visitStatus vs;
	DGNode * firstArc;
	DGNode(int d, visitStatus v, DGNode * fa):data(0),vs(unVisited),firstArc(NULL){
		data = d;
		firstArc = fa;
		vs = v;
	}
}DGNode;

vector<DGNode *> adjacentNodes(DGNode * node){
		vector<DGNode *> aN;
		for(DGNode * arc = node->firstArc; arc != NULL; arc = arc->next){
			aN.push_back(arc);
		}
		return aN;
}

typedef struct DG{
	int nodeNum;
	DGNode nodeList[100];
}DG;

//Tree Node with parent point
typedef struct tNode{
	int data;
	tNode * left, * right, * parent;
}tNode;
