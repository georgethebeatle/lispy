#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lispy.h"

void init_grammar() {
  Number = mpc_new("number");
  Operator = mpc_new("operator");
  Expr = mpc_new("expr");
  Lispy = mpc_new("lispy");

  mpca_lang(MPCA_LANG_DEFAULT,
    "                                                    \
      number   : /-?[0-9]+/ ;                            \
      operator : '+' | '-' | '*' | '/' ;                 \
      expr     : <number> | '(' <operator> <expr>+ ')' ; \
      lispy    : /^/ <expr> /$/ ;                        \
    ",
    Number, Operator, Expr, Lispy);
}

void free_grammar() {
  mpc_cleanup(4, Number, Operator, Expr, Lispy);
}

lval* eval(char* input) {
  lval* eval_result = NULL;

  mpc_result_t res;
  if (mpc_parse("<stdin>", input, Lispy, &res)) {
    // TODO: use res.output to actually evaluate the epression
    eval_result = lval_num(42);
    mpc_ast_delete(res.output);
  } else {
    mpc_err_print(res.error);
    // TODO: create error struct with message
    // Use: void mpc_err_print_to(mpc_err_t *e, FILE *f);
    // Open string stream for writing - see: http://www.gnu.org/software/libc/manual/html_node/String-Streams.html
    eval_result = lval_err("some error occurred");
    mpc_err_delete(res.error);
  }

  return eval_result;
}

lval* lval_num(int num) {
  lval* val = (lval*) malloc(sizeof(lval));
  val->type = LVAL_NUM;
  val->num = num;
  val->err = NULL;
  return val;
}

lval* lval_err(char* err) {
  lval* val = (lval*) malloc(sizeof(lval));
  val->type = LVAL_ERR;
  val->err = (char*) malloc(sizeof(err));
  strcpy(val->err, err);
  return val;
}

void free_lval(lval* val) {
  if (val->err != NULL) {
    free(val->err);
  }
  free(val);
}

void lval_print(lval v) {
  switch(v.type) {
    case LVAL_NUM:
      printf("=>%d\n", v.num);
      break;
    case LVAL_ERR:
      printf("=>%s\n", v.err);
      break;
  }
}

