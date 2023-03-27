#include "../../vector/vector_fun.h"
#include <chrono>

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
        if (lo < v[i].abs() && v[i].abs() <hi)
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
    auto start_b = chrono::steady_clock::now();
    complex.sort('b');
    auto end_b = chrono::steady_clock::now();
    auto time_b = chrono::duration_cast<chrono::nanoseconds>(end_b - start_b).count();
    auto start_m = chrono::steady_clock::now();
    complex.sort('m');
    auto end_m = chrono::steady_clock::now();
    auto time_m = chrono::duration_cast<chrono::nanoseconds>(end_m - start_m).count();
    cout << "˳�����������ʱ:    " << (double) time_b << "ns" << endl
         << "˳��鲢�����ʱ:    " << (double) time_m << "ns" << endl;
    complex.reverse();
    start_b = chrono::steady_clock::now();
    complex.sort('b');
    end_b = chrono::steady_clock::now();
    time_b = chrono::duration_cast<chrono::nanoseconds>(end_b - start_b).count();
    complex.reverse();
    start_m = chrono::steady_clock::now();
    complex.sort('m');
    end_m = chrono::steady_clock::now();
    time_m = chrono::duration_cast<chrono::nanoseconds>(end_m - start_m).count();
    cout << "�������������ʱ:    " << time_b << "ns" << endl
         << "����鲢�����ʱ:    " << time_m << "ns" << endl;
    complex.unsort();
    Vector<Complex> bak(complex);
    start_b = chrono::steady_clock::now();
    complex.sort('b');
    end_b = chrono::steady_clock::now();
    time_b = chrono::duration_cast<chrono::nanoseconds>(end_b - start_b).count();
    start_m = chrono::steady_clock::now();
    bak.sort('m');
    end_m = chrono::steady_clock::now();
    time_m = chrono::duration_cast<chrono::nanoseconds>(end_m - start_m).count();
    cout << "�������������ʱ:    " << time_b << "ns" << endl
         << "����鲢�����ʱ:    " << time_m << "ns" << endl;
    cout << "����ģ��������ң������ʽ:<�����½�> <�����Ͻ�>" << endl;
    cin >> a >> b;
    bak = Abssort(complex, a, b);
    bak.print();
    return 0;
}
