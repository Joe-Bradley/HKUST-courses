//----------------  Ex10.2  ------------------------------------
class  Time
{  private:  int h,m,s; //时分秒
public:
	Time(int hh,int mm,int ss) { set(hh,mm,ss); }
	Time() {  h=m=s=0; }
	void set(int hh,int mm,int ss);
	void get(int &hh,int &mm,int &ss){ hh=h; mm=m; ss=s; }
	void show() { cout<<h<<":"<<m<<":"<<s<<endl;  }
};
void Time::set(int hh,int mm,int ss)
{	int tt=(hh*3600+mm*60+ss)%(24*3600);
	if(tt<0) tt+=24*3600;
	s=tt%60;  tt/=60;  m=tt%60;  h=tt/60;
}
int main()
{	Time t1(10,10,59),t2;  int hh,mm,ss;
	t1.show();   
	t1.get(hh,mm,ss);   t2.set(hh+2,mm+50,ss+30);
	t2.show();
	return 0;
}
// 问题1：get函数没有能取出数据


//----------------  Ex10.8  ------------------------------------
# include <iostream>
# include <cmath>
using namespace std;
const double eps=1e-7;
class Line
{ private: double a,b,c;
public:
    Line(double aa=1,double bb=0,double cc=0) { a=aa;b=bb;c=cc;}
    void show(){cout<<"("<<a<<")x+("<<b<<")y+("<<c<<")=0"<<endl;}
    bool isParalell(Line L) {  return fabs(a*L.b-L.a*b)<eps; }
    bool isVertical(Line L) { return fabs(a*L.a+b*L.b)<eps; }
};
int main( )
{	Line L1(1,2,1),L2(2,4,3),L3(1,-0.5,2.5); 
	L1.show();  L2.show();  L3.show();
	if(L1.isParallel(L2)) cout<<"L1和L2平行"<<endl;
	if(L1.isVertical(L2)) cout<<"L1和L2垂直"<<endl;
	if(L1.isVertical(L3)) cout<<"L1和L3垂直"<<endl;
	return 0;
}
// 问题1：输出用 L1.show; 实际不是函数调用，而是取函数指针，可改为 L1.show();
// 问题2：判定平行用表达式：fabs(a/L.a-b/L.b)<eps，当直线方程为 y-10=0 时会出错
// 问题3：判定平行用表达式：a*L.b-b*L.a==0，没有考虑误差的影响，应该考虑误差因素
// 问题4：误差定义：const double eps=10e-7; 实际表示10×10^(-7)，1e-7才表示10^(-7)

 
//----------------  Ex10.10  ------------------------------------
# include <iostream>
# include <cmath>
using namespace std;
class Statistics
{ private: double p[1000];  int n;
public:
    Statistics(double pp[],int nn){n=nn;for(int i=0;i<n;i++)p[i]=pp[i];}
    Statistics()  { n=0; }
    void add(double x) { p[n++]=x; }
    double max()
    {double t=p[0];for(int i=1;i<n;i++)if(p[i]>t)t=p[i];return t;}
    double min()
    {double t=p[0];for(int i=1;i<n;i++)if(p[i]<t)t=p[i];return t;}
    double average()
    {double t=0;for(int i=0;i<n;i++)t+=p[i];return t/n;}
    double variance()
    {	double av=average(),t=0;
	for(int i=0;i<n;i++)t+=(p[i]-av)*(p[i]-av);return t/n;
    }
    void show(){for(int i=0;i<n;i++)cout<<p[i]<<"\t";cout<<endl;}
};
int main( )
{	double a[1000];  int i,n;
	cin>>n;  for(i=0;i<n;i++) cin>>b[i];
	Statistics s1(a,n);  s1.show();
	Statistics s2; s2.add(s1.max()); s2.add(s1.min());
	s2.add(s1.average()); s2.add(s1.variance()); s2.show9);
	return 0;
}
// 问题1：max()内的代码：for(int t=a[0],i=1;i<n;i++) ... ，变量t是int型，
// 	应该改成double型，可改动如下：double t=a[0];for(int i=1;i<n;i++) ...
// 问题2：默认构造函数定义为：Statistics() { }
// 	若主函数代码：Statistics b; double x; for(int i=1;i<=10;i++){cin>>x;b.add(x);}
// 	会出问题，因为默认构造的b，成员变量n值不确定，并不是0，使用a[n++]=x;时会出错
// 问题3：variance()内的代码：for(int i=0;i<n;i++)t+=(p[i]-average)*(p[i]-average);
// 	average为函数名，表示函数指针，并非函数调用average()
// 问题4：variance()内的代码：for(int i=0;i<n;i++)t+=(p[i]-average())*(p[i]-average());
// 	代码语法没错，但效率低下，因为每次循环计算时要调用两次average()，共2n次函数调用
// 	可改为：double t=0,av=average();for(int i=0;i<n;i++)t+=(p[i]-av)*(p[i]-av);


