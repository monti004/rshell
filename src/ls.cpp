#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(int argc, char **argv)
{
    
    vector<char*> inputs; //this will be a vector of all the commands and/or directories
    int i=1;
    while(i<argc)
    {
        inputs.push_back(argv[i]);
        i++:
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
        if(strcmp(inputs[j])=="-a")
        {
            ls_a = true;
            count++;
        }
        else if(strcmp(inputs[j])=="-l")
        {
            ls_l = true;
            count++;
        }
        else if(strcmp(inputs[j])=="-R")
        {
            ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j])=="-al")||(strcmp(inputs[j])=="-la") )
        {
            ls_a = true; la_l = true;
            count++;
        }
        else if( (strcmp(inputs[j])=="-aR")||(strcmp(inputs[j])=="-Ra") )
        {
            ls_a = true; ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j])=="-lR")||(strcmp(inputs[j])=="-Rl") )
        {
            ls_l = true; ls_R = true;
            count++;
        }
        else if( (strcmp(inputs[j])=="-alR")||(strcmp(inputs[j])=="-aRl") 
        || (strcmp(inputs[j])=="-laR")||(strcmp(inputs[j])=="-lRa") 
        || (strcmp(inputs[j])=="-Ral")||(strcmp(inputs[j])=="-Rla") )
        {
            ls_a = true; ls_l = true; ls_R = true;
            count++;
        }
        j++:
    }
    vector<string> directories; // this will be a  vector of all the dorectories (if any were inputted)
    while(count<size)
    {
        directories.push_back(string(inputs[count]));
        count++;
    }

    if ( (ls_a == false)&&(ls_l == false)&&(ls_R == false))
    {
        if(inputs.size()) // i will display the files in the given directory/ies
        {
        }
        else // i will just display the file names in the current directory
        {
        }
    }
    //the following will check which of the ls commands will be executed
    else if ( (ls_a == true)&&(ls_l == false)&&(ls_R == false) )
    {
    }
    else if ( (ls_a == true)&&(ls_l == true)&&(ls_R == false) )
    {
    }
    else if ( (ls_a == true)&&(ls_l == false)&&(ls_R == true) )
    {
    }
    else if ( (ls_a == false)&&(ls_l == true)&&(ls_R == false) )
    {
    }
    else if ( (ls_a == false)&&(ls_l == true)&&(ls_R == true) )
    {
    }
    else if ( (ls_a == false)&&(ls_l == false)&&(ls_R == true) )
    {
    }
    else if ( (ls_a == true)&&(ls_l == true)&&(ls_R == true) )
    {
    }





    return 0;
}
