#include"stdlib.h"
#include"stdio.h"
#include"ctype.h"
#include"string.h"

enum states
{
    S = 0,
    N,
};

enum input_char
{
    num = 0,
    el
};

typedef void (*transition_callback)(enum states state, char r);

struct transition
{
    enum states new_state;
    transition_callback procedure;
};

char res[80];   //результирующая строка в виде польской формы 

char res_num[15];

char w[] = "12 231 465 +";  //пробная входная цепочка

char* c = w;

void S_d(enum states state, char r){
    strncat(res_num, &r, 1);
    return;
}

void N_d(enum states state, char r){
    strncat(res_num, &r, 1);
    return;
}

void S_el(enum states state, char r){
    switch (r){
        case ' ':
            return;
        case '+':
            strncat(res, &r, 1);
            return;
        default:
            exit(1);
    };
}



void N_el(enum states state, char r){
    strcat(res, res_num);
    strcat(res, ",");
    memset(res_num, 0, strlen(res_num));
    c--;
    return;
} 
const struct transition state_transition_table[2][2] = {
    [S][num] = {N, S_d},
    [S][el] = {S, S_el},
    [N][num] = {N, N_d},
    [N][el] = {S, N_el}
}; 

int main(){
    int current_state = S;
    struct transition current_transition;
    while (*c != '\0'){
        if (isdigit(*c)){
            current_transition = state_transition_table[current_state][num];
        }
        else{
            current_transition = state_transition_table[current_state][el];
        }

        if (current_transition.procedure != NULL){
                current_transition.procedure(current_state, *c);
            
            }
                current_state = current_transition.new_state; 
        c++;
    }   
    printf("%s", res);
}