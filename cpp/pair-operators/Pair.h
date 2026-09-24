#pragma once
// A member operator+ requires a Pair as its left operand; int has no such member.
// Non-member friend operators allow 2 + pair, pair + 2, and pair + pair.
class Pair
{
private:

    int num1, num2;
public:
    friend Pair operator+(int x, Pair p);
    friend Pair operator+(Pair p, const Pair& other);
    friend Pair operator+(Pair p, int otherNum);
    Pair();
    Pair(int num1, int num2);
    int get1() const;
    int get2() const;

};
