#include <iostream>
#include <list>
#include <cctype>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <vector>
#include <grp.h>
#include <string.h>
#include <time.h>
#include <iomanip>
using namespace std;


//this funtion will be used to sort 
bool compare_nocase( const string &first, const string &second)
{
    unsigned int i=0;
    while((i<first.length()) && (i<second.length()))
    {
        if(tolower(first[i])<tolower(second[i]) )
            return true;
        else if(tolower(first[i])>tolower(second[i]) )
            return false;
        i++;
    }
    return ( first.length() < second.length() );
}
//this is where the directory names will be sorted alhabetically
void sort_vector(vector<string> &v)
{
    list<string> l;
    list<string>::iterator it;

    for(unsigned int i=0; i< v.size(); i++)
    {
        l.push_back(v[i]);
    }
    l.sort(compare_nocase);
    int i=0;
    for( it = l.begin(); it != l.end(); it++)
    {
        v[i] = *it;
        i++;
    }

}

void display_l2(string direc, string dfile)
{
    //cerr<<direc<<endl;
    //cerr<<dfile<<endl;
        
    DIR *dirp;
    dirent *direntpp;
    //string s = ".";
    if(!(dirp = opendir(direc.c_str()) ))
    {
        perror("OPENDIR ERROR");
    }
    while ((direntpp = readdir(dirp)))
    {
        if (errno != 0)
        {
            perror("ERRNO ERROR");
        }
        
        //if(direntp->d_name == direc)
        //{
           // DIR *dir;
            //dirent *direntpp;
            //if(!(dir = opendir(direc.c_str())))
           // {
             //   perror("OPENDIR ERROR2: ");
           // }
            //cerr<<"direntp->"<<direntp->d_name<<endl;
           // while((direntpp = readdir(dir)))
           // {
             //   if(errno != 0)
               // {
                 //   perror("ERRNO ERROR2: ");
               // }
                if(direntpp->d_name == dfile)
                {
                    //cerr<<"direntpp   "<<direntpp->d_name<<endl;
                    struct stat buff;
                    string path = direc+ "/" + direntpp->d_name;
                    stat(path.c_str(), &buff);
                   
                    (buff.st_mode & S_IFREG) ? cout<<'-':
                    (buff.st_mode & S_IFDIR) ? cout<<'d':
                    (buff.st_mode & S_IFLNK) ? cout<<'l':
                    cout<<endl;
                    (buff.st_mode & S_IRUSR) ? cout<<'r':cout<<'-';
                    (buff.st_mode & S_IWUSR) ? cout<<'w':cout<<'-';
                    (buff.st_mode & S_IXUSR) ? cout<<'x':cout<<'-';
                    (buff.st_mode & S_IRGRP) ? cout<<'r':cout<<'-';
                    (buff.st_mode & S_IWGRP) ? cout<<'w':cout<<'-';
                    (buff.st_mode & S_IXGRP) ? cout<<'x':cout<<'-';
                    (buff.st_mode & S_IROTH) ? cout<<'r':cout<<'-';
                    (buff.st_mode & S_IWOTH) ? cout<<'w':cout<<'-';
                    (buff.st_mode & S_IXOTH) ? cout<<'x':cout<<'-';
                    cout<<" ";
                    
                    cerr<<right<<setw(3)<<buff.st_nlink<<" ";

                    struct passwd *pass;
                    string userID;
                    struct group *grp;
                    string groupID;

                    if (!(pass = getpwuid(buff.st_uid)))
                    {
                        perror("GETPWID ERROR: ");
                    }
                    userID = pass->pw_name;
                    cerr<<userID<<" ";
                    if(!(grp = getgrgid(buff.st_gid)))
                    {
                        perror("GETGRGRID ERROR: ");
                    }
                    groupID = grp->gr_name;
                    cerr<<groupID<<" ";

                    int size = buff.st_size;
                    cerr<<right<<setw(10)<<size<<" ";
                    
                    struct tm time;
                    time_t t= buff.st_mtime;
                    if(localtime_r(&t, &time) == NULL)
                    {
                        perror("TIME ERROR: ");
                    }
                    char display_time[80];
                    tm *time2 = localtime(&t);
                    strftime(display_time,80, "%b %d %R", time2 );
                    cerr<<display_time<<" ";

                    if((direntpp->d_name[0] == '.') && (buff.st_mode & S_IFDIR))
                    {
                        cout<<"\033[47m\033[38;5;32m"<<dfile<<"\033[0;00m"<<endl;
                    }
                    else if((direntpp->d_name[0] == '.') && (buff.st_mode & S_IXUSR))
                    {
                        cout<<"\033[47m\033[38;5;34m"<<dfile<<"\033[0;00m"<<endl;
                    }
                    else if(direntpp->d_name[0] == '.') 
                    {
                        cout<<"\033[47m"<<dfile<<"\033[0;00m"<<endl;
                    }
                    else if(buff.st_mode & S_IFDIR)
                    {
                        cout<<"\033[38;5;32m"<<dfile<<"\033[0;00m"<<endl;
                    }
                    else if(buff.st_mode & S_IXUSR)
                    {
                        cout<<"\033[38;5;34m"<<dfile<<"\033[0;00m"<<endl;
                    }

                   else
                    {
                        cerr<<dfile<<endl;
                    }
     
                }
           // }closedir(dir);
       // }
    }closedir(dirp); 
}

