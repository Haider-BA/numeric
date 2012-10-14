#include <iostream>
#include <string>
#include <cstdlib> // For getenv()

int main()
{
  // Namespace definitions
  using std::cout;
  using std::string;

  // Get USER environment variable
  string username = getenv("USER");

  // Greet user
  cout << "Hello, " << username << '\n';

  // Successfull exit
  return 0;
}
