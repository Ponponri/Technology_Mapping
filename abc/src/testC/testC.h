#ifndef TestC_h
#define TestC_h

#include "base/main/main.h"

ABC_NAMESPACE_HEADER_START

#define MAX_SIZE 100

#define LIB_NAME "../PA2/pa2.lib"


struct node;

struct list{
	struct node *nextNode;
	struct list *next;
};

struct node{
	char name[MAX_SIZE];
    int id;
    int type; // -2:head,end -1:buf 0:pi 1:inv 2:nand  
	double delay[4];
	double power[4];
	int select;
    double require;
    double arrival;
	

	struct node * next;
    struct node * last;
	struct list * pre;
	struct list * post;
};


extern int TestC_FirstFunctionAbc(Abc_Frame_t * pAbc);
extern int TestC_Part1Abc(Abc_Frame_t * pAbc);
extern int TestC_Part2Abc(Abc_Frame_t * pAbc, int argc, char **argv);
extern int TestC_Hw2Abc(Abc_Frame_t * pAbc);

#endif

ABC_NAMESPACE_HEADER_END