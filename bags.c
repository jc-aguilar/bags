/*
 * University of Central Florida 
 * COP 3502C - Fall 2018 
 * Author: Jose Aguilar 
 */ 
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// structs
typedef struct Bag
{
	int cost;
	int weight;
	char items[20];
	struct Bag* next;
}Bag;

typedef struct Queue{
	Bag* headPtr;
	Bag* tailPtr;
}Queue;

// prototypes 
void print(Bag*);
void leaveABag(Bag* []);
void buyABag(Bag* []);
Bag* push(Bag*);
Bag* pop(Bag*);
Queue* deq(Queue*);
Queue* enq(Queue* q, Bag*);

int main(void)
{
	Bag* locations[1001];
	int userChoice = -2;
	
	// set all elements in Bag array to null
	for (int i = 0; i < 1001; i++)
		locations[i] = NULL;
	
	while (userChoice != 0)
	{
		scanf("%d", &userChoice);
		
		if (userChoice == -1)
		{
			buyABag(locations);
		}
		
		if (userChoice == 1)
		{
			leaveABag(locations);
		}
	}// end while loop for user choice 
	
	return EXIT_SUCCESS;
}

void leaveABag(Bag* locations[1001])
{
	int index, numBags;
	
	scanf("%d", &index);
	
	if(index > 1000)
	{
		printf("0\n");
		return;
	}
	
	scanf("%d", &numBags);
	
	// push the bags into the locations array
	for (int i = 0; i < numBags; i++)
		locations[index] = push(locations[index]);
}

void buyABag(Bag* locations[1001])
{
	Queue* q;
	int index, cash, capacity, totalSpent = 0, totalWeight = 0;
	
	q = (Queue*) calloc(1, sizeof(Queue));
	q->headPtr = NULL;
	q->tailPtr = NULL;
	
	scanf("%d", &index);
	scanf("%d", &cash);
	scanf("%d", &capacity);
	
	// check if there is a bag in the requested location
	if (locations[index] == NULL)
	{
		printf("0\n");
		return;
	}
	
	if(capacity >= 100000 || index > 1000)
	{
		printf("0\n");
		return;
	}
	
	while (locations[index] != NULL && cash >= locations[index]->cost && capacity >= locations[index]->weight)
	{
		// calculate total ammount spent and update available cash
		totalSpent = totalSpent + locations[index]->cost;
		cash = cash - locations[index]->cost;
		// update the carrying weight and capacity 
		totalWeight = totalWeight + locations[index]->weight;
		capacity = capacity - locations[index]->weight;
		// send to queue for printing
		q = enq(q, locations[index]);
		// pop the bag bought
		locations[index] = pop(locations[index]); 
	}
	
	printf("%d ", totalSpent);
	
	print(q->headPtr);
	q =deq(q);
	
	free(q);
}

Bag* push(Bag* oldHead)
{
    // Create the new bag
    Bag* newHead = (Bag*) calloc(1, sizeof(Bag));
    
	scanf("%d", &newHead->cost);
	scanf("%d", &newHead->weight);
	scanf("%s", newHead->items);
	// link new bag to old head 
    newHead->next = oldHead;
    
    return newHead;
}

Bag* pop(Bag* head)
{
    if (head == NULL)
		return head;
	
    Bag* newHead = head->next;
    
    // Free the old memory
    free(head);
    head = NULL;
    
    // Return the new head of the linked list to top of the stack
    return newHead;
}

Queue* deq(Queue* q)
{
	if (q->headPtr == NULL)
		return q;
	
	// storing old head for removal
	Bag* head = q->headPtr;
	
	// storing new head
	Bag* newHead = q->headPtr->next;
	
	// free old head
	free(head);
	head = NULL;
	
	// update queue head pointer
	q->headPtr = newHead;
	
	// check if queue is empty and update
	if (q->headPtr == NULL)
		q->tailPtr = NULL;
	// return new head of linked list
	return q;
}

Queue* enq(Queue* q, Bag* node)
{
	// create new Node
	Bag* newTail = (Bag*) calloc(1, sizeof(Bag));
	
	if (q == NULL)
		return q;
	// copy the items into the tail of the queue 
	strcpy(newTail->items, node->items);
	newTail->next = NULL;
	
	if (q->tailPtr != NULL)
		q->tailPtr->next = newTail;
	
	q->tailPtr = newTail;
	
	if(q->headPtr == NULL)
		q->headPtr = newTail;
	
	return q;
}

void print(Bag* start)
{
    while (start != NULL)
    {
        printf("%s ", start->items);
        start = start->next;
    }
	printf("\n");
}