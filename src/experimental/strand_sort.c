#include "../../include/sort_algorithms.h"
#include <stdlib.h>
#include <stdbool.h> // For bool type

// Structure for a linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
static Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        // Handle memory allocation error
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to convert an array to a linked list
static Node* arrayToList(int arr[], int n) {
    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 0; i < n; i++) {
        Node* newNode = createNode(arr[i]);
        if (head == NULL) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    return head;
}

// Function to convert a linked list back to an array and free the list memory
static void listToArray(Node* head, int arr[], int n) {
    Node* current = head;
    int i = 0;
    while (current != NULL && i < n) {
        arr[i++] = current->data;
        Node* temp = current;
        current = current->next;
        free(temp); // Free node memory
    }
}

// Function to merge two sorted linked lists
static Node* mergeSortedLists(Node* list1, Node* list2) {
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;

    Node* result = NULL;
    if (list1->data <= list2->data) {
        result = list1;
        result->next = mergeSortedLists(list1->next, list2);
    } else {
        result = list2;
        result->next = mergeSortedLists(list1, list2->next);
    }
    return result;
}

// Strand Sort function for linked list
static void strandSortList(Node** head_ref) {
    Node* input_list = *head_ref;
    Node* output_list = NULL; // The final sorted list

    while (input_list != NULL) {
        Node* sub_list = NULL; // Current strand
        Node* current_input = input_list;
        Node* prev_input = NULL; // To manage deletions from input_list

        // Move the first element of input_list to sub_list
        sub_list = current_input;
        input_list = current_input->next;
        sub_list->next = NULL; // Detach from input_list

        Node* sub_list_tail = sub_list; // Keep track of sub_list's tail for appending

        current_input = input_list;
        prev_input = NULL;

        // Extract increasing subsequence (strand)
        while (current_input != NULL) {
            if (current_input->data > sub_list_tail->data) {
                // Move current_input to sub_list
                if (prev_input != NULL) {
                    prev_input->next = current_input->next;
                } else {
                    input_list = current_input->next;
                }
                sub_list_tail->next = current_input;
                sub_list_tail = current_input;
                current_input = current_input->next; // Move to next in original input_list
                sub_list_tail->next = NULL; // Detach
            } else {
                // Keep current_input in input_list, move to next
                prev_input = current_input;
                current_input = current_input->next;
            }
        }
        
        // Merge the extracted strand into the output_list
        output_list = mergeSortedLists(output_list, sub_list);
    }
    *head_ref = output_list; // Update the original head to the sorted list
}

// Wrapper function for array-based strand sort
void strand_sort_wrapper(int arr[], int n) {
    if (n <= 1) {
        return;
    }
    Node* head = arrayToList(arr, n);
    strandSortList(&head);
    listToArray(head, arr, n); // listToArray also frees the list nodes
}