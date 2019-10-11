//
//  symbol.h
//  
//
//  Created by 주성호 on 2019/10/11.
//
#include <string.h>
#ifndef symbol_h
#define symbol_h
#define NSYMS 20
struct symtab {
    char *name;
    double value;
}symtab[NSYMS];

struct symtab *symlook();

#endif /* symbol_h */
