#include <stdio.h>
#include <stdlib.h>
#ifdef    __EMSCRIPTEN__
#include <emscripten.h>
#endif // __EMSCRIPTEN__

#include "util.h"
#include "tree.h"

const int max = 1;

int main()
{
    random_init();
#ifdef    __EMSCRIPTEN__
    EM_ASM({
        novemberizing.chart.init();
    });
#endif // __EMSCRIPTEN__
    for(int i = 0; i<max; i++)
    {
        struct tree * t = red_black_tree_new();
        for(int j = 0; j < 32; j++)
        {
            int v = random_get(100);
            if(red_black_tree_add(t, v) == NULL)
            {
                assertion(1, "red_black_tree_add(t, v) == NULL");
            }
            // red_black_tree_print(t);
        }
        red_black_tree_print(t);
        struct node * n = NULL;
        while((n = red_black_tree_del(t, random_get(100))) == NULL)
        {

        }
        red_black_tree_node_free(n);
        red_black_tree_print(t);
        red_black_tree_free(t);
    }
    return 0;
}