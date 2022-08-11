#include<iostream>
#include<fstream> 
#include<queue>                                     //library for priority queue
#include<string>


using namespace std;

struct Node                                         
{
    //data variables
    
    
    //--------------------------------------------------------
    char data;                                     
    int freq;                                      
    Node* left;                                     
    Node* right;                                    
    int arr[100];                                   
    double abr = 0;                                 
    double divisor = 0;                             
    
    //default constructor for the node
    //--------------------------------------------------------
    Node()
    {
        left = NULL;                                //setting left node as NULL
        right = NULL;                               //setting right node as NULL
        data = ' ';                                 //setting data 
        freq = 0;                                   //setting freq variable to 0
    }

    //Insert function for allocating the values according
    //--------------------------------------------------------
    void Insert(Node* temp, Node* ptr)
    {
        this->left = temp;                          //allocation on left side
        this->right = ptr;                          //allocation on right side
        this->freq = temp->freq + ptr->freq;        //addition of the frequencies after allocation
    }


    //--------------------------------------------------------
    //traverse function for traversing the tree 
    double traverse(Node* temp, int arr[], int size /*string str*/)
    {
        if (temp->right)                                    //if the node of the tree is right
        {
            arr[size] = 0;                                  //the size will become 0
            traverse(temp->right, arr, size + 1);           //traverse the right node data
        }

        if (temp->left)                                     //if the node of the tree is right
        {
            arr[size] = 1;                                  //the size will become 1
            traverse(temp->left, arr, size + 1);            //traverse the left node data
        }

        if (temp->left == NULL && temp->right == NULL)      //if both nodes are empty
        {

            //for the display of Huffman's codes 

            cout << "CHAR  :  " << temp->data << "     |  FREQ  :  " << temp->freq << "  |  HUFFMAN's CODES  : ";
            
            //--------------------------------------------------------
            //formula for calculating abr and length
                                    
            abr += temp->freq * size;                       //(f1*L1 + f2*l2 + ......) calculation
            divisor += temp->freq;                          //length of the file content calculation

            //loop used to display the Huffman's codes in accordance to the characters and their frequency
            for (int i = 0; i < size; i++)                  
            {
                cout << arr[i];                             
            }
            cout << endl;                                  
        }
        return abr / divisor;                               //returning the average bit rate after dividing by the divisor variable
    }

};                                                       



//--------------------------------------------------------

//struct for comparing the frequencies of two nodes

struct GreaterNodeCOMP                                         //struct start
{
    bool operator()(const Node* a, const Node* b) const        //operator overloading to find priority
    {
        return a->freq > b->freq;                              //comparing the two frequencies
    }
};                                                             //struct end


//--------------------------------------------------------------

//for printing out the tree

void depthfirst(Node* tree)                                    
{
    if (tree != NULL)                                          
    {
        cout << tree->data << tree->freq << " --->> ";         //printing tree
        depthfirst(tree->right);                               //recursiving on right subtree
        depthfirst(tree->left);                                //recursiving on left subtree


    }
    else{                                                      //if node is empty (case for leaf nodes)
        cout << "NULL ";                                       //printing NULL
        return;                                                //returning
    }
}


//--------------------------------------------------------------

//Function for Huffman Coding

