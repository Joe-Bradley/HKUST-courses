5��12��C++��ҵ����
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
	{ os<<b.yuan<<"Ԫ"<<b.jiao<<"��"<<b.fen<<"��"<<endl;return os; }
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
// ����1��û�����غ���++��--
// ����2��û�����ת������
// ����3������>>ʱ���ڶ����������������ò����������������ʧ��


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
// ����1�����ƹ��캯��������=�ĺ�����û�н�����ƣ�����ֱ�Ӹ���ָ��(ǳ����)
// ����2������+=ʱ������Ҫ������չ�������û�п��ٸ���Ķ�̬���飬����ֱ������size��ֵ
// ����3������+=ʱ��������չ�Ķ�����û���û����������Ϊһ����Ƕ��䣬�Ӷ����д���
// ����4����¼���鳤�ȵĳ�Ա��������Сд��ĸl������������1����


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
// ����1������=ʱû�����¿����µĶ�̬���飬���µľ������ʱ�ᳬ��ʹ��ԭ���Ķ�̬����
// ����2������+��-ʱ���Ķ��˵�һ������
// ����3������Բ����()ʱ�������������Ǿ�̬������ʵ��ʹ��ʱ��ʹ���Ѳ����ڵı���
// ����4���ڲ���ʾ(i,j)Ԫ��ʱ��һά����Ԫ�ر�ʾΪp[i*m+j]��Ӧ��Ϊp[i*n+j]
// ����5��Ĭ�Ϲ��캯����ƴ��󣬼����룺
// 	Matrix(int mm=0,int nn=0) { p=new double[mm*nn]; ... }
// 	Ĭ�Ϲ���ʱ����� p=new double[0];�������Ĭ�ϲ����ɸ�Ϊ��(1,1)
// ����6�����ƹ��캯�������ͷŶ�̬���飬�����룺
// 	Matrix(Matrix &b) { delete[]p; ... }
// 	�˴�p��û��ָ��̬���飬��delete[]p;���������д��󣬶�����=ʱ����delete[]p;


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
int count(string s[],int n,int c[])  //����ͳ��s��n�����ظ��ĵ��ʣ�������ظ�
{	int i,j,k;			//���ʸ������أ�ͳ��ֵ��¼��c��
	for(k=i=0;i<n;i++)
	{	for(j=0;j<k;j++) if(s[j]==s[i]) break;   //����s[i]�Ƿ��ڱ����ĵ���s[0]~s[k-1]��
		if(j==k) { s[k]=s[i]; c[k++]=1; } //�������µ���s[i]���浽s[k]�У�c[k]Ϊ1
		else  c[j]++;                     //����s[i]��s[0]~s[k-1]�е�s[j]���֣�ͳ��ֵ����1��c[j]++
	}
	return k;
}
void sort(string s[],int n,int c[])  //������s��cͬ�����ֵ����������
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
����sort���ϣ���������Ϊ��
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