#include <iostream>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <boost/tokenizer.hpp>
#include <list>
#include <fcntl.h>
#include <signal.h>
#include <stack>

using namespace std;
using namespace boost;

const int IN_RD = 1;
const int OUT_RD = 2;
const int OUT_RDA = 3;
const int PIPE = 4;
const int ERR_RD = 5;
const int ERR_RDA = 6;

int pid = 0;
stack<int> my_child;
//int pid_child = 0;

void convert_vector(vector< vector<string> > &v, vector<char*> &arg, int i)
{
	for(unsigned j = 0; j < v[i].size(); ++j)
	{
		arg[j] = &v[i][j][0];
	}
}

int out_redir(vector< vector<string> > &v, int i)
{
	int flag = 1;
	unsigned temp = i;
	int oldfd, newfd;

	if(temp >= v.size())
	{
		cout << "Error in syntax" << endl;
		return -1;
	}
	else
	{
		string d_file = v[i+1][0];
		
		vector<char*> argv(v[i].size() +1);
		convert_vector(v, argv, i);
		

		if(-1 == (oldfd = dup(1)))
		{
			perror("dup");
			_exit(1);
		}
		if(-1 == (newfd = open(d_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR)))
		{
			perror("open");
			return flag;
		}
		if(-1 == dup2(newfd,1))
		{
			perror("dup2");
			_exit(1);
		}
		int	status;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			_exit(1);
		}
		else if(0 == pid)
		{
			if(-1 == execvp(v[i][0].c_str(), argv.data()))
			{
				perror("execvp");
				_exit(1);
			}
		}
		else if( pid > 0)
		{
			if(-1 == waitpid(-1, &status, 0))
			{
				perror("waitpid");
				exit(1);
			}
		}
		if(-1 == dup2(oldfd,1))
		{
			perror("dup2");
			exit(1);
		}
		if(-1 == close(newfd))
		{
			perror("close");
			exit(1);
		}
	}
	return flag+1;
}

int stderr_redir(vector< vector<string> > &v, int i)
{
	int flag = 1;
	unsigned temp = i;
	int oldfd, newfd;

	if(temp >= v.size())
	{
		cout << "Error in syntax" << endl;
		return -1;
	}
	else
	{
		string d_file = v[i+1][0];
		
		vector<char*> argv(v[i].size() +1);
		convert_vector(v, argv, i);
		

		if(-1 == (oldfd = dup(2)))
		{
			perror("dup");
			_exit(1);
		}
		if(-1 == (newfd = open(d_file.c_str(), O_WRONLY | O_CREAT | O_TRUNC,
					S_IRUSR | S_IWUSR)))
		{
			perror("open");
			return flag;
		}
		if(-1 == dup2(newfd,2))
		{
			perror("dup2");
			_exit(1);
		}
		int	status;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			_exit(1);
		}
		else if(0 == pid)
		{
			if(-1 == execvp(v[i][0].c_str(), argv.data()))
			{
				perror("execvp");
				_exit(1);
			}
		}
		else if( pid > 0)
		{
			if(-1 == waitpid(-1, &status, 0))
			{
				perror("waitpid");
				exit(1);
			}
		}
		if(-1 == dup2(oldfd,2))
		{
			perror("dup2");
			exit(1);
		}
		if(-1 == close(newfd))
		{
			perror("close");
			exit(1);
		}
	}
	return flag+1;
}

int out_append_redir(vector< vector<string> > &v, int i)
{
	int flag = 1;
	unsigned temp = i;
	int oldfd, newfd;

	if(temp >= v.size())
	{
		cout << "Error in syntax" << endl;
		return -1;
	}
	else
	{
		string d_file = v[i+1][0];
		
		vector<char*> argv(v[i].size() +1);
		convert_vector(v, argv, i);
		

		if(-1 == (oldfd = dup(1)))
		{
			perror("dup");
			_exit(1);
		}
		if(-1 == (newfd = open(d_file.c_str(), O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR)))
		{
			perror("open");
			return flag;
		}
		if(-1 == dup2(newfd,1))
		{
			perror("dup2");
			_exit(1);
		}
		int	status;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			_exit(1);
		}
		else if(0 == pid)
		{
			if(-1 == execvp(v[i][0].c_str(), argv.data()))
			{
				perror("execvp");
				_exit(1);
			}
		}
		else if( pid > 0)
		{
			if(-1 == waitpid(-1, &status, 0))
			{
				perror("waitpid");
				exit(1);
			}
		}
		if(-1 == dup2(oldfd,1))
		{
			perror("dup2");
			exit(1);
		}
		if(-1 == close(newfd))
		{
			perror("close");
			exit(1);
		}
	}
	return flag+1;
}

