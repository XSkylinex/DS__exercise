//Alex
//Data Structure


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 50

//Structs
typedef struct TorBST
{
    int _data;

    struct TorBST* _next;

    struct TorBST* _left;
    struct TorBST* _right;

}torBST;

typedef struct Tor
{
    int _data;
    struct Tor *_next;
}tor;

typedef struct InsertionSortStruct
{
    int _data;
    struct InsertionSortStruct* _next;

}insertionSortStruct;

//Global Functions
struct TorBST* _head = NULL;
struct TorBST globalTor;
struct TorBST *_tail = NULL;
struct Tor *front = NULL;
struct Tor*rear = NULL;



//Functions
void queue();
void insert(int data);
int dequeue();
void enqueue(int number);
void binaryTreeFunc();
torBST *newBST(int data);
torBST* insertToBST(torBST* BST, int data);
int isEmpty();
void sortedInsert(insertionSortStruct** funcHead, insertionSortStruct* newTor);
void insertionSort(insertionSortStruct **funcHead);
void delete();
int getListLength();
void push(insertionSortStruct** funcHead, int dataFunc);
void printFromTree(torBST *root);

int main(int argc, char *argv[]) {
    int choose = 0, space = 1, number;
    int i;



    printf("Data Structure exercise ,choose what you want to test:\n");

    printf("generate random number between 1 to 1000 in\n");
    srand(time(NULL));
    printf("Print 50 numbers :\n");
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        number = rand() % 1000 + 1; // generate random number between 1 to 1000 in " c "
        insert(number);
        printf("%d %s", number, " ");
        if (i == 10 * space) {
            printf("\n");
            space++;
        }
    }
    printf("\n");

    printf("to Queue using Linked List and Insertion sort press 1.\n");
    printf("to Queue using Linked List and Binary search tree press 2.\n");
    printf("your choose is?: ");
    do {
        scanf("%d", &choose);
        if (choose > 3 || choose < 0) {
            printf("choose again: ");

        }
    } while (choose != 1 && choose != 2);


    switch (choose) {
        case 1:
            queue();
            break;
        case 2:
            binaryTreeFunc();
            break;

        default:
            printf("Fatal Error!!!");
            break;
    }

    return 0;
}

void queue(){
    int i,temp,space = 1;
    int linkedList = getListLength();
    int *_n = (int*)malloc(linkedList*sizeof(int));
    insertionSortStruct* sort_struct = NULL;

    for (i = 0; i < linkedList;i++) {
        push(&sort_struct,_head->_data);
        _head = _head->_next;
    }

    insertionSort(&sort_struct);

    for (i = linkedList; i != 0; i--) {
        temp = sort_struct->_data;
        sort_struct = sort_struct->_next;
        _n[i] = temp;
    }
    for (i = 0; i < linkedList; i++) {
        enqueue(_n[i+1]);
    }
    printf("\n");

    printf("Now dequeue from functions \n");

    for (i = 0; i < linkedList; i++) {
        printf("%d   ",dequeue());
        if (i == 10 * space) {
            printf("\n");
            space++;
        }
    }

    printf("\n");
    printf("Done\n");
}

void insert(int data){
    torBST *newTorBST = (torBST*)malloc(sizeof(torBST));
    if(!newTorBST){
        printf("Error");
        exit(-1);

    }
    newTorBST->_data = data;
    newTorBST->_next = newTorBST;

    if (_head == NULL){
        _head = newTorBST;
        _tail = newTorBST;
    }else{
        newTorBST->_next = _head;
        _tail->_next = newTorBST;
        _head = newTorBST;
    }

}

void delete(){
    if (_head == NULL){
        return;
    }
    torBST *temp = _head;
    _tail->_next = _head->_next;
    _head = _head->_next;

    free(temp);
}

int dequeue(){
    tor *tempTorFunc;
    int temp = 0;
    if (front == NULL) {
        printf("Queue is Empty. Unable to perform dequeue\n");
    }else{
        tempTorFunc = front;
        temp = front->_data;
        front = front->_next;
        if (front == NULL){
            rear = NULL;
        }
        free(tempTorFunc);
    }

    return temp;

}

void enqueue(int number){
    tor *newTor = (tor*)malloc(sizeof(tor));
    newTor->_data = number;
    newTor->_next = NULL;
    if (front == NULL && rear == NULL){
        front = rear = newTor;

    }else{
        rear->_next = newTor;
        rear = newTor;
    }
}

void binaryTreeFunc(){
    printf("\n");
    int i;
    int linkedList = getListLength();

    torBST *root = NULL;
    for(i = 0 ; i < linkedList ; i++){
        root = insertToBST(root, _head->_data);
        _head = _head->_next;
    }
    printFromTree(root);
    printf("\n");
    printf("Done \n");
}

torBST *newBST(int data){
    torBST *tempBST = (torBST*)malloc(sizeof(torBST));
    tempBST->_data = data;
    tempBST->_left = tempBST->_right = NULL;
    return tempBST;
}

torBST* insertToBST(torBST* BST, int data){
    if (BST == NULL) {
        return newBST(data);
    }
    if (data < BST->_data) {
        BST->_left = insertToBST(BST->_left, data);
    }
    else if (data > BST->_data) {
        BST->_right = insertToBST(BST->_right, data);
    }

    return BST;
}

int isEmpty() {
    return _head == NULL;
}

void sortedInsert(insertionSortStruct** funcHead, insertionSortStruct* newTor){
    torBST* current;
    if (*funcHead == NULL || (*funcHead)->_data >= newTor->_data){
        newTor->_next = *funcHead;
        *funcHead = newTor;
    }else{
        current = *funcHead;
        while (current->_next != NULL && current->_next->_data < newTor->_data){
            current = current->_next;
        }
        newTor->_next = current->_next;
        current->_next = newTor;
    }
}

void insertionSort(insertionSortStruct **funcHead){
    insertionSortStruct *sorted = NULL;
    insertionSortStruct *current = *funcHead;
    while (current != NULL){

        insertionSortStruct *next = current->_next;
        sortedInsert(&sorted, current);

        current = next;
    }

    *funcHead = sorted;
}

int getListLength(){
    if (_head == NULL){
        return 0;
    }

    int count = 0;
    torBST *current = _head;

    do{
        count++;
        current = current->_next;
    } while (current != _head);

    return count;
}

void push(insertionSortStruct** funcHead, int dataFunc){
    insertionSortStruct* sort_struct = (insertionSortStruct*)malloc(sizeof(insertionSortStruct));
    sort_struct->_data = dataFunc;
    sort_struct->_next = (*funcHead);
    (*funcHead) = sort_struct;
}

void printFromTree(torBST *root){
    if (root != NULL){
        printFromTree(root->_right);
        printf("%d ", root->_data);
        printFromTree(root->_left);

    }
}