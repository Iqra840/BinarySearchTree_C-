#include <iostream>
#include <list>
#include <unordered_map> 
#include <thread>
#include <cstdlib>
#include <vector> 
#include <utility>
using namespace std;
list<int> nodelist;
vector< pair <int,int> > vect; 
class node
{   friend class BST;
    int key, val;           //stores keys and values of the node
    node *left,*right;      //left and right branches from the node
    bool ispresent;         //boolean flag determines if a child or thread is present
     
};

class BST
{
    public:
        node *root,*temporary;   //the root and temporary node for storing key values
        list<node*>nodesinseq;       //storing nodes in sequence for preorder traversal
        BST();                     //using BST to initialisze node as null
        void initialize(int );           //accepting total number of nodes to be inserted
        node *insert(node*,node*);  //insert function defined
        void display();             //a preorder display function defined
        void Preorder(node*);         //the function for preorder conversion is defined
        void threading(node*);         //threading function is defined
        void search(int); //searches for value with the given key
};


void BST :: initialize(int total)
{
    //takes in values and calls insert function to recursively add nodes to the tree
    for(int unsigned it = 0; it<vect.size(); it++ ){
       temporary = new node;
        int x= vect[it].first;
        temporary->key= x;
        temporary->ispresent = false;
        temporary->left = NULL;
        temporary->right = NULL;
     root = insert(root,temporary);   //adding nodes into the binary search tree
    }
    //passing nodes as threads to be preordered 
    threading(root);
}

void BST :: search(int item){
    bool found = false;//flag to see if node is found
    
    node *present = root; //current node as a reference to traverse the tree
    while(present != NULL && found != true){
        if(present->ispresent)   {  //if the node has a child
            
            present = present->right;
            if (present->key ==item){//if key is detected
                
                found = true;
                
            }
            
        }
        else if(present->left){          //traverse to the left if theres no right thread, and vice versa
            present = present->left;
            
       } else{
            present = present->right; 
            
    }
    
    }
    
    for (int unsigned it = 0; it<vect.size(); it++){
        if (item == vect[it].first && found == true){
            //the value is found
            int value = vect[it].second;
            cout<<"age of patient of identity 6 is "<<value<<endl;
        }
    }
}

BST :: BST(){root = NULL;} //initializing root as null

node* BST :: insert(node* current,node* t)
{
    //Inserting nodes using recursion
    if(current == NULL)
        return t;
    else if(current->key > t->key)
    {
        current->left = insert(current->left,t);
    }
    else
    {
        current->right = insert(current->right,t);
    }

    return current;
}

void BST :: display()
{   cout<<"Preorder Traversal: ";
    //instead of using recursion I used threads which link together to give the preordered result
    node *present = root;   //set a pointer 'present' which traverses the tree
    while(present != NULL)
    {
        cout<<" "<<present->key;      //output key of current node

        if(present->ispresent)              //if a child is present, traverse to its right
        {
            present = present->right;
            cout<<"";
        }
        else if(present->left)          //traverse left child if it is present with no right child, and vice versa
            present = present->left;
        else
            present = present->right;      
    }
}

void BST :: Preorder(node *current)
{
    //use the nodesinseq to push nodes in prepodered manner into the list, and traverse root->left->right through the tree
    if(current != NULL)
    {
        nodesinseq.push_back(current);
        Preorder(current->left);
        Preorder(current->right);
    }
}

void BST :: threading(node *current)
{
    bool complete = false;         //checks to see if traversal has been completed
    node *present ;                //reference pointer for traversing the nodes
    Preorder(current);             //calling preorder on every current node
    while(!complete)               
    {
        present = nodesinseq.front();       //accessing the first reference node
        if(nodesinseq.empty())           //every time a node has been traversed, it's popped from the list. so 
            complete = true;               //the process is complete when the list is empty.
        else
        {
                nodesinseq.pop_front();     //delete reference node after accessing it
               
                if(!present->right && !present->left) //if no child
                {
                    if(nodesinseq.empty())      
                        present->right = NULL; //last node of the traversal should point to NULL
                    else
                    {
                        present->right = nodesinseq.front(); //passing next node in the sequence as a thread
                        present->ispresent = true;       //indicate that a child exists
                }
        }
    }
    
    }
}

int main()
{
//we create an instance of class BST called treeobj, and push all the nodes into a list which will be initialized in
//the function "initialize".
//implemented a vector of pairs to insert key value pair into the tree
BST treeobj;
vect.push_back(make_pair(8, 25));
vect.push_back(make_pair(3, 10));
vect.push_back(make_pair(6, 31));
vect.push_back(make_pair(10, 11));
vect.push_back(make_pair(1, 20));
vect.push_back(make_pair(14, 28));
vect.push_back(make_pair(4, 17));
vect.push_back(make_pair(13, 9));
vect.push_back(make_pair(2, 49));
vect.push_back(make_pair(0, 33));

treeobj.initialize(nodelist.size()); //the size controls the loop of the insert function
treeobj.search(6); //searches for id 6 
treeobj.display(); //display preordered result

return 0;
}