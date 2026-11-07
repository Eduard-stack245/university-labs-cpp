#include <cmath>
#include <cstdio>
#include <vector>

int main() {
    int n = 0;
    std::printf("Input n: ");
    if (std::scanf("%d", &n) != 1 || n < 2 || n > 1000000) {
        std::fprintf(stderr, "Error: n must be between 2 and 1000000.\n");
        return 1;
    }

    std::vector<bool> is_prime(static_cast<std::size_t>(n) + 1, true);
    is_prime[0] = false;
    is_prime[1] = false;
    for (int p = 2; p <= n / p; ++p) {
        if (is_prime[p])
            for (int multiple = p * p; multiple <= n; multiple += p)
                is_prime[multiple] = false;
    }
    std::printf("Primes up to %d:", n);
    for (int p = 2; p <= n; ++p)
        if (is_prime[p]) std::printf(" %d", p);
    std::printf("\n");

    int sum = 0;
    for (int value = 1; value <= 100; value += 2) sum += value;
    std::printf("Sum of odd numbers from 1 to 100: %d\n", sum);

    for (int i = 0; i <= 12; ++i) {
        const double x = i * (2.0 / 12.0);
        const double y = std::exp(x) - std::exp(-x) + 2.0;
        std::printf("x[%2d] = %4.2f: y = %7.3f\n", i, x, y);
    }
    return 0;
}
