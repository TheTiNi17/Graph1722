#include "node.h"

Node::Node() {}

Node::Node(int new_id, std::string new_name, std::string new_description)
{
    id = new_id;
    name = new_name;
    description = new_description;
}

void Node::set_name(std::string new_name)
{
    name = new_name;
}

void Node::set_descriptoin(std::string new_description)
{
    description = new_description;
}

int Node::get_id()
{
    return id;
}
std::string Node::get_name()
{
    return name;
}
std::string Node::get_description()
{
    return description;
}
