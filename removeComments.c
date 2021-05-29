#include <stdio.h>
#include <string.h>

/* ------------------------------------------------- */
/*  Declare States that the given input might be in  */
/* ------------------------------------------------- */
enum State {FIRSTSLASH, FIRSTAESTERIKS, SECONDAESTERKIS, 
            STRING, CHARACTER, NORMAL, BACKSLASH, ERROR};

int commentLine;
int newLineInComment = 0;


/* ------------------------------------------------- */
/*                  Main function                    */
/* ------------------------------------------------- */
int main(void){

    /* ------------------------------------------------- */
    /*  Declare one variable to iterate through given
        input and another to keep track of state         */
    /* ------------------------------------------------- */
    int c; 
    enum State state = NORMAL;
    enum State prevState;


    for ( ; ; ){

        c = getchar();

       
        if (c == EOF)
            break;

        switch (state)
        {
        case NORMAL:

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
            
            break;

        case FIRSTSLASH:
            if (c == '*'){
                state = FIRSTAESTERIKS;
            }
            else if (c == '/'){
                putchar(c);
                continue;

            }
            else {
                putchar('/');
                putchar(c);
                state = NORMAL;
            }

            break;
        
        case FIRSTAESTERIKS:
            if (c == '*'){
                state = SECONDAESTERKIS;
            }

            else if (c == '\n'){
                newLineInComment += 1; 
            }

            else continue;
        
            break;
        
        case SECONDAESTERKIS:
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
            break;

        // case ERROR:
        //     printf("We've got an error");
        //     break;

            case STRING:
                if (c == '"'){
                    state = NORMAL;
                }
                else if (c == '\\'){
                    prevState = STRING;
                    state = BACKSLASH;
            }
                putchar(c);

                break;
            case CHARACTER:
                if (c == '\''){
                    state = NORMAL;
                }
                else if (c == '\\'){
                    prevState = CHARACTER;
                    state = BACKSLASH;
            }
                putchar(c);

                break;

            case BACKSLASH:
                // if (!(c == '\\')){
                state = prevState;
                
                putchar(c);
                
                break;
                
        
        default:
            break;
        }

    }

    if (state == FIRSTAESTERIKS || state == SECONDAESTERKIS) {
        printf("We've got an error");
        return 1;
    }
    else{
        return 0;
    }
    
}