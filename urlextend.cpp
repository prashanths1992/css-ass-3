#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>
#include <errno.h>
#include <sys/user.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/reg.h>
#include<iostream>

using namespace std;

bool replaceFileName(string s,unsigned long addr,int pid)
{

	for(int i=0;i<s.length();i++)
	{
		long int ret = ptrace(PTRACE_POKEDATA, pid, addr+i,s[i]);
	}

}


// ref: https://techoverflow.net/2013/08/21/how-to-get-filesize-using-stat-in-cc/
size_t getFilesize(const std::string& filename) {
    struct stat st;
    if(stat(filename.c_str(), &st) != 0) {
        return 0;
    }
    return st.st_size;   
}


int main(int argc,char* argv[])
{
	int status ;
	struct user_regs_struct regs;

	int pid_wget,pid,enter;

	if(argc<3)
	{
		cout<<"ERROR: Invalid arguments passed"<<endl;
		cout<<"\nCases Supported are: \n\t1. wc  for ex. urlextend wc www.google.com\n\t2. cp  for ex. urlextend cp www.google.com tempFile.html \n\t3. mv  for ex. urlextend mv www.google.com tempFile.txt\n\t4. vi  for ex. urlextend vi www.google.com\n";
		return 1;
	}

    int caseNum;

	if(strcmp(argv[1],"wc")==0) caseNum = 1;
	else if(strcmp(argv[1],"cp")==0) caseNum = 2;
	else if(strcmp(argv[1],"mv")==0) caseNum = 3;
	else if(strcmp(argv[1],"vi")==0) caseNum = 4;
	else caseNum=-1;

    
    
    switch(caseNum)
    {
    	case 1:
    	{
			pid_wget = fork();

			if(!pid_wget)
			{
				char* temp_arr[] = {"/usr/bin/wget",argv[2],"-q","-O",": lines\ words\ bytes",NULL}; 
				execvp("/usr/bin/wget", temp_arr);
			}
			else
			{
				while(1)
				{
					wait(&status);
					if ( WIFEXITED( status ) ) break;
				}
			}


			pid = fork();
			enter =1;
			char *arr1[] = {argv[1],argv[2], NULL};



			if (!pid) 
			{
				ptrace(PTRACE_TRACEME,0,0,0);
				execvp(argv[1], arr1);
			}
			else 
			{
				while(1)
				{
					ptrace( PTRACE_SYSCALL, pid, 0, 0 );

					wait( &status );
					if ( WIFEXITED( status ) ) break;

					ptrace( PTRACE_GETREGS, pid, 0, &regs );

					int syscall_n = regs.orig_eax;

					if ( syscall_n == SYS_stat64) 
					{
						
						if(enter == 1)
						{

							string s  = ": lines\ words\ bytes\0";
							replaceFileName(s,regs.ebx,pid);

						}
					else
					{
						// return 0;
					}

				//cout<<regs.eax<<" "<<regs.ebx<<" "<<regs.ecx<<endl;
				}
			}

			}

			remove(": lines\ words\ bytes");
		}
			break;

		case 2:
		{
			pid_wget = fork();

			if(argc<4)
			{
				cout<<"ERROR : Invalid args passed"<<endl;
				cout<<"\nCases Supported are: \n\t1. wc  for ex. urlextend wc www.google.com\n\t2. cp  for ex. urlextend cp www.google.com tempFile.html \n\t3. mv  for ex. urlextend mv www.google.com tempFile.txt\n\t4. vi  for ex. urlextend vi www.google.com\n";
				break;
			}


			if(!pid_wget)
			{
				char* temp_arr[] = {"/usr/bin/wget",argv[2],"-q","-O","oot",NULL}; 
				execvp("/usr/bin/wget", temp_arr);
			}
			else
			{
				while(1)
				{
					wait(&status);
					if ( WIFEXITED( status ) ) break;
				}
			}


			pid = fork();
			enter =0;
			char* arr2[] = {argv[1],argv[2],argv[3], NULL};



			if (!pid) 
			{
				ptrace(PTRACE_TRACEME,0,0,0);
				execvp(argv[1], arr2);
			}
			else 
			{
				while(1)
				{
					ptrace( PTRACE_SYSCALL, pid, 0, 0 );

					wait( &status );
					if ( WIFEXITED( status ) ) break;

					ptrace( PTRACE_GETREGS, pid, 0, &regs );

					int syscall_n = regs.orig_eax;

					if ( syscall_n == SYS_stat64) 
					{
						enter++;
						unsigned long a = ptrace(PTRACE_PEEKDATA, pid,regs.ebx, NULL);

						char s[100];

						memcpy(s,(void*)&a,10);
						// cout<<s<<" "<<enter<<endl;

						
						if(enter == 3 )
						{

							string s  = "oot\0";
							replaceFileName(s,regs.ebx,pid);

						}
					

				//cout<<regs.eax<<" "<<regs.ebx<<" "<<regs.ecx<<endl;
				    }
			    }

		    }

			remove("oot");
			break;
		}

		case 3:
		{
			pid_wget = fork();

			if(argc<4)
			{
				cout<<"ERROR : Invalid args passed"<<endl;
				cout<<"\nCases Supported are: \n\t1. wc  for ex. urlextend wc www.google.com\n\t2. cp  for ex. urlextend cp www.google.com tempFile.html \n\t3. mv  for ex. urlextend mv www.google.com tempFile.txt\n\t4. vi  for ex. urlextend vi www.google.com\n";
				break;
			}


			if(!pid_wget)
			{
				char* temp_arr[] = {"/usr/bin/wget",argv[2],"-q","-O","oot",NULL}; 
				execvp("/usr/bin/wget", temp_arr);
			}
			else
			{
				while(1)
				{
					wait(&status);
					if ( WIFEXITED( status ) ) break;
				}
			}


			pid = fork();
			enter =0;
			char* arr2[] = {argv[1],argv[2],argv[3], NULL};



			if (!pid) 
			{
				ptrace(PTRACE_TRACEME,0,0,0);
				execvp(argv[1], arr2);
			}
			else 
			{
				while(1)
				{
					ptrace( PTRACE_SYSCALL, pid, 0, 0 );

					wait( &status );
					if ( WIFEXITED( status ) ) break;

					ptrace( PTRACE_GETREGS, pid, 0, &regs );

					int syscall_n = regs.orig_eax;
                   
                    //cout<<syscall_n<<" "<<SYS_lstat64<<endl;

					if ( syscall_n == SYS_lstat64) 
					{
						enter++;
						// unsigned long a = ptrace(PTRACE_PEEKDATA, pid,regs.ebx, NULL);

						// char s[100];

						// memcpy(s,(void*)&a,10);
						// cout<<s<<" "<<enter<<endl;

						
						if(enter == 1)
						{

							string s  = "oot\0";
							replaceFileName(s,regs.ebx,pid);

						}
					

				//cout<<regs.eax<<" "<<regs.ebx<<" "<<regs.ecx<<endl;
				    }
			    }

		    }

			remove("oot");
			break;
		}

		case 4:
		{
			pid_wget = fork();

			int fileModified;

			if(argc<3)
			{
				cout<<"Invalid args passed"<<endl;
				break;
			}


			if(!pid_wget)
			{
				char* temp_arr[] = {"/usr/bin/wget",argv[2],"-q","-O","URLFile",NULL}; 
				execvp("/usr/bin/wget", temp_arr);
			}
			else
			{
				while(1)
				{
					wait(&status);
					if ( WIFEXITED( status ) ) break;
				}
			}


			pid = fork();
			enter =0;
			char* arr2[] = {argv[1],"-R",argv[2], NULL};



			if (!pid) 
			{
				ptrace(PTRACE_TRACEME,0,0,0);
				execvp(argv[1], arr2);
			}
			else 
			{
				while(1)
				{
					ptrace( PTRACE_SYSCALL, pid, 0, 0 );

					wait( &status );
					if ( WIFEXITED( status ) ) break;

					ptrace( PTRACE_GETREGS, pid, 0, &regs );

					int syscall_n = regs.orig_eax;
                   
                    //cout<<syscall_n<<" "<<SYS_lstat64<<endl;

					if ( syscall_n == SYS_stat64) 
					{
					    enter++;


                         
						
						if(enter == 5)
						{
							fileModified = getFilesize("URLFile");

							string s  = "URLFile\0";
							replaceFileName(s,regs.ebx,pid);

						}						

						// unsigned long a = ptrace(PTRACE_PEEKDATA, pid,regs.ebx, NULL);

						// char s[100];

						// memcpy(s,(void*)&a,10);
						// cout<<s<<" "<<enter<<endl;
					

				//cout<<regs.eax<<" "<<regs.ebx<<" "<<regs.ecx<<endl;
				    }
			    }

		    }
            cout<<fileModified<<" "<<getFilesize("URLFile")<<endl;

		    if(getFilesize("URLFile")-fileModified<=1)
			     remove("URLFile");

			break;
		}

		default:
					cout<<"\nCases Supported are: \n\t1. wc  for ex. urlextend wc www.google.com\n\t2. cp  for ex. urlextend cp www.google.com tempFile.html \n\t3. mv  for ex. urlextend mv www.google.com tempFile.txt\n\t4. vi  for ex. urlextend vi www.google.com\n";

    }


    

	return 0;

}