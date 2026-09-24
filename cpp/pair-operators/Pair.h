#pragma once
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
