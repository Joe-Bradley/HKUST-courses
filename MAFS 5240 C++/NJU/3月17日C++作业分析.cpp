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
//问题1：在子函数而不是在主函数输出矩阵的和，不符合题目要求


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
	if(isMagic(a,n))  cout<<"是魔方阵"<<endl;
	else              cout<<"不是魔方阵"<<endl;
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
// 问题1：没有判断矩阵由1~n*n这n个数的全部数据组成。有可能不是魔方阵，如5构成的3阶矩阵不是魔方阵。
// 问题2：求和代码错误，见代码：for(i=0;i<n;i++){s=0;s=s+A[i][i];}
// 	应改成：for(s=0,i=0;i<n;i++) { s=s+A[i][j]; }
// 问题3：循环条件问题，见代码：for(i=j=0;i<n,j<n;i++,j++){s1+=A[i][i];s2+=A[j][n-1-j];}
// 	实际起作用的j<n，可改为：for(i=0;i<n;i++){s1+=A[i][i];s2+=A[i][n-1-i];}


//----------------  Ex8.12  ------------------------------------
#include <iostream>
using namespace std;
void sort(int **p,int n);
int main( )
{	int a[10]={1,3,-5,7,9,2,8,-11,10,-3},*idx[10],n=10,i;
	for(i=0;i<n;i++) idx[i]=&a[i];
	cout<< "原始数据为：\n";
	for(i=0;i<n;i++) cout<<a[i]<<"\t";  cout<<endl;
	sort(idx,n);
	cout<< "索引排序后原始数据为：\n";
	for(i=0;i<n;i++)  cout<<a[i]<< "\t";  cout<<endl;
	cout<< "索引的数据为：\n";
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
// 问题1：进行升序排序，没有符合题目要求
// 问题2：使用指针进行循环时错误，见代码：
// 	for(;p<p+n;p++){for(max=p,q=p+1;q<p+n;q++)... }
// 	循环条件：p<p+n是恒成立的条件，可改为：
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
// 问题1：字符数组定义含义错误，见定义：
// 	char *ps[]={"Apple","Peach","Banana","Pear",'\0'};
// 	数组初值应该是指针类型，而不是char类型，故 '\0'应改成 0


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
// 问题1：直接调用二维数组名，见代码：y=mulAdd(A,x,b,n);
// 	A类型是行指针double(*)[40]类型，而pA为指向指针的指针double**类型，
// 	应该传递指针数组名，而指针数组的每个元素指向A的每一行
// 问题2：数据叠加错误，见代码：
// 	static double y[40];
// 	for(i=0;i<n;i++) for(j=0;j<n;j++) y[i]+=pA[i][j]*x[j]+b[i];
// 	首先b[i]应该叠加一次，而不是每个j循环都叠加。
// 	其次，y定义时默认初值为0，故叠加是从0开始。但多次使用就会有问题。
// 	可改为：
// 	static double y[40];
// 	for(i=0;i<n;i++){for(y[i]=0,j=0;j<n;j++)y[i]+=pA[i][j]*x[j];y[i]+=b[i];}
// 问题3：计算结果保存在全局数组中，与保存在静态局部数组的题目要求不相符
// 问题4：计算结果保存在b数组中，与保存在静态局部数组的题目要求不相符，
// 	且会改动y=Ax+b中的b数组的值，这种设计不好