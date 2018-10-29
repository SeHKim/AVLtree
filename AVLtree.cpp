#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <queue>
using namespace std;
struct Node {
//AVL¸¬X xÜ| 􀀀¥X lp´
 Node(int d, int l = 0, Node *left = 0, Node *right = 0)
: data(d), level(l), leftChild(left), rightChild(right){}
// xÜ Ð@ àX height, |½Ý, $x½Ý Ál| 􀀀Àà ä.
 Node *leftChild;
 int data;
 int level;
 Node *rightChild;

};
class Tree {
	//AVL¸¬ t¤
public:
	Tree() { root = 0; } // D´ 0ø ¸¬ Ý1
	void Insert(Node* &ptr, int);//xÜ| 􀀀X h
	void Search(Node* &ptr, int);//¹ ÐD 􀀀Ä xÜ| ÉX h
	void Delete(Node* &ptr, int);//¹ ÐD 􀀀Ä xÜ| ­X h
	void Print(Node* ptr);//´ ¸¬| %X h
	int getLevel(Node* &ptr);//t| Xtü h
	int getBF(Node* &ptr);
	//àX |½¨ü $x½¨X (t| t©t BF| lX h
	void setLevel(Node* &ptr);
	//t| $tü h
	Node* repair(Node* &ptr);
	Node* LL(Node* &ptr);
	Node* RR(Node* &ptr);
	Node* LR(Node* &ptr);
	Node* RL(Node* &ptr);

private: // helper hä
	Node *root;


};
int Tree::getLevel(Node* &ptr)
{
 if (!ptr) return -1;
 //ptrt t¬XÀJät  empty¸¬|t -1 X
 else return max(getLevel(ptr->leftChild), getLevel(ptr->rightChild)) + 1;
 //|½ÝX t@ $x½ÝX t  T @D è| 1D T\ä.(øx ìh)
 }
