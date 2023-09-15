//binary tree implementation
//spirtual coder in the building man simple!

#include<iostream>

struct leaf{    
    //characteristics of nodes in a binary tree
    int data;
    //nodes will always have a left and right child, either pointing to nodes or nullptr
    leaf* left_child;       
    leaf* right_child;
};

class btree{
    public:
        btree(): root(nullptr){};
        ~btree();                   //declare and a body "{}" needed for you constructor
        void insertion(int);     
        void recursion(leaf*, int);  
        bool search(int);         
        bool look_up(leaf*, int);
        void destory_tree(leaf*);
        

    private:
        //the only think we need to keep track of is the root, where to start searching from in the binary tree
        leaf* root;
};

btree::~btree(){
    destory_tree(root);
}

//recursively deletes each node
void btree::destory_tree(leaf* current){
    if(current != nullptr){
        destory_tree(current->left_child);
        destory_tree(current->right_child);
        delete current;
    }
}


/*insertion function
    - starts at root and recursively treverses left or right direction of the tree based on rule:
    - (samllest nodes left and largest/equal nodes right) untill you reach a nullptr meaning you reached end of tree
    - allocate new node and insert it at that postion of nullptr
    - binary tree property allows all insertion to be forced at the end of the tree, compared to a priority queue where you have to bubble up or sink down
    - binary tree's and pritorit queues are totally different
*/

//since were recursively going down the tree, we need to return the next leaf position either a (left child or right child pointer)
void btree::insertion(int value){
    //setting up root node
    if(root == nullptr){
        leaf* node = new leaf;
        node->data = value;
        node->right_child = nullptr;
        node->left_child = nullptr;
        root = node;
    }else{
        recursion(root, value);
    }
}

//lesson dont return pointers unnecessarly, they get confusing! Just use the pointer in that function!
void btree::recursion(leaf* current, int value){

    //moves left through tree
    if(value < current->data){
        //if the current's left child points to a nullptr it means it's an avaliable spot
        if(current->left_child == nullptr){ 
            //create a new node at that postion of null ptr
            leaf* temp = new leaf;
            //node = current->left_child;     #im setting temp to an empty nullptr? thats why seg fult
            temp->data = value;
            temp->left_child = nullptr;
            temp->right_child = nullptr;
            //want left child to equal the temp node
            current->left_child = temp;
        }else{
            recursion(current->left_child, value);      //now the new current is the left child
        }

    }
    //moves right through tree
    else if(value >= current->data){
        //if the current's right child points to a null pointer, it means it's an avaliable spot
        if(current->right_child == nullptr){
            leaf* temp = new leaf;
            //node = current->right_child;  # im setting temp to an empty nullptr? thats why seg fult
            temp->data = value;
            temp->right_child = nullptr;
            temp->left_child = nullptr;
            current->right_child = temp;
        }else{
            recursion(current->right_child, value);
        }
    }
}

bool btree::search(int value){
    //value happens to be in root
    if(root->data == value){
        return true;
    }else{
        bool check = look_up(root, value);
        return check;
    }
}

//when we pass pointers in function, were passing a copy of the pointer, so we wont change orginal root reference
bool btree::look_up(leaf* current, int value){

    //recursion will go thorugh each level of the tree and mark it as a current node
    if(current->data == value){
        return true;
    }

    //traversing through the tree, will move along the tree aslong as the child exist 
    if(value < current->data){
        if(current->left_child != nullptr){
            return look_up(current->left_child, value);
        }else{
            //if leftchild reaches nullptr meaning end of tree the value is not found
            return false;
        }
    }

    if(value >= current->data){
        if(current->right_child != nullptr){
            return look_up(current->right_child, value);
        }else{
            //if rightchild reaches nullptr meaning end of tree the value is not found
            return false;
        }
    }
    
}

int main(){

    btree tree;
    tree.insertion(5);
    tree.insertion(4);
    tree.insertion(6);
    tree.insertion(7);
    bool check = tree.search(7);
    if(check == true){
        std::cout << "value is in tree" << std::endl;
    }else{
        std::cout << "value is not found" << std::endl;
    }

    
    

    return 0;
}