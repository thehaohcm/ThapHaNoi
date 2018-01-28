#include<iostream>
#include "mylib.h"
#include<time.h>
#include<conio.h>
#include<math.h>
using namespace std;
char A[10][20]={"","111","22222","3333333","444444444","55555555555","6666666666666","777777777777777","88888888888888888","9999999999999999999"};
int const xCotA=11,xCotB=32,xCotC=53,yDay=14,yDinh=5;
int count=0;
int timer=100;
void sleep(long d)
{
    clock_t start=clock();
    while(clock()-start<d);
}
 
void ChangeTimeDelay()
{
    if(kbhit())
    {	
    	int k=getch();
    	if(k==72&&timer>=10)
        	timer-=10;
    	if(k==80&&timer<=240)
        	timer+=10;	
        	
        for(int i=1;i<=3;i++)
        {
        	gotoxy(30+i,22);
        	cout<<" ";
		}
        gotoxy(2,22);
		cout<<"Thoi gian nghi (milisecond): "<<timer;
	}
}
 
typedef struct point{
    int x,y;
};
point CotA,CotB,CotC;
 
void SetPoint(point &p,int x,int y)
{
    p.x=x;
    p.y=y;
}
 
void ChuyenDia(char Dau,char Cuoi,int n)
{
    point *dau,*cuoi;
    switch(Dau)
    {
        case 'A': dau=&CotA;break;
        case 'B': dau=&CotB;break;
        case 'C': dau=&CotC;break;
    }
    switch(Cuoi)
    {
        case 'A': cuoi=&CotA;break;
        case 'B': cuoi=&CotB;break;
        case 'C': cuoi=&CotC;break;
    }
    point t;
    SetPoint(t,dau->x,yDinh-1);
    for(int i=dau->y;i>=t.y;i--)  //up
    {
        gotoxy(t.x-n,i);
        cout<<A[n];
        if(i<dau->y)
        {
            for(int j=t.x-n;j<=t.x+n;j++)
            {
                gotoxy(j,i+1);
                if(j==t.x)
                    cout<<"|";
                else
                    cout<<" ";
            }
        }
        sleep(timer);
        ChangeTimeDelay();
    }
    SetPoint(t,cuoi->x,yDinh-1);
    if(dau->x > cuoi->x)  //right -> left
    {
        for(int i=dau->x-n;i>=cuoi->x-n;i--)
        {
            gotoxy(i,t.y);
            cout<<A[n];
            for(int j=i+n+n+1;j<=i+(n*3);j++)
            {
                gotoxy(j,t.y);
                cout<<" ";
            }
            sleep(timer);
            ChangeTimeDelay();
        }
    }
    if(dau->x < cuoi->x) //left -> right
    {
        for(int i=dau->x-n+1;i<=cuoi->x-n;i++)
        {
            gotoxy(i,t.y);
            cout<<A[n];
            for(int j=i-n-n;j<=i-1;j++)
            {
                gotoxy(j,t.y);
                cout<<" ";
            }
            sleep(timer);
            ChangeTimeDelay();
        }
    }
    SetPoint(t,cuoi->x,yDay-1);
    for(int i=yDinh;i<cuoi->y;i++)  //down
    {
        if(i<cuoi->y)
        {
            for(int j=t.x-n;j<=t.x+n;j++)
            {
                gotoxy(j,i-1);
                if(j==t.x&&i-1!=yDinh-1)
                    cout<<"|";
                else
                    cout<<" ";
            }
        }
        gotoxy(t.x-n,i);
        cout<<A[n];
        sleep(timer);
        ChangeTimeDelay();
    }
    dau->y+=1;
    cuoi->y-=1;
}
 
void ThapHN(int n,char CotDau,char CotDich,char CotTG)
{
    if(n>0)
    {
        ThapHN(n-1,CotDau,CotTG,CotDich);
        gotoxy(2,20);
        count++;
        cout<<count<<") Chuyen dia so "<<n<<" tu Cot "<<CotDau<<" -> Cot "<<CotDich;
        ChuyenDia(CotDau,CotDich,n);
        sleep(timer);
        ChangeTimeDelay();
        ThapHN(n-1,CotTG,CotDich,CotDau);
    }
}
 
void Initial(int n)
{
    SetPoint(CotA,xCotA,yDay-n);
    SetPoint(CotB,xCotB,yDay);
    SetPoint(CotC,xCotC,yDay);
    cout<<"Di chuyen "<<n<<" dia tu cot A -> Cot C."<<endl;
	cout<<"Tong so buoc di: "<<pow(2,n)-1<<endl;
	gotoxy(50,18);
	cout<<"Key up:   Tang toc do";
	gotoxy(50,20);
	cout<<"Key down: Giam toc do";
	gotoxy(2,22);
	cout<<"Thoi gian nghi (milisecond): "<<timer;
}
 
void CreateTower(int n)
{
        system("cls");
        Initial(n);
        gotoxy(0,5);
        int i;
        for(i=5;i<=13;i++)
        {
            gotoxy(xCotA,i);
            cout<<"|";
            gotoxy(xCotB,i);
            cout<<"|";
            gotoxy(xCotC,i);
            cout<<"|";
        }
        int j=10,k=1;
        for(int i=yDay-n;i<=yDay;i++,j--,k++)
        {
            gotoxy(j,i);
            cout<<A[k];
        }      
        gotoxy(0,i);
        cout<<"-----------+--------------------+--------------------+--------------------"<<endl;
        cout<<"         Cot A                Cot B                Cot C"<<endl;
}

int main()
{
    int n;
    cout<<"Nhap vao so dia: ";
    cin>>n;
    while(n<1||n>9)
    {
    	cout<<"Chuong trinh khong the chay"<<endl;
    	cout<<"Ban vui long nhap lai so dia: ";
    	cin>>n;
	}
    CreateTower(n);
    int k;
    ThapHN(n,'A','C','B');
    gotoxy(2,23);
    cout<<"Da chuyen xong";
    gotoxy(2,24);
    system("pause");
    return 0;
}