//----------------  Ex10.13  ------------------------------------
# include <iostream>
using namespace std;
class String
{
private:
	char *p;
public:
	String(char *s="") { p=new char[strlen(s)+1]; strcpy(p,s);  }
	String(String &b) {  p=new char[strlen(b.p)+1]; strcpy(p,b.p);  }
	~String() { delete[]p; }
	void show() { cout<<p<<endl;  }
	void set(char *s) {  delete[]p;  p=new char[strlen(s)+1]; strcpy(p,s); }
};
int main( )
{	
	String s1("Hello"),s2;
	s2.set("Byby");  s1.show();  s2.show();
	String s3(s1);	 s3.show();
	return 0;
}
// 问题1：成员函数的代码用了 if((p=s)!=0) 或 if(p) 等判断，实际s不可能等于0指针，
// 	set(s)通常也不会使用 set(0)等用法，故内部p一定不会是0指针，不用进行0指针判别
// 问题2：默认构造函数定义：String() { p=""; }，第一不符合题目带默认参数的要求；
// 	第二构造的对象内p应该指向一个动态数组，而不是一个常量区内的字符串


//----------------  Ex10.15  ------------------------------------
# include <iostream>
using namespace std;
class StringArray
{ private:  char **p;  int size,n;
public:
	StringArray(){ size=10; n=0; p=new char*[size]; }
	StringArray(StringArray&b);
	~StringArray(){for(int i=0;i<n;i++)delete[]p[i];delete[]p;}
	void add(char *s);
	void del(char *s);
	void show(){ for(int i=0;i<n;i++) cout<<p[i]<<endl; }
};
StringArray::StringArray(StringArray &b)
{	size=b.size; n=b.n;  p=new char*[size]; 
	for(int i=0;i<n;i++)
	{ p[i]=new char[strlen(b.p[i])+1]; strcpy(p[i],b.p[i]);}
}
void StringArray::add(char *s)
{	if(n==size)
	{	char **p2=new char*[size+=5];
		for(int i=0;i<n;i++) p2[i]=p[i];
		delete[]p;   p=p2;
	}   p[n]=new char[strlen(s)+1]; strcpy(p[n++],s);
}
void StringArray::del(char *s)
{	int k,i;
	for(k=0;k<n;k++) if(strcmp(p[k],s)==0) break;
	if(k<n){delete[]p[k];for(i=k;i<n-1;i++)p[i]=p[i+1];n--;}
	if(n<size-10)
	{	char **p2=new char*[size-=5];
		for(i=0;i<n;i++) p2[i]=p[i];
		delete[]p;   p=p2;
	}
}
int main( )
{	
	StringArray s;  char str[80];  int i,n;
	cin>>n;   cin.get();
	for(i=0;i<n;i++) { cin.getline(str,80); s.add(str); }
	StringArray s2(s);
	cout<<"输入要删除的字符串:";  cin>>ss;  s2.del(ss);
	s2.show();
	return 0;
}
// 问题1：add(char *s)内的代码：
// 	if(n==size){char *p2=new char[size+5];
// 		for(int i=0;i<n;i++){p2[i]=p[i];delete[]p[i];}
// 		delete[]p; p=p2; }
// 	代码有两个问题：一是p2大小为size+5，但是最后记录大小的变量size没有改变；
// 	二是用了delete[]p[i]; 执行p2[i]=p[i];后p2[i]和p[i]都指向同一个动态数组，
// 	delete[]p[i];后该动态数组被释放，p2[i]就不在指向一个存在的字符数组了。
// 	可如此改动：size+5改成size+=5、语句delete[]p[i];删去