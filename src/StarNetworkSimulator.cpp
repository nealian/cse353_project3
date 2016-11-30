#include "StarNetworkSimulator.h"

// cobbled together, doesn't run
int main(int argc, char **argv)
{
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << "[num] number of nodes to spawn" << std::endl;
    exit(EXIT_FAILURE);
  }

  Switch switch1; // TODO program hangs here -- move the switch new connection handler also to its own function and detached thread?
  std::vector<Node *> nodes;

  for (int i = 1; i <= std::stoi(argv[1]); ++i) {
    auto node = new Node(i, switch1.default_port);
    nodes.push_back(node);
  }
  return 0;
}