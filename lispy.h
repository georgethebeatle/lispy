#ifndef LISPY_LANG
#define LISPY_LANG

enum { LVAL_NUM, LVAL_ERR };

typedef struct {
  int type;
  int num;
  char* err;
} lval;


lval* eval(char* input);

lval* lval_num(int num);
void free_lval(lval* val);
lval* lval_err(char* err);

#endif
