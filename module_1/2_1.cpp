/*
 * Даны
 *  отсортированный массив целых чисел A[0..n-1]
 *  массив целых чисел B[0..m-1].
 *
 * Для каждого элемента массива B[i] найдите
 * минимальный индекс k минимального элемента массива A,
 * равного или превосходящего B[i]: A[k] >= B[i].
 *
 * Если такого элемента нет, выведите n.
 *
 * Время работы поиска k для каждого элемента B[i]: O(log(k))
 *
 * n, m ≤ 10000.
*/

#include <iostream>
#include <cassert>

void search_limit(int *arr, int size, int num, int *min, int *max)
{
    int i = 0;
    while (arr[1 << i] < num && (1 << i) < size)
        i++;

    *min = (i == 0) ? 0 : 1 << (i - 1);
    *max = ((1 << i) < size) ? 1 << i : size;
}

int bsearch(int *const arr, int left, int right, int key)
{
    int mid;
    int l = left, r = right;

    while (l < r)
    {
        int mid = (l + r) / 2;

        if (key <= arr[mid])
            r = mid;
        else
            l = mid + 1;
    }

    return key <= arr[r] ? r : right;
}

int main(void)
{
    int n = 0, m = 0;

    std::cin >> n >> m;

    assert(n > 0 && m > 0);

    int *A = new int[n];
    int *B = new int[m];

    for (int i = 0; i < n; i++)
        std::cin >> A[i];

    for (int i = 0; i < m; i++)
        std::cin >> B[i];

    for (int i = 0, l, r; i < m; i++)
    {
        l = 0;
        r = n;

        search_limit(A, n, B[i], &l, &r);
        std::cout << bsearch(A, l, r, B[i]) << ' ';
    }

    std::cout << std::endl;

    delete[] A;
    delete[] B;
}
