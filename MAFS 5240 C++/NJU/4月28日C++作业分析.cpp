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
// 问题1：没有设计静态成员函数，不符合题目要求


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
	{ cout<<"正值对象："<<pos<<"\t0值对象："<<zero<<"\t负值对象："<<neg<<endl;}
};
int A::pos=0,A::zero=0,A::neg=0;
int main( )
{	A oa(12),ob(-1),oc(110);  
	{ 	A d[20];  A::showCount();  }
	A::showCount();
	return 0;
}
// 或者类A设计为：
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
// 	{ cout<<"正值对象："<<pos<<"\t0值对象："<<zero<<"\t负值对象："<<neg<<endl;}
// };
// int A::pos=0,A::neg=0,A::zero=0;

// 问题1：使用 ob.~A()，显式调用析构函数，造成没有对象实际撤销的情况下统计数据发生变动
// 问题2：没有设计静态成员函数，不符合题目要求
// 问题3：漏写了析构函数，当有对象析构时，统计数据就不正确了
// 问题4：使用赋值语句进行对象赋值，会造成赋值中的统计数据改变，需要重载赋值运算符(见12.3节)


//----------------  Ex11.3  ------------------------------------
/*11.3 编程定义链表结点类node，它含一个int型变量x和后向指针next，
定义静态成员变量head和tail作为链表的头指针和尾指针，静态成员函数
getHead()取得链表头指针head，静态成员函数show()输出链表的值，
类node的带参构造函数自动将该结点接入链表末尾，析构函数自动将该
结点从链表中删去。主函数验证。*/
# include <iostream>
using namespace std;
//---------------------- 类 node 的定义 -----------------------
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

// 问题1：没有按要求在node构造函数中将结点接入链表末尾，在析构函数中将结点脱出链表
// 问题2：析构函数只将末结点脱出链表，实际可能删除的是其它结点
// 问题3：构造函数在函数说明和函数外部定义中都提供了默认参数，应该只在函数说明中提供默认参数
// 问题4：node构造函数中用new生成结点，见代码：
// 	node(int ix=0) { node *p; p=new node(ix);
// 			if(head==0) head=p; else tail->next=p; ... }
// 	每次生成node结点，会调用构造函数，执行构造函数中的p=new node(ix);时，
// 	又生成另一个node结点2，在生成结点2时，执行构造函数中的p=new node(ix);时，
// 	又生成另外的node结点3，这样反复执行生成结点的操作，永无止境，成为死循环。
// 	node构造函数体内要添加到链表末尾的结点是this指向的结点，而不是另外生成一个结点。


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
// 问题1：友元函数为 int interval(....) ，不符合题目要求


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
// 问题1：友元函数为 void scale(vector &v,double s) ，不符合题目要求