int stderr_append_redir(vector< vector<string> > &v, int i)
{
	int flag = 1;
	unsigned temp = i;
	int oldfd, newfd;

	if(temp >= v.size())
	{
		cout << "Error in syntax" << endl;
		return -1;
	}
	else
	{
		string d_file = v[i+1][0];
		
		vector<char*> argv(v[i].size() +1);
		convert_vector(v, argv, i);
		

		if(-1 == (oldfd = dup(2)))
		{
			perror("dup");
			_exit(1);
		}
		if(-1 == (newfd = open(d_file.c_str(), O_WRONLY | O_CREAT | O_APPEND,
					S_IRUSR | S_IWUSR)))
		{
			perror("open");
			return flag;
		}
		if(-1 == dup2(newfd,2))
		{
			perror("dup2");
			_exit(1);
		}
		int	status;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			_exit(1);
		}
		else if(0 == pid)
		{
			if(-1 == execvp(v[i][0].c_str(), argv.data()))
			{
				perror("execvp");
				_exit(1);
			}
		}
		else if( pid > 0)
		{
			if(-1 == waitpid(-1, &status, 0))
			{
				perror("waitpid");
				exit(1);
			}
		}
		if(-1 == dup2(oldfd,2))
		{
			perror("dup2");
			exit(1);
		}
		if(-1 == close(newfd))
		{
			perror("close");
			exit(1);
		}
	}
	return flag+1;
}


int in_redir(vector< vector<string> > &v, int i)
{
	int flag = 1;
	unsigned temp = i;
	int oldfd, newfd;

	if(temp >= v.size())
	{
		cout << "Error in syntax" << endl;
		return -1;
	}
	else
	{
		string d_file = v[i+1][0];
		
		vector<char*> argv(v[i].size() +1);
		convert_vector(v, argv, i);
		

		if(-1 == (oldfd = dup(0)))
		{
			perror("dup");
			_exit(1);
		}
		if(-1 == (newfd = open(d_file.c_str(), O_RDONLY)))
		{
			perror("open");
			return flag;
		}
		if(-1 == dup2(newfd,0))
		{
			perror("dup2");
			_exit(1);
		}
		int	status;
		pid = fork();
		if(pid < 0)
		{
			perror("fork");
			_exit(1);
		}
		else if(0 == pid)
		{
			if(-1 == execvp(v[i][0].c_str(), argv.data()))
			{
				perror("execvp");
				_exit(1);
			}
		}
		else if( pid > 0)
		{
			if(-1 == waitpid(-1, &status, 0))
			{
				perror("waitpid");
				exit(1);
			}
		}
		if(-1 == dup2(oldfd,0))
		{
			perror("dup2");
			exit(1);
		}
		if(-1 == close(newfd))
		{
			perror("close");
			exit(1);
		}
	}
	return flag+1;
}




bool do_exec(vector<char*> &arg)
{
	int status;
	pid = fork();
	//error with fork
	if(pid < 0)
	{
		perror("fork()");
		exit(1);
	}
	//child process
	else if(pid == 0)
	{
		if(-1 == execvp(arg[0], arg.data()))//insert arg
		{
			perror("execvp()");
			_exit(1);
		}
		_exit(0);
	}
	//parent process
	else if(pid > 0)
	{
		if(-1 == waitpid(-1, &status, WUNTRACED))
		{
			perror("waitpid()");
			exit(1);
		}
		if(status != 0)
		{
			return false;
		}
	}
	return true;
}

