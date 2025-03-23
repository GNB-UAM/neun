#ifndef AST_H
#define AST_H

#define MAX_EQUATIONS 100

/* Struct for equations */
typedef struct {
    char variable[50];
    char equation[256];
} Equation;

extern int eq_count;
extern Equation equations[MAX_EQUATIONS];

void generate_code();

#endif
