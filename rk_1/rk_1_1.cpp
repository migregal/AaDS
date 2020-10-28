#include <iostream>

int main(void)
{
    size_t n;
    std::cin >> n;

    int *A = new int[n];

    for (size_t i = 0; i < n; ++i)
        std::cin >> A[i];

    int k;
    std::cin >> k;

    size_t res = n;
    for (size_t i = 0; i < n; ++i)
    {
        if (A[i] < k)
            continue;

        res = i;
        break;
    }

    std::cout << res << std::endl;

    delete[] A;
}
