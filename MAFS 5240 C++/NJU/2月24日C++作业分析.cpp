//---------------------��ϰ1---------------------------------------
//����y(ȡֵ1,2,��,46),�ҳ�x(0��x��46)ʹ��5^x %47=y���磺5^36%47=4
# include <iostream>
using namespace std;
int main( )
{	int  x,y,s;
	cin>>y;
	if(y<1||y>46)  return 1;
	for(s=1,x=0;x<=46;x++)
	{	if(s==y) break;  s=s*5%47;  }
	cout<<"5^"<<x<<" %47="<<y<<endl;
	return 0;
}

/*����1������5��x����%47�ô��� int(pow(5,x))%47 �� for(s=j=1;j<=x;j++) s*=5;
ȡֵs%47�������ֵ���󳬳� int ���ܴ�ŵ����ݷ�Χ������ s=s*5%47 ���� s*=5
��չ�����ú������Լ��� (5��x����)%47 ��ֵ(x=0,1,...,45)��������
    int f(int x)
    {
        int s=1,i;
        for(i=1;i<=x;i++) s=s*5%47;
        return s;
    }
�����ģʹ��f(x)������Ӧ��ֵʱ��Ч�ʵ��£�����ӳ��˼�룬����
    int
g[46]={1,5,25,31,14,23,21,11,8,40,12,13,18,43,27,41,17,38,2,10,3,15,28,46,42,22,16
33,24,26 36,39,7,35,34,29,4,20,6,30,  9,45,37,44,32,19}; ��ʹ�� g[x] �����Ӻ���
f(x) ��������Ӧ��ֵ�ɴ����߼���Ч�ʡ�*/

//---------------------��ϰ2---------------------------------------
//��ϰ2������10��ʵ������ (i1,i2,��,i10)=(5,2,7,3,8,9,6,1,10,4)�����û���
//���û���10��ʵ��������a1,a2,��,a10��Ϊ ai1,ai2,��,ai10��
#include <iostream>
using namespace std;
int main() {
    int i[10] = {5, 2, 7, 3, 8, 9, 6, 1, 10, 4}, j;
    double a[10], b[10];
    for (j = 0; j < 10; j++)
        cin >> a[j];
    for (j = 0; j < 10; j++)
        b[j] = a[i[j] - 1]; // b����Ϊai1,ai2,...,ai10
    for (j = 0; j < 10; j++)
        a[j] = b[j];
    for (j = 0; j < 10; j++)
        cout << a[j] << "\t";
    cout << endl;
    return 0;
}

//����1���û�����±���1~10��Χ��û�м�ȥ1ת��Ϊ0~9��Χ��
//����2��ʹ�� b(ik)=a(k)�����û�������õ��������û��Ľ����Ӧ���� b(k)=a(ik)

//---------------------��ϰ3---------------------------------------
//����һ��5��5���������жϸþ����Ƿ���1,2,3,��,25��25���������ɡ�
#include <iostream>
using namespace std;
int main() {
    int a[5][5], c[30] = {0}, i, j, k;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            cin >> a[i][j];
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++) {
            k = a[i][j];
            if (k >= 1 && k <= 25)
                c[k]++;
        }
    for (i = 1; c[i] == 1; i++)
        ;
    if (i > 25)
        cout << "������1,2,3,...,25��25����������" << endl;
    else
        cout << "��������1,2,3,...,25��25����������" << endl;
    return 0;
}
//��
#include <iostream>
using namespace std;
int main() {
    int s, i, j, k, a[5][5];
    cout << "�������" << endl;
    for (i = 0; i < 5; i++)
        for (j = 0; j < 5; j++)
            cin >> a[i][j];
    for (k = 1; k <= 25; k++) {
        for (s = 0, i = 0; i < 5; i++)
            for (j = 0; j < 5; j++) {
                if (a[i][j] == k)
                    s++;
            }
        if (s != 1)
            break;
    }
    if (k > 25)
        cout << "��" << endl;
    else
        cout << "����" << endl;
    return 0;
}
/*����1���ڲ���break����ѭ���������룺
    for(k=1;k<=25;k++)
    {
        for(i=0;i<5;i++)
            for(j=0;j<5;j++)
                if(a[i][j]==k) break;
        if(i==5&&j==5) break;
    }
    �ô���ֻ�������ڲ�j��ѭ����Ҫ�����ڶ���ѭ���ɸ�ѭ����Ϊ
        if(a[i][j]==k) { i=5; break; }
*/

//---------------------��ϰ4---------------------------------------
//��һ���ַ����еķ���ĸ�ַ�ɾ����������ĸ�ַ�ͳһת���ɴ�д��ĸ��
#include <iostream>
using namespace std;
void leaveLetter(char s[]) {
    int i, j;
    for (j = i = 0; s[i] != '\0'; i++) {
        if (s[i] >= 'A' && s[i] <= 'Z')
            s[j++] = s[i];
        else if (s[i] >= 'a' && s[i] <= 'z')
            s[j++] = s[i] + 'A' - 'a';
    }
    s[j] = '\0';
}
int main() {
    char s[80];
    cin.getline(s, 80);
    leaveLetter(s);
    cout << s << endl;
    return 0;
}
//����1��©����� '\0'�������ᵼ���ַ�������û�б仯���������ȷ
//����2��û�а���ĿҪ�����Ӻ��������ַ���
//����3������ַ�����ѭ�� for(int i=0;s[i];i++) cout<<s[i]; ����ֱ�����
//cout<<s<<endl;

//---------------------��ϰ5---------------------------------------
//��д�ݹ麯����һ����������2������ɾȥ���磺312=39��23��ɾȥ2�����Ӻ��39��
#include <iostream>
using namespace std;
int f(int n) {
    if (n % 2 != 0)
        return n;
    else
        return f(n / 2);
}
int main() {
    int a;
    cin >> a;
    cout << a << " ɾȥ2��������Ϊ " << f(a) << endl;
    return 0;
}

//---------------------��ϰ6---------------------------------------
//����n�����������������������������ƽ��ֵ
#include <iostream> 
using namespace std;
int posNum,negNum;
double average;
void proceed(double a[ ],int n);
int main( ) 
{	double a[100];  int i,n;
	cin>>n;
	for(i=0;i<n;i++)  cin>>a[i];
	proceed(a,n);
	cout<<"��������="<<posNum<<"\t��������="<<negNum
		<<"\tƽ��ֵ="<<average<<endl;
	return 0;
}
void proceed(double a[ ],int n)
{	posNum=negNum=0;  average=0;
	for(int i=0;i<n;i++)
	{	if(a[i]>0)      posNum++;
		else if(a[i]<0) negNum++;
		average+=a[i];
	}
	average/=n;
}
//����1��û�а���ĿҪ�������������������������Ӻ��������
//����2��ȫ�ֱ���ʹ��ǰ��Ϊ0����û�и���ֵ