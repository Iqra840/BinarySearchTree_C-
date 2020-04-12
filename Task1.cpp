//Final Project Task 1 Iqra Abbasi

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<thread>
#include <map>
#include <list>
using namespace std;

//first I define a node as a structure and define its key, value, and 2 left and right pointers
struct node
{
int key, val;
struct node *left, *right;
};
multimap<int, int> keyval_pairs; 
map<int,int>::iterator it;
//Now we create *BSTnode, which is an instance of a node to be used
//in the binary search tree
struct node *BSTnode(int item, int value)
{
struct node *instance = (struct node *)malloc(sizeof(struct node));

instance->key = item;
instance->val = item;
instance->left = instance->right = NULL;
return instance;
}


//this function initializez the node according to the program requirements.
struct node* initialize(struct node* node, int key, int val)
{
//Base case checks if tree is empty, it will return a new node which will be the root
//of the tree
if (node == NULL) {
    keyval_pairs.insert({ key, val }); 
    return BSTnode(key, val);
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
    node* bstnode = BSTnode(key,val);

    //pointer node traverses through tree starting from root, 
	//looking for the appropriate position for new insert
    node* point = root;

    //another pointer point_ref is the reference of pointer point and is used to compare values
	//of point as it traverses the tree.
    node* point_ref = NULL;

    while (point != NULL) {//if point is not null, a tree or subtree exists
        point_ref = point;
        if (key < point->key)
            point = point->left;//point goes to the left as key is less than that node's key
        else
            point = point->right;//point goes to the right as key is greater than that node's key
    }

    //then if root is null, the tree is thus empty and point_ref becomes the root
	//i.e the new node
    if (point_ref == NULL) {
        point_ref = bstnode;
    }
	//if the key entered is less that the node's key, it goes on the left
    else if (key < point_ref->key){
        point_ref->left = bstnode;
    }

    //if the key entered is greater that the node's key, it goes on the right
    else{
        point_ref->right = bstnode;
    }

    //returns the pointer at whichever position it reaches
    return point_ref;
}

struct node* remove(node* root, int k)
{

    // base case = tree is empty
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
        return instance;
    }
    else if (root->right == NULL) {
        node* instance = root->left;
        delete root;
        return instance;
    }

    // If the deleted node has children, we rearrange them by comparing their keys
    else {
		//lets start from the right
        node* nextparent = root->right;

        // this loop finds the linked nodes to the key.
		//while it always has a left, we bring the right values to the left to sort the tree.
        node *next = root->right;
        while (next->left != NULL) {
            nextparent = next;
            next = next->left;
        }

        nextparent->left = next->right;

        ///successor's info is given to the root, which returns with this data, showing the new format
		//of the BST.
        root->key = next->key;

        delete next;
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