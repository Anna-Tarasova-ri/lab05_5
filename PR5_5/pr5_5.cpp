#include <iostream>
using namespace std;

// C(n, k) через рекурентне співвідношення
// depth    - поточна глибина виклику (перший виклик = 1)
// maxDepth - максимальна досягнута глибина рекурсії
// calls    - кількість рекурсивних викликів
long long C(int n, int k, int depth, int& maxDepth, long long& calls) 
{
    calls++;
    if (depth > maxDepth) maxDepth = depth;

    if (k == 0 || k == n) return 1;

    return C(n - 1, k - 1, depth + 1, maxDepth, calls)
        + C(n - 1, k, depth + 1, maxDepth, calls);
}

// Обчислення за формулою n! / (k! (n-k)!) для перевірки
long long formulaC(int n, int k) 
{
    long long result = 1;
    for (int i = 1; i <= k; i++) 
    {
        result = result * (n - k + i) / i;
    }
    return result;
}

int main() 
{
    int n, k;
    cout << "n=";
    cin >> n;
    cout << "k=";
    cin >> k;

    if (n < 0 || k < 0 || k > n) 
    {
        cout << "Mistake 0 <= k <= n\n";
        return 1;
    }

    int maxDepth = 0;
    long long calls = 0;
    long long res = C(n, k, 1, maxDepth, calls);

    cout << "C(" << n << ", " << k << ") rec = " << res << endl;
    cout << "C(" << n << ", " << k << ") formula = " << formulaC(n, k) << endl;
    cout << "depth = " << maxDepth << endl;
    cout << "calls = " << calls << endl;

    return 0;
}