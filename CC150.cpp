#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include"structure.h"
using namespace std;

//CC150 1.1
//check whether a string has all unique characters
//requirment: no additional space
//complexity: O(n^2)
bool checkUnique_1(string s){
	int le = s.length();
	for(int i = 0; i<le; i++){
		for(int j = i+1; j<le; j++ )
			if(s[i] == s[j]) return false;
	}
	return true;
}

//same as above
//use constant arrary space
//complexity O(n)
bool checkUnique_2(string s){
	int bitmap[256];
	for(int i = 0; i < 256; i++)
		bitmap[i] = 0;
	for(int i = 0; i< s.length(); i++){
		if(bitmap[s[i]] == 1) return false;
		else {
			bitmap[s[i]] = 1;
		}
	}
	return true;
}

//CC150 1.2
//reverse a C-style string
void reverseCString(char s[], int n){
	int start = 0;
	int end = n-1;
	while(start<end){
		char temp = s[start];
		s[start] = s[end];
		s[end] = temp;
		start++;
		end--;
	}
}

//CC150 1.3
//remove duplicate character in a string
//time complexity O(n^2)
void removeDuplicate(char s[], int n){

	int tail = 1;
	for(int i = 1; i < n; i++){
		int j;
		for(j = 0; j < i; j++){
			if(s[i]==s[j]) break;
		}
		if(j==i){ 
		s[tail] = s[i];
		tail++;
		}
	}
	s[tail]='\0';
}

//CC150 1.4
//string anagram
//notes: I think there are some bugs in the given solution in CC150
bool anagram(string s1, string s2){
	int l1 = s1.length();
	if(l1 != s2.length()) return false;
	int wfreq[256];
	for(int i = 0; i < 256; i++)
		wfreq[i] = 0;
	for(int i = 0; i < l1; i++)
		wfreq[s1[i]]++;
	for(int i = 0; i < l1; i++)
		wfreq[s2[i]]--;
	for(int i = 0; i < 256; i++)
		if(wfreq[i]!=0) return false;
	return true;
}
//CC150 1.5
//replace space with "%20"
void replaceSpace(string & s1){
	int ori_l = s1.length();
	int space_num = 0;
	for(int i = 0; i < ori_l; i++)
		if(s1[i]==' ') space_num++;
	string temps = s1;
	s1.resize(ori_l+2*space_num);
	for(int i = 0, j = 0; i < ori_l; i++)
		if(temps[i]!=' '){
			s1[j]=temps[i];
			j++;
		}
		else {
			s1[j] = '%';
			s1[j+1] = '2';
			s1[j+2] = '0';
			j = j+3;
		}
}

//CC150 1.6
//rotate a n*n matrix right by 90 degree
//time complexity O(n^2)
void rotateMatrix90_right(int **M, int n){
	for(int i = 0; i < n/2; i++){
		int first = i;
		int last = n-i-1;
		for(int j = first; j < last; j++){
			int temp = M[first][j];
			M[first][j] = M[last-j][first];
			M[last-j][first] = M[last][last-j];
			M[last][last-j] = M[j][last];
			M[j][last] = temp;
		}
	}
}

//CC 150 1.7
//set Zero in m*n matrix
void setZero(int M[][3], int m, int n){
	bool * row = new bool[m];
	bool * column = new bool[n];
	for(int i = 0 ; i < m; i++)
		row[i] = false;
	for(int j = 0; j < n; j++)
		column[j] = false;
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			if(M[i][j] == 0){
				row[i] = true;
				column[j] = true;
			}
	for(int i = 0; i < m; i++)
		for(int j = 0; j < n; j++)
			if(row[i]==true || column[j]==true)
				M[i][j]=0;
	delete [] row;
	delete [] column;
}

//CC150 2.1
//delete repuate in linked list
void deleteDuplicateLinkedList(Node * head){
	if(head&&head->next){
		Node * cur = head->next;
		Node * run;
		Node * pre = head;
		while(cur){
			run=head;
			while(run!=cur){
				if(run->data==cur->data){
					pre->next=run->next;
					break;
				}
				pre = run;
				run=run->next;
			}
			cur=cur->next;
		}
	}
}

//CC150 2.2 iterative version
//find the nth element starting from the end
Node * nthFromLast(Node * head, int n){
	if(!head) return NULL;
	Node * p1 = head;
	Node * p2 = head;
	for(int i = 0; i < n-1; i++)
	{
		p2=p2->next;
		if(p2==NULL) return NULL;
	}
	if(p2->next==NULL) return p1;
	while(p2->next){
		p1 = p1->next;
		p2 = p2->next;
	}
	return p1;
}

