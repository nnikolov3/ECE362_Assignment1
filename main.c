/* Nikolay Nikolov
 * ECE 362
 * Assignment 1
 * Proffessor: Tom Schubert
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXC 50
#define DELIM "\t\r\n\a"

// Struct for holding the data 
struct node{

    char  buffer[MAXC];
    struct node *next;
    struct node *prev;
} info;


//Prototypes for the pointers
struct node *insert(char *buffer);// Pointer for insert
struct node *root; // Declare a pointer to first node
struct node *tail;
struct node *current;


//Prototype functions
void history();
int  delete();
int getlength();
void tokenz(char *buffer);
void compare(char *buffer);
void rmcrlf (char *s);
int loop();


// Main
// It just holds a loop

int main (){

    loop ();

    return 0;

}



// An infinite DO - While loop 
int loop(){

    int length; // Holds the length of the list
    int i; // For counting stuff
    char buffer[MAXC];//Input from user is stored
    int counter = 1;// Initializing the counter at 1

    root = NULL;//list is empty
    tail = NULL;
    printf("\e[1;1H\e[2J"); // Clear the screen 

    do{
           
            if (counter > 5) // check if there are more than 5 elements 
                counter = 1; // then reset the counter to 1
            
            printf("[%d]>",counter);// display line number
            counter ++;

            if (!fgets(buffer, MAXC, stdin)){ // get input from the line
                fprintf(stderr, "error:invalid input. \n");

                return 1;
            }

            rmcrlf (buffer);// remove white trainling space form input
            insert (buffer);// insert a node
            length = getlength();// check the length

            if (length > 6){// if the length is 5 then delete the last not from the list
                // Delete TAIL node of a circular doubly linked list
                delete();// delete the first node that was inserted ( root )



            }
            compare (buffer); // the fucntion where all special commands gets carried

    } while(1);
}



int delete(){// Fuction to delete the root ( first element of the list)

    if (root == NULL) return 0; // check if there is nothing

    struct node *temp = root;// temp node

    struct node *current = root;// node current

    while (current ->next != root)// traverse to the first element of the list
    {
        temp = current;
        current = current -> next;
    }

    // delete the node and free memory
    tail -> next = root;
    tail = temp ;
    root -> prev = tail;

    free (current);
}      


    // this function simply removes the white space from the user input

void rmcrlf (char *s){

    if(!s || !*s) return;
    for (; *s && *s != '\n';s++){}
    *s = 0;

}


// The function where all the special commands get performed 

void compare (char *buffer){


// Initialize the pointers and variable to perform the comparisons
    char *token; 
    char ex = '!';
    char ext[5]   ="exit";
    char hist[8] ="history";
    char parse[8]   ="parse";
    int result;
    int length;

    // perfom a hard copy because strtok modifies the orignal input

    char buf[50];
    (void)strncpy(buf,buffer,sizeof(buf)-1);
    buf[sizeof(buf)-1]='\0';

    // converstions to get the first element of the array in the input
    char s=buffer[0];
    char num =buffer[1];
    char b=s;
    char n=num;
    int i;
    int val = atoi(&num);//convert the second element to a numerical


    token = strtok (buf," "); // Get the first word of the input and check for conditions


    // Here it checks to see if the first element of the user input is ("!")
    // IF this is true then checks the second element to see if it is a number

    //------------------------------------------------------------------------
    if (b == '!') 
    {
        if (isdigit (n) == 0)// then check if the second character is a number
            printf("\t >  Error: !+number \n");

        else{

            if ( val > 5){// Checks if the input number is larger than 5

                printf("\t >  Type a num smaller than 5 !");

            }

            else 
            {
                length = getlength(); // Gets the length of the array

                if (length < val) // If the input value is larger than the number of elements
                    printf("\t > Error");

                if (root == NULL){//If the list is empty
                    printf("\t > Empty");

                }else 
                {

                    struct node *current = tail;// node current 

                    for (i = 1; i<n;i++){ // Traverse to the value of element specified

                        current = current ->prev;

                    }

                    printf("\t >) \" %s\" \n", current -> buffer);// Print the element

                }

            }
        }
    }

//-------------------------------------------------------------------------

    // Check if the first elemement of the user input is parse followed by " "

    result = strcmp (token, parse) ;
    if (result == 0 )
    {
        tokenz(buffer); // call the fuction to tokenize
    }

//----------------------------------------------------------------------


    // Check if the user typed "exit"
    
    result = strcmp (token,ext);
    if (result == 0 ){

        exit(EXIT_SUCCESS);
    }


// ------------------------------------------------------------------------

    //Check if the user typed "history"
    result = strcmp (token, hist);
    if (result == 0 ) {

        history();
    }

}
//-----------------------------------------------------------------------


void tokenz(char *buffer){  // The fuction to tokenize the string  



    // Initialize the pointers

    char * str_ptr = NULL;
    int num_tokens = 0;
    char ** loc_token = NULL;
    int i;

    // Create an array of arrays 

    for ( str_ptr = strtok (buffer, " ");
            NULL != str_ptr;
            str_ptr = strtok (NULL," ")){

        // Array of arrays 
        loc_token = (char **)realloc (loc_token,(sizeof(char*) * (num_tokens+1)));

        // If the array is empty
        if (NULL == loc_token){
            fprintf(stderr, "Error:Failed to allocate enough memory! \n");

            exit(EXIT_FAILURE) ;

        }

        
        loc_token[num_tokens] =strdup (str_ptr);
        num_tokens ++;

    }

    // Print the tokenized values
    for (i = 0; i <num_tokens ; ++i) {

        printf ( "\t %d > \"%s\"\n",i,loc_token[i]);

    }


}

//------------------------------------------------------------------------
//The function that inserts 
//It is a doubly circular linked list


struct node *insert (char *buffer)// insert a node at tail of a circular DLL
{
    struct node *newNode = malloc (sizeof *newNode); // Create a new node

    strcpy (newNode -> buffer, buffer); // put input into the node
    newNode ->next = newNode; // add to the list and connect
    newNode ->prev = newNode;

    if (root == NULL) // If there is one node , it points to itself
    {
        root = newNode;
        tail = newNode;

    }

    else // If there are more elements then add to the tail ( at the end) 
    {
        newNode -> next = root;
        newNode -> prev = tail;
        root -> prev = newNode;
        tail ->next = newNode;
        root = newNode;

    }

}

//----------------------------------------------------------------------

// The fuction that will read the history to the use

void history() {//print reverse order in circular doubly linked list


    // if the history is empty
    if(root == NULL){
        printf("No history");

        return ; // if root is NULL
    }

    if(tail == NULL) return ;// if tail is NULL


    struct node *current = tail;// current points to the last element

    do 
    {
        printf("\t >) \" %s\" \n", current -> buffer);// Print to the console
        current = current ->prev;// traverse to the next

    } while (current != tail);


}

//---------------------------------------------------------------


// Determine the number of nodes in circular doubly linked list

int getlength()

{
    if (root == NULL) return 0; // If there are not any elements

    int count = 1;

    struct node *current = root;

    do 
    {
        count ++; 
        current = current -> next;

    } while (current != root);

    return count; // return the count to be used from the main

}







