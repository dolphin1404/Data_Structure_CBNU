
#include <stdio.h>
#include <stdlib.h>

// 2021039002 이규민

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
} headNode;

// Function to insert a node at the beginning of the list
int insertNode(headNode* h, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // Failed to allocate memory
    }
    newNode->data = key;
    newNode->next = h->head;
    h->head = newNode;
    return 1; // Node inserted successfully
}

// Function to insert a node at the end of the list
int insertLast(headNode* h, int key) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return 0; // Failed to allocate memory
    }
    newNode->data = key;
    newNode->next = NULL;
    if (h->head == NULL) {
        h->head = newNode;
    } else {
        Node* current = h->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    return 1; // Node inserted successfully
}

// Function to delete the first node of the list
int deleteFirst(headNode* h) {
    if (h->head == NULL) {
        return 0; // List is empty
    }
    Node* temp = h->head;
    h->head = h->head->next;
    free(temp);
    return 1; // Node deleted successfully
}

// Function to delete a specific node from the list
int deleteNode(headNode* h, int key) {
    if (h->head == NULL) {
        return 0; // List is empty
    }
    Node* current = h->head;
    Node* prev = NULL;
    while (current != NULL && current->data != key) {
        prev = current;
        current = current->next;
    }
    if (current == NULL) {
        return 0; // Node not found
    }
    if (prev == NULL) {
        h->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current);
    return 1; // Node deleted successfully
}

// Function to delete the last node of the list
int deleteLast(headNode* h) {
    if (h->head == NULL) {
        return 0; // List is empty
    }
    if (h->head->next == NULL) {
        free(h->head);
        h->head = NULL;
        return 1; // Node deleted successfully
    }
    Node* current = h->head;
    Node* prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    prev->next = NULL;
    free(current);
    return 1; // Node deleted successfully
}

// Function to invert the order of the list
int invertList(headNode* h) {
    Node* prev = NULL;
    Node* current = h->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    h->head = prev;
    return 1; // List inverted successfully
}

int main() {
    headNode list;
    list.head = NULL;

    // Test the functions
    insertNode(&list, 10);
    insertNode(&list, 20);
    insertNode(&list, 30);
    insertLast(&list, 40);
    deleteFirst(&list);
    deleteNode(&list, 20);
    deleteLast(&list);
    invertList(&list);

    // Print the list
    Node* current = list.head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");

    return 0;
}
