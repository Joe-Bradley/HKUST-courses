/*��̶���ѧ����Student����Ա����Ϊ��ѧ��ID������Name���Ա�Sex(���桰�С���Ů��)���Լ����ſγɼ�Maths��Chinese��English����Ա�����й��캯����Ĭ�Ϲ��캯����average�������ſε�ƽ���ֲ����أ�show���ѧ�����ݣ�set����ѧ�����ݡ���������Student���鱣��һ��ѧ�����ݣ���ƽ���ֽ�����������������ѧ�����ݡ�*/
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
	{	cout<<ID<<"\t"<<Name<<"\t"<<Sex<<"\n��ѧ��"<<Maths
			<<"\t���ģ�"<<Chinese<<"\tӢ�"<<English<<endl;
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