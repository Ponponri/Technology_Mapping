#include <time.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "base/abc/abc.h"

// procedures to start and stop the ABC framework
// (should be called before and after the ABC procedures are called)
extern void  Abc_Start();
extern void  Abc_Stop();

extern void util_getopt_reset ARGS((void));
extern Abc_Ntk_t * Io_ReadBlifAsAig(char *, int);

//***********************************************************
void
PrintEachObj(ntk) 
Abc_Ntk_t *ntk;
{
	Abc_Obj_t *node, *fi;
	int i, j;
	
	printf("<< Print Each Obj- >>\n");
	printf(" ID       Name  Type  Level\n");
	printf("--------------------\n");
	Abc_NtkForEachObj(ntk, node, i){
		printf("%3d %10s %2d %2d\n", node->Id, Abc_ObjName(node), node->Type, node->Level);
	
		Abc_ObjForEachFanin(node, fi, j){
			printf("  %10s %d\n", Abc_ObjName(fi), Abc_ObjFaninC(node, j));
		}
	}
	printf("<< ----- End ----- >>\n");                          
}

//***********************************************************
int 
main(int argc, char **argv)
{
	char circuit[100];			// input circuit name.
	Abc_Ntk_t *ntk;

	printf("Process %s\n", argv[argc-1]);
	
	// << Setup ABC >>
	Abc_Start();
	
  // << Read blif file >>
	strcpy(circuit, argv[argc-1]);
  if (!(ntk = Io_ReadBlifAsAig(circuit, 1))) return 1; 

	PrintEachObj(ntk);   

	Abc_NtkDelete(ntk);

	// << End ABC >>
	Abc_Stop();
	
	return 1;
}
