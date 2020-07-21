#include <stdio.h>
#include <stdlib.h>
#include "circular_buffer.h"

int circular_buffer_create(struct circular_buffer_t *a, int N) {
    if (a == NULL || N <= 0) {
        return 1;
    }


    a->ptr = (int *) calloc(N, sizeof(int));

    if (a->ptr == NULL) {
        return 2;
    }
    a->capacity = N;
    // a->begin = 0;
    // a->end = 0;
    // a->full = 0;

    return 0;
}

int circular_buffer_create_struct(struct circular_buffer_t **cb, int N) {
    if (cb == NULL || N <= 0) {
        return 1;
    }

    *cb = (struct circular_buffer_t *) calloc(1, sizeof(struct circular_buffer_t));
    if (*cb == NULL) {
        return 2;
    }
    circular_buffer_create(*cb, N);

    if ((*cb)->ptr == NULL) {
        free(*cb);
        return 2;
    }

    // (*cb)->begin = 0;
    // (*cb)->end = 0;
    // (*cb)->capacity = N;
    // (*cb)->full = 0;
    return 0;
}

void circular_buffer_destroy(struct circular_buffer_t *a) {
    if (a != NULL) {
        free(a->ptr);

    }
}

void circular_buffer_destroy_struct(struct circular_buffer_t **cb) {
    if (cb != NULL) {
        if (*cb != NULL) {
            circular_buffer_destroy(*cb);
            free(*cb);
        }
    }
}


int circular_buffer_push_back(struct circular_buffer_t *cb, int value) {
    if (cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity < 0 || cb->begin > cb->capacity - 1 ||
        cb->end > cb->capacity - 1) {
        return 1;
    }


    *(cb->ptr + cb->end) = value;
    cb->end = (cb->end + 1) % cb->capacity;

    if (cb->full == 1) {
        cb->begin = (cb->begin + 1) % cb->capacity;
    }

    if ((cb->end) == cb->begin) {
        cb->full = (unsigned char) 1;
    }


    return 0;
}

void circular_buffer_display(const struct circular_buffer_t *cb) {
    if (cb != NULL) {
        if (circular_buffer_empty(cb) == 0) {
            int i = cb->begin;
            if (cb->full == 0) {
                while ( i != cb->end) {
                    if ( i == cb->capacity) {
                        i = 0;
                    } else {
                        printf("%d ", *(cb->ptr + i));
                        i++;
                    }
                }
                printf("\n");
            } else {
                for (i = 0; i < cb->capacity; i++) {
                    printf("%d ", *(cb->ptr + (cb->begin + i) % cb->capacity));
                }
                printf("\n");
            }

        }
    }
}


int circular_buffer_pop_back(struct circular_buffer_t *cb, int *err_code) {
    int temp = 0;
    if (cb == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return temp;
    }
    if (cb->begin < 0 || cb->end < 0 || cb->capacity < 0 || cb->begin > cb->capacity - 1 ||
        cb->end > cb->capacity - 1) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return temp;
    }

    if (circular_buffer_empty(cb) == 1) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return temp;
    }
    cb->end = (cb->end + cb->capacity - 1) % cb->capacity;
    temp = *(cb->ptr + cb->end);
    cb->full = 0;


    if (err_code != NULL) {
        *err_code = 0;
    }
    return temp;
}

int circular_buffer_pop_front(struct circular_buffer_t *cb, int *err_code) {
    int temp = 0;
    if (cb == NULL) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return temp;
    }
    if (cb->begin < 0 || cb->end < 0 || cb->capacity < 0 || cb->begin > cb->capacity - 1 ||
        cb->end > cb->capacity - 1) {
        if (err_code != NULL) {
            *err_code = 1;
        }
        return temp;
    }

    if (circular_buffer_empty(cb) == 1) {
        if (err_code != NULL) {
            *err_code = 2;
        }
        return temp;
    }

    temp = *(cb->ptr + cb->begin);
    cb->begin = (cb->begin + 1) % cb->capacity;
    cb->full = 0;

    if (err_code != NULL) {
        *err_code = 0;
    }
    return temp;
}


int circular_buffer_empty(const struct circular_buffer_t *cb) {
    if (cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity < 0 || cb->begin > cb->capacity - 1 ||
        cb->end > cb->capacity - 1) {
        return -1;
    }
    if (cb->begin == cb->end && cb->full == 0) {
        return 1;
    }
    return 0;
}

int circular_buffer_full(const struct circular_buffer_t *cb) {
    if (cb == NULL || cb->begin < 0 || cb->end < 0 || cb->capacity < 0 || cb->begin > cb->capacity - 1 ||
        cb->end > cb->capacity - 1) {
        return -1;
    }
    if (cb->full == 1) {
        return 1;
    }
    return 0;
}





// Created by macie on 14.05.2019.
//

