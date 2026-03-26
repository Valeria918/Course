#include <iostream>

long long fibIterative(int n) {
    if (n <= 1) {
        return n;
    }
    long long prev = 0, curr = 1;
    for (int i = 2; i <= n; ++i) {
        long long next = prev + curr;
        prev = curr;
        curr = next;
    }
    return curr;
}

long long fibRecursive(int n) {
    if (n <= 1) {
        return n;
    }
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

int main() {
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;

    if (n < 0) {
        std::cout << "n should be a non-negative integer\n";
        return 1;
    }

    std::cout << "Fibonacci(" << n << "):\n";
    std::cout << "  Iterative : " << fibIterative(n) << "\n";
    std::cout << "  Recursive : " << fibRecursive(n) << "\n";
    return 0;
}
