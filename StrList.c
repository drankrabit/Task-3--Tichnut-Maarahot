#include "StrList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char* data;
    struct Node* next;
} Node;

struct _StrList {
    Node* head;
    size_t size;
};

StrList* StrList_alloc() {
    StrList* list = (StrList*)malloc(sizeof(StrList));
    if (list != NULL) {
        list->head = NULL;
        list->size = 0;
    }
    return list;
}

void StrList_free(StrList* list) {
    if (list == NULL)
        return;

    // Free each node and its data
    Node* current = list->head;
    while (current != NULL) {
        Node* next = current->next;
        free(current->data);
        free(current);
        current = next;
    }

    free(list);
}

void StrList_insertLast(StrList* list, const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = strdup(data);
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (index < 0 || index > list->size) {
        fprintf(stderr, "Invalid index\n");
        return;
    }

    if (index == 0) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = strdup(data);
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node* current = list->head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        if (newNode == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        newNode->data = strdup(data);
        newNode->next = current->next;
        current->next = newNode;
    }
    list->size++;
}

char* StrList_firstData(const StrList* list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    return list->head->data;
}

void StrList_print(const StrList* list) {
    if (list == NULL || list->head == NULL) {
        printf("List is empty\n");
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

void StrList_printAt(const StrList* list, int index) {
    if (list == NULL || list->head == NULL || index < 0 || index >= list->size) {
        printf("Invalid index or empty list\n");
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    printf("Word at index %d: %s\n", index, current->data);
}

int StrList_printLen(const StrList* list) {
    int len = 0;
    if (list == NULL || list->head == NULL) {
        return len;
    }
    Node* current = list->head;
    while (current != NULL) {
        len += strlen(current->data);
        current = current->next;
    }
    return len;
}

int StrList_count(StrList* list, const char* data) {
    int count = 0;
    if (list == NULL || list->head == NULL) {
        return count;
    }
    Node* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            count++;
        }
        current = current->next;
    }
    return count;
}

void StrList_remove(StrList* list, const char* data) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->data, data) == 0) {
            if (prev == NULL) {
                list->head = current->next;
                free(current->data);
                free(current);
                current = list->head;
            } else {
                prev->next = current->next;
                free(current->data);
                free(current);
                current = prev->next;
            }
            list->size--;
        } else {
            prev = current;
            current = current->next;
        }
    }
}

void StrList_removeAt(StrList* list, int index) {
    if (list == NULL || list->head == NULL || index < 0 || index >= list->size) {
        return;
    }
    Node* current = list->head;
    Node* prev = NULL;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    free(current->data);
    free(current);
    list->size--;
}

StrList* StrList_clone(const StrList* list) {
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    StrList* clone = StrList_alloc();
    Node* current = list->head;
    while (current != NULL) {
        StrList_insertLast(clone, current->data);
        current = current->next;
    }
    return clone;
}

void StrList_reverse(StrList* list) {
    if (list == NULL || list->head == NULL) {
        return;
    }
    Node* prev = NULL;
    Node* current = list->head;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

int compareStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void StrList_sort(StrList* list) {
    if (list == NULL || list->head == NULL || list->size < 2) {
        return;
    }

    Node* current;
    Node* index;
    char* temp;

    for (current = list->head; current->next != NULL; current = current->next) {
        for (index = current->next; index != NULL; index = index->next) {
            if (strcmp(current->data, index->data) > 0) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
        }
    }
}

int StrList_isSorted(StrList* list) {
    if (list == NULL || list->head == NULL) {
        return 1;
    }
    Node* current = list->head;
    while (current->next != NULL) {
        if (strcmp(current->data, current->next->data) > 0) {
            return 0;
        }
        current = current->next;
    }
    return 1;
}

size_t StrList_size(const StrList* list) {
    return (list != NULL) ? list->size : 0;
}