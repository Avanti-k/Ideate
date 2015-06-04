

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include<string.h>

using namespace std;


void display(char* name, int v=999)
{

	cout<<"\n ----------------"<<name<<"----------------";

	ifstream fin(name, ios::in);
	char *file[20];
	char c;
	int i=0, no,j;
	if(!fin.is_open())
	{	cout<<"not open";
	return;
	}


	char *temp=new char(12);
	int line=0;
	while(!fin.eof() && i<v && line<20)
	{
		fin>>c;
		switch(c)
		{
			case 'a':
				fin.getline(temp, 12);
				file[line]=new char(10);
				strcpy(file[line],temp);
				line++;
				break;
			case 'd':
				fin>>no;
				for(j=no; j<line; j++)
					strcpy(file[j-1],file[j]);
				line--;
				break;
			default:
				break;

		}
		i++;
	}


	for(j=0; j<line; j++)
			cout<<"\n"<<j+1<<file[j];

	if(fin.eof())
		cout<<"\n**encountered end of file**";
	else if(line==20)
		cout<<"\n**file limited to 20 lines**";

	fin.close();
}

void edit(char *name)
{

	ofstream fout(name, ios::app);
	if(!fout.is_open())
	{	cout<<"not open";
	return ;
	}

	string strr;
	string cmd;
	cout<<"\n >>>";
	cin>>cmd;
	if(cmd=="d")
	{
		getline(std::cin, strr);
		fout<<"\nd "<<strr;
	}
	else
	{
		getline(std::cin, strr);
		fout<<"\na "<<cmd<<" "<<strr;
	}
	fout.close();
}

int main(int argc ,char* argv[]) {

	if(argc==1)
	{
		cout<<"1";
		cout<<"\n usage: ./svc filename version";
		return 0;
	}

	char *Name=new char(100);
	strcpy(Name,argv[1] );

	if(argc==2)
		display(Name);
	if(argc==3)
		display(Name, atoi(argv[2]));

	char ch;
	cout<<"\n \n edit?(y/n)";
	cin>>ch;
	if(ch=='y')
		edit(Name);
	return 0;
}

//----------------output-----------------------
/*
[lenovo@localhost svc]$ g++ svc.cpp -o svc
[lenovo@localhost svc]$ ./svc test.txt

 ----------------test.txt----------------
1 the first
2 third
3 fourth
4 fifth
5 sixth
6 seventh 
7 line 9
8
**encountered end of file**
 
 edit?(y/n)y

 >>>10
[lenovo@localhost svc]$ ./svc test.txt 5

 ----------------test.txt----------------
1 the first
2 second
3 third
4 fourth
5 fifth
 
 edit?(y/n)n
[lenovo@localhost svc]$ 
*/
