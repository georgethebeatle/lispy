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

int evaluate(mpc_ast_t* tree) {
  if(strstr(tree->tag, "number")) {
    return atoi(tree->contents);
  }
  return 42;
}

lval* eval(char* input) {
  lval* eval_result = NULL;

  mpc_result_t res;
  if (mpc_parse("<stdin>", input, Lispy, &res)) {
    int eval_res = evaluate(res.output);
    eval_result = lval_num(eval_res);

    mpc_ast_delete(res.output);
  } else {
    char* error_message = mpc_err_string(res.error);
    eval_result = lval_err(error_message);
    free(error_message);
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
  val->err = (char*) malloc(strlen(err) * sizeof(char));
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

