#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"


int main() {
    struct circular_buffer_t *x;
//    int err = 3;
//    circular_buffer_create_struct(&x, 15);
//    for (int i = 0; i< 15; i++){
//        printf("Wywolanie nr %d\n", i);
//        circular_buffer_push_back(x, i+1);
//        circular_buffer_display(x);
//        printf("begin = %d\nend = %d\ncapacity = %d\nfull = %u\n", x->begin, x->end, x->capacity, x->full);
//    }
//    circular_buffer_push_back(x, 22);
//    circular_buffer_push_back(x, 26);
//    circular_buffer_display(x);


//    circular_buffer_display(x);
//    printf("Po petli: begin = %d\nend = %d\ncapacity = %d\nfull = %u\n", x->begin, x->end, x->capacity, x->full);
//    for (int i = 10; i< 15; i++){
//        circular_buffer_push_back(x, i);
//        circular_buffer_display(x);
//        printf("begin = %d\nend = %d\ncapacity = %d\nfull = %u\n", x->begin, x->end, x->capacity, x->full);
//    }

// PROGRAM
    int size;
    printf("Podaj rozmiar buffora:");
    if (scanf("%d", &size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    if (size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    if (circular_buffer_create_struct(&x, size) == 2) {
        printf("Failed to allocate memory");
        return 8;
    }
    int err = 4;
    int choice = -1;
    while (choice != 0) {
        printf("Co chcesz zrobic ? ");
        if (scanf("%d", &choice) != 1) {
            printf("Incorrect input\n");
            circular_buffer_destroy_struct(&x);
            choice = 0;
            return 1;
        } else if (choice < 0 || choice > 6) {
            printf("Incorrect input data\n");
        } else if (choice == 1) {
            printf("Podaj liczbe: ");
            if (scanf("%d", &size) == 1) {
                circular_buffer_push_back(x, size);
            } else
            {
                printf("Incorrect input\n");
                circular_buffer_destroy_struct(&x);
                choice = 0;
                return 1;
            }
        } else if (choice == 2) {
            size = circular_buffer_pop_back(x, &err);
            if (err == 0) {
                printf("%d\n", size);
                err = 3;
            } else {
                printf("Buffer is empty\n");
                err = 3;
            }
        } else if (choice == 3) {
            size = circular_buffer_pop_front(x, &err);
            if (err ==  0) {
                printf("%d\n", size);
                err = 3;
            } else {
                printf("Buffer is empty\n");
                err = 3;
            }
        } else if (choice == 4) {
            if (circular_buffer_empty(x) == 1) {
                printf("Buffer is empty\n");
            } else {
                circular_buffer_display(x);
            }
        } else if (choice == 5) {
            printf("%d\n", circular_buffer_empty(x));

        } else if (choice == 6) {
            printf("%d\n", circular_buffer_full(x));
        }
    }


    circular_buffer_destroy_struct(&x);

    return 0;
}


