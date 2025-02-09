#include <stdio.h>

// Recursive function to print the fibonacci series
void fib(int n, int prev1, int prev2) {
    // Base Case: when n gets less than 3
    if (n < 3) {
        return;
    }
    
    int curr = prev1 + prev2;
    printf("%d ", curr);
  
    return fib(n - 1, prev2, curr);
}

// Function that handles the first two terms and calls the recursive function
void printFib(int n) {
    // When the number of terms is less than 1
    if (n < 1) {
        printf("Invalid number of terms\n");
    }
    // When the number of terms is 1
    else if (n == 1) {
        printf("%d ", 0);
    }
    // When the number of terms is 2
    else if (n == 2) {
        printf("%d %d", 0, 1);
    }
    // When number of terms greater than 2
    else {
        printf("%d %d ", 0, 1);
        fib(n, 0, 1);
    }
    return;
}

int main() {
    int n = 9;
    // Printing first 9 Fibonacci series terms
    printFib(n);

    return 0;
}