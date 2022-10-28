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
//����1����*x=*y; �ֻ�������㷴�ˣ�Ӧ����*y=*x;


//----------------  Ex8.2  ------------------------------------
#include <iostream>
using namespace std;
void maxMin(int *a,int n,int *max,int *min);
int main( )
{	int a[ ]={4,5,6,1,2,3},n,i,vmax,vmin;
	maxMin(a,sizeof(a)/sizeof(a[0]),&vmax,&vmin);
	cout<<"���ֵΪ:"<<vmax<<"\t��СֵΪ:"<<vmin<<endl;
	return 0;
}
void maxMin(int *a,int n,int *max,int *min)
{	*max=*min=*a;
	for(int *p=a;p<a+n;p++)
		if(*p>*max) *max=*p;  
		else if(*p<*min) *min=*p;
}
//����1������Ϊ��maxMin(&a[6],6,&vMax,&vMin); ���鴫�ݴ��󣬵�һ����Ӧ��Ϊ a ����&a[0]
//����2�����������Сֵ���󣬴���Ϊ��
//int *max=&a[0],*min=&a[0];  maxMin(a,6,max,min);
//Ӧ�õ����ñ�����������Сֵ���ɸ�Ϊ int max,min; maxMin(a,6,&max,&min);


//----------------  Ex8.5  ------------------------------------
#include <iostream>
using namespace std;
char *findSubstringRev(char *s1,char *s2);
int main( )
{	
	char s1[80]="This is a book",s2[80]="oo",*p;
	p=findSubstringRev(s1,s2);
	if(p)  cout<<p<<endl;
	else   cout<<"δ�ҵ��Ӵ�"<<endl;
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
// ��findSubstringRev��Ƴ�
// char *findSubstringRev(char *s1,char *s2)
// {	char *r=0;   int i,j;
// 	for(i=0;s1[i];i++)
// 	{	for(j=0;s2[j]&&s1[i+j]==s2[j];j++);
// 		if(s2[j]=='\0')  r=s1+i;
// 	}
// 	return r;
// }
// ��
// char *findSubstringRev(char *s1,char *s2)
// {	char *begin=s1,*p,*q;
// 	while(*s1) s1++;
// 	for(s1--;s1>=begin;s1--)
// 	{	for(p=s1,q=s2;*q&&*p==*q;p++,q++);
// 		if(*q=='\0')  return s1;
// 	}
// 	return 0;
// }
// ����1���Ӻ������ص�һ��ƥ����Ӵ��׵�ַ������û��ƥ���Ӵ�ʱû�з���0ָ�룬������ĿҪ�����
// ����2���ַ����󳤶ȴ��룺for(p=s1;*p;p++) n1=p-s1; ʵ�ʳ���Ӧ��Ϊ n1+1
// 	�ɸ�Ϊ��for(p=s1;*p;p++); n1=p-s1;  ������n1Ϊ�ַ���s1�ĳ���
// ����3������ƥ���Ӵ��Ĵ����д��������A��
// 	for(ret=0;*s1;s1++){for(p=s1,q=s2;*q&&*q==*p;p++,q++) if(*q=='\0')ret=s1;}
// 	�ڲ㺯����Ӧ��Ϊ����䣬������if��䣬�ɸ�Ϊ��
// 	for(ret=0;*s1;s1++){for(p=s1,q=s2;*q&&*q==*p;p++,q++);if(*q=='\0')ret=s1;}
// 		�������B��
// 	for(p=s1;*p;p++){for(q=s2;*q&&*p==*q;q++);if(*q=='\0')break;}
// 	��������1�Ƿ��ص�һ��ƥ����Ӵ��׵�ַ��
// 	        2�ڲ�ѭ������p����s2������ַ��Ƚϣ�����s2������ַ���p�����ַ�*p�Ƚϣ��ɸ�Ϊ��
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
// ����1���ַ���ĩβ�ַ����ԣ�ѭ���岻�ԣ������룺
// 	for(p=s,q=s+strlen(s);p<q;p++,q--) t=*p; *p=*q; *q=t;
// 	�ɸ�Ϊ��for(p=s,q=s+strlen(s)-1;p<q;p++,q--){t=*p;*p=*q;*q=t;}


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
// ����1������ʱ���ַ��������������룺
// 	cout<<toupper("computer")<<endl;
// 	�˴������ַ����ں���toupper��Ҫ�Ķ��������ó������ɸ�Ϊ��
// 	char s1[ ]="computer";  cout<<toupper(s1)<<endl;
// ����2���������Ϊ��cout<<s1<<toupper(s1); �����Ԥ�ڲ��������cout<<ʵ�ֻ����йأ�
// 	�ɸ�Ϊ��cout<<s1; cout<<toupper(s1);
	