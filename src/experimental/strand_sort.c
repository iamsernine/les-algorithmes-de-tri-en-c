#include "../../include/sort_algorithms.h"
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

static Node* create_node(int value) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = value;
    node->next = NULL;
    return node;
}

static void add_node(Node** head, int value) {
    Node* new_node = create_node(value);
    
    if (*head == NULL) {
        *head = new_node;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

static int remove_node(Node** head) {
    if (*head == NULL) return -1;
    
    Node* temp = *head;
    int value = temp->value;
    *head = (*head)->next;
    free(temp);
    return value;
}

static void strand_sort_recursive(int arr[], int n, Node** result) {
    if (n == 0) return;
    
    Node* sublist = create_node(arr[0]);
    int sublist_size = 1;
    
    // Créer la première sous-liste
    for (int i = 1; i < n; i++) {
        if (arr[i] >= sublist->value) {
            add_node(&sublist, arr[i]);
            sublist_size++;
        }
    }
    
    // Fusionner avec le résultat
    Node* merged = NULL;
    Node* result_ptr = *result;
    Node* sublist_ptr = sublist;
    
    while (result_ptr != NULL && sublist_ptr != NULL) {
        if (result_ptr->value <= sublist_ptr->value) {
            add_node(&merged, result_ptr->value);
            result_ptr = result_ptr->next;
        } else {
            add_node(&merged, sublist_ptr->value);
            sublist_ptr = sublist_ptr->next;
        }
    }
    
    while (result_ptr != NULL) {
        add_node(&merged, result_ptr->value);
        result_ptr = result_ptr->next;
    }
    
    while (sublist_ptr != NULL) {
        add_node(&merged, sublist_ptr->value);
        sublist_ptr = sublist_ptr->next;
    }
    
    // Libérer l'ancien résultat
    while (*result != NULL) {
        Node* temp = *result;
        *result = (*result)->next;
        free(temp);
    }
    
    *result = merged;
    
    // Créer un nouveau tableau avec les éléments restants
    int remaining[n - sublist_size];
    int index = 0;
    
    for (int i = 0; i < n; i++) {
        int found = 0;
        Node* ptr = sublist;
        
        while (ptr != NULL) {
            if (arr[i] == ptr->value) {
                found = 1;
                break;
            }
            ptr = ptr->next;
        }
        
        if (!found) {
            remaining[index++] = arr[i];
        }
    }
    
    // Libérer la sous-liste
    while (sublist != NULL) {
        Node* temp = sublist;
        sublist = sublist->next;
        free(temp);
    }
    
    strand_sort_recursive(remaining, n - sublist_size, result);
}

void strand_sort_wrapper(int arr[], int n) {
    Node* result = NULL;
    strand_sort_recursive(arr, n, &result);
    
    int index = 0;
    while (result != NULL) {
        arr[index++] = remove_node(&result);
    }
}