//----------------  Ex9.1  ------------------------------------
# include <iostream>
using namespace std;
#define MAX(x,y)  ((x)>(y)?(x):(y))
#define MIN(x,y)  ((x)<(y)?(x):(y))
int main( )
{	
	double a,b,c;
	cin>>a>>b>>c;
	cout<<MAX(a,b)<<"\t"<<MIN(a,b)<<endl;
	cout<<MAX(a,MAX(b,c))<<"\t"<<MIN(MIN(a,b),c)<<endl;
	return 0;
}


//----------------  Ex9.2  ------------------------------------
# include <iostream>
using namespace std;
#define SGN(x)  ((x)<0?-1:((x)>0?1:0))
int main( )
{	
	double  x;
	cin>>x;  cout<<"x="<<x<<"\tSGN="<<SGN(x)<<endl;
	return 0;
}


//----------------  Ex9.3  ------------------------------------
# include <iostream>
using namespace std;
#define PI  3.141592653589793238
#define TODEGREE(arc)  ((arc)/PI*180)
#define TOARC(degree)  ((degree)*PI/180)
int main( )
{	
	double  x;
	cout<<"输入角度值：";  cin>>x;
	cout<<"角度="<<x<<"°\t弧度="<<TOARC(x)<<endl;
	cout<<"输入弧度值：";  cin>>x;
	cout<<"弧度="<<x<<"°\t角度="<<TODEGREE(x)<<endl;
	return 0;
}
// 问题1：公式用错，宏定义为： #define TOARC(degree) degree*3.1416/2/180
// 问题2：宏定义为：#define TOARC(degree) ((degree)/180*3.1416)
// 	由于整数除，宏调用 TOARC(120) 结果为0，应该用：((degree)/180.*3.1416)
// 问题3：宏定义为：#define TOARC(degree)  ((degree)=(degree)/180.*3.1416)
// 	当宏调用参数为常数时出错，如 TOARC(120)


//----------------  Ex9.4  ------------------------------------
# include <iostream>
using namespace std;
#define FTOC(temp)  ((temp-32)*5/9.)
#define CTOF(temp)  ((temp)*9/5.+32)
int main( )
{	
	double  F,C;
	cout<<"输入摄氏温度：";  cin>>C;
	cout<<"摄氏 "<<C<<"度=华氏 "<<CTOF(C)<<"度\n";
	cout<<"输入华氏温度：";  cin>>F;
	cout<<"华氏 "<<F<<"度=摄氏 "<<FTOC(F)<<"度\n";
	return 0;
}
// 问题1：宏定义为：#define CTOF(temp) (9/5*(temp)+32)
// 	由于整数除，式子中9/5的结果为1，于是公式变为：(1*(temp)+32)
// 	应该用：(9./5*(temp)+32)


//----------------  Ex9.5  ------------------------------------
# include <iostream>
using namespace std;
#define LENGTH
void sort(char **ps);
int main( )
{	char *str[]={"Red","Orange","Yellow","Green","Cyan","Blue",0};
	sort(str);
	for(char **p=str;*p;p++)  cout<<*p<<endl;
	return 0;
}
void sort(char **ps)
{	char **min,**q,*t;
	for(;*ps;ps++)
	{
		for(min=ps,q=ps+1;*q;q++)
#ifdef  LENGTH
			if(strlen(*q)<strlen(*min)) min=q;
#else
			if(strcmp(*q,*min)<0)  min=q;
#endif
		if(min!=ps)  { t=*min; *min=*ps; *ps=t; }
	}
}
// 问题1：字符指针数组漏了0指针结束，见代码：
// 	char *s[]={"ABC","ABCD","AAA"};
// 	应添加0指针，即 char *s[]={"ABC","ABCD","AAA",0};
// 问题2：用函数input或程序片段实现输入多个字符串，不符合题目要求
// 问题3：定义两个排序函数sort1和sort2，用宏LENGTH进行条件编译
// 	来选择调用sort1或sort2，不符合按题目要求


//----------------  Ex9.7  ------------------------------------
# include <iostream>
using namespace  std;
# define  LBRACKET  “(”
# define  COMMA  “,”
# define  RBRACKET  “)”
# define  OUT(x,y)  LBRACKET<<(x)<<COMMA<<(y)<<RBRACKET
# define  COMMA2  “LBRACKET”
int  main()
{	cout<<LBRACKET<<3<<COMMA<< -4<<RBRACKET<<endl;
	cout<<OUT(-100,200)<<endl;
	cout<<COMMA2<<endl;
	return 0;
}
// 运行结果：
// (3,-4)
// (-100,200)
// LBRACKET


//----------------  Ex9.8  ------------------------------------
# include <iostream>
using namespace  std;
# define  SWAP(x,y)  { double t;  t=x; x=y; y=t;  }
# define  OUT(x,y)   cout<<(x)<< “\t”<<(y)<<endl;
# define  ADDSHIFT(x,y,z) {  z=x+y; x=y; y=z; }
# define  PROMPT(m)  “斐波那契数列的第”<<m<< “项是：”
int  main()
{	int  f1=1,f2=0,fn=1,n=10,i;  double a=3.14,b=2.718;
	for(i=1;i<=n;i++)  ADDSHIFT(f1,f2,fn);
	cout<< PROMPT(n)<<fn<<endl;
	OUT(a,b);  SWAP(a,b);   OUT(a,b);	
	return 0;
}
// 运行结果：
// 斐波那契数列的第10项是：55
// 3.14    2.718
// 2.718   3.14
