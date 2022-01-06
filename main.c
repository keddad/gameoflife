#include <stdio.h>
#include <malloc.h>

int **empty_field(int x_size, int y_size) {
    int **f = calloc(y_size, sizeof(int *));

    for (int i = 0; i < y_size; ++i) {
        f[i] = calloc(x_size, sizeof(int));
    }

    return f;
}

void free_field(int **field, int y_size) {
    for (int i = 0; i < y_size; ++i) {
        free(field[i]);
    }

    free(field);
}

int count(int **current_field, int y, int x, int x_size, int y_size) {
    int cnt = 0;

    for (int i = 0; i < 3; ++i) {
        cnt += current_field[y == 0 ? y_size - 1 : y - 1][(x - 1 + i) < 0 ? x_size + (x - 1 + i) : (x - 1 + i) %
                                                                                                   x_size];
    }

    for (int i = 0; i < 3; ++i) {
        cnt += current_field[y == y_size - 1 ? 0 : y + 1][(x - 1 + i) < 0 ? x_size + (x - 1 + i) : (x - 1 + i) %
                                                                                                   x_size];
    }

    cnt += current_field[y][(x == 0 ? x_size - 1 : x - 1)];
    cnt += current_field[y][(x + 1 == x_size ? 0 : x + 1)];

    return cnt;
}

int **step(int **current_field, int x_size, int y_size) {
    int **new_field = empty_field(x_size, y_size);

    for (int i = 0; i < y_size; ++i) {
        for (int j = 0; j < x_size; ++j) {
            int local = count(current_field, i, j, x_size, y_size);

            if ((current_field[i][j] && local == 2) || local == 3) {
                new_field[i][j] = 1;
            }
        }
    }

    free_field(current_field, y_size);
    return new_field;
}

void print_field(int **current_field, int x_size, int y_size) {
    for (int i = 0; i < y_size; ++i) {
        for (int j = 0; j < x_size; ++j) {
            printf("%d\t", current_field[i][j]);
        }
        printf("\n");
    }

    printf("\n\n\n");
}

int main() {
    int x_size, y_size;
    scanf("%d %d\n", &x_size, &y_size);

    int **current_field = empty_field(x_size, y_size);

    int num_preset;
    scanf("%d\n", &num_preset);

    for (int i = 0; i < num_preset; ++i) {
        int x, y;
        scanf("%d %d\n", &x, &y);

        current_field[x - 1][y - 1] = 1;
    }

    int num_steps;
    scanf("%d", &num_steps);

    print_field(current_field, x_size, y_size);
    for (int i = 0; i < num_steps; ++i) {
        current_field = step(current_field, x_size, y_size);
        print_field(current_field, x_size, y_size);
    }

    free_field(current_field, y_size);
    return 0;
}