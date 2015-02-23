#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <sys/types.h>
#include <sys/wait.h>


using namespace std;
bool pipes(char **c)
{
    int i=0;
    while (c[i] != '\0')
    {
        if( strcmp(c[i], "|") == 0)
        {
            return true;
        }
        i++;
    }
    return false;
}

void check_dup(char **c)
{
    int i=0;
    while( c[i] != '\0')
    {
        int fd;
        if( strcmp(c[i], "<") == 0)
        {
            c[i] = '\0';
            fd = open(c[i+1], O_RDONLY);
            if( fd == -1)
            {
                perror("error in open");
                exit(1);
            }
            if( dup2(fd,0) == -1)
            {
                perror("error in dup2");
                exit(1);
            }
        }
        else if( strcmp(c[i], ">") == 0)
        {
            c[i] = '\0';
            fd = open(c[i+1], O_CREAT | O_WRONLY |O_TRUNC, 0666);
            if( fd == -1)
            {
                perror("error in open");
                exit(1);
            }
            if( dup2(fd,1) == -1)
            {
                perror("error in dup2");
                exit(1);
            }
        }
        else if ( strcmp(c[i], ">>") == 0)
        {
            c[i] = '\0';
            fd = open(c[i+1], O_APPEND | O_CREAT | O_WRONLY, 0666);
            if( fd == -1)
            {
                perror("error in open");
                exit(1);
            }
            if( dup2(fd,1) == -1)
            {
                perror("error in dup2");
                exit(1);
            }
        }
        i++;
    }
}

void find_pipes(char **c)
{
    int status = 0;
    int num_pipes = 0;
    int pipe_index = 0;
    int i=0;
    while( c[i] != '\0')
    {
        if( strcmp(c[i], "|") == 0)
        {
            num_pipes++;
            pipe_index = i;
            break;
        }
        i++;
    }
    char **a = new char*[100];
    char **b = new char*[100];
    if(pipe_index > 0)
    {
        int j = 0;
        while( j < pipe_index)
        {
            a[j] = c[j];
            j++;
        }
        a[j] = '\0';
        int k = pipe_index+1;
        int l = 0;
        while( c[k] != '\0') 
        {
            b[l] = c[k];
            l++; k++;
        }
        b[l] = '\0';

        //now i will execute the commands with piping
        int fd[2];
        if(pipe(fd) == -1 )
        {
            perror("pipe fail");
            exit(1);
        }
        int pid = fork();
        if( pid  == -1)
        {
            perror("fork fail");
            exit(1);
        }
        else if(pid == 0)
        {
            if( dup2(fd[1], 1) == -1)
            {
                perror("error with dup2");
                exit(1);
            }
            if( close(fd[0]) == -1)
            {
                perror("error with close");
                exit(1);
            }
            check_dup(a);
            if( execvp( a[0], a) == -1)
            {
                perror("error in execvp");
                exit(1);
            }
            exit(1);
        }
        
        int savestdin;
        savestdin = dup(0);
        if( savestdin == -1)
        {
            perror("error with dup");
            exit(1);
        }
        if( dup2(fd[0],0) == -1)
        {
            perror("error with dup2");
            exit(1);
        }
        if( close(fd[1]) == -1)
        {
            perror("error with close");
            exit(1);
        }
        if (wait(&status) == -1)
        {
            perror("error in wait()");
            exit(1);
        }

        //we need to check that the rest of c does not have any pipes
        find_pipes(b);
        dup2(savestdin, 0);
/*       
        status = 1;
        int pid = fork();
        if(pid == -1)
        {
            perror("fork fail");
            exit(1);
        }
        else if(pid == 0)
        {
            //this will check for i/o redirection
            check_dup(a);

            if (execvp(a[0], a) !=0 )
            {
                perror("error in execvp");
                exit(1);
            }
        }
        //else
        //{
            if (wait(&status) == -1)
            {
                perror("error in wait");
                exit(1);
            }
       //}
    find_pipes(b);
*/
    }
        
    //if there are no more pipes to go through then the find_pipes fxm wil end

    int pid = fork();
    if(pid == -1)
    {
        perror("fork fail");
        exit(1);
    }
    else if(pid == 0)
    {
        //this will check for i/o redirection
        check_dup(c);

        if (execvp(c[0], c) !=0 )
        {
            perror("error in execvp");
            exit(1);
        }
    }
    else
    {
        if (wait(&status) == -1)
        {
            perror("error in wait");
            exit(1);
        }
    }


/*    int f=0;
    while( f < 100)
    {
        delete[] a[f];
        f++;
    }*/
    delete[] a;
/*    int ff=0;
    while( ff < 100)
    {
        delete[] b[ff];
        ff++;
    }*/
    delete[] b;


//    return status;
}

