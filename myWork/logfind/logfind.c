#include <stdio.h>
#include "dbg.h"
#include <unistd.h>

void get_allowed_logfiles(char *LogProfileFile, char **FilesToSearch[], int * CountEntries);
//Take command line arguments and parse them
//for example
//
char **ParseSearchKeywords(char **arguments);

int main(int argc, char *argv[])
{
	//get the file with searchable log files
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));

	char FilePath_SearchList[1024] = {""}; 
	strcat(cwd, "/locationToSearch");
	strcat(FilePath_SearchList, cwd);

	fprintf(stdout, "Search files: %s/n", FilePath_SearchList);	
	
	//get available search locations from file that lists them
	char *SearchLocations[10];
	int CountEntries = 0;
	get_allowed_logfiles(FilePath_SearchList, SearchLocations, &CountEntries);
	log_info("Number of files to Search %d", CountEntries);
	char **SearchKeywords = argv;	
	check(argc > 1, "USAGE: ./logfind textToSearch");

	for(int fileNumber = 0; fileNumber < CountEntries; fileNumber++)
	{
		debug("Searching: %s...", SearchLocations[fileNumber]);
	}	
	//search through each log file for keyword
	printf("Number of entries in SearchLocations: %zu", sizeof(SearchLocations));

	return 0;

error:
	return -1;
}

void get_allowed_logfiles(char *LogProfileFile, char **FilesToSearch[], int * CountEntries)
{
	//LESSON: can't just have a pointer pointing to nothing.
	//have to allocate memory
	//char *FilesToSearch[256];
	FILE *file = fopen(LogProfileFile, "r");

	char line[256]; //why 256?
        int i = 0;
	while (fgets(line, sizeof(line), file)) 
	{
		FilesToSearch[i] = line;
		*CountEntries = i;

		i++;	
	}
	debug("Log Profile file looped through, array initialized");
	fclose(file);
}
