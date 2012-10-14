// Function used for reporting the condition of a 
// statement to stdout using ANSI colors.
#include <iostream>

void check(const bool statement)
{
  if (statement == true)
    std::cout << "\t\033[0;32mPassed\033[0m\n";
  else
    std::cout << "\t\033[1;31mFail!!\033[0m\n";
}
