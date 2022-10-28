//---------------------练习1---------------------------------------
//输入y(取值1,2,…,46),找出x(0≤x≤46)使得5^x %47=y。如：5^36%47=4
# include <iostream>
using namespace std;
int main( )
{	int  x,y,s;
	cin>>y;
	if(y<1||y>46)  return 1;
	for(s=1,x=0;x<=46;x++)
	{	if(s==y) break;  s=s*5%47;  }
	cout<<"5^"<<x<<" %47="<<y<<endl;
	return 0;
}

/*问题1：计算5的x次幂%47用代码 int(pow(5,x))%47 或 for(s=j=1;j<=x;j++) s*=5;
取值s%47，计算的值会大大超出 int 所能存放的数据范围。可用 s=s*5%47 代替 s*=5
拓展：利用函数可以计算 (5的x次幂)%47 的值(x=0,1,...,45)，见函数
    int f(int x)
    {
        int s=1,i;
        for(i=1;i<=x;i++) s=s*5%47;
        return s;
    }
当大规模使用f(x)计算相应数值时，效率低下，利用映射思想，考虑
    int
g[46]={1,5,25,31,14,23,21,11,8,40,12,13,18,43,27,41,17,38,2,10,3,15,28,46,42,22,16
33,24,26 36,39,7,35,34,29,4,20,6,30,  9,45,37,44,32,19}; 可使用 g[x] 代替子函数
f(x) 来计算相应的值可大大提高计算效率。*/

//---------------------练习2---------------------------------------
//练习2：输入10个实数，按 (i1,i2,…,i10)=(5,2,7,3,8,9,6,1,10,4)进行置换，
//即置换后10个实数次序由a1,a2,…,a10变为 ai1,ai2,…,ai10。
#include <iostream>
using namespace std;
int main() {
    int i[10] = {5, 2, 7, 3, 8, 9, 6, 1, 10, 4}, j;
    double a[10], b[10];
    for (j = 0; j < 10; j++)
        cin >> a[j];
    for (j = 0; j < 10; j++)
        b[j] = a[i[j] - 1]; // b数组为ai1,ai2,...,ai10
    for (j = 0; j < 10; j++)
        a[j] = b[j];
    for (j = 0; j < 10; j++)
        cout << a[j] << "\t";
    cout << endl;
    return 0;
}

//问题1：置换后的下标在1~10范围，没有减去1转化为0~9范围。
//问题2：使用 b(ik)=a(k)进行置换，结果得到的是逆置换的结果，应该用 b(k)=a(ik)

//---------------------练习3---------------------------------------
//输入一个5×5整数矩阵，判断该矩阵是否由1,2,3,…,25这25个数填充而成。
#include <iostream>
using namespace std;
int main() {
    int a[5][5], c[30] = {0}, i, j, k;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            cin >> a[i][j];
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++) {
            k = a[i][j];
            if (k >= 1 && k <= 25)
                c[k]++;
        }
    for (i = 1; c[i] == 1; i++)
        ;
    if (i > 25)
        cout << "矩阵由1,2,3,...,25这25个数填充而成" << endl;
    else
        cout << "矩阵不是由1,2,3,...,25这25个数填充而成" << endl;
    return 0;
}
//或
#include <iostream>
using namespace std;
int main() {
    int s, i, j, k, a[5][5];
    cout << "输入矩阵" << endl;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            cin >> a[i][j];
    for (k = 1; k <= 25; k++) {
        for (s = 0, i = 0; i < 5; i++)
            for (j = 0; j < 5; j++) {
                if (a[i][j] == k)
                    s++;
            }
        if (s != 1)
            break;
    }
    if (k > 25)
        cout << "是" << endl;
    else
        cout << "不是" << endl;
    return 0;
}
/*问题1：内层用break跳出循环，见代码：
    for(k=1;k<=25;k++)
    {
        for(i=0;i<5;i++)
            for(j=0;j<5;j++)
                if(a[i][j]==k) break;
        if(i==5&&j==5) break;
    }
    该代码只跳出最内层j的循环，要跳出第二层循环可改循环体为
        if(a[i][j]==k) { i=5; break; }
*/

//---------------------练习4---------------------------------------
//将一个字符串中的非字母字符删除，并将字母字符统一转换成大写字母。
#include <iostream>
using namespace std;
void leaveLetter(char s[]) {
    int i, j;
    for (j = i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[j++] = s[i];
        else if (s[i] >= 'a' && s[i] <= 'z')
            s[j++] = s[i] + 'A' - 'a';
    }
    s[j] = '\0';
}
int main() {
    char s[80];
    cin.getline(s, 80);
    leaveLetter(s);
    cout << s << endl;
    return 0;
}
//问题1：漏了添加 '\0'，这样会导致字符串长度没有变化，结果不正确
//问题2：没有按题目要求用子函数处理字符串
//问题3：输出字符串用循环 for(int i=0;s[i];i++) cout<<s[i]; 可以直接输出
//cout<<s<<endl;

//---------------------练习5---------------------------------------
//编写递归函数将一个正整数的2的因子删去。如：312=39×23，删去2的因子后得39。
#include <iostream>
using namespace std;
int f(int n) {
    if (n % 2 != 0)
        return n;
    else
        return f(n / 2);
}
int main() {
    int a;
    cin >> a;
    cout << a << " 删去2的因数后为 " << f(a) << endl;
    return 0;
}

//---------------------练习6---------------------------------------
//输入n个数，输出正数个数。负数个数，平均值
#include <iostream> 
using namespace std;
int posNum,negNum;
double average;
void proceed(double a[ ],int n);
int main( ) 
{	double a[100];  int i,n;
	cin>>n;
	for(i=0;i<n;i++)  cin>>a[i];
	proceed(a,n);
	cout<<"正数个数="<<posNum<<"\t负数个数="<<negNum
		<<"\t平均值="<<average<<endl;
	return 0;
}
void proceed(double a[ ],int n)
{	posNum=negNum=0;  average=0;
	for(int i=0;i<n;i++)
	{	if(a[i]>0)      posNum++;
		else if(a[i]<0) negNum++;
		average+=a[i];
	}
	average/=n;
}
//问题1：没有按题目要求在主函数输出结果，而是在子函数内输出
//问题2：全局变量使用前清为0，或没有附初值