bool check_connectors(bool status, list<string> &list)
{
	if(list.front() == ";")
	{
		list.pop_front();
		return true;
	}
	else if(list.front() == "&")
	{
		list.pop_front();
		if(list.front() == "&")
		{
			list.pop_front();
			if(!status) return false;
			else return true;
		}
		else{
			cout << "Error: Invalid connector." << endl;
			return false;
		}
	}
	else if(list.front() == "|")
	{
		list.pop_front();
		if(list.front() == "|")
		{
			list.pop_front();
			if(status) return false;
			else return true;
		}
		else{
			cout << "Error: Invalid connector." << endl;
			return false;
		}
	}
	else{
		return false;
	}
	
}

vector< vector<string> > parse_redir(string &str, vector<int> &v)
{
	bool fd_redir = false;

	for(unsigned i = 0; i < str.size(); ++i)
	{
		if(str[i] == '|')
		{
			v.push_back(PIPE);
		}
		else if(str[i] == '>')
		{
			if(str[i+1] == '>')
			{
				++i;
				v.push_back(OUT_RDA);
			}
			else
			{
				v.push_back(OUT_RD);
			}
		}
		else if(str[i] == '1')
		{
			if(str[i+1] == '>')
			{
				++i;
				if(str[i+1] == '>')
				{
					++i;
					v.push_back(OUT_RDA);
				}
				else
				{
					v.push_back(OUT_RD);
				}
			}
		}
		else if(str[i] == '2')
		{
			if(str[i+1] == '>')
			{
				++i;
				if(str[i+1] == '>')
				{
					++i;
					v.push_back(ERR_RDA);
				}
				else
				{
					v.push_back(ERR_RD);
				}
			}
		}
		else if(str[i] == '<')
		{
			v.push_back(IN_RD);
		}
		if(str.find("1>") != string::npos || str.find("1>>") != string::npos
			|| str.find("2>") != string::npos || str.find("2>>") != string::npos)
		{
			fd_redir = true;
		}
			
	}

	vector<string> vtok;
	if(fd_redir == true)
	{
		char_separator<char> delim("|><21");
		tokenizer< char_separator<char> > mytok(str, delim);
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			vtok.push_back(*it);
		}
	}
	else if (fd_redir == false)
	{	
		char_separator<char> delim("|><");
		tokenizer< char_separator<char> > mytok(str, delim);
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			vtok.push_back(*it);
		}
	}
	vector< vector<string> > vvtok;
	vector<string> vtemp;
	char_separator<char> delim2(" \t\n");
	for(unsigned i = 0; i < vtok.size(); ++i)
	{
		vtemp.clear();
		tokenizer< char_separator<char> > mytok2(vtok[i], delim2);
		for(auto itt = mytok2.begin(); itt != mytok2.end(); ++itt)
		{
			vtemp.push_back(*itt);
		}
		vvtok.push_back(vtemp);
	}
	return vvtok;
}

void do_redir(vector< vector<string> > &v, vector<int> &u)
{
	int curr;

	for(unsigned i = 0; i < v.size(); ++i)
	{
		if(i < u.size())
		{
			curr = u[i];
		}
		else
		{
			curr = 0;
		}
		if(curr == OUT_RD)
		{
			int x =	out_redir(v,i);
			if(x == -1)
			{
				return;
			}
			else
			{
				i = x + i;
				continue;
			}
		}
		
		if(curr == OUT_RDA)
		{
			int x =	out_append_redir(v,i);
			if(x == -1)
			{
				return;
			}
			else
			{
				i = x + i;
				continue;
			}
		}

		if(curr == IN_RD)
		{
			int x =	in_redir(v,i);
			if(x == -1)
			{
				return;
			}
			else
			{
				i = x + i;
				continue;
			}
		}
		if(curr == ERR_RD)
		{
			int x = stderr_redir(v,i);
			if(x == -1)
			{
				return;
			}
			else
			{
				i = x + i;
				continue;
			}
		}
		if(curr == ERR_RDA)
		{
			int x = stderr_append_redir(v,i);
			if(x == -1)
			{
				return;
			}
			else
			{
				i = x + i;
				continue;
			}
		}

	}
}

