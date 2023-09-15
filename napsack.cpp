#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<utility>

/*
    0/1 knapsack problem:
    - Given a set of items, each with a weight and a value, determine which items to select based on a maximum weight that you can
    - carry to ensure that you achieve the greatest value


    Lesson: int** array = new int*[list.size()+1];  
      - The problem with this is that I already intialized (array) to be a pointer to a int pointer as a class variable
      - by creating int** again im creating a local variable that only exists in the constructor, meaning the local variable has no 
      - relation to the class variable. 
      - soloution: array = new int*[list.size()+1]; without declaring the type im referencing the class variable and not creating a new var
    
    Problem answer:
    0 1 2 3 4 5 6 7 
    ---------------
    0 1 1 1 1 1 1 1   - Start at last element and figure out where the element came from, if it came from previous row, the current item 
    0 1 1 4 5 5 5 5   - is not part of the solution, if the previous row is different then the item is part of the soloution. 
    0 1 1 4 5 6 6 9   - if we pick the item up we have to find remaining weight left over to pick up more items, so we adjust the position 
    0 1 1 4 5 7 8 9   - of row and col and repeat the same process till the value is zero, meaning zero weight is remaining (first col)
*/

class bestChoice{
    private:
    std::map <int, int> items;
    int** array;                
    int max_weight; 
    public:
    bestChoice(std::map<int,int> list, int weight);  
    ~bestChoice(){}; 
    std::vector<std::pair<int,int>> findChoices();
    int max(int a, int b){
        if(a >= b){
            return a;
        }else{
            return b;
        }
    }
    friend void print(std::vector<std::pair<int,int>> printable, bestChoice &instance);
};

//constructor
bestChoice::bestChoice(std::map<int,int> list, int weight){
    this->items = list;
    this->max_weight = weight;

    //declaring size of matrix in constructor, class variable array keeps reference of the dynamically allocated matrix
    array = new int*[list.size()+1];       //if you declare int** you will create a local variable
    for(int i = 0; i < weight+1; i++){     //+1 to account for 0-max_weight row's
        array[i] = new int[weight+1];       
    }

    //intializing first row to be possible weights (0 - max_weight)
    for(int i = 0; i < weight+1; i++){
        array[0][i] = i;
    }
}

//returns the item's which will give most value for weight limit 
std::vector<std::pair<int,int>> bestChoice::findChoices(){
    std::vector<std::pair<int,int>> result;     
    std::map<int,int>::iterator current_item = items.begin();
    int row = 1;
   
    //each row will be assigned to one item in the map {weight, value}
    while(current_item != items.end()){
        for(int col = 0; col < max_weight+1; col++){    
            //first row we choose to either pick up or leave the item based on weight limit
            if(row == 1){
                if(current_item->second > array[0][col]){
                    array[1][col] = 0;
                }else{
                    array[1][col] = current_item->second;
                }
            }else{
                //if our current item's weight is heavier than our weight limit we bring down the best value from previous row
                if(current_item->first > array[0][col]){
                    array[row][col] = array[row-1][col];
                }else{
                    //each element will contain the best value for the corresponding weight and item
                    //we compare current items value with best remaining weight's value in previous row, to current weight limit in previous row
                    int value = max(current_item->second + array[row-1][col - current_item->first], array[row-1][col]);
                    array[row][col] = value;
                }
            }
        }
        row++;
        current_item++; //moves to next item in map
    }

    //set position to last element in matrix
    row = items.size();
    int col = max_weight;
    current_item = items.end(); //end sets iterator to past-the-end element in the map (null termination)
    current_item--;             //sets to last element in map


    while(array[row][col] != 0){ 
        //if previous row has same value as current row, the row's item is not part of solution  
        if(array[row][col] == array[row-1][col]){
            row--;
            current_item--;
        }else{
            std::pair<int,int> temp = {current_item->first, current_item->second};
            result.push_back(temp);
            //set postition for next row (item)
            //we basically subtract our total max weight, with the item we selected to see the next possible items
            col = col - current_item->first;  
            row--;
            current_item--;
        }
    }

    return result;
}


//for helper function we need to pass the instance into the function, to access the instance variables 
void print(std::vector<std::pair<int,int>> printable, bestChoice &instance){
    std::cout << "items that will ensure best value for weight the limit " << instance.max_weight << " are: " << std::endl;
    std::cout << "{Weight, Value}" << std::endl;
    //prints the pairs (similar to tuples in python)
    for(int i = 0; i < printable.size();i++){
        std::cout << "{" << printable[i].first << ", " << printable[i].second << "}" << std::endl;
    }
}



int main(){

    std::map<int,int> set1 = {
        //first pair is weight second is value
        {1,1},{3,4},{4,5},{5,7} 
    };

    bestChoice firstSet(set1,7);
    std::vector<std::pair<int,int>> find = firstSet.findChoices();
    print(find, firstSet);
    
    return 0;
}