//----------------  Ex8.17  ------------------------------------
# include <iostream> 
using namespace std;
void ForAllDo(int *a,int n,void(*f)(int&));
void show(int&x),increase(int&x),neg(int&x);
int main( )
{	int a[ ]={7,-1,5,9,0,-21,91,4},n,i;
	n=sizeof(a)/sizeof(a[0]);
	ForAllDo(a,n,show);
	ForAllDo(a,n,increase);
	for(i=0;i<n;i++) cout<<a[i]<<"\t";  cout<<endl<<endl;
	ForAllDo(a,n,neg);
	for(i=0;i<n;i++) cout<<a[i]<<"\t";  cout<<endl;
	return 0;
}
void ForAllDo(int *a,int n,void(*f)(int&))
{
	for(int i=0;i<n;i++) f(a[i]);
}
void show(int &x)  {  cout<<x<<endl;  }
void increase(int &x)  {  x++;  }
void neg(int &x)  {  x=-x;  }
// 问题1：函数increase(x)、neg(x)仅仅用于输出，与题目要求不符
// 问题2：使用 x=x++; ，会有模棱两可的结果，应该用 x++; 或 x=x+1;


//----------------  Ex8.18  ------------------------------------
# include <iostream> 
# include <cmath>
using namespace std;
double f2(double x),f3(double x);
double derived(double(*f)(double),double x);
int main( )
{	cout<<"derived(sin)="<<derived(sin,0)<<endl;
	cout<<"derived(f2)="<<derived(f2,1)<<endl;
	cout<<"derived(f3)="<<derived(f3,4)<<endl;
	return 0;
}
double  f2(double x) { return exp(2*x); }
double  f3(double x) { return 3*x*x-5*x+2.7;  }
double derived(double(*f)(double),double x)
{	return (f(x-0.2)-8*f(x-0.1)+8*f(x+0.1)-f(x+0.2))/1.2;  }


//----------------  Ex8.21  ------------------------------------
# include <iostream> 
using namespace std;
int sumChar(const char *s);
int main( )
{	char s[80];  cin.getline(s,80);
	cout<<"\""<<p<<"\"的ASCII码总和为："<<sumChar(s)<<endl;
	return 0;
}
int sumChar(const char *s)
{	int sum=0;  while(*s) sum+=*s++;   return sum;  }
或 sumChar设计成：
int sumChar(const char*s) { int sum=0; for(const char *p=s;*p;p++) sum+=*p; return sum; }

// 问题1：字符ASCII码表示错误，见代码：
// 	for(sum=0;*s;s++) sum+='*s';
// 	s指向的字符的ASCII码就用*s表示，'*s'是错误的字符常量表示


//----------------  Ex8.22  ------------------------------------
#include <iostream>
using namespace std;
void rotate(int &x,int &y,int &z);
int main( )
{	int a,b,c;
	a=3;  b=4;  c=5;
	cout<<a<<"\t"<<b<<"\t"<<c<<endl;
	rotate(a,b,c);
	cout<<a<<"\t"<<b<<"\t"<<c<<endl;
	return 0;
}
void rotate(int &x,int &y,int &z)
{	int t=x; x=z; z=y; y=t;  }  //轮换：x<=z<=y<=x
// 问题1：轮换次序搞错，变成了 x<=y<=z<=x


//----------------  Ex8.23  ------------------------------------
#include <iostream>
using namespace std;
int &min(int &x,int &y);
int main( )
{	int a=3,b=4;
	cout<<min(a,b)<<endl;
	min(a,b)+=5;
	cout<<a<<"\t"<<b<<endl;
	return 0;
}
int &min(int &x,int &y)
{	return x<y?x:y;  }
// 或min设计成
// int &min(int &x,int &y)
// {	if(x<y)  return x;
// 	else     return y;
// }
// 问题1：min函数错误设计成返回最大值的变量的引用
// 问题2：返回的是其它的变量的引用，见代码：
// 	int &min(int &x,int &y) { int m=(x<y?x:y); return m; }
// 	应该返回变量x或y的引用，选择哪一个变量由变量的值确定，取值小的变量
// 	其次，上述代码返回了一个主调函数中已不再存在的变量m(子函数结束m要撤销)的引用


//----------------  Ex8.24  ------------------------------------
# include <iostream> 
using namespace std;
void count(const char *s,int &alphabet,int &space,int &digit);
int main( )
{	char s[80];  int alphabet,space,digit;
	cin.getline(s,80);  count(s,alphabet,space,digit);
	cout<<"字符串:\n"<<s<<"\n含"<<alphabet<<"个字母字符，"
		<<space<<"个空格，"<<digit<<"个数字字符"<<endl;
	return 0;
}
void count(const char *s,int &alphabet,int &space,int &digit)
{	alphabet=space=digit=0;
	while(*s)
	{	if(*s>='A'&&*s<='Z'||*s>='a'&&*s<='z') alphabet++;
		else if(*s==' ')    space++;
		else if(*s>='0'&&*s<='9')  digit++;
		s++;
	}
}
// 问题1：条件表示错误，见代码：if('0'<=*s<='9') digit++;
// 	应该改为：if('0'<=*s&&*s<='9') digit++;
// 问题2：统计值清零不在子函数count内进行，或没有清零。
// 	作为一个完整的功能，count函数内应该包含从统计值清零和统计的全过程，
// 	功能的分散会导致子函数使用不便（如要事先对统计值清零）。
