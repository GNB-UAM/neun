#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ast.h"

int eq_count = 0;
Equation equations[MAX_EQUATIONS];
char modelname[] = "GenericName";



char *variables[MAX_VARIABLES];  // Array para variables de tiempo
int n_variables = 0;               // Contador de variables de tiempo

char *parameters[MAX_VARIABLES];  // Array para variables regulares
int n_parameters = 0;               // Contador de variables regulares




char *strtolower(char *str)
{
    unsigned char *mystr = (unsigned char *)str;

    while (*mystr) {
        *mystr = tolower(*mystr);
        mystr++;
    }
    return str;
}

char *strtoupper(char *str)
{
    unsigned char *mystr = (unsigned char *)str;

    while (*mystr) {
        *mystr = toupper(*mystr);
        mystr++;
    }
    return str;
}

char * toCamelCase(char *str) {
    unsigned char *mystr = (unsigned char *)str;

    int i, j = 0;
    int len = strlen(mystr);
    int capitalizeNext = 0; // Flag for next letter

    for (i = 0; i < len; i++) {
        if (mystr[i] == ' ') {
            capitalizeNext = 1;
        } else {
            if (capitalizeNext) {
                mystr[j++] = toupper(mystr[i]); 
                capitalizeNext = 0;         // Reset flag
            } else {
                mystr[j++] = tolower(mystr[i]); 
            }
        }
    }
    mystr[j] = '\0'; 
}


void write_headers(char * modelname) {

    char aux_modelname[100];
    strcpy(aux_modelname,modelname);

    printf("%s\n",modelname);
    printf( "#ifndef %sMODEL_H_\n", strtoupper(aux_modelname));
    printf( "#define %sMODEL_H_\n\n", strtoupper(aux_modelname));

    printf( "#include <cmath>\n");
    printf( "#include \"NeuronBase.h\"\n\n");

    printf( "template <typename Precission>\n");
    printf( "class %sModel : public NeuronBase<Precission>\n", modelname);
    printf( "{\n");
}

void write_vars()
{

    printf( "public:\n");
    printf( "    typedef Precission precission_t;\n\n");

    printf( "    enum variable {");
    for (int i=0; i < n_variables; i++)
    {
        printf("%s, ", strtolower(variables[i]));
    }
    
    printf("n_variables};\n");
    
    printf( "    enum parameter {");
    for (int i=0; i < n_parameters; i++)
    {
        printf("%s, ", strtolower(parameters[i]));
    }
    
    printf("n_parameters};\n\n");
    

    // printf( "    enum parameter {cm, vna, vk, vl, gna, gk, gl, n_parameters};\n\n");

    printf( "protected:\n");
    printf( "};\n\n");
}


// Function to generate the code
void generate_code() {
    printf("\n// Automatically generated code:\n");
    write_headers(modelname);
    write_vars();

    // Generate the function for each equation
    for (int i = 0; i < eq_count; i++) {
        printf("    Precission %s() {\n", strtolower(equations[i].variable));
        printf("        return %s;\n", strtolower(equations[i].equation));
        printf("    }\n\n");
    }


    printf( "#endif // %sMODEL_\n", strtoupper(modelname));
    // Generate the main function to call the generated functions
    printf("int main() {\n");
    for (int i = 0; i < eq_count; i++) {
        printf("    %s();\n", equations[i].variable);
    }
    printf("    return 0;\n");
    printf("}\n");
}
