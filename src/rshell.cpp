
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

int num_tokens( char *c)
{
    int count = sizeof(c)/sizeof(c[0]);
    return count;
}
//this fxn counts the number of & and | and pushes them back in order
vector<int> cmds_order(char *c)
{
    vector<int> v;
    int i=0;
    while(c[i] != '\0')
    {
        if (c[i] =='&')
            v.push_back(1);
        if (c[i] =='|')
            v.push_back(2);
        i++;
    }
    return v;
}
//this fxm will run the commands passed in as char *c
int  run_exec( char *c, int count)
{    
    char **cmd = (char**)malloc(sizeof(char*)*(count+1));

    string word = string(c);
    istringstream iss(c);
    int i=0;
    while(iss >>word)
    {
        const char *x = word.c_str();
        cmd[i] = (char*)malloc(sizeof(char*)*(word.size()+1));
        strcpy(cmd[i], x );
        i++;
    }
    cmd[i] = NULL;
    
     
    int pid = fork();
    int status = 1;

    if(pid == -1)
    {
        perror("fork fail");
        exit(1);
    }
    else if(pid == 0)
    {
        if (execvp(cmd[0], cmd) !=0 )
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
   free(cmd);
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
        char *line = new char[command_line.length()+1];
        char *commands = new char[command_line.length()+1];
        strcpy(line, command_line.c_str());

        //i am removing the second &,|
        int k=0;
        while(line[k] != '\0')
        {
            if ((line[k] =='&')&&(line[k+1] =='&'))

                commands[k]=line[k];
                commands[k+1]=' ';
                k = k+2;
            }
            else if ((line[k] =='|')&&(line[k+1] =='|'))
            {
                commands[k]=line[k];
                commands[k+1]=' ';
                k = k+2;
            }
            else
            {
                commands[k]=line[k];
                k++;
            }
        }commands[k]='\0';
        delete[] line;
        char *token,*save; 

        token = strtok_r(commands,"#",&save);
        token = strtok_r(commands,";",&save);
  
        while(token!= NULL)
        {
            vector<int> order; 
            bool prev = true;
            //i count the number of conditions and label & with 1 and | with 2
            order = cmds_order(token);
            if ( !(order.empty() ))
            {
                int i = -1;
                char *token2, *save2; 
                token2 = strtok_r(token, "&|", &save2);
                         
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
                    token2 = strtok_r(NULL, "&|", &save2);
                    i++;
               }
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
