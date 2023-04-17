#include "../../vector/vector_fun.h"

class Complex
{
protected:
    double real; // 实部
    double imag; // 虚部

public:
    Complex(double r = 0.0, double i = 0.0)
    {
        real = r;
        imag = i;
    }

    double abs() const
    {
        return sqrt(real * real + imag * imag);
    }

    friend ostream &operator<<(ostream &os, const Complex &c)
    {
        return os << c.real << '+' << c.imag << "i";
    }

    bool operator==(const Complex &other) const
    {
        return ((this->real == other.real) && (this->imag == other.imag));
    }

    bool operator!=(const Complex &other) const
    {
        return (this->real != other.real) || (this->imag != other.imag);
    }

    bool operator<(const Complex &c) const
    {
        if (abs() == c.abs())
        {
            return real < c.real;
        }
        return abs() < c.abs();
    }

    bool operator>(const Complex &c) const
    {
        return c < *this;
    }

    bool operator<=(const Complex &c) const
    {
        return !(c < *this);
    }

    bool operator>=(const Complex &c) const
    {
        return !(*this < c);
    }
};

void Randomize(Vector<Complex> &v)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (int i = 0; i < v.size(); i++)
    {
        double real = double(dis(gen)) / 10.0;
        double imag = double(dis(gen)) / 10.0;
        Complex c(real, imag);
        v[i] = c;
    }
}

Vector<Complex> Abssort(Vector<Complex> &v, double lo, double hi)
{
    int k = 0;
    Vector<Complex> cv;
    for (Rank i = 0; i < v.size(); i++)
    {
        if (lo <= v[i].abs() && v[i].abs() < hi)
            cv.insert(k++, v[i]);
    }
    return cv;
}

int main()
{
    double a, b;
    Rank i;
    Vector<Complex> complex(100, 100);
    Randomize(complex);
    cout << "生成的数组:" << endl;
    complex.print();
    complex.unsort();
    cout << "置乱后的数组:" << endl;
    complex.print();
    cout << "查找复数，输入格式:<实部> <虚部>" << endl;
    cin >> a >> b;
    Complex key(a, b);
    if (complex.find(key) == -1)
        cout << "查找失败!" << endl;
    else
        cout << "位于下标" << complex.find(key) << endl;
    cout << "插入元素，输入格式:<下标> <实部> <虚部>" << endl;
    cin >> i >> a >> b;
    Complex ins(a, b);
    complex.insert(i, ins);
    cout << "插入后的数组" << endl;
    complex.print();
    cout << "输入待删除的元素下标:";
    cin >> i;
    complex.remove(i);
    cout << "删除后的数组" << endl;
    complex.print();
    cout << "去重后的数组" << endl;
    complex.deduplicate();
    complex.print();
    complex.sort('m'); // b为起泡排序，m为归并排序
    auto time_b = 0, time_m = 0;
    time_b = complex.sort('b');
    time_m = complex.sort('m');
    cout << "顺序起泡排序耗时:    " << time_b << "ns" << endl
         << "顺序归并排序耗时:    " << time_m << "ns" << endl;
    complex.reverse();
    time_b = complex.sort('b');
    complex.reverse();
    time_m = complex.sort('m');
    cout << "逆序起泡排序耗时:    " << time_b << "ns" << endl
         << "逆序归并排序耗时:    " << time_m << "ns" << endl;
    complex.unsort();
    Vector<Complex> bak(complex);
    time_b = complex.sort('b');
    time_m = bak.sort('m');
    cout << "乱序起泡排序耗时:    " << time_b << "ns" << endl
         << "乱序归并排序耗时:    " << time_m << "ns" << endl;
    cout << "复数模的区间查找，输入格式:<区间下界> <区间上界>" << endl;
    cin >> a >> b;
    bak = Abssort(complex, a, b);
    bak.print();
    return 0;
}
