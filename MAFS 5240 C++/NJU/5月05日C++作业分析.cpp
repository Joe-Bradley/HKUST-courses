//----------------  Ex11.8  ------------------------------------
# include <iostream>
using namespace std;
class Date
{
private:
	int y,m,d;
public:
	Date(int yy,int mm,int dd) { y=yy; m=mm; d=dd; }
	void show() { cout<<y<<"-"<<m<<"-"<<d<<endl; }
	friend class Person;
};
class Person
{
private:
	char Name[10],Sex[4];
	Date Birthday;
public:
	Person(char *na="",char *se="",int yy=1980,int mm=1,int dd=1);
	void show() {  cout<<Name<<"\t"<<Sex<<"\t"; Birthday.show();  }
	int age(Date d);
};
Person::Person(char *na,char *se,int yy,int mm,int dd):Birthday(yy,mm,dd)
{	strcpy(Name,na); strcpy(Sex,se);  }
int Person::age(Date d)
{	int d1=Birthday.y*10000+Birthday.m*100+Birthday.d,d2=d.y*10000+d.m*100+d.d,s;
	s=(d2-d1-1)/10000+1;  return s;   // s=(d2-d1)/10000;  if(d2>d1) s++;
}
int main( )
{	
	Person a("张三","男",1998,5,8);   Date d(2016,8,28);
	a.show();   d.show();
	cout<<a.age(d)<<endl;
	cout<<a.age(Date(2017,5,5))<<endl;
	return 0;
}
// 或 Person设计为：
// Date defaultDate(1980,1,1);
// class Person
// {
// private:
// 	char Name[20],Sex[4];  
// 	Date Birthday;
// public:
// 	Person(char *na="",char *se="",Date bd=defaultDate):Birthday(bd)
// 		{ strcpy(Name,na); strcpy(Sex,se);  }
// 	void show() {  cout<<Name<<"\t"<<Sex<<"\t"; Birthday.show();  }
// 	int age(Date d);
// };
// int Person::age(Date d)
// {	int a=d.y-Birthday.y;
// 	if((d.m>Birthday.m)||(d.m==Birthday.m&&d.d>Birthday.d)) a++;
// 	return a;
// }
// 问题1：age函数简单地返回年份差，应按题目要求计算岁数


//----------------  Ex12.1  ------------------------------------
# include <iostream>
using namespace std;
class fraction
{ private:
	int numerator,denominator;
public:
	fraction(int nu=0,int de=1) {  if(de==0) exit(1); if(de<0){nu=-nu;de=-de;}
	   int k=de; while(nu%k!=0||de%k!=0)k--; numerator=nu/k;denominator=de/k;}
	void show() { cout<<numerator<<"/"<<denominator<<endl; }
	fraction operator+(fraction b);
	fraction operator-(fraction b){ b.numerator*=-1;return *this+b; }
	fraction operator*(fraction b);
	fraction operator/(fraction b);
	friend bool operator<(fraction a,fraction b)
		{ return a.numerator*b.denominator<b.numerator*a.denominator; }
	friend bool operator<=(fraction a,fraction b){return !(b<a); }
	friend bool operator>(fraction a,fraction b){return b<a; }
	friend bool operator>=(fraction a,fraction b){ return !(a<b); }
	friend bool operator==(fraction a,fraction b){return (a<=b)&&(b<=a);}
	friend bool operator!=(fraction a,fraction b){return !(a==b);}
};
fraction fraction::operator+(fraction b)
{	return fraction(numerator*b.denominator+b.numerator*denominator,
		denominator*b.denominator);
}
fraction fraction::operator*(fraction b)
{	return fraction(numerator*b.numerator,denominator*b.denominator); }
fraction fraction::operator/(fraction b)
{	if(b.numerator==0)exit(1);
	return fraction(numerator*b.denominator,denominator*b.numerator);
}
int main( )
{	
	fraction a(3,4),b(-9,7),c,d,e,f;
	a.show();   b.show();
	c=a+b;  d=a-b;  e=a*b;  f=a/b;
	c.show();  d.show();  e.show();  f.show();
	if(d==b)  cout<<"d==b"<<endl;
	else      cout<<"d!=b"<<endl;
	if(e<f)  cout<<"e<f"<<endl;
	else if(e>f) cout<<"e>f"<<endl;
	else     cout<<"e==f"<<endl;
	return 0;
}
// 问题1：除法时没有考虑0除数或分母小于0的情况
// 问题2：没有默认构造函数，但main中有默认构造的对象


