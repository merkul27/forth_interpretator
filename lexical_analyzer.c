#include"stdlib.h"
#include"stdio.h"
#include"ctype.h"
#include"string.h"
#include"name_table.h"
#include"lexical_analyzer.h"


name** name_table;
int* lex_stream; 
int* lex_p;
char* word;   
char w[] = "11  ses  +  214 8742 saaaas . ";  //пробная входная цепочка
char* c = w;


char* add_symbol_to_string(char* str, char c){
    size_t len = strlen(str);
    char* res = (char*)calloc(len + 2, sizeof(char));
    memcpy(res, str, len);
    char* p = res + len;
    *p = c;
    p++;
    *p = '\0'; 
    return res;
}

char* concat(char *s1, char *s2) {
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);                      
    char *result = (char*)malloc(len1 + len2 + 1);
    if (!result) {
        fprintf(stderr, "malloc() failed: insufficient memory!\n");
        return NULL;
    }
    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);   
    return result;
}

char* make_string_from_char(char c){
    char* res = (char*)malloc(sizeof(char) + 1);
    *res = c;
    res++;
    *res = '\0';
    return res;
}



void number_create(enum states state, char r){
    word = add_symbol_to_string(word, r);
    return;
}

void word_create(enum states state, char r){
    if (isalpha(r)){
        r = tolower(r);
    }
    word = add_symbol_to_string(word, r);
    return;
}

void number_done(enum states state, char r){
    *lex_p = atoi(word);
    lex_p++;
    memset(word, '\0', strlen(word));
    return;
}

void arith_sym(enum states state, char r){
    name* n = find_name(name_table, make_string_from_char(r), 1, id_name);
    *lex_p = n->value;
    lex_p++;
    return; 
}

void word_done(enum states state, char r){
    name* n = find_name(name_table, word, 1, id_name);
    *lex_p = n->value;
    lex_p++;
    c--;
    memset(word, '\0', strlen(word));
    return;
}

void error(enum states state, char r){
    printf("Error occured in state %d when symbol %c came", state, r);
    free(word);
    exit(1);
}

void terminate(enum states state, char r){
    printf("Input string was successfully recognised, output string: %s \n");
    int* p = lex_stream;
    for (int i = 0; i < 6; i++, p++){
        printf("%d, ", *p);
    }
    printf("\n");
    print_table(name_table);
    free(word);
    exit(0);
}


const struct transition state_transition_table[states_num][input_num] = {
    [S][number] = {NorW, number_create},
    [S][letter] = {W, word_create},
    [S][space] = {S, NULL},
    [S][comment_bkt_open] = {COMorW, NULL},
    [S][comment_bkt_close] = {T, NULL},     // добавить обработку ошибки здесь
    [S][minus] = {NorW, number_create},
    [S][other] = {W, word_create},
    [S][exit_symbol] = {T, terminate},
    [S][line_break] = {S, NULL},
    [N][number] = {N, number_create},
    [N][letter] = {W, word_create},
    [N][space] = {S, number_done},
    [N][comment_bkt_open] = {W, word_create},
    [N][comment_bkt_close] = {W, word_create},
    [N][other] = {W, word_create},
    [N][exit_symbol] = {S, number_done},
    [N][line_break] = {S, number_done},
    [N][minus] = {W, word_create},
    [W][number] = {W, word_create},
    [W][letter] = {W, word_create},
    [W][space] = {S, word_done},
    [W][comment_bkt_open] = {W, word_create},
    [W][comment_bkt_close] = {W, word_create},
    [W][other] = {W, word_create},
    [W][exit_symbol] = {S, word_done},
    [W][line_break] = {S, word_done},
    [W][minus] = {W, word_create},
    [NorW][number] = {N, number_create},
    [NorW][letter] = {W, word_create},
    [NorW][space] = {S, number_done},
    [NorW][comment_bkt_open] = {W, word_create},
    [NorW][comment_bkt_close] = {W, word_create},
    [NorW][other] = {W, word_create},
    [NorW][exit_symbol] = {S, number_done},
    [NorW][line_break] = {S, number_done},
    [NorW][minus] = {W, word_create},
    [COMorW][number] = {N, number_create},
    [COMorW][letter] = {ER, error},
    [COMorW][space] = {S, number_done},
    [COMorW][comment_bkt_open] = {ER, error},
    [COMorW][comment_bkt_close] = {ER, error},
    [COMorW][other] = {ER, error},
    [COMorW][exit_symbol] = {S, number_done},
    [COMorW][line_break] = {S, NULL},
    [COMorW][minus] = {S, NULL},
    [COM][number] = {N, number_create},
    [COM][letter] = {ER, error},
    [COM][space] = {S, number_done},
    [COM][comment_bkt_open] = {ER, error},
    [COM][comment_bkt_close] = {ER, error},
    [COM][other] = {ER, error},
    [COM][exit_symbol] = {S, number_done},
    [COM][line_break] = {S, NULL},
    [COM][minus] = {S, NULL},
    [T][number] = {T, NULL},
    [T][letter] = {T, NULL}, 
    [T][space] = {T, NULL},
    [T][comment_bkt_open] = {T, NULL},
    [T][comment_bkt_close] = {T, NULL},
    [T][other] = {T, NULL},
    [T][exit_symbol] = {T, NULL},
    [T][line_break] = {T, NULL},
    [T][minus] = {T, NULL}, 
}; 


char* key_names[44] = {"+", "-", "*", "/", ".", "dup", "drop", "mod",
                       "over", "rot", "swap", "roll", "abs", "negate", "1+",
                       "1-", "pick", ".", ":", ";", "@", "!", "constant",
                       "variable", "and", "or", "xor", "not", ">", "<",
                       "=", "0<", "0=", "0>", "if", "else", "begin", "until",
                       "repeat", "while", "do", "loop", "then", "+loop"};

void fill_table_with_key_names(name** table){
    for (int i = 0; i < 44; i++){
        find_name(table, key_names[i], key_name, 1);
    }
}


void lexical_analyzer(){
    table_size = 40;
    name_table = (name**)calloc(table_size, sizeof(name));
    fill_table_with_key_names(name_table);
    
    lex_stream = (int*)calloc(100, sizeof(int));    // ToDo: довыделение памяти 
    lex_p = lex_stream;
    word = (char*)calloc(31, sizeof(char));

    enum states current_state = S;
    enum input_element current_element;
    struct transition current_transition;
    while (1){
        if (isdigit(*c)){
            current_element = number;
        }
        else if (isalpha(*c)){ 
            current_element = letter;
        }
        else if (isspace(*c)){
            current_element = space;
        }   
        else if (*c == '\0'){
            current_element = exit_symbol;
        }
        else if (*c == ')'){
            current_element = comment_bkt_close;
        }
        else if (*c == '('){
            current_element = comment_bkt_open;
        }
        else if (*c == '\n'){
            current_element = line_break;
        }
        else if (*c == '-'){
            current_element = minus;
        } 
        else{
            current_element = other;
        }

        current_transition = state_transition_table[current_state][current_element];
        if (current_transition.procedure != NULL){
                current_transition.procedure(current_state, *c);
            
            }
                current_state = current_transition.new_state;
        c++;
    }
    
       
}

int main(){
    lexical_analyzer();
    return 0;
}