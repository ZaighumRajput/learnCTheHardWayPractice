#include <stdio.h>
#include "dbg.h"
#include <unistd.h>

char *get_allowed_logfiles(char LogProfileFile);
//Take command line arguments and parse them
//for example
//
char **ParseSearchKeywords(char **arguments);

int main(int argc, char *argv[])
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	char FilePath_SearchList[1024] = {""}; 
	strcat(cwd, "/locationToSearch");
	strcat(FilePath_SearchList, cwd);

	fprintf(stdout, "Search files: %s/n", FilePath_SearchList);	
	char **SearchKeywords = argv;	
	check(argc > 1, "USAGE: ./logfind textToSearch");
	
	//list of keywords
	//location of log files
	
	//search through each log file for keyword


	return 0;

error:
	return -1;
}