void check_spaces(string &s)
{
    int size = s.size();
    int i=0;
    while ( i < size  )
    {
        if (s[i] == '<')
        {
            s.insert(i+1 , " ");
            s.insert(i , " ");
        }
        else if (s[i] == '|')
        {
            s.insert(i+1 , " ");
            s.insert(i , " ");

        }
        else if (s[i] == '>')
        {
            if (s[i+1] == '>')
            {
                s.insert(i+2 , " ");
                s.insert(i , " ");
            }
            else
            {
                s.insert(i+1 , " ");
                s.insert(i , " ");
            }
        }
        i++;
    }
}

int num_tokens( char *c)
{
    int count =0;
    int i=0;
    while(c[i] != '\0')
    {
        if(c[i] == ' ')
        {
            count++;
        }
        i++;
    }
    return count+1;
}
//this fxn counts the number of & and | and pushes them back in order

vector<int> cmds_order(char *c)
{
    vector<int> v;
    int i=0;
    while(c[i] != '\0')
    {
        if ((c[i] =='&')&&(c[i+1]=='&'))
            {
                v.push_back(1);
                c[i+1] = ' ';
                i = i+2;
            }
        if ((c[i] =='|')&&(c[i+1] =='|'))
            {
                v.push_back(2);
                c[i] = '&';
                c[i+1] = ' ';
                i = i+2;
            }
        else
            i++;
    }
    //c[i] = '\0';
    return v;
}
//this fxm will run the commands passed in as char *c
int  run_exec( char *c, int count)
{
    char **cmd = new char*[count+1];

    string word = string(c);
//    cerr<<word<<endl;
    istringstream iss(c);
    int i=0;
    while(iss >>word)
    {
        const char *x = word.c_str();
        cmd[i] = new char[word.size()+1];
        strcpy(cmd[i], x );
        i++;
    }
    cmd[i] = '\0';
    int status;
    //this will run if there are <,>,>> in the command
    //then we wil check to pipes and execute i/o redirection and piping within this loop
    if( pipes(cmd) == true )
    {
//        cerr<<"FOUND PIPE"<<endl;
        //now i have to separate the arguments in the pipe
        find_pipes(cmd);
    }
    //all other regular commands will be ran through this loop
    else
    {
        status = 1;
//        cerr<<"no pipe"<<endl;
        int pid = fork();
        if(pid == -1)
        {
            perror("fork fail");
            exit(1);
        }
        else if(pid == 0)
        {
            //this will check for i/o redirection
            check_dup(cmd);

            if (execvp(cmd[0], cmd) !=0 )
            {
                perror("error in execvp");
                exit(1);
            }
        }
        //else
        //{
            if (wait(&status) == -1)
            {
                perror("error in wait");
                exit(1);
            }
       //}
    }
/*    int f=0;
    while( f < count+1)
    {
        delete[] cmd[f];
        f++;
    }*/
    delete[] cmd;
    return status;
    //this returns 0 if the execvp ran succesfully
}

int main(int argc, char **argv)
{
    while(1)
    {
        cerr<<"$ ";
    	
        string command_line;

        getline(cin, command_line);

        if ( command_line.find("exit") != string::npos)
            exit(0);
//        cerr<<command_line<<endl;
        //this will make sure there is spaces before and after i/o redirection
        check_spaces(command_line);
//        cerr<<command_line<<endl;
        char *commands = new char[command_line.length()+1];
        strcpy(commands, command_line.c_str());
  
        char *token,*save; 

        token = strtok_r(commands,"#",&save);
        token = strtok_r(commands,";",&save);
  
        while(token!= NULL)
        {
            vector<int> order; 
            bool prev = true;
            //i count the number of conditions and label & with 1 and | with 2
            //this will also change || to & to make tokenizing easier when adding pipping.
            //both && and || will be & but the order they appeared as initially will be in the vector
            order = cmds_order(token);
            if ( !(order.empty() ))
            {
                int i = -1;
                char *token2, *save2; 
                token2 = strtok_r(token, "&", &save2);
                         
                while( (token2 != NULL) )
                {  
                    if(i==-1)
                    {
                        if(run_exec(token2,num_tokens(token2)) !=0 )
                                prev = false;
                    }
                    else
                    {
                        if(prev ==true)
                        {
                            if(order.at(i) == 1)
                            {
                                if(run_exec(token2, num_tokens(token2)) !=0 )
                                        prev = false;
                            }
                            //if it is | we will no execute since the first one succeded
                        }
                        else
                        {
                            if(order.at(i) == 2)
                            {
                                if( run_exec(token2, num_tokens(token2)) != 0)
                                        prev = false;
                            }
                            //if it is & we wil not execute since the first part failed
                        }
                    }
                    token2 = strtok_r(NULL, "&", &save2);
                    i++;
               }
//               delete[] line;
            }
            else
            {             
                 run_exec(token, num_tokens(token));
            }
            token = strtok_r(NULL,";",&save);
        }
        //need to free memory
        delete[] commands;        
    }
	return 0;
}
