//----------------��ϰ1------------------------------------
// for ѭ����������
#include <iostream>
using namespace std;
int a = 10;
int main() {
    for (int a = 20, i = 1; i <= 5; i++)
        ;
    if (a == 20)
        cout << "��������for����б��ʽ1����ı�������������" << endl;
    else
        cout << "��������for����б��ʽ1����ı�������������" << endl;
    return 0;
}

//----------------��ϰ2------------------------------------
//�������������ֵ
#include <iostream>
namespace array1 {
void input(double a[], int n);
void output(double a[], int n);
} // namespace array1
namespace array2 {
double max(double a[], int n);
}
using namespace std;
using namespace array2;
int main() {
    double a[200];
    int n;
    cin >> n;
    array1::input(a, n);
    array1::output(a, n);
    cout << "�������ֵΪ��" << max(a, n) << endl;
    return 0;
}
namespace array1 {
void input(double a[], int n) {
    for (int i = 0; i < n; i++)
        std::cin >> a[i];
}
void output(double a[], int n) {
    for (int i = 0; i < n; i++)
        std::cout << a[i] << "\t";
    std::cout << std::endl;
}
} // namespace array1
namespace array2 {
double max(double a[], int n) {
    double t = a[0];
    for (int i = 1; i < n; i++)
        if (a[i] > t)
            t = a[i];
    return t;
}
} // namespace array2

/*����1��max���ô��󣬼����룺
namespace group2
{
    double max(double a[], int n)
    {
        int k, i;
        for (k = i = 0; i < n; i++)
            if (a[i] > a[k])
                k = i;
        return a[k];
    }
}
����������1�� max(a, n);
����������2�� max(a, n);
cout << max << endl;
Ӧ��Ϊ��cout << max(a, n) << endl;

����2��max�������㷨���󣬼����룺
����1����Ϊ double m=a[0];
double max(double a[], int n)
{
    double m = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > m)
            m = a[i];
    return m;
}
����2��//��Ϊa[i]>q
double max(double a[], int n)
{
    double q;
    int i;
    for (q = a[0], i = 0; i < n; i++)
        if (a[i] > a[i + 1])
            q = a[i];
    return q;
}
*/

//----------------��ϰ3------------------------------------
//��gcd
#include <iostream>
using namespace std;
int gcd(int x, int y);
int main() {
    int a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}
int gcd(int x, int y) {
    int gcd, r;
    while (y != 0) {
        r = x % y;
        x = y;
        y = r;
    }
    gcd = x;
    return gcd;
}

//----------------��ϰ4------------------------------------
// 2~1000������������ͣ����⣡����
#include <iostream>
using namespace std;
int count(), countSum(int x);
int main() {
    int k, i;
    //����2-1000
    for (k = 2; k <= 1000; k++) {
        //ɸѡ��С��iȥ����k��������
        //��������true������������false
        for (i = 2; k % i; i++)
            ;
        //�Ҳ��������Լ������������ģ���������
        if (i == k) {
            cout << k << "\t";
            count();
            countSum(k);
        }
    }
    cout << endl << "2~1000����������Ϊ��" << count() - 1 << endl;
    cout << endl << "2~1000������֮��Ϊ��" << countSum(0) << endl;
    return 0;
}
int count() {
    static int c = 0;
    c++;
    return c;
}
int countSum(int x) {
    static int total = 0;
    total += x;
    return total;
}

//----------------��ϰ5--------------------------------------------
//���н��15 15 21 36
//����static
#include <iostream>
using namespace std;

// f1(n)=1+2+3+...+n
int f1(int n) {
    int s = 0, y, i;
    for (y = 0, i = 1; i <= n; i++)
        y += i;
    s += y;
    return s;
}
int f2(int n) {
    static int s = 0, y, i;
    for (y = 0, i = 1; i <= n; i++)
        y += i;
    s += y;
    return s;
}
int main() {
    cout << f1(5) << '\t' << f2(5) << endl;
    cout << f1(6) << '\t' << f2(6) << endl;
    return 0;
}

//----------------��ϰ6------------------------------------
#include <iostream>
using namespace std;
int a = 9;
int main() {
    int b = 3;
    cout << a << "\t" << ::a << "\t" << b << endl;
    double a = 7.8;
    cout << a << "\t" << ::a << "\t" << b << endl;
    {
        int a = -20;
        b += a;
        cout << a << "\t" << ::a << "\t" << b << endl;
    }
    cout << a << "\t" << ::a << "\t" << b << endl;
    return 0;
}

//----------------��ϰ7-------------------------------------------
#include <iostream>
using namespace std;
int n = 100;
int f1(int n) {
    int y, i;
    for (y = 0, i = 1; i <= n; i++)
        y += i;
    return y;
}
int f2() {
    static int s = 0, y, i;
    for (y = 0, i = 1; i <= n; i++)
        y += i;
    s += y;
    return s;
}
int main() {
    cout << f1(20) << '\t' << f2() << endl;
    n = 40;
    cout << f1(6) << '\t' << f2() << endl;
    return 0;
}
