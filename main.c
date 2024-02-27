#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StrList.c"

int main() {
    StrList* list = StrList_alloc();
    int choice;
    int index;
    char data[100];

    while (choice != '0') {
        printf("\nChoose an option:\n");
        printf("1 - Insert string at end\n");
        printf("2 - Insert string at index\n");
        printf("3 - Print list\n");
        printf("4 - Print list length\n");
        printf("5 - Print string at index\n");
        printf("6 - Print character frequency in list\n");
        printf("7 - Delete string\n");
        printf("8 - Delete string at index\n");
        printf("9 - Reverse list\n");
        printf("10 - Delete entire list\n");
        printf("11 - Sort list\n");
        printf("12 - Check if list is sorted\n");
        printf("0 - Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter strings to insert (separated by spaces, end with 'E'): ");
                while (1) {
                    scanf("%s", data);
                    if (data[0] == 'E')
                        break;
                    StrList_insertLast(list, data);
                }
        }
        else if (choice == 2) {
                printf("Enter index and string to insert: ");
                scanf("%d %s", &index, data);
                StrList_insertAt(list, data, index);
        }
        else if (choice == 3) {
                printf("List contents:\n");
                StrList_print(list);
        }
        else if (choice == 4) {
                printf("Length of the list: %zu\n", StrList_size(list));
        }
        else if (choice == 5) {
                printf("Enter index to print: ");
                scanf("%d", &index);
                StrList_printAt(list, index);
        }
        else if (choice == 6) {
                printf("Enter string to count occurrences: ");
                scanf("%s", data);
                printf("Occurrences of '%s' in the list: %d\n", data, StrList_count(list, data));
        }
        else if (choice == 7) {
                printf("Enter string to remove: ");
                scanf("%s", data);
                StrList_remove(list, data);
        }
        else if (choice == 8) {
                printf("Enter index to remove: ");
                scanf("%d", &index);
                StrList_removeAt(list, index);
        }
        else if (choice == 9) {
                StrList_reverse(list);
                printf("List reversed.\n");
        }
        else if (choice == 10) {
                StrList_free(list);
                list = StrList_alloc();
                printf("List deleted.\n");
        }
        else if (choice == 11) {
                StrList_sort(list);
                printf("List sorted in lexicographical order.\n");
        }
        else if (choice == 12) {
                if (StrList_isSorted(list)) {
                    printf("The list is sorted in lexicographical order.\n");
                }
                else {
                    printf("The list is not sorted in lexicographical order.\n");
                }
        }
        else if (choice == 0) {
                exit(0);
        }
        else {
                printf("Invalid option!\n");
        }
    
    }

    return 0;
}