void set_cd_prev(char* &cd_prev)
{	
	//set prev pwd
	cd_prev = getenv("PWD");
	if(cd_prev == NULL)
	{
		perror("getenv()");
	}
}

void C_handle(int x)
{
	if(x == SIGINT)
	{
		cout << endl;
		if(pid != 0)
		{
			//pid = getpid() + 1;
		//}
			if(-1 == kill(pid, x))
			{
				perror("kill(): ^C");
			}
		}
		pid = 0;
	}
}

void Z_handle(int x)
{
	if(x == SIGTSTP)
	{
		cout << endl;
		if(pid != 0)
		{
			//pid = getpid() + 1;
		//}
			if(-1 == kill(pid, x))
			{
				perror("kill(): ^Z");
				//return;
			}
				
			else
			{
				cout << "\nProcess stopped " << endl;
				//return;
			}
			my_child.push(pid);
		}
	}
}


void sig_C()
{
	struct sigaction sigC;
	sigC.sa_handler = &C_handle; 	
	sigC.sa_flags = SA_RESTART;
	if(sigaction(SIGINT, &sigC, NULL) < 0)
	{
		perror("sigaction(): SIGINT");
	}
}

void sig_Z()
{
	struct sigaction sigZ;
	sigZ.sa_handler = &Z_handle;
	sigZ.sa_flags = SA_RESTART;
	if(sigaction(SIGTSTP, &sigZ, NULL) < 0)
	{
		perror("sigaction(): SIGTSTP");
	}
}

