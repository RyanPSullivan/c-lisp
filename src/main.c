#include <stdio.h>
#include <stdlib.h>

#include <histedit.h>

#include "mpc/mpc.h"

int main(int argc, char** argv) {

  /* Create Some Parsers */
  auto number   = mpc_new("number");
  auto operator = mpc_new("operator");
  auto expr     = mpc_new("expr");
  auto lispy    = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
	  "number    : /-?[0-9]+/;                             \
           operator  : '+' | '-' | '*' | '/';                  \
           expr      : <number> | '(' <operator> <expr>+ ')';  \
           lispy     : /^/ <operator> <expr>+ /$/;             \
           ", number, operator, expr, lispy);

  puts("Lispy Version 0.0.0.0.1");
  puts("Press Ctrl+c to Exit\n");
   
  while (1) {
    /* Now in either case readline will be correctly defined */
    char* input = readline("lisp > ");
    add_history(input);

    mpc_result_t r;
    if( mpc_parse("<stdin>", input, lispy, &r) )
    {
	    mpc_ast_print(r.output);
	    mpc_ast_delete(r.output);
    }
    else
    {
	    mpc_err_print(r.error);
	    mpc_err_delete(r.error);
    }
    printf("No you're a %s\n", input);
    free(input);
    
  }

  mpc_cleanup(4, number, operator, expr, lispy);
  return 0;
}
