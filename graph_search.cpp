/*
    Praticing different graph traversal algorithms including BFS and DFS (08-31-2020)
*/

#include<iostream>
#include<list>
#include<vector>
#include<iterator>
#include<map>
#include<ctime>

//data structures used in traversal algorithms (Stacks and Queues)
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
            /*
            !Error Code!: end = current->next; 
            **  end is set to a nullptr, after (current = end line 50) is executed, a block of mem with data cant equal a nullptr which
                which lead to a seg fault; "basic mistake was the node was set to a nullptr"
            */
        }else{
            //allocate mem for new node
            node* current = new node;
            end->next = current;        //end points to the previous node, end->next points to this current node
            current->data = value;
            current->next = nullptr;
            end = current;
            /*
            !Error Code!
            node* current = new node;
            current->data = value;
            current->next = nullptr;
            ** end was pointing to the previous node, we were overlapping two nodes which lead to a seg fault  which lead to seg fault
            current = end;
            end = current->next;        
            */
        }
        /*
        [Solution analysis]
        - We wanted reference to previous node before the insertion of a new node so that the previous node will point to the current node
        - end keeps track of the previous node, and end->next pointer will point to the new node thats going to be inserted
        - using end->next each node has a *next pointer that points to the next node, bit confusing but makes sense :D
        */
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
    void test(){   //test's the queue data structure
        node* iter = front;
        if(front != end->next){
            while(iter != end->next){
            std::cout << iter->data << " ";
            iter = iter->next;
            }
            std::cout << std::endl;
        }
    }
};

class Stack{
    private:
    node* top;
    public:
    Stack():top(nullptr){};
    ~Stack(){};

    void push(int value){
        //allocate new memory for node
        node* current = new node;
        //we set the pointer direction from top to bottom because we have ref to top and need to go down the stack to get next element
        node* oldtop = top;
        current->next = oldtop;
        current->data = value;
        top = current;
    }

    int pop(){
        //ref of top to delete node to save memory
        node* ref = top;
        if(ref != nullptr){
            top = ref->next;
            delete ref;
            return top->data;
        }else{
            std::cerr << "Cannot pop, stack is empty" << std::endl;
        }
    }
    void display(){
         //create a temp pointer to move through stack 
        node* temp = top;
        if(temp == nullptr){
           std::cerr << "stack is empty" << std::endl;
        }else{
            std::cout << "top -> ";
            while(temp != nullptr){
                std::cout << temp->data << " ";
                temp = temp->next;
            }
            std::cout << std::endl; 
        }
    }
};

//bfs search's in layers so queue is optimal data structure
std::vector<int> bread_search(std::list<int> adj_list[], int vertices){
    std::vector<int> order;
    Queue search;               //keeps track of the nodes that still need their neighbour's or branches to be searched
    std::vector<int> visited;   //keep track of already encountered nodes

    //pick random node in graph to be start point 
    srand(time(0));
    int start_point = rand()%vertices;
    search.insert(start_point);
    visited.push_back(start_point);

    while(visited.size() != vertices){
        //look at all neighbour nodes
        std::list<int>::iterator it;
        for(it = adj_list[start_point].begin(); it != adj_list[start_point].end(); it++){
            //check to see if neighbour node isn't already visited 
            bool already_checked = false;
            for(int i = 0; i < visited.size(); i++){
                if(visited[i] == *it){
                    already_checked = true;
                }
            }
            if(already_checked == false){
                search.insert(*it);
                visited.push_back(*it);
            }
        }

        //pop off fully searched nodes and move start node
        search.pop();
        start_point = search.getStart();
    }

    return visited;
}

//using stack data strucutre for dfs
std::vector<int> depth_search(std::list<int> adj_list[], int vertices){
    std::vector<int> visited;
    Stack stack;

    //pick random start point
    srand(time(0));
    int start_point = rand()%vertices;
    stack.push(start_point);
    visited.push_back(start_point);

    //loop will explore all the nodes in the graph
    while(visited.size() != vertices){
        //find an avaliable branch from the current start_point, if we can't we backtrack to previous node and continue process
        bool backtrack = true;
        std::list<int>::iterator it;
        //check to find an unexplored branch/node
        for(it = adj_list[start_point].begin(); it != adj_list[start_point].end();it++){
            bool valid_branch = true;
            for(int i = 0; i < visited.size();i++){
                if(*it == visited[i]){
                    valid_branch = false;
                }
            }
            if(valid_branch == true){
                backtrack = false;      //no need to backtrack since we found a valid branch to explore
                start_point = *it;
                stack.push(*it);
                visited.push_back(*it);
                break;                  //we only need one valid_branch
            }
        }
        if(backtrack == true){
            start_point = stack.pop();
        }
    }
    return visited; 
}

int main(){
    //test graph
    int vertex = 10;
    //empty map container which links node number to a specific value
    std::map<int,int> nodes_to_value;
    for(int i = 0; i < vertex; i++){
        nodes_to_value.insert(std::pair<int,int>(i,i+1));
    }
    //adjacency list that holds graph info, connection's of nodes
    std::list<int> adj_list[vertex];
    adj_list[0].push_back(1);
    adj_list[0].push_back(3);
    adj_list[1].push_back(4);
    adj_list[1].push_back(0);
    adj_list[1].push_back(6);
    adj_list[1].push_back(7);
    adj_list[2].push_back(8);
    adj_list[2].push_back(9);
    adj_list[2].push_back(1);
    adj_list[2].push_back(3);
    adj_list[3].push_back(0);
    adj_list[3].push_back(2);
    adj_list[4].push_back(1);
    adj_list[4].push_back(5);
    adj_list[4].push_back(6);
    adj_list[4].push_back(7);
    adj_list[5].push_back(4);
    adj_list[6].push_back(4);
    adj_list[6].push_back(1);
    adj_list[6].push_back(7);
    adj_list[7].push_back(1);
    adj_list[7].push_back(6);
    adj_list[7].push_back(4);
    adj_list[8].push_back(2);
    adj_list[9].push_back(2);

    /*
        TEST GRAPH DIAGRAM


                       5 
                     /  
                0   4    
               / \ /|\
              3  1----6
              \ / \| /
               2   7
              / \
             9  8
    */

    std::cout << "Test Graph: " << std::endl;
    std::list<int>::iterator it;
    for(int i = 0; i < vertex; i++){
        std::cout << i << "--> ";
        for(it = adj_list[i].begin(); it != adj_list[i].end(); it++){
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------" << std::endl;

    std::vector<int> BFS = bread_search(adj_list,vertex);
    std::cout << "bread-first search: ";
    for(int i = 0; i < BFS.size();i++){
        std::cout << BFS[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> DFS = depth_search(adj_list,vertex);
    std::cout << "depth-first search: ";
    for(int i = 0; i < DFS.size();i++){
        std::cout << DFS[i] << " ";
    }
    std::cout << std::endl;

   
    return 0;
}