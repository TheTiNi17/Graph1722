#ifndef NODE_H
#define NODE_H

#include <string>

class Node
{
private:
    int id;
    std::string name;
    std::string description;
public:
    Node();
    Node(int new_id, std::string new_name, std::string new_description);
    void set_name(std::string new_name);
    void set_descriptoin(std::string new_description);
    int get_id();
    std::string get_name();
    std::string get_description();
};

#endif // NODE_H
