#include "Tests.h"
#include "Utils.h"

void tests::SampleTest()
{
	Utils::AutoTimeLog start("SampleTest");
	start.StopAndPrint();
}

static int fib(int n)
{
    if (n <= 1)
        return n;
    return fib(n - 1) + fib(n - 2);
}

void tests::RecursiveFibonacciTest()
{
    Utils::AutoTimeLog start("Recursive Fib Test banch constant");
    long long result = 0ll;
    for (int i = 0; i < 100000000; i++)
        result += fib(42);
    printf("Result: %lld \n", result);
    start.StopAndPrint();
}
