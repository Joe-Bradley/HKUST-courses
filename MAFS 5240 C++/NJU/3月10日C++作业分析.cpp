//----------------  Ex8.1  ------------------------------------
#include <iostream>
using namespace std;
void rotate(int *x,int *y,int *z);
int main( )
{	
	int a=3,b=4,c=5;
	std::cout<<"a="<<a<<"\tb="<<b<<"\tc="<<c<<endl;
	rotate(&a,&b,&c);
	std::cout<<"a="<<a<<"\tb="<<b<<"\tc="<<c<<endl;
	return 0;
}
void rotate(int *x,int *y,int *z)
{	int t=*z;  *z=*y;  *y=*x;  *x=t;  }
//问题1：用*x=*y; 轮换，方向搞反了，应该用*y=*x;


//----------------  Ex8.2  ------------------------------------
#include <iostream>
using namespace std;
void maxMin(int *a,int n,int *max,int *min);
int main( )
{	int a[ ]={4,5,6,1,2,3},n,i,vmax,vmin;
	maxMin(a,sizeof(a)/sizeof(a[0]),&vmax,&vmin);
	cout<<"最大值为:"<<vmax<<"\t最小值为:"<<vmin<<endl;
	return 0;
}
void maxMin(int *a,int n,int *max,int *min)
{	*max=*min=*a;
	for(int *p=a;p<a+n;p++)
		if(*p>*max) *max=*p;  
		else if(*p<*min) *min=*p;
}
//问题1：调用为：maxMin(&a[6],6,&vMax,&vMin); 数组传递错误，第一参数应该为 a 或者&a[0]
//问题2：保存最大最小值错误，代码为：
//int *max=&a[0],*min=&a[0];  maxMin(a,6,max,min);
//应该单独用变量存放最大最小值，可改为 int max,min; maxMin(a,6,&max,&min);


//----------------  Ex8.5  ------------------------------------
#include <iostream>
using namespace std;
char *findSubstringRev(char *s1,char *s2);
int main( )
{	
	char s1[80]="This is a book",s2[80]="oo",*p;
	p=findSubstringRev(s1,s2);
	if(p)  cout<<p<<endl;
	else   cout<<"未找到子串"<<endl;
	return 0;
}

char *findSubstringRev(char *s1,char *s2)
{	char *p,*q,*r=0;
	for(;*s1;s1++)
	{	for(p=s1,q=s2;*q&&*p==*q;p++,q++);
		if(*q=='\0') r=s1;
	}            
	return r;
}
// 或findSubstringRev设计成
// char *findSubstringRev(char *s1,char *s2)
// {	char *r=0;   int i,j;
// 	for(i=0;s1[i];i++)
// 	{	for(j=0;s2[j]&&s1[i+j]==s2[j];j++);
// 		if(s2[j]=='\0')  r=s1+i;
// 	}
// 	return r;
// }
// 或
// char *findSubstringRev(char *s1,char *s2)
// {	char *begin=s1,*p,*q;
// 	while(*s1) s1++;
// 	for(s1--;s1>=begin;s1--)
// 	{	for(p=s1,q=s2;*q&&*p==*q;p++,q++);
// 		if(*q=='\0')  return s1;
// 	}
// 	return 0;
// }
// 问题1：子函数返回第一个匹配的子串首地址，或者没有匹配子串时没有返回0指针，均与题目要求不相符
// 问题2：字符串求长度代码：for(p=s1;*p;p++) n1=p-s1; 实际长度应该为 n1+1
// 	可改为：for(p=s1;*p;p++); n1=p-s1;  这样的n1为字符串s1的长度
// 问题3：查找匹配子串的代码有错，错误代码A：
// 	for(ret=0;*s1;s1++){for(p=s1,q=s2;*q&&*q==*p;p++,q++) if(*q=='\0')ret=s1;}
// 	内层函数体应该为空语句，而不是if语句，可改为：
// 	for(ret=0;*s1;s1++){for(p=s1,q=s2;*q&&*q==*p;p++,q++);if(*q=='\0')ret=s1;}
// 		错误代码B：
// 	for(p=s1;*p;p++){for(q=s2;*q&&*p==*q;q++);if(*q=='\0')break;}
// 	两个错误：1是返回第一个匹配的子串首地址；
// 	        2内层循环不是p串和s2串逐个字符比较，而是s2串逐个字符与p串首字符*p比较，可改为：
// 	for(p=s1;*p;p++){for(q=s2,r=p;*q&&*r==*q;q++,r++);if(*q=='\0')ret=p;}


//----------------  Ex8.6  ------------------------------------
#include <iostream>
using namespace std;
char *reverse(char *s);
int main( )
{	char s1[80]="computer",s2[80]="Madam";
	cout<<s1<<"\t"<<s2<<endl;
	reverse(s1);
	cout<<s1<<"\t"<<reverse(s2)<<endl;
	return 0;
}

char *reverse(char *s)
{	char *p,*q,ch;
	for(p=s,q=s+strlen(s)-1;p<q;p++,q--)
	{	ch=*p;  *p=*q;  *q=ch;  }
	return s;
}
// 问题1；字符串末尾字符不对，循环体不对，见代码：
// 	for(p=s,q=s+strlen(s);p<q;p++,q--) t=*p; *p=*q; *q=t;
// 	可改为：for(p=s,q=s+strlen(s)-1;p<q;p++,q--){t=*p;*p=*q;*q=t;}


//----------------  Ex8.7  ------------------------------------
#include <iostream>
using namespace std;
char *toupper(char *s);
int main( )
{	char s1[ ]="computer",s2[ ]="3 plus 4 is 7.";
	cout<<toupper(s1)<<endl;
	toupper(s2);  cout<<s2<<endl;
	return 0;
}
char *toupper(char *s)
{	for(char *p=s;*p;p++)  if(*p>='a'&&*p<='z') *p+='A'-'a';
	return s;
}
// 问题1：调用时用字符串常量，见代码：
// 	cout<<toupper("computer")<<endl;
// 	此处参数字符串在函数toupper内要改动，不能用常量，可改为：
// 	char s1[ ]="computer";  cout<<toupper(s1)<<endl;
// 问题2：输出代码为：cout<<s1<<toupper(s1); 结果与预期不相符，与cout<<实现机理有关，
// 	可改为：cout<<s1; cout<<toupper(s1);
	