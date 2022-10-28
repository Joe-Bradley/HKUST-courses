/*编程定义学生类Student，成员数据为：学号ID，姓名Name，性别Sex(保存“男”或“女”)，以及三门课成绩Maths、Chinese、English。成员函数有构造函数和默认构造函数，average计算三门课的平均分并返回，show输出学生数据，set设置学生数据。主函数用Student数组保存一批学生数据，按平均分降序排序后输出排序后的学生数据。*/
# include <iostream>
using namespace std;
class Student
{
private:
	char ID[12],Name[20],Sex[4];  
	int Maths,Chinese,English;
public:
	Student()  {  set("","","",0,0,0); }
	Student(char *id,char *na,char *se,int ma,int ch,int en) {  set(id,na,se,ma,ch,en); }
	double average() {  return (Maths+Chinese+English)/3.0;  }
	void show()
	{	cout<<ID<<"\t"<<Name<<"\t"<<Sex<<"\n数学："<<Maths
			<<"\t语文："<<Chinese<<"\t英语："<<English<<endl;
	}
	void set(char *id,char *na,char *se,int ma,int ch,int en);
};
void Student::set(char *id,char *na,char *se,int ma,int ch,int en) 
{	strcpy(ID,id); strcpy(Name,na); strcpy(Sex,se); Maths=ma; Chinese=ch; English=en;  }
int main( )
{	
	Student st[200],t;  int i,n,k,j,ma,ch,en;  char id[12],na[20],se[4];
	cin>>n;
	for(i=0;i<n;i++) {  cin>>id>>na>>se>>ma>>ch>>en;  st[i].set(id,na,se,ma,ch,en);  }
	for(i=0;i<n;i++)
	{	for(k=i,j=i+1;j<n;j++) if(st[j].average()>st[k].average()) k=j;
		if(k!=i)  {  t=st[k];  st[k]=st[i];  st[i]=t;  }
	}
	for(i=0;i<n;i++)  st[i].show();
	return 0;
}