#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "cbehave.h"
#include "lispy.h"


FEATURE(1, "Expression evaluation")
  SCENARIO("Lispy can answer the ultimate question")

     GIVEN("The ultimate question")
         char *expr = "What is the Ultimate Answer of Life, The Universe and Everything?";
     GIVEN_END

     WHEN("Lispy evaluates the question")
         int result = eval(expr);
     WHEN_END

     THEN("We should get the correct answer")
         SHOULD_INT_EQUAL(result, 42);
     THEN_END
 SCENARIO_END
FEATURE_END

int main() {
    cbehave_feature strstr_features[] = {
       {feature_idx(1)},
    };

    return cbehave_runner("Lispy Features:", strstr_features);
}
