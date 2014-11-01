#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "cbehave.h"
#include "lispy.h"


FEATURE(1, "Expression evaluation")
  SCENARIO("Lispy can evaluate a positive number")

     GIVEN("A positive number")
         char *expr = "42";
     GIVEN_END

     WHEN("Lispy evaluates the number")
         lval* result = eval(expr);
     WHEN_END

     THEN("We should get the correct number")
         SHOULD_INT_EQUAL(result->num, 42);
         free_lval(result);
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
