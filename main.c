#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node
{
    int data;
    struct Node *pointer;

} Node;

Node *create_list(int *array, size_t lenght){

    Node *current;
    Node *next = malloc(sizeof(int) + sizeof(Node *));
    Node *linked_list = next;

    for (unsigned i = 0; i < lenght; i++){
        current = next;
        current->data = array[i];
        if (i != lenght - 1){
            next = malloc(sizeof(int) + sizeof(Node *));
        } else {
            next = NULL;
        }
        current->pointer = next;
    }

    return linked_list;

}

void free_list(Node *list){
    Node *current = list;
    while(current != NULL){
        Node *next = current->pointer;
        free(current);
        current = next;
    }
}

void remove_next_node(Node *node){

    Node *next = node->pointer;
    node->pointer = next->pointer;
    free(next);

}

Node *remove_duplicates(Node *list) {

    Node *current = list;
    while(current->pointer != NULL){
        if (current->data == current->pointer->data){
            remove_next_node(current);
            if(current == NULL){
            break;
        }
        } else{
            current = current->pointer;
        }
    }

    return list;
}

bool equal_lists(Node *list1, Node *list2) {
    Node *curr1 = list1;
    Node *curr2 = list2;
    
    while (curr1 != NULL && curr2 != NULL) {
        if (curr1->data != curr2->data) {
            return false;
        }
        curr1 = curr1->pointer;
        curr2 = curr2->pointer;
    }
    
    // Если оба списка закончились одновременно, они равны
    return (curr1 == NULL && curr2 == NULL);
}

void print_list(Node *list){
    Node *current = list;
    printf("[");
    while(current != NULL){
        printf(" %d ", current->data);
        current = current->pointer;
    }
    printf("]");
}

bool test(char *test_name, int number, Node *expected, Node *input){
    
    printf("\n\nTest %d: %s", number, test_name);
    printf("\nInput:      ");
    print_list(input);
    printf("\nExpected:   ");
    print_list(expected);
    printf("\nReal:       ");
    print_list(remove_duplicates(input));
    if (equal_lists(expected, input)) {
        printf("\nTest %d........................PASSED\n\n", number);
        return true;
    } else {
        printf("\nTest %d........................FAILED\n\n", number);
        return false;
    }
}


int main(){

    int passed_tests = 0;
    int total_tests = 4;

    //=============TESTS=======================================================

    // Test 1: List with no duplicates
    int arr1[] = {1, 2, 3, 1, 4};
    Node *list1 = create_list(arr1, 5);
    Node *expected_list1 = create_list(arr1, 5);
    passed_tests += test("no dublicates", 1, expected_list1, list1);
    free_list(list1);
    free_list(expected_list1);

    // Test 2: List with multiple duplicate sequences
    int arr2[] = {1, 2, 2, 2, 8, 4, 4, 4, 4};
    Node *list2 = create_list(arr2, 9);
    int expected_arr2[] = {1, 2, 8, 4};
    Node *expected_list2 = create_list(expected_arr2, 4);
    passed_tests += test("a lot of dublicates", 2, expected_list2, list2);
    free_list(list2);
    free_list(expected_list2);

    // Test 3: List with all identical elements
    int arr3[] = {1, 1, 1, 1, 1};
    Node *list3 = create_list(arr3, 5);
    int expected_arr3[] = {1};
    Node *expected_list3 = create_list(expected_arr3, 1);
    passed_tests += test("a lot of dublicates of the single number", 3, expected_list3, list3);
    free_list(list3);
    free_list(expected_list3);

    // Test 4: Single element list
    int arr4[] = {2};
    Node *list4 = create_list(arr4, 1);
    Node *expected_list4 = create_list(arr4, 1);
    passed_tests += test("single element", 4, expected_list4, list4);
    free_list(list4);
    free_list(expected_list4);

    printf("========== TEST SUMMARY ==========\n");
    printf("Tests passed: %d out of %d\n", passed_tests, total_tests);
    
    if (passed_tests == total_tests) {
        printf("🎉 ALL TESTS PASSED SUCCESSFULLY!\n");
    } else {
        printf("⚠ SOME TESTS FAILED\n");
    }
    
    return (passed_tests == total_tests) ? EXIT_SUCCESS : EXIT_FAILURE;
}
