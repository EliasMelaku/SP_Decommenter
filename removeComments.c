#include <stdio.h>
#include <string.h>

/* ------------------------------------------------- */
/*  Declare States that the given input might be in  */
/* ------------------------------------------------- */
enum State {FIRSTSLASH, FIRSTAESTERIKS, SECONDAESTERKIS, 
            STRING, CHARACTER, NORMAL, BACKSLASH, ERROR};


/* Delare prevState variable to store previous states for special cases */

enum State prevState = STRING;


/* Declare variables to store where a certain comment started and 
 how many lines it spans it has*/

int commentLine;
int newLineInComment = 0;


/*------------------------------------------------------------*/
/* handleNORMALcases: Implement the NORMAL state of the DFA. */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/

enum State handleNORMALcases(int c){
    enum State state = NORMAL;
    if (c == '/'){
        state = FIRSTSLASH;            
    }
    else{
        if (c == '\''){
            state = CHARACTER;
        }
        if (c == '"'){
            state = STRING;
        }       
        putchar(c);
    }
    return state;
}


/*------------------------------------------------------------*/
/* handleFIRSTSLASHcases: Implement the FIRSTSLASH state of the DFA. */
/* State that could be start of the comment                  */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleFIRSTSLASHcases(int c){
    enum State state = FIRSTSLASH;

    if (c == '*'){
        state = FIRSTAESTERIKS;
    }
    else if (c == '/'){
        putchar(c);
    }
    else {
        putchar('/');
        putchar(c);
        state = NORMAL;
    }
    return state;
}



/*------------------------------------------------------------*/
/* handleFIRSTAESTRIKScases: Implement the FIRSTAESTRIKS state of the DFA. */
/* Checks if the comment really started or not               */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleFIRSTAESTERIKScases(int c){
    enum State state = FIRSTAESTERIKS;

    if (c == '*'){
        state = SECONDAESTERKIS;
    }
    else if (c == '\n'){
        newLineInComment += 1; 
    }
    return state;
}


/*------------------------------------------------------------*/
/* handleSECONDAESTRIKScases: Implement the SECONDAESTRIKS state of the DFA. */
/* checks if the comment is closing or not                   */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleSECONDAESTERIKScases(int c){
    enum State state = SECONDAESTERKIS;

    if (c == '/'){
        putchar(' ');
        for (newLineInComment; newLineInComment>0; newLineInComment-- ){
            putchar('\n');
        }
        state = NORMAL;
    }
    
    else {
        
        state = FIRSTAESTERIKS;
    }
    return state;
}

/*-------------------------------------------------------------*/
/* handleSTRINGcases: Implement the STRING state of the DFA.  */
/* handles states that are in STRING literals                */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleSTRINGcases(int c){
    enum State state = STRING;

     if (c == '"'){
        state = NORMAL;
    }
    else if (c == '\\'){
        prevState = STRING;
        state = BACKSLASH;
    }
    putchar(c);

    return state;
}


/*-------------------------------------------------------------*/
/* handleCHARACTERcases: Implement the CHARACTER state of the DFA.  */
/* handles states that are in CHARACTER literals                */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleCHARACTERcases(int c){
    enum State state = CHARACTER;

    if (c == '\''){
        state = NORMAL;
    }
    else if (c == '\\'){
        prevState = CHARACTER;
        state = BACKSLASH;
    }
    putchar(c);
    return state;
}

/*-------------------------------------------------------------*/
/* handleBACKSLASHcases: Implement the BACKSLASH state of the DFA.  */
/* handles states when BACKSLASH  appears                */
/* c is the current DFA character. Return the next state.   */
/*---------------------------------------------------------*/
enum State handleBACKSLASHcases(int c){
    enum State state;

    state = prevState;
    putchar(c);

    return state;
}




/* ------------------------------------------------- */
/*                  Main function                    */
/* ------------------------------------------------- */
/* Read text from stdin, search for comments and     */
/* remove them, where "comments" are in the C90 standard */
/* meaning  / followed by * opens a comment and  */
/* * follwed by / closes it(when not a string or character literal)*/ 
/* Also // is not considered a comment */
                                                

int main(void){

    /* ------------------------------------------------- */
    /*  Declare one variable to iterate through given
        input and another to keep track of state         */
    /* ------------------------------------------------- */
    int c; 

    /* Initialize the state variable to start with a normal state */
    enum State state = NORMAL;

    /* using DFA approach here*/
    for ( ; ; ){

        /* read from stdin*/
        c = getchar();
       
       /* check if file has ended*/
        if (c == EOF)
            break;

        switch (state)
        {
        case NORMAL:
            state = handleNORMALcases(c);
            break;

        case FIRSTSLASH:
            state = handleFIRSTSLASHcases(c);
            break;
        
        case FIRSTAESTERIKS:
            state = handleFIRSTAESTERIKScases(c);
            break;
        
        case SECONDAESTERKIS:
            state = handleSECONDAESTERIKScases(c);
            break;

        case STRING:
            state = handleSTRINGcases(c);
            break;

        case CHARACTER:
            state = handleCHARACTERcases(c);
            break;

        case BACKSLASH:
            state = handleBACKSLASHcases(c);
            break;
    
        default:
            break;
        }

    }

    /* Handle errors here */
    if (state == FIRSTAESTERIKS || state == SECONDAESTERKIS) {
        printf("We've got an error");
        return 1;
    }
    else{
        return 0;
    }
    
}