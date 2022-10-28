5月12日C++作业分析
//----------------  Ex12.10  ------------------------------------
# include <iostream>
using namespace std;
class money
{
private:
	int yuan,jiao,fen;
public:
	money(int y=0,int j=0,int f=0) { set(y,j,f); }
	void set(int y,int j,int f)
	{  int d=y*100+j*10+f; yuan=d/100; jiao=d/10%10; fen=d%10;}
	money operator+(money b) 
	{ return money(yuan+b.yuan,jiao+b.jiao,fen+b.fen);}
	money operator-(money b)
	{ return money(yuan-b.yuan,jiao-b.jiao,fen-b.fen); }
	money &operator++(){ set(yuan,jiao,fen+1);return *this;}
	money operator++(int){money t(*this);set(yuan,jiao,fen+1);return t;}
	money &operator--(){ set(yuan,jiao,fen-1);return *this;}
	money operator--(int){money t(*this);set(yuan,jiao,fen-1);return t;}
	friend ostream &operator<<(ostream &os,money &b)
	{ os<<b.yuan<<"元"<<b.jiao<<"角"<<b.fen<<"分"<<endl;return os; }
	friend istream &operator>>(istream &is,money &b)
	{ is>>b.yuan>>b.jiao>>b.fen; b.set(b.yuan,b.jiao,b.fen); return is; }
	operator double() { return yuan+jiao/10.0+fen/100.0; }
};
int main( )
{	
	money a(23,4,5),b(12,3,0),c,d;
	c=a+b;  d=a-b;   
	cout<<(double)a<<"\t"<<a<<(double)b<<"\t"<<b<<c<<d<<endl;
	cin>>a;
	a++;  b=--a;
	cout<<a<<b<<endl;
	return 0;
}
// 问题1：没有重载后置++、--
// 问题2：没有设计转换函数
// 问题3：重载>>时，第二操作数对象不是引用参数，造成输入数据失败


//----------------  Ex12.13  ------------------------------------
# include <iostream>
using namespace std;
class Array
{
private:
	int *p,size,n;
	void copy(int ss,int nn,int *pp=0)
	{ size=ss; n=nn; p=new int[size]; if(pp)for(int i=0;i<n;i++)p[i]=pp[i]; }
public:
	Array(){ copy(10,0); }
	Array(Array &b){ copy(b.size,b.n,b.p); }
	~Array() { delete[]p; }
	void show(){ for(int i=0;i<n;i++) cout<<p[i]<<"\t"; cout<<endl; }
	int getNum() { return n; }
	Array &operator=(Array &b){delete[]p;copy(b.size,b.n,b.p);return *this;}
	Array &operator+=(int x);
	Array &operator-=(int x);
	int &operator[](int k){ static int t=0;return (k>=0&&k<n?p[k]:t);}
};
Array &Array::operator+=(int x)
{	if(n==size)  { int *pp=p; copy(size+5,n,pp); delete[]pp;  }
	p[n++]=x;  return *this;
}
Array &Array::operator-=(int x)
{	int i; for(i=0;i<n;i++) if(x==p[i]) break;
	if(i<n) {  for(int j=i;j<n-1;j++) p[j]=p[j+1]; n--; }  return *this;
}
int main()
{
	Array oa;  int i;
	for(i=1;i<=10;i++) oa+=i*i;
	oa.show();
	for(i=20;i<=80;i++) oa-=i;
	oa.show();
	i=oa.getNum();  oa[i-1]=12345;
	oa.show();
	return 0;
}
// 问题1：复制构造函数和重载=的函数，没有进行深复制，而是直接复制指针(浅复制)
// 问题2：重载+=时，在需要数组扩展的情况下没有开辟更大的动态数组，而是直接增加size的值
// 问题3：重载+=时，进行扩展的多个语句没有用花括号括起成为一个内嵌语句，从而运行错误
// 问题4：记录数组长度的成员变量名用小写字母l，极易与数字1混淆


//----------------  Ex12.14  ------------------------------------
# include <iostream>
using namespace std;
class Matrix
{ private:
	double *p;   int m,n;
	void copy(int mm,int nn,double *pp=0)
	{ m=mm;n=nn; p=new double[m*n];for(int i=0;i<m*n;i++)p[i]=(pp?pp[i]:0);}
public:
	Matrix(int mm=1,int nn=1) { copy(mm,nn); }
	Matrix(Matrix &b) { copy(b.m,b.n,b.p);  }
	~Matrix() { delete[]p; }
	void show(){for(int i=0;i<m*n;i++) cout<<p[i]<<((i+1)%n?"\t":"\n"); }
	int getRow() { return m; }
	int getColumn() { return n; }
	Matrix &operator=(Matrix &b) { delete[]p;copy(b.m,b.n,b.p);return *this;}
	Matrix operator+(Matrix &b);
	Matrix operator-(Matrix &b)
	{  Matrix t(b); for(int i=0;i<t.m*t.n;i++)t.p[i]=-t.p[i]; return *this+t;}
	Matrix operator*(Matrix &b);
	double &operator()(int i,int j)
	{ static double t=0;if(i>=0&&i<m&&j>=0&&j<n)return p[i*n+j];else return t;}
};
Matrix Matrix::operator+(Matrix &b)
{  if(m!=b.m||n!=b.n)  return *this;
   Matrix c(*this); for(int i=0;i<c.m*c.n;i++) c.p[i]+=b.p[i]; return c;
}
Matrix Matrix::operator*(Matrix &b)
{  if(n!=b.m)  return *this;
   Matrix c(m,b.n),&a=*this;
   for(int i=0;i<c.m;i++) for(int j=0;j<c.n;j++)
   {for(int k=0;k<n;k++)c(i,j)+=a(i,k)*b(k,j);}  return c;  }
