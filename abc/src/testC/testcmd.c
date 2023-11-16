#include "base/main/main.h"
#include "testC.h"

static int TestC_CommandTestC(Abc_Frame_t * pAbc, int argc, char **argv);
static int TestC_CommandPart1(Abc_Frame_t * pAbc, int argc, char **argv);
static int TestC_CommandPart2(Abc_Frame_t * pAbc, int argc, char **argv);
static int TestC_CommandHw2(Abc_Frame_t * pAbc, int argc, char **argv);

void TestC_Init(Abc_Frame_t *pAbc){
   Cmd_CommandAdd (pAbc, "Various", "testc", TestC_CommandTestC, 0);
   Cmd_CommandAdd (pAbc, "Various", "iteratentk", TestC_CommandPart1, 0);
   Cmd_CommandAdd (pAbc, "Various", "andtree", TestC_CommandPart2, 0);
   Cmd_CommandAdd (pAbc, "Various", "hw2", TestC_CommandHw2, 0);
}

// hw1 part1
int TestC_CommandPart1(Abc_Frame_t * pAbc, int argc, char **argv){
    int fVerbose;
    int c,result;
    fVerbose = 0;
    Extra_UtilGetoptReset();
    while( (c = Extra_UtilGetopt( argc,argv, "wh" ) ) != EOF){
        switch( c ){
            case 'v':
                fVerbose ^= 1;
                break;
            case 'h':
                goto usage;
            default:
                goto usage;
        }
    }

    result = TestC_Part1Abc( pAbc );

    if( fVerbose ){
        Abc_Print( 1, "\nVerbose mode is on.\n" );
        if(result)
            Abc_Print( 1, "The command finished successfully.\n" );
        else Abc_Print( 1, "The command execution has failed.\n" );
    }
    
    return 0;
usage:
    Abc_Print(-2, "Usage firstcmd [-vh]\n");
    Abc_Print(-2, "\t First command in ABC\n");
    Abc_Print(-2, "\t-v : toggle printing verbose information[default = %s]\n", fVerbose ? "yes" : "no");
    Abc_Print(-2, "\t-h : print the command usage\n");
    return 1;

}

// hw1 part2
int TestC_CommandPart2(Abc_Frame_t * pAbc, int argc, char **argv){
    int fVerbose;
    int c,result;
    fVerbose = 0;
    Extra_UtilGetoptReset();
    while( (c = Extra_UtilGetopt( argc,argv, "whS" ) ) != EOF){
        switch( c ){
            case 'S':
                break;
            case 'v':
                fVerbose ^= 1;
                break;
            case 'h':
                goto usage;
            default:
                goto usage;
        }
    }

    result = TestC_Part2Abc( pAbc ,argc, argv);

    if( fVerbose ){
        Abc_Print( 1, "\nVerbose mode is on.\n" );
        if(result)
            Abc_Print( 1, "The command finished successfully.\n" );
        else Abc_Print( 1, "The command execution has failed.\n" );
    }
    
    return 0;
usage:
    Abc_Print(-2, "Usage firstcmd [-vh]\n");
    Abc_Print(-2, "\t First command in ABC\n");
    Abc_Print(-2, "\t-v : toggle printing verbose information[default = %s]\n", fVerbose ? "yes" : "no");
    Abc_Print(-2, "\t-h : print the command usage\n");
    return 1;

}

// hw2
int TestC_CommandHw2(Abc_Frame_t * pAbc, int argc, char **argv){
    int fVerbose;
    int c,result;
    fVerbose = 0;
    Extra_UtilGetoptReset();
    while( (c = Extra_UtilGetopt( argc,argv, "wh" ) ) != EOF){
        switch( c ){
            case 'v':
                fVerbose ^= 1;
                break;
            case 'h':
                goto usage;
            default:
                goto usage;
        }
    }

    result = TestC_Hw2Abc( pAbc );

    if( fVerbose ){
        Abc_Print( 1, "\nVerbose mode is on.\n" );
        if(result)
            Abc_Print( 1, "The command finished successfully.\n" );
        else Abc_Print( 1, "The command execution has failed.\n" );
    }
    
    return 0;
usage:
    Abc_Print(-2, "Usage firstcmd [-vh]\n");
    Abc_Print(-2, "\t First command in ABC\n");
    Abc_Print(-2, "\t-v : toggle printing verbose information[default = %s]\n", fVerbose ? "yes" : "no");
    Abc_Print(-2, "\t-h : print the command usage\n");
    return 1;

}

// Test
int TestC_CommandTestC(Abc_Frame_t * pAbc, int argc, char **argv){
    int fVerbose;
    int c,result;
    fVerbose = 0;
    Extra_UtilGetoptReset();
    while( (c = Extra_UtilGetopt( argc,argv, "wh" ) ) != EOF){
        switch( c ){
            case 'v':
                fVerbose ^= 1;
                break;
            case 'h':
                goto usage;
            default:
                goto usage;
        }
    }

    result = TestC_FirstFunctionAbc( pAbc );

    if( fVerbose ){
        Abc_Print( 1, "\nVerbose mode is on.\n" );
        if(result)
            Abc_Print( 1, "The command finished successfully.\n" );
        else Abc_Print( 1, "The command execution has failed.\n" );
    }
    
    return 0;
usage:
    Abc_Print(-2, "Usage firstcmd [-vh]\n");
    Abc_Print(-2, "\t First command in ABC\n");
    Abc_Print(-2, "\t-v : toggle printing verbose information[default = %s]\n", fVerbose ? "yes" : "no");
    Abc_Print(-2, "\t-h : print the command usage\n");
    return 1;


}