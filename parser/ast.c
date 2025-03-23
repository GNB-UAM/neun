#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"

int eq_count = 0;
Equation equations[MAX_EQUATIONS];

char *strtolower(char *str)
{
    unsigned char *mystr = (unsigned char *)str;

    while (*mystr) {
        *mystr = tolower(*mystr);
        mystr++;
    }
    return str;
}


// Function to generate the code
void generate_code() {
    printf("\n// Código generado automáticamente:\n");
    printf("#include <stdio.h>\n\n");

    // Generate the function for each equation
    for (int i = 0; i < eq_count; i++) {
        printf("Precission %s() {\n", strtolower(equations[i].variable));
        printf("    return %s;\n", strtolower(equations[i].equation));
        printf("}\n\n");
    }

    // Generate the main function to call the generated functions
    printf("int main() {\n");
    for (int i = 0; i < eq_count; i++) {
        printf("    %s();\n", equations[i].variable);
    }
    printf("    return 0;\n");
    printf("}\n");
}