int Tree::getBF(Node* &ptr)
{
	return (getLevel(ptr->leftChild)) - (getLevel(ptr->rightChild));
	//BF |½¸¬t-$x½¸¬t| getLevelX ¬À )<\ l\ä.
}
void Tree::setLevel(Node* &ptr)
{//repairh| µt Ü􀀀Ä levelD äÜ $tüh.
	if (!ptr)
	{
		//¸¬􀀀 D´ÀJät
		setLevel(ptr->leftChild);
		//¬À)<\ ¬􀀀¬¤ xÜ0 |½ ÝD 0| ¨D $\ä.
		setLevel(ptr->rightChild);
		//¬À)<\ ¬􀀀¬¤ xÜ0 $x½ ÝD 0| ¨D $\ä.
		ptr->level = getLevel(ptr);
		//ptrX ¨@ getLevelD µt ¬À<\ àX ¸¬| µt LD¸ä.
	}
}
Node* Tree::repair(Node* &ptr)
{
	int BF = getBF(ptr);
	//getBF| µt ¬ 􀀀¬¤ xÜX BFD l\ä.
	if (BF > 1)
	{
		if (getBF(ptr->leftChild) > 0)
			ptr = LL(ptr);
		else
			ptr = LR(ptr);
	}
	else if (BF < -1)
	{
		if (getBF(ptr->rightChild)>0)
			ptr = RL(ptr);
		else
			ptr = RR(ptr);
	}
	return ptr;
}
Node* Tree::LL(Node* &ptr)
{
	Node* node = ptr->leftChild;
	ptr->leftChild = node->rightChild;
	node->rightChild = ptr;
	return node;
}
Node* Tree::RR(Node* &ptr)
{
	Node* node = ptr->rightChild;
	ptr->rightChild = node->leftChild;
	node->leftChild = ptr;
	return node;
}
Node* Tree::LR(Node* &ptr)
{
	Node* temp;//XD\ ìx0
	Node* leftNode = ptr->leftChild;
	temp = leftNode->rightChild;
	leftNode->rightChild = temp->leftChild;
	temp->leftChild = leftNode;
	ptr->leftChild = temp;
	temp = ptr->leftChild;
	ptr->leftChild = temp->rightChild;
	temp->rightChild = ptr;
}
Node* Tree::RL(Node* &ptr)
{
	Node* temp;//XD \ ìx0
	Node* rightNode = ptr->rightChild;
	temp = rightNode->leftChild;
	rightNode->leftChild = temp->rightChild;
	temp->rightChild = rightNode;
	ptr->rightChild = temp;
	temp = ptr->rightChild;
	ptr->rightChild = temp->leftChild;
	temp->leftChild = ptr;
	return temp;
}
void Tree::Insert(Node* &ptr, int value) { //xÜ| 􀀀X h.
	Node* temp;//¬À )<\ ¬©` L D\ Ü ìx0 À| ¬©\ä.
	if (!ptr)
	{
		ptr = new Node(value);
	}
	else if (value < ptr->data)
	{
		Insert(ptr->leftChild, value);
		temp = repair(ptr);
		ptr = temp;
	}
	else if (value > ptr->data)
	{
		Insert(ptr->rightChild, value);
		ptr = repair(ptr);
	}
	setLevel(ptr);
}
void Tree::Search(Node* &ptr, int value) { //¹ xÜ| ÉX h.
	if (!ptr) cout << endl << "Tree is empty\n";
	else if (value < ptr->data)
	{
		cout << ptr->data << " ->";
		Search(ptr->leftChild, value);
	}
	else if (value > ptr->data)
	{
		cout << ptr->data << " ->";
		Search(ptr->rightChild, value);
	}
	else cout << " " << value << " \n";
}
void Tree::Print(Node* ptr) {
	queue<Node*> q;
	q.push(ptr);
	while (!q.empty()){//P􀀀 D´À JÙH õ
		cout << ptr->data << " ";
		if (ptr->leftChild != NULL)
		{
			q.push(ptr->leftChild);
			cout << "left :" << ptr->leftChild->data << " ";
		}
		if (ptr->rightChild != NULL)
		{
			q.push(ptr->rightChild);
			cout << "right :" << ptr->rightChild->data << " ";
		}
		if (!ptr->rightChild&&!ptr->leftChild) cout << "Leaf Node";
		cout << endl;
		q.pop();
		if (q.empty()) break;
		else ptr = q.front();
	}
	cout << endl;
}
void Tree::Delete(Node* &ptr, int value) { 
	Node* tmpptr;
	if (!ptr) cout << endl << "Tree is empty\n";
	else if (value < ptr->data)
	{
		Delete(ptr->leftChild, value);
		ptr = repair(ptr);
	}
	else if (value > ptr->data){
		Delete(ptr->rightChild, value);
		ptr = repair(ptr);
	}
	else
		if (!ptr->leftChild && !ptr->rightChild) 
		{
		delete ptr; ptr = 0; return;
		} //
	else if (ptr->leftChild && !ptr->rightChild) //|½ÝÌ ät
		{
		tmpptr = ptr; ptr = ptr->leftChild; delete tmpptr; return;
		}
	else if (!ptr->leftChild && ptr->rightChild) // $x½ ÝÌ ät
		{
		tmpptr = ptr; ptr = ptr->rightChild; delete tmpptr; return;
		}
	else { //PÝL:
		Node *rc = ptr->rightChild; // rc􀀀 è¸x subtree
		if (!rc->leftChild) // rc􀀀 |½Ýt Æ<t rc􀀀 ø xÜ!	
		{
			ptr->data = rc->data;
			ptr->rightChild = rc->rightChild;
			delete rc;
		}
		else // rcX |½ Ýt  ½°, rcX |½ÝX |½ÝX
		{
			while (rc->leftChild->leftChild)//rcX leftchild􀀀 t¬XÀ JD L LÀ
			{
				rc = rc->leftChild;
			}
			ptr->data = rc->leftChild->data;
			rc->leftChild = rc->leftChild->rightChild;
			delete rc->leftChild;
		}
	}
#endif