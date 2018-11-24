#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
int data[100],n;
int divisor[]={1,1,0,1};
#define m 3
void crcgen(int data[],int n) 
{
fstream file;
file.open("crc.txt",ios::app);
if(!file) 
{
cout<<"\nError in creating file ";return;
}
int crc[10],x=0;
for(int i=0;i<m;i++)
crc[i]=0; 
while(x<m+n)
{
if(crc[0]==0)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[x];
x++;
}
else if(crc[0]==1)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[x];
x++;
for(int i=0;i<m;i++)
if(crc[i]==divisor[i+1])
crc[i]=0;
else
crc[i]=1;
}
}
for(int i=0;i<n;i++)
file<<data[i];
for(int i=0;i<m;i++)
file<<crc[i];
file<<'\n';
file.close();
}
void findSegmentData(int message[],int len)
{
	
	int segment[5][35];
	int i,j;
	cout<<endl;
	for(i=0;i<len;i++)
	cout<<message[i]<<" ";
	cout<<" has been sent to the multi user request system\n";
	for(i=0;i<5;i++)
	{
		for(j=0;j<35;j++)
		segment[i][j] = 0;
	}
	i=j=0;int k=0;
	while(k<len)
	{
		segment[i][j] = message[k++];
		if(i==4)
		{
			j++;
			i=0;
			continue;
		}
		i++;
	}
	 int len1,len2,len3,len4,len5;
	 len1 = len2 = len3 = len4 = len5 = (len / 5);
	 int rem = (len % 5);
	 if(rem == 1)
	 {
	 	len1++;
	  } 
	  else if(rem == 2)
	  {
	  	len1++;
	  	len2++;
	  }
	  else if(rem == 3)
	  {
	  	len1++;
	  	len2++;
	  	len3++;
	  }
	  else if(rem == 4)
	  {
	  	len1++;
	  	len2++;
	  	len3++;
	  	len4++;
	  }
	  int row1[100],row2[100],row3[100],row4[100],row5[100];
	  for(i=0;i<100;i++)
	  row1[i]=0,row2[i]=0,row3[i] = 0,row4[i] = 0,row5[i] = 0;
	  for(i=0;i<len1;i++)
	  row1[i] = segment[0][i];
	  for(i=0;i<len2;i++)
	  row2[i] = segment[1][i];
	  for(i=0;i<len3;i++)
	  row3[i] = segment[2][i];
	  for(i=0;i<len4;i++)
	  row4[i] = segment[3][i];
	  for(i=0;i<len5;i++)
	  row5[i] = segment[4][i];
	  crcgen(row1,len1);
	  crcgen(row2,len2);
	  crcgen(row3,len3);
	  crcgen(row4,len4);
	  crcgen(row5,len5);
}
int crcchk(int data[],int n) 
{
int crc[10],x=0;
for(int i=0;i<10;i++)
crc[i]=0; 
while(x<(m+n))
{
if(crc[0]==0)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[x];
x++;
}
else if(crc[0]==1)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[x];
x++;
for(int i=0;i<m;i++)
if(crc[i]==divisor[i+1])
crc[i]=0;
else
crc[i]=1;
}
}
int f=0;
for(int i=0;i<m;i++) if(crc[i]!=0) f++;
if (f) return 1;else return 0;
}
void crccor(int data[],int n,int u)
{
int dt[100],cr[10];
int crc[10],k=0;
for(int i=0;i<10;i++)
crc[i]=0; 
while(k<(m+n))
{
if(crc[0]==0)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[k];
k++;
}
else if(crc[0]==1)
{
for(int i=0;i<m-1;i++)
crc[i]=crc[i+1];
crc[m-1]=data[k];
k++;
for(int i=0;i<m;i++)
if(crc[i]==divisor[i+1])
crc[i]=0;
else
crc[i]=1;
}
}
for(int x=0;x<100;x++) {if (x<(n+m))dt[x]=0;else dt[x]=-1;}
int g=0;
for(int y=0;y<(n+m);y++)
{
	dt[y]=1;
	int x=0;
for(int i=0;i<m;i++)
cr[i]=0; 
while(x<(n+m))
{
if(cr[0]==0)
{
for(int i=0;i<m-1;i++)
cr[i]=cr[i+1];
cr[m-1]=dt[x];
x++;
}
else if(cr[0]==1)
{
for(int i=0;i<m-1;i++)
cr[i]=cr[i+1];
cr[m-1]=dt[x];
x++;
for(int i=0;i<m;i++)
if(cr[i]==divisor[i+1])
cr[i]=0;
else
cr[i]=1;
}
}
int c=0;
for(int i=0;i<m;i++) if(crc[i]!=cr[i]) c++;
cout<<" ";
if(c==0) 
{
if(y<(n-m)) cout<<"\nError in bit "<<(5*y)+u+1;
else cout<<"\nError in redundant bit ";
data[y]=(data[y]+1)%2;g++;
}
dt[y]=0;
}
if(g==0) cout<<"\nBurst error of length greater than 5 present.\nResulting message might not be accurate ";
}
void chkSegmentData()
{
int t=1;
fstream file;
file.open("crc.txt",ios::in);
if(!file) 
{
cout<<"\nError in creating file ";return;
}
while(!file.eof())
{
int segment[5][35];int err[5];int size[5];
for(int i=0;i<35;i++)
for(int j=0;j<5;j++)
segment[j][i]=0;
for(int i=0;i<5;i++)
{
err[i]=0;
char ch[150];
file.getline(ch,150,'\n');
if(file.eof()) return;
size[i]=strlen(ch);
for(int k=0;k<size[i];k++)
segment[i][k]=ch[k]-'0';
err[i]=crcchk(segment[i],size[i]);
}
int f=0;
cout<<endl<<t++<<".";
for(int i=0;i<5;i++) if(err[i]==1) f++;
if(f) cout<<"Error present. Error checking in progress...\n";
else cout<<"No Error present ";
for(int i=0;i<5;i++) 
{
if(err[i]==1) 
crccor(segment[i],size[i],i);
}
int k=1;
for(int i=0;i<5;i++) if(size[i]==size[(i+1)%5]) k=(k+1)%5; else break;
int n=5*(size[4]-m)+k;
cout<<"\n\nMessage size - "<<n;
cout<<"\nFinal Message - ";k=0;
for(int i=0;i<35;i++)
for(int j=0;j<5;j++)
{
if(k<n) {cout<<segment[j][i];k++;}
else break;
}
cout<<endl;
}
file.close();
}
void clr()
{
fstream file;
file.open("crc.txt",ios::out|ios::trunc);
if(!file) 
{
cout<<"\nError in opening file ";return;
}
cout<<"\nContents of file have been cleared.\n";
file.close();
}
int main()
{
int ch;char rep='y';string s;

while(rep=='y')
{
cout<<"\nEnter your choice\n1.Generate CRC\n2.Check for errors\n3.Clear contents ";
cin>>ch;
switch(ch)
{
case 1:
{
cout<<"\nEnter message ";
cin>>s;
n = s.length();
for(int i=0;i<100;i++) data[i]=0;
for(int i=0;i<s.length();i++)
data[i] = s[i] - '0';
findSegmentData(data,n);
break;
}
case 2:
{
chkSegmentData();
break;
}
case 3:{clr();break;}
default: cout<<"\nInvalid choice ";
}
cout<<"\nContinue? ";
cin>>rep;
}
}