//CC150 2.2 recursive version
Node * nthFromLast_recursive(Node * head, int n, int & k){
	if(!head) return NULL;
	if(head->next == NULL) k = 1;
	else { 
		nthFromLast_recursive(head->next, n, k);
		if(k == n) return head;
	}
	k++;
	return NULL;
}

//CC150 2.3
//delete a middle node only with access to this given node
bool deleteMiddleNode(Node * middle){
	if(!middle || middle->next == NULL) return false;
	middle->data = middle->next->data;
	middle->next = middle->next->next;
	return true;
}

//CC150 2.4
//add operation in Linked List representation
Node * addLinkedList(Node * head1, Node * head2, int & carry){
	if(!head1&&!head2) return NULL;
	Node * res = new Node(0, NULL);
	if(!head1){
		head2->data += carry;
		res = head2;
		carry = 0;
	}
	else if(!head2){
		head1->data += carry;
		res = head1;
		carry = 0;
	}
	else {
		int temp = head1->data + head2->data + carry;
		if(temp>=10){
			temp = temp%10;
			carry = 1;
		}else carry = 0;
		res->data = temp;
		res->next = addLinkedList(head1->next, head2->next, carry);
	}
	return res;
}

//CC150 2.5
//find first node of a circle in a Linked List
//assue there must be a circle in the Linked List
Node * firstNodeInCircle(Node * head){
	if(!head) return NULL;
	Node * one = head;
	Node * two = head;
	while(one->next != two->next){
		one = one->next;
		two = two->next->next;
	}
	two = two->next;
	one = head;
	while(one != two){
		one = one->next;
		two = two->next;
	}
	return one;
}

//CC150 3.1
//Use a single array to implement three stacks
class threeStacks{
		int stackSize;
		int * buffer;
		int pointer[3];
		threeStacks(int size){
			stackSize = size;
			buffer = new int[size*3];
			pointer[0] = -1;
			pointer[1] = -1;
			pointer[2] = -1;
		}
		~threeStacks(){
			delete [] buffer;
		}
		bool push(int stackNo, int value){
			if(pointer[stackNo]+1 >= stackSize*(stackNo+1))
				return false;
			buffer[++pointer[stackNo] + stackSize*stackNo] = value;
		}
		int peek(int stackNo){
			if(pointer[stackNo] == -1)
				return 0;
			return buffer[pointer[stackNo]+stackSize*stackNo];
		}
		int pop(int stackNo){
			int v = peek(stackNo);
			pointer[stackNo]--;
			return v;
		}
		bool isEmpty(int stackNo){
			return pointer[stackNo]+1 ==stackSize;
		}
};

//CC150 4.1
int maxDepth(treeNode * root){
	if(!root) return 0;
	return max(maxDepth(root->left), maxDepth(root->right)) + 1;
}

int minDepth(treeNode * root){
	if(!root) return 0;
	return min(minDepth(root->left), minDepth(root->right)) + 1;
}

bool balancedTree(treeNode * root){
	return (maxDepth(root) - minDepth(root) <= 1);
}

//CC150 4.2
bool search(DG G, DGNode * start, DGNode * end){
	queue<DGNode *> Q;
	start->vs = Visiting;
	Q.push(start);
	while(!Q.empty()){
		DGNode * tmp = Q.front();
		Q.pop();
		vector<DGNode *> ajnodes = adjacentNodes(tmp);
		for(vector<DGNode *>::iterator it = ajnodes.begin; it !=ajnodes.end(); it++ ){
			if((*it)->vs == unVisited){
				if((*it) == end) return true;
				(*it)->vs = Visiting;
				Q.push((*it));
			}
		}
		tmp->vs = Visited;
	}
}

//CC150 4.3
treeNode * subTree(int array[], int start, int end){
	if(start < end) return NULL;
	int mid = (start + end)/2;
	treeNode * root = new treeNode(array[mid], NULL, NULL);
	root->left = subTree(array, start, mid-1);
	root->right = subTree(array, mid+1, end);
	return root;
}
treeNode * createMinBST(int array[], int length){
	if(length == 0) return NULL;
	return subTree(array, 0, length-1);
}

//CC150 4.4
vector<vector<treeNode *>> findLevelList(treeNode * root){
	vector<vector<treeNode *>> res;
	if(!root) return res;
	vector<treeNode *> tmp;
	tmp.push_back(root);
	do{
		res.push_back(tmp);
		vector<treeNode *> lastLevel = tmp;
		tmp.clear();
		for(vector<treeNode *>::iterator it = lastLevel.begin(); it != lastLevel.end(); it++){
			if((*it)->left) tmp.push_back((*it)->left);
			if((*it)->right) tmp.push_back((*it)->right);
		}
	}while(!tmp.empty());
}

