#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node structure
typedef struct Node{
    int index;
    int value;
    struct Node* previousNode;
    struct Node* nextNode;
} Node;

// Linked list structure that consist of nodes.
typedef struct LinkedList {
    Node *firstNode;
    Node *lastNode;
    Node *currentNode;
    int total;
} LinkedList;

void AddNode(LinkedList *linkedList, int inputValue)
{
    // Create a new node and assign values. The pointers should be null
    Node *tempNode = malloc(sizeof(struct Node));
    tempNode->index = linkedList->total;
    tempNode->value = inputValue;
    tempNode->nextNode = NULL;
    tempNode->previousNode = NULL;

    // Increase the total.
    linkedList->total = linkedList->total + 1;

    if(linkedList->firstNode == NULL)
    {
        linkedList->firstNode = tempNode;
        linkedList->lastNode = tempNode;
        linkedList->currentNode = tempNode;
        return;
    }

    // Insert to end of list.
    linkedList->lastNode->nextNode = tempNode;
    tempNode->previousNode = linkedList->lastNode;
    linkedList->lastNode = tempNode;
}

// Function to print the linked list
void PrintList(LinkedList *linkedList, int totalIndex)
{
    // Temp node to hold the first node.
    Node* temp = linkedList->firstNode;
    // While the temp node isn't null print it.
    while(temp != NULL)
    {
        printf("%d", temp->value);
        temp = temp->nextNode;
    }
    printf("\n");
}

Node* PrintPreviousNode(Node *currentNode)
{
    if(currentNode->previousNode == NULL)
    {
        printf("There are no previous nodes\n");
        return currentNode;
    }
    printf("%i\n", currentNode->previousNode->value);
    return currentNode->previousNode;
}
Node* PrintNextNode(Node *currentNode)
{
    if(currentNode->nextNode == NULL)
    {
        printf("There are no more nodes\n");
        return currentNode;
    }
    printf("%i\n", currentNode->nextNode->value);
    return currentNode->nextNode;
}

void FreeList(LinkedList *list) {
    struct Node *ptr = list->firstNode;
    struct Node *temp;
    while(ptr != NULL) {
        temp = ptr->nextNode;
        free(ptr);
        ptr=temp;
    }
    free(ptr);
    free(list);
}

int main() 
{
    // Construct the first node of the linked list.
    // Allocate space for the new Linked List.
    LinkedList *linkedList = malloc(sizeof(struct LinkedList));
    linkedList->firstNode = NULL;
    linkedList->currentNode = NULL;
    linkedList->lastNode = NULL;
    linkedList->total = 0;

    // Add a new node.
    AddNode(linkedList, 1);
    AddNode(linkedList, 2);
    AddNode(linkedList, 5);
    AddNode(linkedList, 3);
    // Print the linked list. This is where the error is happening because the 'nextNode' is pointing in the wrong place.
    PrintList(linkedList, linkedList->total);

    bool breakValue = false;
    char input = 0;
    printf("\n%i\n", linkedList->currentNode->value);
    while(!breakValue)
    {
        printf("Would you like to print the next or previous node.\nNext: n\nPrevious: p\nQuit: q\n");
        scanf(" %c", &input);
        printf("%c: ", input);
        switch(input)
        {
            case 'p':
                input = '\0';
                linkedList->currentNode = PrintPreviousNode(linkedList->currentNode);
                break;
            case 'n':
                input = '\0';
                linkedList->currentNode = PrintNextNode(linkedList->currentNode);
                break;
            case 'q':
                input = '\0';
                printf("Closing Aplication...\n\n");
                FreeList(linkedList);
                breakValue = true;
                break;
            default:
                input = '\0';
                printf("invalid input\n\n");
                break;
        }
    }
    return 0;
}
