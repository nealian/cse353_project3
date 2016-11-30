#include "StarNetworkSimulator.h"

// cobbled together, doesn't run
int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << "[num] number of nodes to spawn" << std::endl;
    exit(EXIT_FAILURE);
  }

  auto aSwitch = new Switch();
  std::vector<Node *> nodes;

  for (int i = 1; i <= std::stoi(argv[1]); ++i) {
    auto node = new Node(i, aSwitch->default_port);
    nodes.push_back(node);
  }

  return 0;
}