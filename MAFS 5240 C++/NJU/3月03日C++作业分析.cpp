//----------------练习1------------------------------------
// for 循环的作用域
#include <iostream>
using namespace std;
int a = 10;
int main() {
    for (int a = 20, i = 1; i <= 5; i++)
        ;
    if (a == 20)
        cout << "现在仍在for语句中表达式1定义的变量的作用域内" << endl;
    else
        cout << "现在已在for语句中表达式1定义的变量的作用域外" << endl;
    return 0;
}

//----------------练习2------------------------------------
//输入数组求最大值
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
    cout << "数据最大值为：" << max(a, n) << endl;
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

/*问题1：max调用错误，见代码：
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
主函数调用1： max(a, n);
主函数调用2： max(a, n);
cout << max << endl;
应改为：cout << max(a, n) << endl;

问题2：max函数的算法错误，见代码：
错误1：改为 double m=a[0];
double max(double a[], int n)
{
    double m = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > m)
            m = a[i];
    return m;
}
错误2：//改为a[i]>q
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

//----------------练习3------------------------------------
//求gcd
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

//----------------练习4------------------------------------
// 2~1000中素数个数与和，好题！！！
#include <iostream>
using namespace std;
int count(), countSum(int x);
int main() {
    int k, i;
    //遍历2-1000
    for (k = 2; k <= 1000; k++) {
        //筛选最小的i去整除k！！！！
        //整除就是true，不整除就是false
        for (i = 2; k % i; i++)
            ;
        //找不到除了自己以外能整除的，就是素数
        if (i == k) {
            cout << k << "\t";
            count();
            countSum(k);
        }
    }
    cout << endl << "2~1000中素数个数为：" << count() - 1 << endl;
    cout << endl << "2~1000中素数之和为：" << countSum(0) << endl;
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

//----------------练习5--------------------------------------------
//运行结果15 15 21 36
//区分static
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

//----------------练习6------------------------------------
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

//----------------练习7-------------------------------------------
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