//----------------  Ex12.2  ------------------------------------
# include <iostream>
using namespace std;
class vector3D
{
private:
	double x,y,z;
public:
	vector3D(double xx=0,double yy=0,double zz=0) { x=xx; y=yy; z=zz; }
	void show() { cout<<"("<<x<<","<<y<<","<<z<<")"<<endl; }
	vector3D operator+(vector3D b) { return vector3D(x+b.x,y+b.y,z+b.z); }
	vector3D operator-(vector3D b) { return vector3D(x-b.x,y-b.y,z-b.z); }
	bool operator==(vector3D b) { return x==b.x&&y==b.y&&z==b.z; }
	bool operator!=(vector3D b) { return !(*this==b); }
	friend vector3D operator*(double s,vector3D b)
		{return vector3D(s*b.x,s*b.y,s*b.z);}
	friend double operator&(vector3D a,vector3D b)
	{	return a.x*b.x+a.y*b.y+a.z*b.z;}
};
int main() 
{	vector3D  v1(3,4,-2),v2(7,-1,5),v3,v4,v5;  double d;
	v1.show();   v2.show();
	v3=v1+v2;  v4=v1-v2;  v5=3.0*v1;  d=v1&v2;
	v3.show();  v4.show();  v5.show();
	cout<<d<<endl;
	return 0;
}
// 问题1：重载数乘为vector3D*double，按题目要求重载的是double*vector3D
// 问题2：重载&返回叉乘结果，按题目要求应该返回内积


//----------------  Ex12.6  ------------------------------------
# include <iostream>
using namespace std;
class Set
{
private:
	int p[1000];  int n;
public:
	Set() { n=0; }
	void show() { for(int i=0;i<n;i++) cout<<p[i]<<"\t"; cout<<endl;}
	bool in(int x){for(int i=0;i<n;i++)if(x==p[i])return true; return false;}
	bool empty() { return n==0; }
	Set operator+(Set &b);
	Set operator+(int x){Set c(*this); if(!c.in(x))c.p[c.n++]=x; return c; }
	Set operator-(int x);
	Set operator*(Set &b);
	bool operator==(Set &b) { return (*this+b).n==(*this*b).n; }
	bool operator!=(Set &b) { return !(*this==b); }
};
Set Set::operator+(Set &b)
{Set c(*this); for(int i=0;i<b.n;i++) if(!c.in(b.p[i]))c.p[c.n++]=b.p[i]; return c; }
Set Set::operator-(int x)
{	Set c(*this);  int i,j;	for(i=0;i<c.n;i++) if(c.p[i]==x) break;
	if(i<c.n) { for(j=i;j<c.n-1;j++) c.p[j]=c.p[j+1]; c.n--; }  
	return c;
}
Set Set::operator*(Set &b)
{	Set c; for(int i=0;i<b.n;i++) if(in(b.p[i])) c.p[c.n++]=b.p[i]; return c;}
int main( )
{	
	Set a,b,c,d,e;   int i,j;
	for(i=0;i<10;i++)  { a=a+(i*i);  b=b+5*i;  }
	a.show();  b.show();
	c=a+b;  d=a*b;   c.show();  d.show();
	for(j=9;j>=0;j--)  e=e+j*j;
	a.show();  e.show();
	if(a==e)  cout<<"a==e"<<endl;
	return 0;
}
// 问题1：没有默认构造函数，不符合题目要求
// 问题2：没有重载==，不符合题目要求
// 问题3：重载==时，比较的是有序数据，但集合数据是无序的，{1,2,3}=={3,1,2}
// 问题4：重载Set+int时，没有考虑添加的数据必须与集合内数据不重复
// 问题5：重载+,-,*时，改动了第一操作数，即c=a+b时，对象a也发生改变


