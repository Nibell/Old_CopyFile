// cp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

void *mal1;
HANDLE ut;
HANDLE in;
DWORD bytesread;
DWORD byteswritten;
int i;

int wmain( int argc, wchar_t *argv[ ], wchar_t *envp[ ] )
{

	ut = CreateFile(argv[2], GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
	in = CreateFile(argv[1], GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);	

	int filesize;
	filesize = GetFileSize(in,NULL);
	printf("\nInfilens storlek= %i",filesize);

	mal1 = malloc(256);
	int counter = 0;

	if(ReadFile(in, mal1, 256, &bytesread, NULL))
	{
		free(mal1);
		counter=1;
		printf("\nLASTE %s\n",argv[1]);
		while(!(bytesread<256))
		{
			mal1 = malloc(256);
			ReadFile(in, mal1, 256, &bytesread, NULL);
			WriteFile(ut, mal1, bytesread, &byteswritten, NULL);
			if(byteswritten != bytesread)
			{
				printf("Kunde inte skriva till '%s'.\n", in);
				return 2;
			}
			counter = counter+1;
			free(mal1);
		}
	}
	else
	{
		printf("\nLASTE INTE FIL");
	}	
	printf("\n\nSkrev: %i block med bytes till %s",counter,argv[2]);


	CloseHandle(in);
	CloseHandle(ut);
	return 0;
}