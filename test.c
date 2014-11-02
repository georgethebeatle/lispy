#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "cbehave.h"
#include "lispy.h"

FEATURE(1, "Expression evaluation")
  SCENARIO("It can evaluate a positive number")

     GIVEN("A positive number")
         char *expr = "42";
     GIVEN_END

     WHEN("It evaluates the number")
         lval* result = eval(expr);
     WHEN_END

     THEN("We should get a number value")
         SHOULD_INT_EQUAL(result->type, LVAL_NUM);
     THEN_END

     THEN("And it should be correct")
         SHOULD_INT_EQUAL(result->num, 42);
         free_lval(result);
     THEN_END
 SCENARIO_END

 SCENARIO("It can evaluate a negative number")
   GIVEN("A negative number")
     char* expr = "-5";
   GIVEN_END

   WHEN("It evaluates the expression")
     lval* result = eval(expr);
   WHEN_END

   THEN("We should get a number value")
     SHOULD_INT_EQUAL(result->type, LVAL_NUM);
   THEN_END

   THEN("And it should be correct")
     SHOULD_INT_EQUAL(result->num, -5);
     free_lval(result);
   THEN_END
 SCENARIO_END

 SCENARIO("It can sum numbers")
   GIVEN("A valid sum expression")
     char* expr = "(+ 2 -3 4)";
   GIVEN_END

   WHEN("It evaluates the expression")
     lval* result = eval(expr);
   WHEN_END

   THEN("We should get a number value")
     SHOULD_INT_EQUAL(result->type, LVAL_NUM);
   THEN_END

   THEN("And it should be the correct sum")
     SHOULD_INT_EQUAL(result->num, 3);
     free_lval(result);
   THEN_END
 SCENARIO_END

 SCENARIO("It returns error on unknown operator")
   GIVEN("A valid expression with unknown operator")
     char* expr = "(^ 1 2)";
   GIVEN_END

   WHEN("It evaluates the expression")
     lval* result = eval(expr);
   WHEN_END

   THEN("We should get an error")
     SHOULD_INT_EQUAL(result->type, LVAL_ERR);
   THEN_END
 SCENARIO_END
FEATURE_END

int main() {
  init_grammar();

  cbehave_feature strstr_features[] = {
    {feature_idx(1)},
  };

  int success = cbehave_runner("Lispy Features:", strstr_features);

  free_grammar();
  return success;
}
