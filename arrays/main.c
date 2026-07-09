/*
This consists of a few exercises to practice the handling of arrays.
*/

// Take two arrays and find items common to both
void find_commons(int a[], int b[], int size) {
    // TODO Find common items and print here
}

// Take the average of n consecutive items
void find_moving_average(int a[], int n) {
    // TODO Calculate and print the moving averages here
}

// Sort an array of integers from lowest to highest values
void sort_nums(int a[], int size) {
    // TODO Sort and print the sorted array here
}

// Sort an array of strings in ASCII order
void sort_strings(char * a[], int size) {
    // TODO Sort and print the sorted array here
}

int main() {
    int a[] = { 1, 2, 3, 2, 3, 4, 3, 4, 5, 6 };
    int b[] = { 7, 2, 10, 2, 7, 4, 9, 4, 9, 8 };
    
    find_commons(a, b, sizeof(a) / sizeof(int));

    find_moving_average(a, 3);

    sort_nums(b, sizeof(b) / sizeof(int));

    char * s[] = {
        "hello",
        "world",
        "kitty",
        "Delhi",
        "hi",
        "average",
        "yellow",
        "caller"
    };
    sort_strings(s, sizeof(s) / sizeof(char*));

    return 0;
}