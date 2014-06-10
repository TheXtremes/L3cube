#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
using namespace std;
struct file_info
{
    char file_name[20];
    double file_size;
    char file_path[100];
    int dup_no;
};
void display_delete()
{
    ifstream fp;
    fp.open("duplicates.txt");
    file_info f;
    fp>>f.file_name;
    fp>>f.file_size;
    fp>>f.file_path;
    cout<<"\nThe List of Duplicate Files is:";
    cout<<"\nFile Name\t\tFile Size\t\tFile Path\n\n";
    while(!fp.eof())
    {
        cout<<"\n"<<f.file_name<<"\t"<<f.file_size<<"\t"<<f.file_path;
        fp>>f.file_name;
        fp>>f.file_size;
        fp>>f.file_path;
    }
    fp.close();
    //Delete fn
    char answer;
    char del_name[200],del_path[1000];
    ifstream delfp;
    ofstream newfp;
    int i,j;
    char temp_str[1000];
    while(1)
    {
        cout<<"\nDo you wish to delete a file? y-Yes n-No";
        cin>>answer;

        if(answer=='y' || answer=='Y')
        {
            cout<<"\nEnter name of the file to be deleted:\t";
            cin>>del_name;

            cout<<"\nEnter exact path of the file to be deleted as mentioned above:\t";
            cin>>del_path;

            delfp.open("Duplicates.txt",ios::in);
            newfp.open("temp.txt",ios::out);

            while(delfp)
            {

            delfp>>f.file_name;
            delfp>>f.file_size;
            delfp>>f.file_path;

            if(!strcmp(f.file_name,del_name) && !strcmp(f.file_path,del_path))
            {
                strcpy(temp_str,f.file_path); j=0;
                //cout<<"\nInitial condition of i:\t"<<strlen(f.file_path)-3;
                //cout<<"\nLimiting condition of i:\t"<<strlen(f.file_name);
                for(i=strlen(f.file_path)-3;i<strlen(f.file_path)-3+strlen(f.file_name);i++)
                {
                    temp_str[i]=f.file_name[j];
                    //cout<<"\nCurrent letter\t"<<f.file_name[j];
                    j++;
                }
                temp_str[i]='\0';
                cout<<"\nThe new file to be deleted:\t"<<temp_str;
                remove(temp_str);
                break;
            }
            else
            {
                newfp<<f.file_name;
                newfp<<"\t";
                newfp<<f.file_size;
                newfp<<"\t";
                newfp<<f.file_path;
                newfp<<"\n";
            }

            }
            newfp.close();
            delfp.close();
            remove("Duplicates.txt");
            rename("temp.txt","Duplicates.txt");
        }
        else
            break;
    }
}
int already_present(char x[], int y,char path[])
{
    fstream fp;
    ofstream fdup;
    file_info f;
    fp.open("file_temp.txt",fstream::in|fstream::out);
    while(fp)
    {
        //cout<<"\nIn while";
        fp>>f.file_name;
        fp>>f.file_size;
        fp>>f.file_path;
        fp>>f.dup_no;
        if(!strcmp(x,f.file_name)&& y==f.file_size)
        {
            if(f.dup_no==0)
            {
            fdup.open("duplicates.txt",ofstream::app);
            fdup<<f.file_name;
            fdup<<"\t";
            fdup<<f.file_size;
            fdup<<"\t";
            fdup<<f.file_path;
            fdup<<endl;
            fdup.close();
            }
            //cout<<"\nIn if: Duplicate file! filename:"<<x;
            f.dup_no++;
            fp.seekg(-3,fp.cur);
            fp<<f.dup_no;
            fp.close();
            fdup.open("duplicates.txt",ofstream::app);
            fdup<<x;
            fdup<<"\t";
            fdup<<y;
            fdup<<"\t";
            fdup<<path;
            fdup<<endl;
            fdup.close();
            //cout<<"\n\nAlready Present! File name:"<<x<<"\nFile Path1:"<<z<<"\nFile Path2:"<<f.file_path<<"\n";
            return 1;
        }
       // memset(&f,0,sizeof(f));
    }
    fp.close();
    return 0;
}
void findfiles(char foldername[30])
{
    int i;
    WIN32_FIND_DATA file;
    HANDLE search_handle=FindFirstFile(foldername,&file);
    FindNextFile(search_handle,&file);
    FindNextFile(search_handle,&file);
    if (search_handle)
    {
        do
        {
            if(file.dwFileAttributes != 16)
            {
                //cout << file.cFileName << "\t" <<file.nFileSizeLow<<std::endl;
                if(!already_present(file.cFileName,file.nFileSizeLow,foldername))
                {
                    ofstream fp;
                    fp.open("file_temp.txt",ios::app);
                    file_info f;
                    strcpy(f.file_name,file.cFileName);
                    strcpy(f.file_path,foldername);
                    f.file_size=file.nFileSizeLow;
                    f.dup_no=0;
                    //cout<<"\nFile name:"<<f.file_name<<"\tFile size:"<<f.file_size<<"\tFile path:"<<f.file_path;
                    fp<<f.file_name;
                    fp<<"\t";
                    fp<<f.file_size;
                    fp<<"\t";
                    fp<<f.file_path;
                    fp<<"\t";
                    fp<<f.dup_no;
                    fp<<"\t";
                    //f.p=(char**)malloc(sizeof(char*)*f.dup_no);

                    //fp<<f.p;
                    fp<<endl;
                    fp.close();
                }
            }
            else
            {
                char temp[20];
                int len=strlen(foldername);
                //cout<<"\nOld FolderName is "<<foldername;
                for(i=0;i<len-3;i++)
                    temp[i]=foldername[i];
                temp[i]='\0';
                //cout<<"\nTemp is "<<temp;
                //cout<<"\nFile name is "<<file.cFileName;
                strcat(temp,file.cFileName);
                char newpath[20];
                strcat(temp,"\\*.*");
                strcpy(newpath,temp);
                //cout<<"\nNewPath is :\t"<<newpath;
                findfiles(newpath);
            }

        }while(FindNextFile(search_handle,&file));

        CloseHandle(search_handle);
    }
}
int main()
{
    findfiles("C:\\*.*");
    remove("file_temp.txt");
    display_delete();
    remove("duplicates.txt");
    return 0;
}