//----------------  Ex12.7  ------------------------------------
# include <iostream>
# include <cmath>
using namespace std;
double zero[1]={0};
class Polynomial
{
private:
	double *p;  int n;
	void copy(double *pp,int nn)
	{ while(nn>0&&fabs(pp[nn])<1e-8) nn--;n=nn;p=new double[n+1];
		for(int i=0;i<=n;i++) p[i]=pp[i]; }
public:
	Polynomial(double *pp=zero,int nn=0){ copy(pp,nn); }
	Polynomial(Polynomial &b){ copy(b.p,b.n); }
	~Polynomial() { delete[]p; }
	Polynomial &operator=(Polynomial &b){delete[]p;copy(b.p,b.n);return *this;}
	void show();
	Polynomial operator+(Polynomial &b);
	Polynomial operator-(Polynomial &b)
	   {Polynomial c(b);for(int i=0;i<=c.n;i++)c.p[i]=-c.p[i];return *this+c;}
	Polynomial operator*(Polynomial &b);
	friend bool operator==(Polynomial &a,Polynomial &b)
	{	if(a.n!=b.n) return false;
		for(int i=a.n;i>=0;i--) if(fabs(a.p[i]-b.p[i])>=1e-8) return false;
		return true;}
 	friend bool operator!=(Polynomial &a,Polynomial &b){return !(a==b);}
};
void Polynomial::show()
{ for(int i=n;i>0;i--)cout<<"("<<p[i]<<")x^"<<i<<"+"; cout<<"("<<p[0]<<")"<<endl;}
Polynomial Polynomial::operator+(Polynomial &b)
{	double d[200]={0}; int i;
	for(i=0;i<=n;i++) d[i]+=p[i];  for(i=0;i<=b.n;i++) d[i]+=b.p[i];
	return Polynomial(d,n>b.n?n:b.n);
}
Polynomial Polynomial::operator*(Polynomial &b)
{	double d[200]={0};
	for(int i=0;i<=n;i++)for(int j=0;j<=b.n;j++) d[i+j]+=p[i]*b.p[j]; 
	return Polynomial(d,n+b.n);
}
int main( )
{	// 3x^2-5x+6     x^3-2x^2+5x+2.7
	double ap[ ]={6,-5,3},bp[ ]={2.7,5,-2,1};
	Polynomial a(ap,2),b(bp,3),c,d,e;
	a.show();  b.show(); 
	c=a+b;  d=c-b;  e=a*b;
	c.show();  d.show();  e.show();
	if(a==d) cout<<"a==d"<<endl;
	return 0;
}
// 问题1：没有重载=，不符合题目要求
// 问题2：重载+,-,*时，改动了第一操作数
// 问题3：构造函数中复制数据时，改动了成员变量p的值
// 问题4：没有考虑最高次项系数必须非零，+,-运算后应该调整
// 问题5：成员变量n不是多项式次数，而是多项式元素个数
// 问题6：加法运算时，代码错误：
// 	见代码1：double *q=new double[(n>b.n?n:b.n)+1];
// 		for(i=0;i<=n;i++) q[i]+=p[i]; for(i=0;i<=b.n;i++) q[i]+=b.p[i];
// 	代码2：double q[200]; int nn=n>b.n?n:b.n;
// 		for(i=0;i<=nn;i++) q[i]=p[i]+b.p[i];
// 	代码1的q数组没有清零，应该运算前清零，可添加 memset(q,0,((n>b.n?n:b.n)+1)*8);
// 	代码2的循环运算当i为nn时，其中一个数组可能超界使用，会将一些额外数据加入q数组