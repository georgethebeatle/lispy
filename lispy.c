#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lispy.h"

lval* eval(char* input) {
  return lval_num(42);
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
  val->type = LVAL_NUM;
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

