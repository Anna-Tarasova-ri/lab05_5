#include "pch.h"
#include "CppUnitTest.h"
#include "../PR5_5/pr5_5.cpp"   // підключаємо файл з функціями C та formulaC

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest55
{
    TEST_CLASS(UnitTest55)
    {
    public:

        // допоміжна функція: запускає рекурсивну C(n, k) зі свіжими лічильниками
        long long RunC(int n, int k, int& maxDepth, long long& calls)
        {
            maxDepth = 0;
            calls = 0;
            return C(n, k, 1, maxDepth, calls);
        }

        // Крайні випадки: C(n, 0) = 1 і C(n, n) = 1
        TEST_METHOD(TestBaseCases)
        {
            int d; long long c;
            Assert::AreEqual(1LL, RunC(5, 0, d, c));
            Assert::AreEqual(1LL, RunC(5, 5, d, c));
            Assert::AreEqual(1LL, RunC(0, 0, d, c));
        }

        // Для крайніх випадків один виклик і глибина 1
        TEST_METHOD(TestBaseCaseCallsAndDepth)
        {
            int d; long long c;
            RunC(7, 0, d, c);
            Assert::AreEqual(1, d);
            Assert::AreEqual(1LL, c);
        }

        // Відомі значення
        TEST_METHOD(TestKnownValues)
        {
            int d; long long c;
            Assert::AreEqual(10LL, RunC(5, 2, d, c));    // C(5,2) = 10
            Assert::AreEqual(20LL, RunC(6, 3, d, c));    // C(6,3) = 20
            Assert::AreEqual(252LL, RunC(10, 5, d, c));  // C(10,5) = 252
            Assert::AreEqual(2LL, RunC(2, 1, d, c));     // C(2,1) = 2
        }

        // Кількість викликів і глибина для C(6, 3)
        TEST_METHOD(TestCallsAndDepth_6_3)
        {
            int d; long long c;
            long long res = RunC(6, 3, d, c);
            Assert::AreEqual(20LL, res);
            Assert::AreEqual(39LL, c);   // 2 * 20 - 1
            Assert::AreEqual(6, d);      // глибина = n
        }

        // C(2, 1): найменший нетривіальний випадок
        TEST_METHOD(TestCallsAndDepth_2_1)
        {
            int d; long long c;
            RunC(2, 1, d, c);
            Assert::AreEqual(3LL, c);    // корінь + 2 листки
            Assert::AreEqual(2, d);
        }

        // Рекурсивне значення має збігатися з формулою для всіх n, k
        TEST_METHOD(TestRecursiveEqualsFormula)
        {
            for (int n = 0; n <= 15; n++)
            {
                for (int k = 0; k <= n; k++)
                {
                    int d; long long c;
                    Assert::AreEqual(formulaC(n, k), RunC(n, k, d, c));
                }
            }
        }

        // Функція formulaC на відомих значеннях
        TEST_METHOD(TestFormulaC)
        {
            Assert::AreEqual(1LL, formulaC(5, 0));
            Assert::AreEqual(1LL, formulaC(5, 5));
            Assert::AreEqual(10LL, formulaC(5, 2));
            Assert::AreEqual(252LL, formulaC(10, 5));
        }

        // Симетрія: C(n, k) = C(n, n - k)
        TEST_METHOD(TestSymmetry)
        {
            int d; long long c;
            Assert::AreEqual(RunC(9, 3, d, c), RunC(9, 6, d, c));
        }
    };
}