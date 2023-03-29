#include "../../vector/vector_fun.h"


class Complex {
protected:
    double real; // ʵ��
    double imag; // �鲿

public:
    Complex(double r = 0.0, double i = 0.0) {
        real = r;
        imag = i;
    }

    double abs() const {
        return sqrt(real * real + imag * imag);
    }

    friend ostream &operator<<(ostream &os, const Complex &c) {
        return os << c.real << '+' << c.imag << "i";
    }

    bool operator==(const Complex &other) const {
        return ((this->real == other.real) && (this->imag == other.imag));
    }

    bool operator!=(const Complex &other) const {
        return (this->real != other.real) || (this->imag != other.imag);
    }

    bool operator<(const Complex &c) const {
        if (abs() == c.abs()) {
            return real < c.real;
        }
        return abs() < c.abs();
    }

    bool operator>(const Complex &c) const {
        return c < *this;
    }

    bool operator<=(const Complex &c) const {
        return !(c < *this);
    }

    bool operator>=(const Complex &c) const {
        return !(*this < c);
    }
};

void Randomize(Vector<Complex> &v) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100);
    for (unsigned i = 0; i < v.size(); i++) {
        double real = double(dis(gen)) / 10.0;
        double imag = double(dis(gen)) / 10.0;
        Complex c(real, imag);
        v[i] = c;
    }
}

Vector<Complex> Abssort(Vector<Complex> &v, double lo, double hi) {
    int k = 0;
    Vector<Complex> cv;
    for (Rank i = 0; i < v.size(); i++) {
        if (lo <= v[i].abs() && v[i].abs() < hi)
            cv.insert(k++, v[i]);
    }
    return cv;
}

int main() {
    double a, b;
    Rank i;
    Vector<Complex> complex(20, 20);
    Randomize(complex);
    cout << "���ɵ�����:" << endl;
    complex.print();
    complex.unsort();
    cout << "���Һ������:" << endl;
    complex.print();
    cout << "���Ҹ����������ʽ:<ʵ��> <�鲿>" << endl;
    cin >> a >> b;
    Complex key(a, b);
    if (complex.find(key) == -1)
        cout << "����ʧ��!" << endl;
    else
        cout << "λ���±�" << complex.find(key) << endl;
    cout << "����Ԫ�أ������ʽ:<�±�> <ʵ��> <�鲿>" << endl;
    cin >> i >> a >> b;
    Complex ins(a, b);
    complex.insert(i, ins);
    cout << "����������" << endl;
    complex.print();
    cout << "�����ɾ����Ԫ���±�:";
    cin >> i;
    complex.remove(i);
    cout << "ɾ���������" << endl;
    complex.print();
    cout << "ȥ�غ������" << endl;
    complex.deduplicate();
    complex.print();
    complex.sort('m');//bΪ��������mΪ�鲢����
    auto time_b = 0, time_m = 0;
    time_b = complex.sort('b');
    time_m = complex.sort('m');
    cout << "˳�����������ʱ:    " << (double) time_b << "ns" << endl
         << "˳��鲢�����ʱ:    " << (double) time_m << "ns" << endl;
    complex.reverse();
    time_b = complex.sort('b');
    complex.reverse();
    time_m = complex.sort('m');
    cout << "�������������ʱ:    " << time_b << "ns" << endl
         << "����鲢�����ʱ:    " << time_m << "ns" << endl;
    complex.unsort();
    Vector<Complex> bak(complex);
    time_b = complex.sort('b');
    time_m = bak.sort('m');
    cout << "�������������ʱ:    " << time_b << "ns" << endl
         << "����鲢�����ʱ:    " << time_m << "ns" << endl;
    cout << "����ģ��������ң������ʽ:<�����½�> <�����Ͻ�>" << endl;
    cin >> a >> b;
    bak = Abssort(complex, a, b);
    bak.print();
    return 0;
}
