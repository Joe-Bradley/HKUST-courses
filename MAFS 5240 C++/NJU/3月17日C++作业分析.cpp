//----------------  Ex8.9  ------------------------------------
#include <iostream>
using namespace std;
void add(int(*A)[40],int(*B)[40],int(*C)[40],int m,int n);
int main( )
{	int a[40][40],b[40][40],c[40][40],i,j,m,n;
	cin>>m>>n;
	for(i=0;i<m;i++) for(j=0;j<n;j++)  cin>>a[i][j];
	for(i=0;i<m;i++) for(j=0;j<n;j++)  cin>>b[i][j];
	add(a,b,c,m,n);
	for(i=0;i<m;i++,cout<<endl) for(j=0;j<n;j++)  cout<<c[i][j]<<"\t";
	return 0;
}
void add(int(*A)[40],int(*B)[40],int(*C)[40],int m,int n)
{	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++)  
			C[i][j]=A[i][j]+B[i][j];
}
//����1�����Ӻ������������������������ĺͣ���������ĿҪ��


//----------------  Ex8.11  ------------------------------------
#include <iostream>
using namespace std;
bool isMagic(int(*A)[40],int n);
int main( )
{	
	int a[40][40],i,j,n;
	cin>>n;
	for(i=0;i<n;i++) for(j=0;j<n;j++)  cin>>a[i][j];
	for(i=0;i<n;i++,cout<<endl) for(j=0;j<n;j++) cout<<a[i][j]<<"\t";
	if(isMagic(a,n))  cout<<"��ħ����"<<endl;
	else              cout<<"����ħ����"<<endl;
	return 0;
}
bool isMagic(int (*A)[40],int n)
{	int s=n*(1+n*n)/2,t1,t2,i,j,k,b[1602]={0};
	for(i=0;i<n;i++)
	{	for(t1=t2=j=0;j<n;j++) 
		{	k=A[i][j];
			if(k>=1&&k<=n*n) b[k]++;
			t1+=A[i][j];  t2+=A[j][i];  
		}
		if(t1!=s||t2!=s) return false;
	}
	for(t1=t2=i=0;i<n;i++) { t1+=A[i][i]; t2+=A[i][n-1-i]; }
	if(t1!=s||t2!=s) return false;
	for(i=1;i<=n*n;i++) if(b[i]!=1) return false;
	return true;
}
// ����1��û���жϾ�����1~n*n��n������ȫ��������ɡ��п��ܲ���ħ������5���ɵ�3�׾�����ħ����
// ����2����ʹ�����󣬼����룺for(i=0;i<n;i++){s=0;s=s+A[i][i];}
// 	Ӧ�ĳɣ�for(s=0,i=0;i<n;i++) { s=s+A[i][j]; }
// ����3��ѭ���������⣬�����룺for(i=j=0;i<n,j<n;i++,j++){s1+=A[i][i];s2+=A[j][n-1-j];}
// 	ʵ�������õ�j<n���ɸ�Ϊ��for(i=0;i<n;i++){s1+=A[i][i];s2+=A[i][n-1-i];}


//----------------  Ex8.12  ------------------------------------
#include <iostream>
using namespace std;
void sort(int **p,int n);
int main( )
{	int a[10]={1,3,-5,7,9,2,8,-11,10,-3},*idx[10],n=10,i;
	for(i=0;i<n;i++) idx[i]=&a[i];
	cout<< "ԭʼ����Ϊ��\n";
	for(i=0;i<n;i++) cout<<a[i]<<"\t";  cout<<endl;
	sort(idx,n);
	cout<< "���������ԭʼ����Ϊ��\n";
	for(i=0;i<n;i++)  cout<<a[i]<< "\t";  cout<<endl;
	cout<< "����������Ϊ��\n";
	for(i=0;i<n;i++)  cout<<*idx[i]<< "\t";  cout<<endl;
	return 0;
}
void sort(int **p,int n)
{	int **pend,**pmax,**pj;  int *t;
	for(pend=p+n;p<pend;p++)
	{	for(pmax=p,pj=p+1;pj<pend;pj++) 
			if(**pj>**pmax) pmax=pj;
		if(pmax!=p) { t=*pmax; *pmax=*p; *p=t;  }
	}
}
// ����1��������������û�з�����ĿҪ��
// ����2��ʹ��ָ�����ѭ��ʱ���󣬼����룺
// 	for(;p<p+n;p++){for(max=p,q=p+1;q<p+n;q++)... }
// 	ѭ��������p<p+n�Ǻ�������������ɸ�Ϊ��
// 	for(end=p+n;p<end;p++){for(max=p,q=p+1;q<end;q++)...}


