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

  for (int i = 0; i < std::stoi(argv[1]); ++i) {
    auto node = new Node(i, aSwitch->default_port);
    nodes.push_back(node);
  }

  aSwitch->handle_new_connection();

  for (auto n : nodes) {
    n->read_from_input();
    n->send_loop();
    n->receive_loop();
  }

  return 0;
}