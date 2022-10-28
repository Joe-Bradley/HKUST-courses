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
// ����1������increase(x)��neg(x)�����������������ĿҪ�󲻷�
// ����2��ʹ�� x=x++; ������ģ�����ɵĽ����Ӧ���� x++; �� x=x+1;


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
	cout<<"\""<<p<<"\"��ASCII���ܺ�Ϊ��"<<sumChar(s)<<endl;
	return 0;
}
int sumChar(const char *s)
{	int sum=0;  while(*s) sum+=*s++;   return sum;  }
�� sumChar��Ƴɣ�
int sumChar(const char*s) { int sum=0; for(const char *p=s;*p;p++) sum+=*p; return sum; }

// ����1���ַ�ASCII���ʾ���󣬼����룺
// 	for(sum=0;*s;s++) sum+='*s';
// 	sָ����ַ���ASCII�����*s��ʾ��'*s'�Ǵ�����ַ�������ʾ


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
{	int t=x; x=z; z=y; y=t;  }  //�ֻ���x<=z<=y<=x
// ����1���ֻ������������ x<=y<=z<=x


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
// ��min��Ƴ�
// int &min(int &x,int &y)
// {	if(x<y)  return x;
// 	else     return y;
// }
// ����1��min����������Ƴɷ������ֵ�ı���������
// ����2�����ص��������ı��������ã������룺
// 	int &min(int &x,int &y) { int m=(x<y?x:y); return m; }
// 	Ӧ�÷��ر���x��y�����ã�ѡ����һ�������ɱ�����ֵȷ����ȡֵС�ı���
// 	��Σ��������뷵����һ�������������Ѳ��ٴ��ڵı���m(�Ӻ�������mҪ����)������


//----------------  Ex8.24  ------------------------------------
# include <iostream> 
using namespace std;
void count(const char *s,int &alphabet,int &space,int &digit);
int main( )
{	char s[80];  int alphabet,space,digit;
	cin.getline(s,80);  count(s,alphabet,space,digit);
	cout<<"�ַ���:\n"<<s<<"\n��"<<alphabet<<"����ĸ�ַ���"
		<<space<<"���ո�"<<digit<<"�������ַ�"<<endl;
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
// ����1��������ʾ���󣬼����룺if('0'<=*s<='9') digit++;
// 	Ӧ�ø�Ϊ��if('0'<=*s&&*s<='9') digit++;
// ����2��ͳ��ֵ���㲻���Ӻ���count�ڽ��У���û�����㡣
// 	��Ϊһ�������Ĺ��ܣ�count������Ӧ�ð�����ͳ��ֵ�����ͳ�Ƶ�ȫ���̣�
// 	���ܵķ�ɢ�ᵼ���Ӻ���ʹ�ò��㣨��Ҫ���ȶ�ͳ��ֵ���㣩��
