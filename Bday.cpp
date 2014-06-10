#include<iostream.h>
#include<stdlib.h>
#include<conio.h>
int grp[80][80];
int grpsize;
int markedgrp[20];
void mark()
{
	int n,flag=0;
	n=365/grpsize;

	int i,j,k;
	int temp[20];
	for(i=0;i<n;i++)
		temp[i]=rand()%grpsize;
	for(i=0;i<n;i++)
	{
		for(j=0;j<grpsize-1;j++)
		{
			for(k=j+1;k<grpsize-1;k++)
			{
				if(grp[j][temp[i]]==grp[k][temp[i]])
				{
					markedgrp[i]=1;
					flag=1;
					break;
				}
			}
			if(flag==1)
			{
				flag=0;
				break;
			}
		}
	}
	int cnt=0;
	for(i=0;i<n;i++)
	{
		if(markedgrp[i]==1)
			cnt++;
	}

	float prob;
	prob=(float)cnt/n;

	cout<<"\n***Probability is:\t\t"<<prob;

}




int main()
{

	int i,j;
	clrscr();
	int choice;
	for(i=0;i<20;i++)
		markedgrp[i]=0;
	do
	{
	cout<<"\nEnter the group size:\t";
	cin>>grpsize;
	}while(grpsize<=0 || grpsize>80);
	choice=1;
	do
	{
		cout<<"\nEnter a random number:\t";
		cin>>choice;
	}while(choice<=0);

	for(i=0;i<grpsize;i++)
		for(j=0;j<grpsize;j++)
			grp[i][j]=(choice+rand())%365;
	for(i=0;i<grpsize;i++)
	{
		cout<<"\n";
		for(j=0;j<grpsize;j++)
			cout<<" "<<grp[i][j];
	}
	cout<<"\n\n_________________________________";
	mark();
	getch();
	return 0;
}

