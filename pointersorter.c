//CS214 Systems Programming - Spring 2017

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

//Node struct for implementing linked list
//Each node will hold component string data
typedef struct Node{
	char *strComponent;
	int strLength;
	struct Node *next;
} Node;


Node *addNode(Node *head, char *word, int j);
void printLinkedList(Node *head);




//This function will add a new node to the linked list
//Node will be placed in proper descending alphabetical order during add process
Node *addNode(Node *head, char *strComponentCopy, int strLengthCopy){
	
	if(head->strLength == 0){
		head->strComponent = strComponentCopy;
		head->strLength = strLengthCopy;
		head->next = NULL;
		return head;
	}

	//creates new node and allocates memory of correct size
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->strComponent = strComponentCopy;
	newNode->strLength = strLengthCopy;

	//Position Check #1 : if new Node comes before first in list, adds to front and replace head
	int positionTest = strcmp(newNode->strComponent, head->strComponent);
	if(positionTest < 0){
		newNode->next = head;
		head = newNode;
		return head;
	}

	//creates pointer to represent current position during search
	Node *currNode = head;
	
	//Position Check #2 : Iterates through linked list until correct position is found, adds inbetween appropiate nodes
	while(currNode->next != NULL){
		positionTest = strcmp(newNode->strComponent, currNode->next->strComponent);
		if(positionTest < 0){
			newNode->next = currNode->next;
			currNode->next = newNode;
			return head;
		}
		currNode = currNode->next;
	}
	
	//Position Check #3 : If entire list is searched and new node not added, add to end of the linked list
	currNode->next = newNode;
	newNode->next = NULL;
	
	return head;
}




//This function will print the entire linked list of component strings
void printLinkedList(Node *head){
	if(head->strComponent == NULL)
		return;
	for(head = head; head != NULL; head = head->next)
		printf("%s\n", head->strComponent);
}




//This function will free all memory allocated for the linked list 
void freeList(struct Node* head){
   struct Node* temp;
   while (head != NULL){
       temp = head;
       head = head->next;
       free(temp);
    }

}



int main(int argc, char *argv[]){
	
	//Check that arguments are met and display error message if not
	if(argc != 2){ 
		printf("Error. For proper usage see example below.\n./pointersorter \"inputStr string to be sorted here\"\n");
		return 0;
	}

	char *inputStr = argv[1]; 
	//If only white space is entered, return and print nothing
	int positionTest = strcmp(inputStr, "");
	if(positionTest == 0)
		return 0;
	
	//Check length of input string
	int inputStrLength = strlen(inputStr);

	Node *head = (Node*)malloc(sizeof(Node));
	head->strComponent = NULL;
	head->strLength = 0; 
	head->next = NULL;

	char c;

	//Allocate memory for component string of proper size
	char *word = (char *)malloc(sizeof(char)); 
	
	//Declare int for length and component length 
	int i = 0;
	int k = 0;
	for(i = 0; i <= inputStrLength; i++){
		c = inputStr[i];
		//Check if the char is alphabetical and realloc memory for char 
		if(isalpha(c)){
			word[k] = c; k++; word[k] = '\0';
			word = (char *)realloc(word, (k+1)*sizeof(char));
		}
		else{	
			//If no letters between non alphabetical chars ingore them 
			if(k == 0)
				continue;
			word[k] = '\0';
			//Copy of component string 
			char *strComponentCopy = (char *)malloc(sizeof(strlen(word) + 1));
			strcpy(strComponentCopy, word);
			//add node to the head 
			head = addNode(head, strComponentCopy, k);
			k = 0;
			word = (char *)realloc(word, (k+1)*sizeof(char));
		}
	}
	
	
	//Print thge final sorted list and free all memory
	printLinkedList(head);
	freeList(head);
	return 1;
}





