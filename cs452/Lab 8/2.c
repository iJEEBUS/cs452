#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int init_global = 5235;
int uninit_global;
int g_array[50];
char *g_ptr;

int main() {

    // playground
    // Experiment with different types of variable (global, local, initialized, unitialized, arrays, pointers, structures, etc...)
    
    char *l_ptr = malloc(sizeof(char));
    int local = 555;
    int uninit_local;
    
    g_ptr = malloc(sizeof(char));
    printf("Dynamic\n");
    printf("global array:     %x     %X    %p\n", g_array, g_array, &g_array);
    printf("init global:      %x     %X    %p\n", init_global, init_global, &init_global);
    printf("uninit global:      %x     %X    %p\n", uninit_global, uninit_global, &uninit_global);
    printf("global pointer:    %x     %X     %p\n", g_ptr, g_ptr, g_ptr);
    printf("local pointer:     %x     %X     %p\n", l_ptr, l_ptr, l_ptr);
    printf("\n");
    printf("Stack\n");
    printf("init local:       %x     %X     %p\n", local, local, &local);
    printf("uninit local:       %x     %X     %p\n", uninit_local, uninit_local, &uninit_local);
    function_variable();
    

    

return 0;
}


void function_variable()
{
    int function = 2483;
    g_ptr = malloc(sizeof(char));
    printf("function stack:     %x    %X     %p\n", function, function, &function);
    printf("function heap:      %x    %X     %p\n", g_ptr, g_ptr, &g_ptr);
};