void display_nl( string direc, string dfile )
{
    DIR *dirp;
    dirent *direntpp;
    //string s = ".";
    if(!(dirp = opendir(direc.c_str()) ))
    {
        perror("OPENDIR ERROR");
    }
    while ((direntpp = readdir(dirp)))
    {
        if (errno != 0)
        {
            perror("ERRNO ERROR");
        }

        if(direntpp->d_name == dfile)
        {
            struct stat buff;
            string path = direc+ "/" + direntpp->d_name;
            stat(path.c_str(), &buff);

            if((direntpp->d_name[0] == '.') && (buff.st_mode & S_IFDIR))
            {
                cout<<"\033[47m\033[38;5;32m"<<dfile<<"\033[0;00m"<<" ";
            }
            else if((direntpp->d_name[0] == '.') && (buff.st_mode & S_IXUSR))
            {
                cout<<"\033[47m\033[38;5;34m"<<dfile<<"\033[0;00m"<<" ";
            }
            else if(direntpp->d_name[0] == '.') 
            {
                cout<<"\033[47m"<<dfile<<"\033[0;00m"<<" ";
            }
            else if(buff.st_mode & S_IFDIR)
            {
                cout<<"\033[38;5;32m"<<dfile<<"\033[0;00m"<<" ";
            }
            else if(buff.st_mode & S_IXUSR)
            {
                cout<<"\033[38;5;34m"<<dfile<<"\033[0;00m"<<" ";
            }
            else
            {
                cerr<<dfile<<" ";
            }
        }
    }closedir(dirp);
}

