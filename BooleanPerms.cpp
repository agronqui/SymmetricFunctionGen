#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BooleanPerms.h"

#ifdef BOOLEAN_PERMS_MAIN
#define BOOLAEN_PERMS_MAIN 1
int main(int argc, char **argv) {

    long long int numPerms = -1;
    int  nvars      = 0;
    int  npos       = 0;

    if (argc < 3) {
        printf("usage: combs <nvars> <true-literals> \n");
        exit(-1);
    }

    nvars   = atoi(argv[1]);
    npos    = atoi(argv[2]);

    numPerms = GenAllBooleanPermutations(nvars, npos, false, NULL );
    printf("Number Permutations = %lld \n", numPerms );
    GenAllBooleanPermutations(nvars, npos, true,  stdout );
    return(0);
}
#endif // BOOLEAN_PERMS_MAIN


// count the number of Boolean permutations of nvars bits, where  npos are 1 and the rest are 0
//  return the number of permutations
//  optionally, if doPrint is true, fprintf the bitstring out to outFile in standard .pla single output format 
long long int GenAllBooleanPermutations(int nvars, int npos, bool doPrint, FILE *outFile) {

    long long int numberPerms = 0;
    int  upvar      = 0; 
    int  *iterates  = NULL;
    char *literal   = NULL;

    iterates    = (int*)   malloc(nvars*sizeof(int));
    literal     = (char*)  malloc(nvars*sizeof(char));

    if ((nvars == 0) && (npos == 0)) {
        // degenerate corner case, we define the number of Perms(0,0) to be 0
        return(0);
    }
    if (nvars < npos) {
        // input is in error, this is undefined, we will return 0 to conform to the "how many lines we would write out" convention
        return(0);
    }

    // blank literal to all '0' chars
    for (int i = 0; i < nvars ; i++) {
        literal[i] = '0';
    }

    // set up the initial iterates as 0->1->2->3->etc, and also set their terms to '1'
    for (upvar = 0; upvar < npos ; upvar++) {
           iterates[upvar] = upvar;
           literal[iterates[upvar]] = '1';  
    }

    upvar = npos - 1;
    bool shallExit;
    bool genLiteral;

    do {
        if (iterates[upvar] < ((nvars - 1) - (npos - 1 - upvar )) && (npos != 0)) {
            // generate new literal
            for (int i = 0; i < nvars ; i++) {
                literal[i] = '0';
            }
            for (int i = 0; i < npos ; i++) {
                literal[iterates[i]] = '1';
            }
            if (doPrint) {
                fprintf(outFile,"%s  1\n", literal); 
            }
            numberPerms++;
            // now make the next state
            iterates[upvar]++;
            if (upvar != (npos-1)) {
                int startIteratesUpvar = iterates[upvar];
                // we are not the highest upvar, so we need to reset all the ones after us, and 
                for (  ; upvar < npos ; upvar++) {
                    iterates[upvar] = startIteratesUpvar++; 
                }
                upvar--;
            }

        }
        else {
            upvar = upvar - 1;
        }
        // exit condition
        shallExit = 1;
        for (int i = 0; i < npos ; i++) {
            if (iterates[i] != ((nvars - 1) - (npos - 1 - i))) {
                shallExit  = 0;
            }
        }
        if (shallExit) {
            // generate new literal
            for (int i = 0; i < nvars ; i++) {
                literal[i] = '0';
            }
            for (int i = 0; i < npos ; i++) {
                literal[iterates[i]] = '1';
            }
            if (doPrint) {
                fprintf(outFile,"%s  1\n", literal); 
            }
            numberPerms++;
        }

    } while (shallExit == 0);

    return(numberPerms);
}
