//Final Project Task 2 Iqra Abbasi
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include <map>
using namespace std;
multimap<int, int> keyval_pairs; 
map<int,int>::iterator it;
//first I define a node as a structure, and define its key, value, and 2 left and right pointers
struct node
{
int key, val;
int large;
struct node *left, *right;
};

//Now we create *newNode, which is an instance of the struct node to be used
//in the binary search tree, and declare instance as a pointer to temporarily delete unbalanced nodes
struct node *newNode(int item, int value)
{
struct node *instance = (struct node *)malloc(sizeof(struct node));

instance->key = item;
instance->val = item;
instance->left = instance->right = NULL;
return instance;
}

int height(struct node* node)//checks height of tree
    {
        return (node == NULL ? -1 : node->large);
    }

void  Empty(struct node* node)//recursively deletes nodes until null node is reached
    {
        if(node == NULL){
        return;
        }
        Empty(node->left);
        Empty(node->right);
        delete node;
    }


struct node* findMin(struct node* node) //finds minimum and pushes it to the left side of tree
    {
        if(node == NULL){
            return NULL;
        }
        else if(node->left == NULL){
            return node;
        }
        else{
            return findMin(node->left);
        }
    }

    
struct node* findMax(struct node* node) //finds maximum and pushes it to the right side of tree
    {
        if(node == NULL){
            return NULL;
        }
        else if(node->right == NULL){
            return node;
        }
        else{
            return findMax(node->right);
        }
    }
    
  
struct node* singleRightRotate(struct node* &node) //to rotate to the right only once
    {
        struct node* u = node->left;
        node->left = u->right;
        u->right = node;
        
        node->large = max(height(node->left), height(node->right))+1;
        u->large = max(height(node->left), node->large)+1;
        return u;
    }
struct node* singleLeftRotate(struct node* &node) //to rotate to the left only once
    {
        struct node* u = node->right;
        node->right = u->left;
        u->left = node;
        
        node->large = max(height(node->left), height(node->right))+1;
        u->large = max(height(node->right), node->large)+1 ;
        return u;
    }

struct node* doubleLeftRotate(struct node* &node) //to rotate to the left twice
    {
        node->right = singleRightRotate(node->right);
        return singleLeftRotate(node);
    }

struct node* doubleRightRotate(struct node* &node) //to rotate to the right twice
    {
        node->left = singleLeftRotate(node->left);
        return singleRightRotate(node);
    }


int getBalance(struct node* node)//function to find difference between the two sides of a tree
    {
        if(node == NULL){
            return 0;
        }
        else{
            return height(node->left) - height(node->right);
        }
    }
//rebalance function    
struct node* rebalance (struct node* node){
    node->large = max(height(node->left), height(node->right))+1;
    if(height(node->left) - height(node->right) == 2) //eligible for rebalanceing
        {
            //implementing right right case
            if(height(node->left->left) - height(node->left->right) == 1)
                return singleLeftRotate(node);
            //implementing right left case
            else
                return doubleLeftRotate(node);
        }
        // If right node is deleted, implement left case
        else if(height(node->right) - height(node->left) == 2)
        {
            //implementing left left case
            if(height(node->right->right) - height(node->right->left) == 1)
                return singleRightRotate(node);
            //implementing left right case
            else
                return doubleRightRotate(node);
        }
        return node;
    }

//this function initializez the node according to the program requirements.
struct node* initialize(struct node* node, int key, int val)
{
//Base case checks if tree is empty, it will return a new node which will be the root
//of the tree
if (node == NULL) {
    keyval_pairs.insert({ key, val }); 
    return newNode(key, val);
    }

//if key is less than the node's key, it means a tree exists and we
//can traverse through it
if (key < node->key){
//initialize values to the left since key is less than the node's key
node->left = initialize(node->left, key, val);
node->left = initialize(node->left, key, val);
}
else if (key > node->key){
//initialize values to the right since key is greater than the node's key
node->right = initialize(node->right, key, val);
node->right = initialize(node->right, key,val);}
//pointer is returned
return node;
}
struct node* insert(node* root, int key, int val)
{
    //a new node is created which holds the key and value assigned to it
    node* newnode = newNode(key,val);

    //pointer node traverses through tree starting from root, 
	//looking for the appropriate position for new insert
    node* x = root;

    //another pointer y is the reference of pointer x and is used to compare values
	//of x as it traverses the tree.
    node* y = NULL;

    while (x != NULL) {//if x is not null, a tree or subtree exists
        y = x;
        if (key < x->key)
            x = x->left;//x goes to the left as key is less than that node's key
        else
            x = x->right;//x goes to the right as key is greater than that node's key
    }

    //then if root is null, the tree is thus empty and x(y)becomes the root
	//i.e the new node
    if (y == NULL) {
        y = newnode;
    }
	//if the key entered is less that the node's key, it goes on the left
    else if (key < y->key){
        y->left = newnode;
    }

    //if the key entered is greater that the node's key, it goes on the right
    else{
        y->right = newnode;
    }

    //returns the pointer at whichever position it reaches
    return rebalance(y);
    //return y;
}

struct node* remove(node* root, int k)
{

    // Base case of tree being empty
    if (root == NULL)
        return root;

    //now we recursively check the position of the node.
	//so if node id being checked has greater value than key, key 
	//goes to the left, and vice versa.
    if (root->key > k) {
        root->left = remove(root->left, k);
        return root;
    }
    else if (root->key < k) {
        root->right = remove(root->right, k);
        return root;
    }

    //if one subnode exists, we delete the node.
    if (root->left == NULL) {
        node* instance = root->right;
        delete root;
        return rebalance(instance);//tree is rebalanced when node is removed
    }
    else if (root->right == NULL) {
        node* instance = root->left;
        delete root;
        return rebalance(instance);//tree is rebalanced when node is removed
    }

    // If the required node has children, we check the keys of these nodes and
	//rearrange them
    else {
		//lets strat from the right
        node* parent = root->right;

        // this loop finds the linked nodes to the key.
		//while it always has a left, we bring the right values to the left to sort the tree.
        node *child = root->right;
        while (child->left != NULL) {
            parent = child;
            child = child->left;
        }

        parent->left = child->right;

        ///successor's info is given to the root, which returns with this data, showing the new format
		//of the BST.
        root->key = child->key;

        delete child;
        return root;
    }
}
//  function to search a node's value given the key
struct node* search(struct node* root, int key)
{
    // if root is null or key is present at root
    if (root == NULL || root->key == key) {
        auto value = keyval_pairs.find(key);
        cout<<"Age of patient with id 13 is "<<value->second<<endl;
        
        return root;

       
    }
	//otherwise recursively look for key until found.
    else if(root->key < key){

        return search(root->right, key);
    }else{
        return search(root->left, key);
    }

}


// main function
int main()
{


struct node *root = NULL;//declaring root node as null
//initialize function initializes the values as required in the task
root = initialize(root, 3,10);
initialize(root, 1,20);
initialize(root, 4,17);
initialize(root, 6,31);
initialize(root, 7,17);
initialize(root, 13,9);
initialize(root, 8,25);
initialize(root, 10,11);
initialize(root, 14,28);
//insert function prototype
insert(root,2,49);
insert(root,0,33);
//search function prototype
search(root, 13);
//remove function prototype
root= remove(root, 7);

return 0;
}