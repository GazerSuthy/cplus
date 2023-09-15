#include<iostream>
#include<string>

//can't lie this problem was actually fun cuh! :D

//-----------------------description-----------------------
// Create two functions to encode and then decode a string using the Rail Fence Cipher. This cipher is used to encode a string by placing each character successively in a diagonal along a set of "rails". First start off moving diagonally and down. When you reach the bottom, reverse direction and move diagonally and up until you reach the top rail. Continue until you reach the end of the string. Each "rail" is then read left to right to derive the encoded string.
// For example, the string "WEAREDISCOVEREDFLEEATONCE" could be represented in a three rail system as follows:
// W       E       C       R       L       T       E
//   E   R   D   S   O   E   E   F   E   A   O   C  
//     A       I       V       D       E       N    
// The encoded string would be:
// WECRLTEERDSOEEFEAOCAIVDEN

//[Encoding Algorighm]
/*        how pattern will look if we plot the rails into a  two dimensional grid
               0    [   W E   C   R   l   T   E             -key patterns to notice
               1        E R D S O E E F E A O C             -every even column has a space at the last row except for first column
               2        A   I   V   D   E   N   ]           -every odd column has a space at the first row except for first column
                                                            -odd rows are top to bottom  in order
                                                            -even rows are bottom to top in order (reversed)

                i love the challenge :D
*/

//[decoding Alorighm]
/*
               0     [  W E   C   R   l   T   E             -top row has a space every even column except zero
               1        E R D S O E E F E A O C             -bottom row has a space every odd column
               2        A   I   V   D   E   N   ]           -middle rows do not have any spaces


*/


std::string encode_rail_fence_cipher(const std::string &str, int n) {
    std::string result = "";
    int length = 0;

    if(str == ""){          //empty string case
        return result;
    }

    //rough estimate to find aprox length needed for 2D array
    for(int i = 2; i < str.length(); i+= (n-1)){
        length += 1;
    }

    std::string plot [length+1][n];           
    
    int row = 0;
    int col = 0;
   
    //this for loop will map out all the characters through the 2D array
    for(int i = 0; i < str.length(); i++){                    
        
        plot[col][row] = str[i];       

        //row manupliation if even it will go down the column else it will go up the column
        if(col % 2 == 0){                  
            row++;
        }else{
            row--;
        }

        //column manuplation: goes to the next column when there is an out of array bounds scenrio (either index is -1 or index = n)
        //pattern: one way to look at it is when you move to the next column, you start from the previous row index and that new index is a blank element ("0")
        if(row == n){                
            col++;
            //when moving to the next column and the previous column is an even, the row will start at the end 
            row = n-1;
            //"0" means that this index in the 2D array is to be skipped when finding rails
            plot[col][row] = "0";
            row--;                   
        }
        //odd
        if(row < 0){
            col++;
            //when moving to the next column and the previous column is an odd, the row will start at the beginning 
            row = 0;
            //"0" means that this index in the 2D array is to be skipped when finding rails
            plot[col][row] = "0";
            row++;
        }
    }

    //personal comment:
    //visualize arrays as a single horizonal array (first box), and each index has a vertical array component (second box)

    int count = 0;
    //while loop basically appends characters horizonally through each rail, and will skip blanch index's "0"
    while(count < n){
        for(int i = 0; i < length+1;i++){
            if(plot[i][count] != "0"){
                result += plot[i][count];
            }
        }
        count++;
    }
    
  return result;
}

std::string decode_rail_fence_cipher(const std::string &str, int n) {
    //both the 2D arrays for the encode and decode are same, 
    //once I recreate the 2D array in the decode function I reverse the algorithm used to encoded the string to get oringal

    std::string result = "";
    int length = 0;

    if(str == ""){          //empty string case
        return result;
    }

    //rough estimate to find aprox length needed for 2D array
    for(int i = 2; i < str.length(); i+= (n-1)){
        length += 1;
    }

    //since were going across instead of vertical, I switched the dimensions for personal preference :)
    std::string plot [n][length+1];

    
    
    int row = 0;
    int col = 0;

    //algorithm used to recreate the 2D array 
    for(int i = 0; i < str.length(); i++){
        //top row 
        if(row == 0){
            plot[row][col] = str[i];
            col++;
            //if column is even and is not on the last column
            if(col % 2 == 0 && col != length){
                //acts as an empty index
                plot[row][col] = "0";
                col++;
            }
        }
        //bottom row
        if(row == n-1){
            plot[row][col] = str[i];
            col++;
            //if column is odd and is not on the last column
            if(col % 2 != 0 && col != length){
                //acts as empty index
                plot[row][col] = "0";
                col++;
            }
        }

        //middle row
        if(row != 0 && row != n-1){
            plot[row][col] = str[i];
            col++;
        }

        //manupulating rows
        if(col == length){
            row++;
            col = 0;
        }

    }

    //using the same algorithm used to encode to get back the original string
    row = 0;
    col = 0;
    for(int i = 0; i < str.length(); i++){  //str length because we know that the result has to equal the same length

        result += plot[row][col];

        //row manupliation if even it will go down the column else it will go up the column
        if(col % 2 == 0){                  
            row++;
        }else{
            row--;
        }

        //column manuplation: goes to the next column when there is an out of array bounds scenrio (either index is -1 or index = n)
        //pattern: one way to look at it is when you move to the next column, you start from the previous row index and that new index is a blank element ("0")
        if(row == n){                
            col++;
            //when moving to the next column and the previous column is an even, the row will start at the end 
            row = n-1;
            //"0" means that this index in the 2D array is to be skipped when finding rails
            if(plot[row][col] == "0"){      //if the index is a blank space, skip it
                row--;
            }                   
        }
        //odd
        if(row < 0){
            col++;
            //when moving to the next column and the previous column is an odd, the row will start at the beginning 
            row = 0;
            //"0" means that this index in the 2D array is to be skipped when finding rails
            if(plot[row][col] == "0"){
                row++;
            }
        }
    }
    return result;
}


int main(){
    std::string hee = encode_rail_fence_cipher("WEAREDISCOVEREDFLEEATONCE", 3);
    std::string cuh = decode_rail_fence_cipher("WECRLTEERDSOEEFEAOCAIVDEN", 3);
    std::cout << cuh << std::endl;
    std::cout << hee << std::endl;
    return 0;
}