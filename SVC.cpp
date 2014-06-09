//The Xtremes
//Group members: Kruti Chauhan 
//		 Saniya Kaluskar
//		 Janhavi Kulkarni
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<fstream>
#include<iostream>
#define MAX 10000
using namespace std;
struct lookuptable
{
    int linenumber;
    int versionnumber;
};
class version
{
     friend class file;
     lookuptable h[MAX];
     int maxversionno;
     int maxlines;
public:
    version()
     {
       maxversionno=-1;
       maxlines=0;
       for(int i=0;i<MAX;i++)
              h[i].linenumber=h[i].versionnumber=-1;
     }

};
class file
{
   fstream fp;

public:
    void create(version *);
    int errcheckdisp();
    int display(version*,int );
    void append(version *v);
    void delete1(version *v);
};
void file::create(version *x)
{
    char ch;
    int i;
    char arr[200],temp[10];
    cout<<"\nDo you want to write to the file ?\nThe Xtremes>Press y to continue and n to terminate \n\nThe Xtremes>";
    cin>>ch;
    if(ch!='n' && ch!='N')
    {
        fp.open("test.txt",fstream::out);
        cout<<"Enter data:";
         fflush(stdin);
        gets(arr);
        int k=strlen(arr);
        /*(*x).maxlines=ceil(k/9);*/
        (*x).maxversionno++;
        (*x).h[0].linenumber=(*x).h[0].versionnumber=0;
        int rem=k/9;
        for(i=0;i<rem*9;i=i+9)
        {
                  memset(temp,0,sizeof(temp));
                  strncpy(temp,&arr[i],9);
                  strcat(temp,"\n");
                  fp<<temp;
                  (*x).maxlines++;
        }
        if(k%9)
        {
        memset(temp,0,sizeof(temp));
        strncpy(temp,&arr[rem*9],k%9);
        strcat(temp,"\n");
        fp<<temp;
        (*x).maxlines++;
        }
        fp.close();
    }
    else
        return ;
}

int file::display(version *t,int x)
{
       int maxptr,i;
       char line[10];
       if((*t).maxversionno>=x)
       {
              fp.open("test.txt",fstream::in);
              if((*t).maxversionno==x)
                     maxptr=(*t).maxlines;
              else
              maxptr=((*t).h[x+1].linenumber);
               i=0;
               cout<<"maxptr"<<maxptr;
               while(i<maxptr)
               {
                      memset(line,0,sizeof(line));
                      fp.getline(line,sizeof(line));
                      cout<<line<<endl;
                      i++;
               }
               fp.close();
       }
       else
       {
              cout<<"you have entered wrong version number";
              return -1;
       }

      return 0;
}
int file::errcheckdisp()
{  
    char arr[30],temp1[10],temp2[10],temp3[10];
    cout<<"\n\nSyntax: Svc <Version number>\n\nThe Xtremes>";
    fflush(stdin);
    gets(arr);
    sscanf(arr,"%s %s %s ",temp1,temp2,temp3);
    //add temp1, add temp2
    if(isdigit(temp2[0]))
        return atoi(temp2);
    else
        return -1;
}
void file::append(version *v)
{
       char arr[200],temp[10];
       if((*v).maxlines<20)
       {
                cout<<"Enter data to append:";
                fflush(stdin);
                gets(arr);
                fp.open("test.txt",fstream::app|fstream::out);
                  (*v).maxversionno++;
                  (*v).h[(*v).maxversionno].versionnumber=(*v).maxversionno;
                  (*v).h[(*v).maxversionno].linenumber=(*v).maxlines;
                  cout<<(*v).h[(*v).maxversionno].linenumber<<"linenumber"<<endl;
                  int k=strlen(arr);
                  int rem=k/9;
                  for(int i=0;i<rem*9 && (*v).maxlines<20;i=i+9)
                  {
                     memset(temp,0,sizeof(temp));
                     strncpy(temp,&arr[i],9);
                     (*v).maxlines++;
                     cout<<temp;
                     strcat(temp,"\n");
                     fp<<temp;
                  }
                  if(k%9)
                  {
                    memset(temp,0,sizeof(temp));
                    strncpy(temp,&arr[(int)(floor(k/9))*9],k%9);
                    cout<<temp;
                    strcat(temp,"\n");
                     fp<<temp;
                     (*v).maxlines++;
                  }
                  fp.close();
       }
       else
              cout<<" Maximum limit exceeded";
}
void file::delete1(version *t)
{
               char arr[200],line[10];
                cout<<"Enter data to delete:";
                fflush(stdin);
                gets(arr);
                fstream f;
                fp.open("test.txt",fstream::in);
               f.open("temp.txt",fstream::out);
               int i=0,k;
               int flag=1;
                while(!fp.eof())
                {
                       i++;
                      fp.getline(line,sizeof(line));
                       if(strcmp(arr,line)!=0)
                            {
                                   f<<line;
                                   f<<"\n";
                            }
                        else
                         {
                              k=i;
                              flag=0;
                         }
                }
                if(flag==1)
                {
                       cout<<"Line not present in file";
                       return;
                }
                 fp.close();
                 f.close();
                 remove("test.txt");
                 rename("temp.txt","test.txt");

                (*t).maxlines--;
                i=0;
                while(i<(*t).maxversionno)
                {
                       if(k<(*t).h[i].linenumber)
                       {
                             // cout<<"in if"<<endl;
                       }
                       else
                       {
                              (*t).h[i].linenumber--;
                       }
                       i++;
                }
                /*for(int j=k+1;j<=maxversionno;j++)
                     (*v).h[j].linenumber--;
                (*v).h[k].linenumber=(*v).h[k-1].linenumber; */
}
int main()
{
    char c='y';
    int ch,x;
    file f;
    version v;
    f.create(&v);

    while(c!='n')
    {
        cout<<"\nThe Xtremes>\n\t\tMenu :\n 1.Append a line \n 2.Delete a line\n 3.Display file \nEnter choice\n\nThe Xtremes>";
        cin>>ch;
        switch(ch)
        {
        case 1:f.append(&v);
            break;
        case 2:f.delete1(&v);
            break;
        case 3:x=f.errcheckdisp();
            if(x!=-1)
                f.display(&v,x);
            break;
        default:
            cout<<"You have entered a wrong option";
            break;
        }
        cout<<"\nThe Xtremes>Press y to continue and n to terminate \nThe Xtremes>";
        cin>>c;
    }
    return 0;
}
