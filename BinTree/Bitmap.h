#pragma once
#include <iostream>

class Bitmap
{
public:
    Bitmap(int n) : size((n + 31) >> 5), bits(new int[size]) { clear(); }
    ~Bitmap() { delete[] bits; }
    void clear()
    {
        for (int i = 0; i < size; i++)
        {
            bits[i] = 0;
        }
    }
    void set(int k) { bits[k >> 5] |= (1 << (k & 31)); }
    void reset(int k) { bits[k >> 5] &= ~(1 << (k & 31)); }
    bool test(int k) const { return bits[k >> 5] & (1 << (k & 31)); }
    int size;
    int *bits;
};