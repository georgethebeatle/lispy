#ifndef LISPY_LANG
#define LISPY_LANG

#include "mpc.h"

enum { LVAL_NUM, LVAL_ERR };

typedef struct {
  int type;
  int num;
  char* err;
} lval;

mpc_parser_t* Number;
mpc_parser_t* Operator;
mpc_parser_t* Expr;
mpc_parser_t* Lispy;

void init_grammar();
void free_grammar();

lval* eval(char* input);

lval* lval_num(int num);
lval* lval_err(char* err);
void free_lval(lval* val);
void lval_print(lval v);

#endif
