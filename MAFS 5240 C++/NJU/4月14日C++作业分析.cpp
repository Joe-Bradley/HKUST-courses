//----------------  Ex10.2  ------------------------------------
class  Time
{  private:  int h,m,s; //ʱ����
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
// ����1��get����û����ȡ������


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
	if(L1.isParallel(L2)) cout<<"L1��L2ƽ��"<<endl;
	if(L1.isVertical(L2)) cout<<"L1��L2��ֱ"<<endl;
	if(L1.isVertical(L3)) cout<<"L1��L3��ֱ"<<endl;
	return 0;
}
// ����1������� L1.show; ʵ�ʲ��Ǻ������ã�����ȡ����ָ�룬�ɸ�Ϊ L1.show();
// ����2���ж�ƽ���ñ��ʽ��fabs(a/L.a-b/L.b)<eps����ֱ�߷���Ϊ y-10=0 ʱ�����
// ����3���ж�ƽ���ñ��ʽ��a*L.b-b*L.a==0��û�п�������Ӱ�죬Ӧ�ÿ����������
// ����4�����壺const double eps=10e-7; ʵ�ʱ�ʾ10��10^(-7)��1e-7�ű�ʾ10^(-7)

 
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
// ����1��max()�ڵĴ��룺for(int t=a[0],i=1;i<n;i++) ... ������t��int�ͣ�
// 	Ӧ�øĳ�double�ͣ��ɸĶ����£�double t=a[0];for(int i=1;i<n;i++) ...
// ����2��Ĭ�Ϲ��캯������Ϊ��Statistics() { }
// 	�����������룺Statistics b; double x; for(int i=1;i<=10;i++){cin>>x;b.add(x);}
// 	������⣬��ΪĬ�Ϲ����b����Ա����nֵ��ȷ����������0��ʹ��a[n++]=x;ʱ�����
// ����3��variance()�ڵĴ��룺for(int i=0;i<n;i++)t+=(p[i]-average)*(p[i]-average);
// 	averageΪ����������ʾ����ָ�룬���Ǻ�������average()
// ����4��variance()�ڵĴ��룺for(int i=0;i<n;i++)t+=(p[i]-average())*(p[i]-average());
// 	�����﷨û����Ч�ʵ��£���Ϊÿ��ѭ������ʱҪ��������average()����2n�κ�������
// 	�ɸ�Ϊ��double t=0,av=average();for(int i=0;i<n;i++)t+=(p[i]-av)*(p[i]-av);


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
// ����1����Ա�����Ĵ������� if((p=s)!=0) �� if(p) ���жϣ�ʵ��s�����ܵ���0ָ�룬
// 	set(s)ͨ��Ҳ����ʹ�� set(0)���÷������ڲ�pһ��������0ָ�룬���ý���0ָ���б�
// ����2��Ĭ�Ϲ��캯�����壺String() { p=""; }����һ��������Ŀ��Ĭ�ϲ�����Ҫ��
// 	�ڶ�����Ķ�����pӦ��ָ��һ����̬���飬������һ���������ڵ��ַ���


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
	cout<<"����Ҫɾ�����ַ���:";  cin>>ss;  s2.del(ss);
	s2.show();
	return 0;
}
// ����1��add(char *s)�ڵĴ��룺
// 	if(n==size){char *p2=new char[size+5];
// 		for(int i=0;i<n;i++){p2[i]=p[i];delete[]p[i];}
// 		delete[]p; p=p2; }
// 	�������������⣺һ��p2��СΪsize+5����������¼��С�ı���sizeû�иı䣻
// 	��������delete[]p[i]; ִ��p2[i]=p[i];��p2[i]��p[i]��ָ��ͬһ����̬���飬
// 	delete[]p[i];��ö�̬���鱻�ͷţ�p2[i]�Ͳ���ָ��һ�����ڵ��ַ������ˡ�
// 	����˸Ķ���size+5�ĳ�size+=5�����delete[]p[i];ɾȥ