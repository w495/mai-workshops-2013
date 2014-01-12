#include <stdio.h>
#include <limits.h>
#include <stdio.h>
#include <fcntl.h>
//#include <sys/file.h>

#include "stud.h"

stud FAK8;

int main(int argc, char *argv[] )
{
FILE *fout;
int count=0;
int nn=0;


if (argc > 2 )
	{
	printf("you are wrong:");
	printf("\n %s ", argv[0]);
	return 1;
	}
	
if (argc == 1 )	argv[1]="student.db" ;  ;

printf("\nENTER A GROUP NUMBER: \t");
scanf("%i", &nn);

if((fout = fopen( argv[1],"r"))==NULL ) 
	{
	perror(argv[1]);
	return 1;
	}
	

fseek(fout, 0L , SEEK_SET);
while (1)
{
	if(fread(&FAK8, sizeof(FAK8), 1, fout))
	{

	if (FAK8.fm == 'F'  || FAK*.group == nn )
		{
		

		if(FAK8.matan1==5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 !=5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr!=5 ) 		{count++; }
		if(FAK8.matan1!=5 && FAK8.infa1==5 && FAK8.prakt1!=5 && FAK8.prakt2!=5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr!=5 ) 		{count++; }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1==5 && FAK8.prakt2 !=5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr==5 ) 		{count++; }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 ==5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr!=5 ) 		{count++; }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 !=5 && FAK8.matan2==5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr!=5 ) 		{count++;  }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 !=5 && FAK8.matan2!=5 && FAK8.linal==5 && FAK8.hist!=5 && FAK8.diskr!=5 ) 		{count++; }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 !=5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist==5 && FAK8.diskr!=5 ) 		{count++;  }
		if(FAK8.matan1!=5 && FAK8.infa1!=5 && FAK8.prakt1!=5 && FAK8.prakt2 !=5 && FAK8.matan2!=5 && FAK8.linal!=5 && FAK8.hist!=5 && FAK8.diskr==5 ) 		{count++;  }
		}
	}
	else break;
}

printf("\n %d \n", count );
fclose(fout);
}