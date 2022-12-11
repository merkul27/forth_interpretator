#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
enum states
{
    S,
    N,
    W,
    NorW,
    COMorW,
    COM, 
    T,
    states_num
};

enum input_element
{
    number,
    letter,
    space,
    comment_bkt_open,
    comment_bkt_close,
    other,
    exit_symbol,
    line_break,
    minus,
    input_num
};

char* add_symbol_to_string(char* str, char c);

char* concat(char *s1, char *s2);


typedef void (*transition_callback)(enum states state, char r);

struct transition
{
    enum states new_state;
    transition_callback procedure;
};  

#endif