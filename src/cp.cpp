#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "Timer.h"

using namespace std;



void cp_one(const char* a, const char* b){
	ifstream is(a);
	ofstream os;
	os.open(b);
	char c;
	while(is.get(c)){
		os << c;
	}
	is.close();
	os.close();
}

void cp_two(const char* a, const char* b){
        ifstream is(a);
        ofstream os;
        os.open(b);
        char buf[1];
        int n;
        int i = open(a, O_RDONLY);
        int f = open(b, O_WRONLY);
        while((n = read(i, buf, 1)) > 0){
                write(f,buf,1);
        }
        is.close();
        os.close();

}

void cp_three(const char* a, const char* b){
	ifstream is(a);
	ofstream os;
	os.open(b);
	char buf[BUFSIZ];
	int n;
	int i = open(a, O_RDONLY);
	int f = open(b, O_WRONLY);
	while((n = read(i, buf, 1)) > 0){
		write(f,buf,1);
	}
	is.close();
	os.close();
}

int main(int argc, char *argv[]){
	char string[512];
	char *input = argv[1];
	char *output = argv[2];
	/*char a = '1';	
	if(argv[3] == a){
        Timer t1;
        double et1,e4,e7;
        t1.start();
        cp_one(input,output);
        t1.elapsedUserTime(et1);
        t1.elapsedWallclockTime(e4);
        t1.elapsedSystemTime(e7);
        cout << "1) CP:\nelapsed User Time: " << et1 << endl;
        cout << "elapsed Wall Clock Time: " << e4 << endl;
        cout << "elapsed System Time: " << e7 << endl;
	}
        else if(argv[3] == '2'){
        Timer t2;
	double et2,e5,e8;
	t2.start();
        cp_two(input,output);
        t2.elapsedUserTime(et2);
        t2.elapsedWallclockTime(e5);
        t2.elapsedSystemTime(e8);
        cout << "2) CP :\nelapsed User Time: " << et2 << endl;
        cout << "elapsed Wall Clock Time: " << e5 << endl;
        cout << "elapsed System Time: " << e8 << endl;
	}
	else if(argv[3] == '3'){
        Timer t3;
	double et3, e6, e9;
	t3.start();
        cp_three(input,output);
        t3.elapsedUserTime(et3);
        t3.elapsedWallclockTime(e6);
        t3.elapsedSystemTime(e9);

        cout << "3) CP :\nelapsed User Time: " << et3 << endl;
        cout << "elapsed Wall Clock Time: " << e6 << endl;
        cout << "elapsed System Time: " << e9 << endl;
	}
	else{ */	
        	Timer t1;
       		Timer t2;
        	Timer t3;
        	double et1,et2,et3,e4,e5,e6,e7,e8,e9;
		t1.start();
		cp_one(input,output);
		t1.elapsedUserTime(et1);
		t1.elapsedWallclockTime(e4);
		t1.elapsedSystemTime(e7);
		cout << "1) CP:\nelapsed User Time: " << et1 << endl;
		cout << "elapsed Wall Clock Time: " << e4 << endl;
		cout << "elapsed System Time: " << e7 << endl;

		t2.start();
		cp_two(input,output);
		t2.elapsedUserTime(et2);
		t2.elapsedWallclockTime(e5);
		t2.elapsedSystemTime(e8);
		cout << "2) CP :\nelapsed User Time: " << et2 << endl;
		cout << "elapsed Wall Clock Time: " << e5 << endl;
		cout << "elapsed System Time: " << e8 << endl;

		t3.start();
		cp_three(input,output);
		t3.elapsedUserTime(et3);
		t3.elapsedWallclockTime(e6);
		t3.elapsedSystemTime(e9);

		cout << "3) CP :\nelapsed User Time: " << et3 << endl;
		cout << "elapsed Wall Clock Time: " << e6 << endl;
		cout << "elapsed System Time: " << e9 << endl;
	//}


	return 0;
}