void exec(vector<string> directories, bool ls_a, bool ls_l, bool ls_R)
{
    if ( ls_R == false)
    {
        int x =0;
        int num = directories.size();
        while(x<num)
        {
            vector<string> allFiles;
                
            DIR *dirp;
            dirent *direntp;
            string file = directories[x]; 
            if(!(dirp = opendir(file.c_str()) ))
            {
                perror("OPENDIR ERROR");
            }
            while ((direntp = readdir(dirp)))
            {
                if (errno != 0)
                {
                    perror("ERRNO ERROR");
                }
                struct stat buff;
                char get_file[1024];
                strcpy(get_file, file.c_str());
                strcat(get_file, "/");
                strcat(get_file, direntp->d_name);

                if((stat(get_file,&buff))==-1)
                {
                    perror("STAT ERROR");
                }
                if(direntp->d_name[0] == '.')
                {
                    if(ls_a == false)
                        continue;
                }
                allFiles.push_back((direntp->d_name));
            }
            closedir(dirp);
            sort_vector(allFiles);

            if(ls_l == true)
            {
                /*if(directories[0] == ".")
                {
                    for(unsigned int i=0; i<allFiles.size(); i++)
                        display_l(allFiles[i]);
                }*/   
                cerr<<directories[x]<<": "<<endl;
                for(unsigned int i=0; i<allFiles.size();i++)
                {
                    display_l2(directories[x], allFiles[i]);
                }
            }
           
            else
            {
                if(directories.size() >1)
                cerr<<directories[x]<<":"<<endl;
                for(unsigned int i=0; i<allFiles.size(); i++)
                    //cerr<<allFiles[i]<<" ";
                    display_nl(directories[x], allFiles[i]);
            }cerr<<endl;
            x++;
        }
    }
    else if (ls_R == true)
    {
        //cerr<<"R is true"<<endl;
        vector<string> allFiles;
        /*vector<string> directories2;
        for  (unsigned int i=0; i< directories.size(); i++)
        {
            cerr<<"Inside loop"<<endl;
            cerr<<directories[i]<<endl;
            directories2[i] = directories[i];
            cerr<<directories2[i]<<endl;
        }
        sort_vector(directories2);
        cerr<<"direc vector"<<endl;
        */
        int x=0;
        while(!directories.empty())
        {
            DIR *dirp;
            dirent *direntp;
            string file = directories[x]; 
            //cerr<<file<<endl;
            if(!(dirp = opendir(file.c_str()) ))
            {
                perror("OPENDIR ERROR");
            }
            while ((direntp = readdir(dirp)))
            {
                if (errno != 0)
                {
                    perror("ERRNO ERROR");
                }
                struct stat buff;
                char get_file[1024];
                strcpy(get_file, file.c_str());
                strcat(get_file, "/");
                strcat(get_file, direntp->d_name);

                if((stat(get_file,&buff))==-1)
                {
                    perror("STAT ERROR");
                }
                if(direntp->d_name[0] == '.')
                {
                    if(ls_a == false)
                        continue;
                } 
                allFiles.push_back((direntp->d_name));
                //cerr<<direntp->d_name<<endl;
                if(buff.st_mode & S_IFDIR)
                {
                    if((direntp->d_name[0] =='.')&&(direntp->d_name[1]=='.'))
                    {
                    }
                    else if ((direntp->d_name[0] == '.')&&(direntp->d_name[1]=='\0'))
                    {
                    }
                    else
                    {
                        string file = string(get_file);
                        //cerr<<file<<endl;
                        directories.insert(directories.begin()+1, file);
                    }
                }
            }
            closedir(dirp);
            sort_vector(directories);
            sort_vector(allFiles);

            if(ls_l == true)
            {
                /*if(directories[0] == ".")
                {
                    for(unsigned int i=0; i<allFiles.size(); i++)
                        display_l(allFiles[i]);
                }*/   
                cerr<<directories[x]<<": "<<endl;
                for(unsigned int i=0; i<allFiles.size();i++)
                {
                    display_l2(directories[x], allFiles[i]);
                    //cerr<<allFiles[i]<<endl;
                }
            }
           
            else
            {
                //if(directories.size() >1)
                cerr<<directories[x]<<":"<<endl;
                for(unsigned int i=0; i<allFiles.size(); i++)
                    //cerr<<allFiles[i]<<" ";
                    display_nl(directories[x], allFiles[i]);
            }cerr<<endl;

            directories.erase(directories.begin());
            allFiles.clear();
        }
    }
    
}
int main(int argc, char **argv)
{
    
    vector<char*> inputs; //this will be a vector of all the commands and/or directories
    int i=1;
    while(i<argc)
    {
        inputs.push_back(argv[i]);
        i++;
    }
    //i will check if the commands are called at least once so i can avoid repeating them later on
    bool ls_a = false;
    bool ls_l = false;
    bool ls_R = false;
    int j=0;
    int count=0;
    int size =inputs.size();
    while(j<size)
    {
        if(strcmp(inputs[j],"-a") == 0)
        {
            ls_a = true;
            count++;
        }
        else if(strcmp(inputs[j],"-l") == 0)
        {
            ls_l = true;
            count++;
        }
        else if(strcmp(inputs[j],"-R") == 0)
        {
            ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j],"-al") == 0)||(strcmp(inputs[j],"-la") == 0) )
        {
            ls_a = true; ls_l = true;
            count++;
        }
        else if( (strcmp(inputs[j],"-aR") == 0)||(strcmp(inputs[j],"-Ra") == 0) )
        {
            ls_a = true; ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j],"-lR") == 0)||(strcmp(inputs[j],"-Rl") == 0) )
        {
            ls_l = true; ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j],"-alR") == 0)||(strcmp(inputs[j],"-aRl") == 0) 
        || (strcmp(inputs[j],"-laR") == 0)||(strcmp(inputs[j],"-lRa") == 0) 
        || (strcmp(inputs[j],"-Ral") == 0)||(strcmp(inputs[j],"-Rla") ==0) )
        {
            ls_a = true; ls_l = true; ls_R = true;
            count++;
        }
        j++;
    }
    vector<string> directories; // this will be a  vector of all the dorectories (if any were inputted)
    while(count<size)
    {
        directories.push_back(string(inputs[count]));
        count++;
    }
    if(directories.size() == 0)
    {
        directories.push_back(".");
    }

    exec(directories, ls_a, ls_l, ls_R);

    return 0;
}
