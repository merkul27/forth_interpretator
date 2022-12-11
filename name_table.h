#ifndef NAME_TABLE_H
#define NAME_TABLE_H

enum lexem_type{
    word,
    constant
};

typedef struct name{
    char *string;
    struct name* next;
    int value;
    enum lexem_type type;
} name;

int table_size;

enum name_type
{
    key_name, 
    id_name,
    constant
};

name* find_name(name** table,char* str, enum name_type type, int insert);

void print_table(name** table);

#endif /*NAME_TABLE_H*/