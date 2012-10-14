#include <iostream>
#include <string>
#include <cstdlib> // For getenv()

void your_username()
{

  // Get USER environment variable
  std::string username = getenv("USER");

  // Print username to stdout
  std::cout << username << '\n';

}