//----------------  Ex8.15  ------------------------------------
#include <iostream>
using namespace std;
void sortLength(char **ps);
int main( )
{	char *s[ ]={"Apple","Peach","Banana","Pear",0};  int i;
	for(i=0;s[i];i++)  cout<<s[i]<<endl;   cout<<endl;
	sortLength(s);
	for(i=0;s[i];i++)  cout<<s[i]<<endl;   cout<<endl;
	return 0;
}
void sortLength(char **ps)
{	char **min,**q,*t;
	for(;*ps;ps++)
	{	for(min=ps,q=ps+1;*q;q++) {  if(strlen(*q)<strlen(*min)) min=q;  }
		if(min!=ps)  {  t=*min; *min=*ps; *ps=t;  }
	}
}
// ����1���ַ����鶨�庬����󣬼����壺
// 	char *ps[]={"Apple","Peach","Banana","Pear",'\0'};
// 	�����ֵӦ����ָ�����ͣ�������char���ͣ��� '\0'Ӧ�ĳ� 0


//----------------  Ex8.16  ------------------------------------
#include <iostream>
using namespace std;
double *mulAdd(double **pA,double *x,double *b,int n);
int main( )
{	double A[40][40],*pA[40],x[40],b[40],*y;   int i,j,n;
	cin>>n;
	for(i=0;i<n;i++) for(j=0;j<n;j++)  cin>>A[i][j];
	for(i=0;i<n;i++) cin>>x[i];
	for(i=0;i<n;i++) cin>>b[i];
	for(i=0;i<n;i++) pA[i]=A[i];
	y=mulAdd(pA,x,b,n);
	for(i=0;i<n;i++) cout<<y[i]<<"\t";  cout<<endl;	
	return 0;
}
double *mulAdd(double **pA,double *x,double *b,int n)
{	static double yy[40];  int i,j;
	for(i=0;i<n;i++)
	{	for(yy[i]=b[i],j=0;j<n;j++)  yy[i]+=pA[i][j]*x[j];   }
	return yy;
}
// ����1��ֱ�ӵ��ö�ά�������������룺y=mulAdd(A,x,b,n);
// 	A��������ָ��double(*)[40]���ͣ���pAΪָ��ָ���ָ��double**���ͣ�
// 	Ӧ�ô���ָ������������ָ�������ÿ��Ԫ��ָ��A��ÿһ��
// ����2�����ݵ��Ӵ��󣬼����룺
// 	static double y[40];
// 	for(i=0;i<n;i++) for(j=0;j<n;j++) y[i]+=pA[i][j]*x[j]+b[i];
// 	����b[i]Ӧ�õ���һ�Σ�������ÿ��jѭ�������ӡ�
// 	��Σ�y����ʱĬ�ϳ�ֵΪ0���ʵ����Ǵ�0��ʼ�������ʹ�þͻ������⡣
// 	�ɸ�Ϊ��
// 	static double y[40];
// 	for(i=0;i<n;i++){for(y[i]=0,j=0;j<n;j++)y[i]+=pA[i][j]*x[j];y[i]+=b[i];}
// ����3��������������ȫ�������У��뱣���ھ�̬�ֲ��������ĿҪ�����
// ����4��������������b�����У��뱣���ھ�̬�ֲ��������ĿҪ�������
// 	�һ�Ķ�y=Ax+b�е�b�����ֵ��������Ʋ���