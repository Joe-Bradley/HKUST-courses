//----------------  Ex11.1  ------------------------------------
# include <iostream>
using namespace std;
class A
{
private:
	int x;
	static int max;
public:
	A(int xx=0) { x=xx; if(x>max) max=x; }
	A(A &ob) { x=ob.x; if(x>max) max=x; }
	~A() { }
	void show() { cout<<"x="<<x<<endl; }
	static int getMax() { return max; }
};
int A::max=0x80000000;
int main()
{	A oa(10),ob(100);  A *p; p=new A(345);
	delete p;    cout<<A::getMax()<<endl;
	return 0;
}
// ����1��û����ƾ�̬��Ա��������������ĿҪ��


//----------------  Ex11.2  ------------------------------------
# include <iostream>
using namespace std;
class A
{
private:
	int x;
	static int pos,zero,neg;
public:
	A(int xx=0) { x=xx; if(x>0) pos++; else if(x<0) neg++; else zero++; }
	A(A &ob) { x=ob.x; if(x>0) pos++; else if(x<0) neg++; else zero++; }
	~A() { if(x>0) pos--; else if(x<0) neg--; else zero--; }
	void show() { cout<<"x="<<x<<endl; }
	void set(int xx)
	{ if(x>0) pos--; else if(x<0) neg--; else zero--; x=xx;
		if(x>0) pos++; else if(x<0) neg++; else zero++; }
	static void showCount() 
	{ cout<<"��ֵ����"<<pos<<"\t0ֵ����"<<zero<<"\t��ֵ����"<<neg<<endl;}
};
int A::pos=0,A::zero=0,A::neg=0;
int main( )
{	A oa(12),ob(-1),oc(110);  
	{ 	A d[20];  A::showCount();  }
	A::showCount();
	return 0;
}
// ������A���Ϊ��
// class A
// {
// private:
// 	int x;
// 	static int pos,zero,neg;
// 	void modify(int step=1) { int &t=(x>0?pos:x<0?neg:zero); t+=step;  }
// public:
// 	A(int ix=0) { x=xx; modify(); }
// 	A(A &ob) { x=ob.x; modify();  }
// 	~A()  {  modify(-1);  }
// 	void show() { cout<<"x="<<x<<endl; }
// 	void set(int ix) { modify(-1); x=ix; modify();  }
// 	static void showCount() 
// 	{ cout<<"��ֵ����"<<pos<<"\t0ֵ����"<<zero<<"\t��ֵ����"<<neg<<endl;}
// };
// int A::pos=0,A::neg=0,A::zero=0;

// ����1��ʹ�� ob.~A()����ʽ�����������������û�ж���ʵ�ʳ����������ͳ�����ݷ����䶯
// ����2��û����ƾ�̬��Ա��������������ĿҪ��
// ����3��©д���������������ж�������ʱ��ͳ�����ݾͲ���ȷ��
// ����4��ʹ�ø�ֵ�����ж���ֵ������ɸ�ֵ�е�ͳ�����ݸı䣬��Ҫ���ظ�ֵ�����(��12.3��)


//----------------  Ex11.3  ------------------------------------
/*11.3 ��̶�����������node������һ��int�ͱ���x�ͺ���ָ��next��
���徲̬��Ա����head��tail��Ϊ�����ͷָ���βָ�룬��̬��Ա����
getHead()ȡ������ͷָ��head����̬��Ա����show()��������ֵ��
��node�Ĵ��ι��캯���Զ����ý���������ĩβ�����������Զ�����
����������ɾȥ����������֤��*/
# include <iostream>
using namespace std;
//---------------------- �� node �Ķ��� -----------------------
class node
{
private:
	int x;
	node *next;
	static node *head,*tail;
public:
	node(int ix=0);
	~node();
	static node *getHead();
	static void show();
};
node *node::head=0,*node::tail=0;
int main( )
{	int xx;
	while(cin>>xx) {  new node(xx); }  cin.clear();
	node::show();
	while(node::getHead()) delete node::getHead();
	node oa(123),ob(345),oc[10];  node::show();
	return 0;
}
node::node(int ix)
{	x=ix;  next=0;
	if(head==0) head=tail=this;
	else { tail->next=this; tail=this; }
}
node::~node()
{	node *p1,*p2;
	for(p1=0,p2=head;p2!=0&&p2!=this;p1=p2,p2=p2->next);
	if(p1!=0)  p1->next=p2->next;
	else head=p2->next;
	if(tail==p2) tail=p1;
}
node *node::getHead()
{	return head;  }
void node::show()
{	for(node *p=head;p!=0;p=p->next) cout<<p->x<<"\t"; cout<<endl; }