void Hoffman()
{

    int numberofcharacter = 0;                                  //declaring variable
    string filename;                                            //initializing variable
    cout << "Enter filename : ";                                //asking for input for the filename
    cin >> filename;                                            //entering filename
    fstream file;                                               //creation of fstream class object
    file.open(filename);                                        //opening the file

    if (!file)                                                  //if file not opened
    {

        //display message for file not opening

        cout << "--------------------------------" << endl;
        cout << "      FILE COULDN'T OPEN !!!    " << endl;
        cout << "--------------------------------" << endl;
        return;
    }
    else{                                                       //otherwise

        //display message for file opening

        cout << "--------------------------------" << endl;
        cout << "   FILE LOADED SUCCESSFULLY !!! " << endl;
        cout << "--------------------------------" << endl;
    }

    string c1;                                               
    int i, j, k = 0;                                         
    char a[256] = {};                                           //initializing a character array for the characters
    int fre[256] = { 0 };                                       //initializing an int array for frequency
    char ch;


    //-------------------------------------------------------
    //Character by Character reading of file until end
        //calcuating the frequency of the characters in the file


    cout << "\n\n ::FREQUENCY  CALCULATION::           " << endl;          
    cout << "----------------------------------------\n" << endl;         


    while (!file.eof())                                         //executing a loop for until file ends
    {
        while (file >> ch) {                                    //reading file character by character

            if (ch != ' ' && ch != '\n')                        //if the characters are not a space or going to next line
            {
                a[ch] = ch;                                     //
                fre[ch]++;                                      //frequency adding of that char

            }
        }
    }
    //-------------------------------------------------------

    //priority queue 

    priority_queue<Node, vector<Node*>, GreaterNodeCOMP >queue2;           //priority queue in max heap
    priority_queue<Node, vector<Node*>, GreaterNodeCOMP > optimaltree1;    //priority queue in max heap
    priority_queue<Node, vector<Node*>, GreaterNodeCOMP > optimaltree2;    //priority queue in max heap


    //--------------------------------------------------------




    //using loop to traverse through all 256 characters

    for (int i = 0; i < 256; i++)
    {
        if (fre[i] != 0)                                                   //if any of the character's frequency is not zero
        {
            cout << a[i] << " -->" << fre[i] << endl;                   
            Node* temp = new Node;                                         //allocate node to the heap
            Node* temp2 = new Node;                                        //allocate node to the heap
            temp->data = a[i];                                             //putting in the character from character array in the data of first node
            temp->freq = fre[i];                                           //putting in the frequency from frequency array in the freq of first node

            temp2->data = a[i];                                            
            temp2->freq = fre[i];                                          

            queue2.push(temp);                                             
            optimaltree1.push(temp2);                                      //pushing in p.queues

            numberofcharacter++;                                           
        }
    }

    file.close();                                                          

    // -------------------------------------------------------

    // purpose of function

    for (int i = 0; i < numberofcharacter - 1; i++)
    {
        Node* temp = new Node;                                             //allocating node to the heap
        temp->left = queue2.top();                                         
        queue2.pop();                                                      
        temp->right = queue2.top();                                        
        queue2.pop();                                                      
        temp->freq = temp->left->freq + temp->right->freq;                 

        queue2.push(temp);                                                 //pushing in the queue
    }







    // -------------------------------------------------------
    //Optimal Huffman's tree formation

    cout << "\n----------------------------------------  " << endl;
    cout << "     BUILDING  HUFFMAN's TREE-1             " << endl;
    cout << "------------------------------------------\n" << endl;

    Node* tree = queue2.top();                                              //getting the tree
    depthfirst(tree);                                                       //printing the tree
    cout << endl;                                                           
    cout << endl;                                                           

    int arr[100];                                                          
    int aa = 0;                                                            

    cout << "\n-------------------------------------------------------" << endl;
    double q = queue2.top()->traverse(tree, arr, aa);               //traversing the whole of tree to get ABR
    cout << "-------------------------------------------------------\n\n" << endl;


    cout << "COMPRESSION RATIO : " << 8 / q << endl;                      




    




    cout << "\n\n\n\n";
    //For tree 2

    cout << "\n----------------------------------------  " << endl;
    cout << "     BUILDING  HUFFMAN's TREE-2             " << endl;
    cout << "------------------------------------------\n" << endl;

    int node_count = 0;                                         //initializing var
    while (optimaltree1.size() > 1)                           
    {

        cout << "Node Count: " << node_count << endl;           
        Node* temp_optimal = new Node;                          
        temp_optimal->left = optimaltree1.top();                
        optimaltree1.pop();                                     
        temp_optimal->right = optimaltree1.top();               
        optimaltree1.pop();                                     

        //adding the frequencies of left and right childs

        temp_optimal->freq = temp_optimal->left->freq + temp_optimal->right->freq;

        optimaltree2.push(temp_optimal);                    //pushing in the queue
        node_count++;                                           //incrementing
      
    }
    // -------------------------------------------------------



    //Hoffman(optimaltree2 , node_count+2);
    while (optimaltree2.size() > 1)                             //if the priority queue has 
    {
        Node* temp = new Node;                                  //allocating node to the heap
        temp->left = optimaltree2.top();                       
        optimaltree2.pop();                                    
        temp->right = optimaltree2.top();                       //getting the right child of the node
        optimaltree2.pop();                                    
        temp->freq = temp->left->freq + temp->right->freq;      //adding the frequencies of left and right childs

        optimaltree2.push(temp);                                //pushing in the queue
    }

    // -------------------------------------------------------
    
    
    
    
    Node* tree3 = optimaltree2.top();                           //getting the second tree
    depthfirst(tree3);                                          //printing the second tree

   
    cout << endl;                                               
    cout << endl;                                               

    int arr1[100];                                              
    int bb = 0;                                                 
    cout << "\n-------------------------------------------------------" << endl;
    double q1 = optimaltree2.top()->traverse(tree3, arr1, bb);  //traversing the whole tree to get ABR
    cout << "-------------------------------------------------------\n\n" << endl;

    cout << " COMPRESSION  RATIO : " << 8 / q1 << endl;         //printing compression ratio
    
    
    
    
    
    
    
    
    // -------------------------------------------------------------------------------//
}

int main()                                                     
{
    //displaying message

    cout << "---------------------------------------------\n";
    cout << "         ---DATA COMMPRESSION---             \n";
    cout << "---------------------------------------------\n";


    Hoffman();                                                 


    return 0;                                                   
}