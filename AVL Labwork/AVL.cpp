#include "AVL.h"
#include "Node.h"

using namespace std;

AVL::AVL() {
	this->root = NULL;
	
	this->grew = false;
	this->changed = false;
}
AVL::~AVL(){
	this->clear();
} 

Node* AVL::getRootNode() const
{
	//cout << "In AVL::getRootNode"<<endl;
	return this->root;
}

/*Rotate functions just use the examples from the book code to do the musical chairs*/

void AVL::rotateRight(Node *&root){
	Node* temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root = temp;
	//right rotation should push balance to the right (up)
	root->BalanceUp();
	root->right->BalanceUp();
}

void AVL::rotateLeft(Node *&root){
	Node* temp = root->right;
	root->right = temp->left;
	temp->left = root;
	root = temp;
	//left rotation should push the balance to the left (down)
	root->BalanceDown();
	root->left->BalanceDown();
}

//This is the function that checks balance and performs any rotations that are necessary. The add and remove functions call it as much as is needed until the rebalance function does not set the 'changed' flag to true. 
void AVL::rebalance(Node *&root){
	if (root == NULL){ //always gotta check base case
		return;
	}
	rebalance(root->right);
	rebalance(root->left);
	if(root->getBalance()==-2){
		if(root->left->getBalance()==1){
			//LR tree
			rotateLeft(root->left);
		}
		rotateRight(root);
		changed = true;
	}
	else if(root->getBalance()==2){
					if(root->right->getBalance()==-1){
						//Must be RL tree
						rotateRight(root->right);
					}
					rotateLeft(root);
					changed = true;
				}
}

//Created the addRoot function that add uses since separating them was easier to follow.

bool AVL::add(int data)
{
	//cout << "In AVL::add"<<endl;
	this->grew = false;
	bool DidAdd = addRoot(this->root,data);
	
	//This do while loop ensures the rebalance function runs until the tree is balanced.
	do{
		changed = false;
		if(root!= NULL){
			root->refreshTree();
		}
		rebalance(root);
	}while(changed);
	return DidAdd;
}

//add Root: checks if data matches any of the roots it traverses. 

bool AVL::addRoot(Node *&root, int data){
	
	bool DataAdded = false;
	//this is the base case. when this is triggered 'grew' flag is set to true so the balancing if statements will engage.
	if (root == NULL){
		root = new Node(data);
		
		this->grew = true;
		return true;
	}
	else{
		if(root->getData()==data){
			return false;
		}
		else if(data < root->getData()){
			//recursively calls itself down the left side if data is less than current node value
			DataAdded = addRoot(root->left,data);
			if (grew){
				//Left subtree has grown!
				root->BalanceDown();
				if(root->getBalance()==-2){
					if(root->left->getBalance()==1){
						//Must be a LR tree
						rotateLeft(root->left);
					}
					rotateRight(root);
					this->grew = false;
				}
				else if(root->getBalance()==0){
					this->grew = false;
				}
			}
		}
		else if(data > root->getData()){
			//recursively calls itself down the right side if data if greater than current node value
			DataAdded = addRoot(root->right, data);
			if(grew){
				//Right subtree has grown!
				root->BalanceUp();
				if(root->getBalance()==2){
					if(root->right->getBalance()==-1){
						//Must be RL tree
						rotateRight(root->right);
					}
					rotateLeft(root);
					this->grew = false;
				}
				else if(root->getBalance()==0){
					this->grew = false;
				}
			}
		}
	}
	//gets here if data added to left or right
	return DataAdded;
}

//Again added a removeRoot function so it would be easier to follow for me.

bool AVL::remove(int data)
{
	//cout << "In AVL::remove"<<endl;
	bool DidRemove = removeRoot(this->root,data);
	//This do while loop ensures the rebalance function runs until the tree is balanced.
	do{
		changed = false;
		if(root!= NULL){
			root->refreshTree();
		}
		rebalance(root);
	}while(changed);
	return DidRemove;
}

//This one was kinda crazy. I definitely had some help with the pointers and references and keeping everything straight. But it works now!

bool AVL::removeRoot(Node *&root, int data){
	if(root==NULL){
		return false;
	}
	Node** temp;
	if(root->getData()==data){
		if(root->left != NULL){ //replace the node with the left child
			temp = &root->left;
			while((*temp)->right != NULL){
				temp = &((*temp)->right);
			}
			root->setData((*temp)->getData());
			Node* temp2 = (*temp)->left;
			delete *temp;
			*temp = temp2;
		}
		else if(root->right != NULL){ //replace the node with the right child
			temp = &root->right;
			Node* temp2 = root;
			root = *temp;
			delete temp2;
		}
		else{ //delete the node
			delete root;
			root = NULL;
		}
		
		return true;
	}
	//Recursive searching throught the tree for the matching node.
	else if(data<root->getData()){
		return removeRoot(root->left, data);
	}
	else if(data>root->getData()){
		return removeRoot(root->right, data);
	}
}


/*Uses the clearRoot function for recursively stepping through the tree and deleting each Node starting from the root passed. Then resets tree root to NULL. */
void AVL::clear()
{
	//cout << "In AVL::clear"<<endl;
	clearRoot(this->root);
	this->root = NULL;
}

void AVL::clearRoot(Node* root){
	if(root != NULL){
		clearRoot(root->left);
		//cout <<root->getData();
		clearRoot(root->right);
		delete root;
	}
}

