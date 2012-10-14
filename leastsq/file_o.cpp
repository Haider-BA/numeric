#include <iostream>
#include <fstream>
#include <vector>
#include "header.h"

// Write arrays to text file, readable by plotting tools
int write_output(const std::vector<Floattype> &a, 
    		 const std::vector<Floattype> &b, 
		 const char *outfile)
{
  std::ofstream outstream;

  // Open outfile for write
  outstream.open(outfile);

  // Write output arrays in two columns
  for (Lengthtype i=0; i<(Lengthtype)a.size(); ++i)
    outstream << a[i] << '\t' << b[i] << '\n';

  // Close file
  outstream.close();

  // Return successfully
  return 0;
}
