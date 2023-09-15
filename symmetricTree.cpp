//leetcode 101.Symmetric Tree

#include<iostream>
#include<vector>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct node{
    int data;
    node* next;
};

class Queue{
    private:
    node* front;    
    node* end;      //keeps track of the previous node, end->next is where the next node will be located

    public:
    Queue():front(nullptr), end(nullptr){};   
    ~Queue(){};

    void insert(int value){
        if(front == nullptr){
            //allocate mem for new node
            node* current = new node;
            current->data = value;
            current->next = nullptr;
            front = current;
            end = current;
        }else{
            //allocate mem for new node
            node* current = new node;
            end->next = current;        //end points to the previous node, end->next points to this current node
            current->data = value;
            current->next = nullptr;
            end = current;
        }
    }
    void pop(){
        if(front != end->next){
            node* oldfront = front;
            front = oldfront->next;
            delete oldfront;
        }else{
           throw std::invalid_argument("Cannot pop, queue is empty!");
        }
    }
    //returns start of the queue
    int getStart(){
        if(front != nullptr){
            return front->data;
        }else{
            throw std::invalid_argument("queue is empty!");
        }
    }
};

bool isSymmetric(TreeNode* root) {
    std::vector<int> visited;
    std::vector<int> queue; 
    //add current node to queue
    queue.push_back(root->val);
    //check left and right child
    if(root->left != nullptr){
        isSymmetric(root->left);
    }
    if(root->right != nullptr){
        isSymmetric(root->right);
    }

    //after checking both right and left nodes pop from queue and put in visited
    queue.pop_back()


    
    
    
}