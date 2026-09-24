#include "Pair.h"
#include <limits>
#include <stdexcept>

namespace {
int checkedAdd(int a, int b) {
    if ((b > 0 && a > std::numeric_limits<int>::max() - b) ||
        (b < 0 && a < std::numeric_limits<int>::min() - b))
        throw std::overflow_error("Pair addition overflows int");
    return a + b;
}
}

Pair::Pair() : num1(0), num2(0)
{
}

Pair::Pair(int num1, int num2) : num1(num1), num2(num2)
{
}

int Pair::get1() const
{
    return num1;
}

int Pair::get2() const
{
    return num2;
}

Pair operator+(int x, Pair p)
{
    Pair newPair(p.num1, p.num2);
    newPair.num1 = checkedAdd(newPair.num1, x);
    newPair.num2 = checkedAdd(newPair.num2, x);
    return newPair;
}

Pair operator+(Pair p, int otherNum)
{

    Pair newPair(p.num1, p.num2);
    newPair.num1 = checkedAdd(newPair.num1, otherNum);
    newPair.num2 = checkedAdd(newPair.num2, otherNum);
    return newPair;
}

Pair operator+(Pair p, const Pair& other)
{
    Pair newPair(p.num1, p.num2);
    newPair.num1 = checkedAdd(newPair.num1, other.num1);
    newPair.num2 = checkedAdd(newPair.num2, other.num2);
    return newPair;

}