// ����1��û�а�Ҫ����node���캯���н�����������ĩβ�������������н�����ѳ�����
// ����2����������ֻ��ĩ����ѳ�����ʵ�ʿ���ɾ�������������
// ����3�����캯���ں���˵���ͺ����ⲿ�����ж��ṩ��Ĭ�ϲ�����Ӧ��ֻ�ں���˵�����ṩĬ�ϲ���
// ����4��node���캯������new���ɽ�㣬�����룺
// 	node(int ix=0) { node *p; p=new node(ix);
// 			if(head==0) head=p; else tail->next=p; ... }
// 	ÿ������node��㣬����ù��캯����ִ�й��캯���е�p=new node(ix);ʱ��
// 	��������һ��node���2�������ɽ��2ʱ��ִ�й��캯���е�p=new node(ix);ʱ��
// 	�����������node���3����������ִ�����ɽ��Ĳ���������ֹ������Ϊ��ѭ����
// 	node���캯������Ҫ��ӵ�����ĩβ�Ľ����thisָ��Ľ�㣬��������������һ����㡣


//----------------  Ex11.5  ------------------------------------
# include <iostream>
using namespace std;
class Time
{
private:
	int hour,minute,second;
public:
	Time(int hh=0,int mm=0,int ss=0);
	void show() {  cout<<hour<<":"<<minute<<":"<<second<<endl; }
	friend Time interval(Time t1,Time t2);
};
int main( )
{	Time t1(12,30,5),t2(20,19,2),t;  t1.show();  t2.show();
	t=interval(t1,t2);   t.show();
	return 0;
}
Time::Time(int hh,int mm,int ss)
{	int s=hh*3600+mm*60+ss;  s=s%(24*3600);  if(s<0) s+=24*3600;
	hour=s/3600;  minute=s%3600/60;  second=s%60;
}
Time interval(Time t1,Time t2)
{	int s1=t1.hour*3600+t1.minute*60+t1.second;
	int s2=t2.hour*3600+t2.minute*60+t2.second;
	if(s1>s2)  return Time(0,0,s1-s2);
	else       return Time(0,0,s2-s1);
}
// ����1����Ԫ����Ϊ int interval(....) ����������ĿҪ��


//----------------  Ex11.7  ------------------------------------
# include <iostream>
# include <cmath>
using namespace std;
class vector
{
private:
	double x,y;
public:
	vector(double xx=0,double yy=0) { x=xx; y=yy; }
	void show() { cout<<"[ "<<x<<"  "<<y<<" ]"<<endl; }
	friend vector scale(vector v,double s);
	friend vector rotate(vector v,double stia);
};
vector scale(vector v,double s)
{	return vector(v.x*s,v.y*s);  } //{vector c;c.x=v.x*s;c.y=v.y*s;return c;}
vector rotate(vector v,double sita)
{   double c=cos(sita),s=sin(sita); return vector(v.x*c-v.y*s;v.x*s+v.y*c);}
int main( )
{	vector v(1,-2);  v.show();
	v=scale(v,3);  v=rotate(v,3.1415927/2);  v.show();
	return 0;
}
// ����1����Ԫ����Ϊ void scale(vector &v,double s) ����������ĿҪ��