int main()
{
	//signals
	sig_C();
	sig_Z();

	char hostname[256];
	char *login_info;
	char buf[1024];

	if(gethostname(hostname, 256) == -1)
	{
		perror("hostname()");
	}

	login_info = getlogin();
	if(login_info == NULL)
	{
		perror("getlogin()");
	}
	
	char* cwd = getcwd(buf, 1024);
	if(cwd == NULL)
	{
		perror("getcwd()");
	}

	char* cd_save = NULL;
	char* cd_prev = NULL;	
	if(-1 == setenv("PWD", cwd, 1))
	{
		perror("setenv()");
	}
	set_cd_prev(cd_prev);
	cd_save = cd_prev;

	char* home = getenv("HOME");
	if(home == NULL)
	{
		perror("getenv()");
	}
	string home_str(home);


	while(1)
	{
		string input_cmd;
		list<string> parse_list;
		bool exec_check = false;
		bool redir_check = false;


		//taking out home folder from prompt
		string cwd_str(cwd);
		if(home != NULL && cwd_str.find(home_str) != string::npos)
		{
			size_t pos = cwd_str.find(home_str);
			cwd_str = cwd_str.substr(pos + home_str.length());
			cout << login_info << "@" << hostname << ":~" << cwd_str << " $ ";
		}
		else
		{
			//outputs user login and host name along with command prompt
			cout << login_info << "@" << hostname << ":" << cwd << " $ ";
		}
		
		//takes in commands
		getline(cin, input_cmd);
		

		//parse command input
		char_separator<char> delim(" \t","#;&|");
		tokenizer< char_separator<char> > mytok(input_cmd, delim);
		for(auto it = mytok.begin(); it != mytok.end(); ++it)
		{
			parse_list.push_back(*it);
		}


		if(input_cmd.find('<') != string::npos)
		{
			redir_check = true;
		}
		if(input_cmd.find('>') != string::npos)
		{
			redir_check = true;
		}
		if(input_cmd.find('|') != string::npos && input_cmd.find("||") == string::npos)
		{
			redir_check = true;
		}

		vector<int> v_redir;		
		vector<string> cmd_line;
		vector<char*> arg(parse_list.size() + 1);

		string exit_flag = parse_list.front();
		
		vector< vector<string> > cmd_vec;
		cmd_vec = parse_redir(input_cmd, v_redir);
		

		//make it so that anything after exit will still exit
		//
		//if exit entered, exit shell
		if(exit_flag == "exit")
		{
			exit(0);
		}	


		while(!(parse_list.empty()))
		{	
			//comments
			if(parse_list.front() == "#")
			{
				break;
			}
			//cd to home
			else if(parse_list.front() == "cd" && !(parse_list.size() >= 2))
			{
				
				set_cd_prev(cd_prev);
				cd_save = cd_prev;
				
				
				//
				const char *cd_home = getenv("HOME");
				if(cd_home == NULL)
				{
					perror("getenv()");
				}
				if(-1 == chdir(cd_home))
				{
					perror("chdir()");
				}
				//

				cwd = getcwd(buf,1024);
				if(NULL == cwd)
				{
					perror("getcwd()");
				}

				if(-1 == setenv("PWD", cwd, 1))
				{
					perror("setenv()");
				}
				set_cd_prev(cd_prev);


			}
			//cd to path
			else if(parse_list.front() == "cd" && parse_list.size() >= 2 
					&& input_cmd.find("-") == string::npos)
			{
				cmd_line.push_back(parse_list.front());
				parse_list.pop_front();

				set_cd_prev(cd_prev);
				cd_save = cd_prev;

				

				//
				const char *cd_path = parse_list.front().c_str();	
				if(-1 == chdir(cd_path))
				{
					perror("chdir()");
				}
				//

				cwd = getcwd(buf,1024);
				if(NULL == cwd)
				{
					perror("getcwd()");
				}

				if(-1 == setenv("PWD", cwd, 1))
				{
					perror("setenv()");
				}
				set_cd_prev(cd_prev);
				
			}
			//cd to previous
			else if(parse_list.front() == "cd" 
					&& input_cmd.find("-") != string::npos)
			{
				char* cd_saveb = cd_save;

				if(-1 == chdir(cd_save))
				{
					perror("chdir()");
				}
				cd_save = cd_prev;
				cd_prev = cd_saveb;	
				
				cwd = getcwd(buf, 1024);
				if(NULL == cwd)
				{
					perror("getcwd()");
				}
				if(-1 == setenv("PWD", cwd, 1))
				{
					perror("setenv()");
				}
				set_cd_prev(cd_prev);


			}
			//fg
			else if(parse_list.front() == "fg")
			{
				int status;
				
				if(!(my_child.empty()))
				{
					if(-1 == kill(my_child.top(), SIGCONT))
					{
						perror("kill(): SIGCONT");
					}
					if(!(my_child.empty()))
					{
						my_child.pop();
					}
				}
				if(-1 == waitpid(pid, &status, WUNTRACED) && !(my_child.empty()) )
				{
					perror("waitpid()");
				}
				else if(my_child.empty())
				{
					cout << "Error: no such job running" << endl;
					break;
				}
				break;
			}
			
			//bg
			else if(parse_list.front() == "bg")
			{
				if(!(my_child.empty()))
				{
					if(-1 == kill(my_child.top(), SIGCONT))
					{
						perror("kill(): SIGCONT");
					}
				}
				else if(my_child.empty())
				{
					cout << "Error: no such job running" << endl;
					break;
				}
			}
			
			
			//push only the commands, saving connectors in list
			while(!parse_list.empty() && parse_list.front() != "&"
					&& parse_list.front() != "|" && parse_list.front() != ";"
					&& parse_list.front() != "#")
			{
				cmd_line.push_back(parse_list.front());
				parse_list.pop_front();
			}
			if(cmd_line.size() == 0)
			{
				cout << "Error in syntax" << endl;
				break;
			}
			else if(cmd_line.front() == "exit")
			{
				exit(0);
			}
			else if(redir_check == true)
			{
				do_redir(cmd_vec, v_redir);
			}
			else if(cmd_line.front() != "cd")
			{

				for(unsigned int i = 0; i != cmd_line.size(); ++i)  
				{
					arg[i] = &cmd_line[i][0];
				}
				
				exec_check = do_exec(arg);
			}
			if(!check_connectors(exec_check, parse_list))
			{
				break;
			}

			cmd_line.clear();
			
		}		

	}

	return 0;
}
