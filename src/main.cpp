#include <iostream>

#include "engine/engine.h"

using namespace Nighthawk;
int main()
{
  NighthawkEngine app;

  try
  {
    app.run();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }
}