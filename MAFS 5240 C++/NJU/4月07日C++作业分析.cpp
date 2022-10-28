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
	cout<<"����Ƕ�ֵ��";  cin>>x;
	cout<<"�Ƕ�="<<x<<"��\t����="<<TOARC(x)<<endl;
	cout<<"���뻡��ֵ��";  cin>>x;
	cout<<"����="<<x<<"��\t�Ƕ�="<<TODEGREE(x)<<endl;
	return 0;
}
// ����1����ʽ�ô��궨��Ϊ�� #define TOARC(degree) degree*3.1416/2/180
// ����2���궨��Ϊ��#define TOARC(degree) ((degree)/180*3.1416)
// 	����������������� TOARC(120) ���Ϊ0��Ӧ���ã�((degree)/180.*3.1416)
// ����3���궨��Ϊ��#define TOARC(degree)  ((degree)=(degree)/180.*3.1416)
// 	������ò���Ϊ����ʱ������ TOARC(120)


//----------------  Ex9.4  ------------------------------------
# include <iostream>
using namespace std;
#define FTOC(temp)  ((temp-32)*5/9.)
#define CTOF(temp)  ((temp)*9/5.+32)
int main( )
{	
	double  F,C;
	cout<<"���������¶ȣ�";  cin>>C;
	cout<<"���� "<<C<<"��=���� "<<CTOF(C)<<"��\n";
	cout<<"���뻪���¶ȣ�";  cin>>F;
	cout<<"���� "<<F<<"��=���� "<<FTOC(F)<<"��\n";
	return 0;
}
// ����1���궨��Ϊ��#define CTOF(temp) (9/5*(temp)+32)
// 	������������ʽ����9/5�Ľ��Ϊ1�����ǹ�ʽ��Ϊ��(1*(temp)+32)
// 	Ӧ���ã�(9./5*(temp)+32)


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
// ����1���ַ�ָ������©��0ָ������������룺
// 	char *s[]={"ABC","ABCD","AAA"};
// 	Ӧ���0ָ�룬�� char *s[]={"ABC","ABCD","AAA",0};
// ����2���ú���input�����Ƭ��ʵ���������ַ�������������ĿҪ��
// ����3����������������sort1��sort2���ú�LENGTH������������
// 	��ѡ�����sort1��sort2�������ϰ���ĿҪ��


//----------------  Ex9.7  ------------------------------------
# include <iostream>
using namespace  std;
# define  LBRACKET  ��(��
# define  COMMA  ��,��
# define  RBRACKET  ��)��
# define  OUT(x,y)  LBRACKET<<(x)<<COMMA<<(y)<<RBRACKET
# define  COMMA2  ��LBRACKET��
int  main()
{	cout<<LBRACKET<<3<<COMMA<< -4<<RBRACKET<<endl;
	cout<<OUT(-100,200)<<endl;
	cout<<COMMA2<<endl;
	return 0;
}
// ���н����
// (3,-4)
// (-100,200)
// LBRACKET


//----------------  Ex9.8  ------------------------------------
# include <iostream>
using namespace  std;
# define  SWAP(x,y)  { double t;  t=x; x=y; y=t;  }
# define  OUT(x,y)   cout<<(x)<< ��\t��<<(y)<<endl;
# define  ADDSHIFT(x,y,z) {  z=x+y; x=y; y=z; }
# define  PROMPT(m)  ��쳲��������еĵڡ�<<m<< �����ǣ���
int  main()
{	int  f1=1,f2=0,fn=1,n=10,i;  double a=3.14,b=2.718;
	for(i=1;i<=n;i++)  ADDSHIFT(f1,f2,fn);
	cout<< PROMPT(n)<<fn<<endl;
	OUT(a,b);  SWAP(a,b);   OUT(a,b);	
	return 0;
}
// ���н����
// 쳲��������еĵ�10���ǣ�55
// 3.14    2.718
// 2.718   3.14