//CC150 4.5
tNode * inorderSuccess(tNode * e){
	if(!e) return NULL;
	tNode * p = e->right;
	if(e->right){
		while(p->left){
			p = p->left;
		}
		return p;
	}else if(!e->parent) 
		return NULL;
	else if(e == e->parent->left)
		return e->parent;
	else {
		p = e->parent;
		while(p != p->parent->left)
			p = p->parent;
		return p->parent;
	}
}

//CC150 4.6
bool covers(treeNode * root, treeNode * p){
	if(!root) return false;
	if(root == p) return true;
	return covers(root->left, p)||covers(root->right, p);
}
treeNode * commonAncester(treeNode * root, treeNode * p, treeNode * q){
	if(!root) return NULL;
	if(covers(root->left, p)&&covers(root->right,q))
		return commonAncester(root->left, p ,q);
	if(covers(root->right,p)&& covers(root->right,q))
		return commonAncester(root->right, p, q);
}

//CC150 4.7
bool matchTree(treeNode *t1, treeNode * t2){
	if(t1 == NULL && t2 == NULL) return true;
	if(t1 == NULL || t2 == NULL) return false;
	if(t1->data == t2->data){
		return matchTree(t1->left, t2->left)&&matchTree(t1->right, t2->right);
	}
	return false;
}
bool containsTree(treeNode * t1, treeNode * t2){
	if(!t1) return false;
	if(t1->data == t2->data){
		if(matchTree(t1, t2)) return true;
	}
	return containsTree(t1->left, t2)||containsTree(t1->right, t2);
}
//CC150 5.1
int updateBits(int n, int m, int i, int j){
	int max = ~0;
	int left = max - (1<<j - 1);
	int right = (1<<i) - 1;
	int mask = left | right;
	return (n&mask)|(m<<i);
}

//CC150 5.3
bool getBit(int n, int index){
	return (n&(1<<index) > 0);
}
int setBits(int n, int index, bool set){
	if(set){
		n |= 1<<index;
	}else n &= ~(1<<index);
	return n;
}

int getNext_NP(int n){
	if(n < 0) return -1;
	//get first 1
	int index = 0;
	int countOnes = 0;
	while(!getBit(n, index)) index++;
	//get first 0 and count ones
	while(getBit(n, index)) {
		index++;
		countOnes++;
	}
	//turn 0 to 1
	setBits(n, index, true);
	index--;
	//turn off 1 that right next to the turned on 0
	setBits(n, index, false);
	countOnes--;
	//set zeroes
	for(int i = index - 1; i >=countOnes; i--){
		setBits(n, i, false);
	}
	//set ones
	for(int i = countOnes - 1; i >= 0; i--){
		setBits(n, i, true);
	}
	return n;
}


int getPrevious_NP(int n){
	if(n < 0) return -1;
	int index = 0;
	int countZeroes = 0;
	while(getBit(n, index)) index++;
	while(!getBit(n, index)) {
		index++;
		countZeroes++;
	}
	setBits(n, index, false);
	index--;
	setBits(n, index, true);
	countZeroes--;
	for(int i = index-1; i >= countZeroes; i--)
		setBits(n, i, true);
	for(int i = countZeroes-1; i >= 0; i-- )
		setBits(n, i, false);
	return n;
}

//CC150 5.5
int diffBits(int n, int m){
	int count = 0;
	for(int xor = n^m; xor > 0; xor = xor>>1)
		count += xor&1;
	return count;
}

//CC150 5.6
void swapOddEven(int & n){
	return (n&0xaaaaaaaa)>>1|(n&0x55555555)<<1;
}

//CC150 8.1
int Fabonacci(int n){
	if(n == 1 || n == 2) return 1;
	return Fabonacci(n - 1) + Fabonacci(n - 2); 
}
int Fabonacci_iterative(int n){
	if(n == 1 || n == 2) return 1;
	int f1 = 1, f2 = 1;
	for(int i = 3; i <= n; i++){
		int tmp = f2;
		f2 = f1 + f2;
		f1 = tmp;
	}
	return f2;
}

//CC150 8.2
int maxPath(int m, int n){
	if(m <= 0 || n <= 0) return 0;
	if(m == 1 || n == 1) return 1;
	return maxPath(m, n-1) + maxPath(m-1, n);
}
int robotMaxPath(int n){
	return maxPath(n, n);
}
/*Follow Up Question*/