int main()
{	int m,n,k,i,j;  cin>>m>>n>>k;  Matrix a(m,n),b(m,n),c(n,k),d;
	for(i=0;i<m;i++) for(j=0;j<m;j++) cin>>a(i,j);
	for(i=0;i<m;i++) for(j=0;j<m;j++) cin>>b(i,j);
	for(i=0;i<n;i++) for(j=0;j<k;j++) cin>>c(i,j);
	a.show();  b.show();  c.show();  d=(a+b)*c; d.show();
	return 0;
}
// 问题1：重载=时没有重新开辟新的动态数组，当新的矩阵更大时会超界使用原来的动态数组
// 问题2：重载+、-时，改动了第一操作数
// 问题3：重载圆括号()时，垃圾变量不是静态变量，实际使用时会使用已不存在的变量
// 问题4：内部表示(i,j)元素时，一维数组元素表示为p[i*m+j]，应该为p[i*n+j]
// 问题5：默认构造函数设计错误，见代码：
// 	Matrix(int mm=0,int nn=0) { p=new double[mm*nn]; ... }
// 	默认构造时会出现 p=new double[0];的情况，默认参数可改为：(1,1)
// 问题6：复制构造函数中先释放动态数组，见代码：
// 	Matrix(Matrix &b) { delete[]p; ... }
// 	此处p并没有指向动态数组，故delete[]p;将产生运行错误，而重载=时需先delete[]p;


//----------------  Ex12.15  ------------------------------------
# include <iostream>
# include <cmath>
using namespace std;
class LessClass
{
private:
	double v;
public:
	LessClass(double vv=0) { v=vv; }
	bool operator()(double x,double y) { return fabs(x-v)<fabs(y-v); }
};
double min(double *a,int n,LessClass less)
{	double vmin=a[0];
	for(int i=0;i<n;i++)  if(less(a[i],vmin)) vmin=a[i];
	return vmin;
}
int main( )
{	
	double a[10]={2.1,-7.8,22.2,5.8,9.9,1.12,0.34,-10.1,-2.9,4.7};
	for(int i=0;i<10;i++) cout<<a[i]<<"\t";  cout<<endl;
	cout<<min(a,10,LessClass(0))<<endl;
	cout<<min(a,10,LessClass(5))<<endl;
	cout<<min(a,10,LessClass(-2))<<endl;
	return 0;
}


//----------------  Ex12.16  ------------------------------------
# include <iostream>
# include <string>
using namespace std;
int count(string s[],int n,int c[])  //函数统计s中n个有重复的单词，最后无重复
{	int i,j,k;			//单词个数返回，统计值记录在c中
	for(k=i=0;i<n;i++)
	{	for(j=0;j<k;j++) if(s[j]==s[i]) break;   //查找s[i]是否在保留的单词s[0]~s[k-1]中
		if(j==k) { s[k]=s[i]; c[k++]=1; } //不在则将新单词s[i]保存到s[k]中，c[k]为1
		else  c[j]++;                     //否则s[i]在s[0]~s[k-1]中的s[j]出现，统计值增加1，c[j]++
	}
	return k;
}
void sort(string s[],int n,int c[])  //函数对s和c同步按字典序进行排序
{	int i,j,k,t;
	for(i=0;i<n;i++)
	{	for(k=i,j=i+1;j<n;j++) if(s[j]<s[k]) k=j;
		if(k!=i) { s[k].swap(s[i]); t=c[k]; c[k]=c[i]; c[i]=t; }
	}
}
int main( )
{	string str[1000];  int c[1000];  int n=0;
	while(cin>>str[n]) n++;
	n=count(str,n,c);   sort(str,n,c); 
	for(int i=0;i<n;i++) cout<<str[i]<<"\t"<<c[i]<<endl;
	return 0;
}
或者sort如上，主函数改为：
int main( )
{	string str[1000],word;  int c[1000]={0},n=0,i;
	while(cin>>word)
	{	for(i=0;i<n;i++) if(word==str[i]) break;
		if(i==n) str[n++]=word;
		c[i]++;
	}
	sort(str,c,n);
	for(i=0;i<n;i++) cout<<str[i]<<"\t"<<c[i]<<endl;
	return 0;
}