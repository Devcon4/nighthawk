
#include <vector>
#include <fstream>
#include <iostream>

namespace Nighthawk
{

  std::vector<char> LoadShader(const std::string &path)
  {
    std::ifstream file(path, std::ios::ate | std::ios::binary);

    if (!file.is_open())
    {
      throw std::runtime_error("Failed to load shader at " + path);
    }

    size_t fileSize = (size_t)file.tellg();
    std::vector<char> buffer(fileSize);

    file.seekg(0);
    file.read(buffer.data(), fileSize);

    std::cout << "Loaded shader: " + path + "\n";
    file.close();
    return buffer;
  }
}