#include "graph.h"

Graph::Graph(){}

void Graph::addNode(int id, const std::string& name, const std::string& description)
{
    Node node = {id, name, description};
    nodes[id] = node;
}

void Graph::removeNode(int id)
{
    nodes.erase(id);

    auto it = edges.begin();
    while (it != edges.end())
    {
        if (it->first == id || it->second == id)
        {
            it = edges.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void Graph::addEdge(int id1, int id2)
{
    edges.insert(std::make_pair(id1, id2));
}

void Graph::removeEdge(int id1, int id2)
{
    // Сначала создаем пару, которая соответствует ребру, которое мы хотим удалить
    std::pair<int, int> edge(id1, id2);

    // Затем ищем это ребро в наборе edges
    auto it = edges.find(edge);

    // Если ребро найдено, удаляем его
    if (it != edges.end())
    {
        edges.erase(it);
    }
}

void Graph::printGraph()
{
    std::cout << "Nodes:\n";
    for (auto& pair : nodes)
    {
        auto& node = pair.second;
        std::cout << "  ID: " << node.get_id() << ", Name: " << node.get_name() << ", Description: " << node.get_description() << "\n";
    }
    std::cout << "Edges:\n";
    for (auto& edge : edges)
    {
        std::cout << "  From: " << edge.first << " To: " << edge.second << std::endl;
    }
}

std::string Graph::saveToJson()
{
    std::string res = "";
    res += "{\n";
    res +=  "  \"nodes\": [\n";
    for (auto it = nodes.begin(); it != nodes.end(); ++it)
    {
        res += "    {\n";
        res +="      \"id\": " + std::to_string(it->second.get_id()) + ",\n";
        res += "    \"name\": \"" +  it->second.get_name() + "\",\n";
        res +="      \"description\": \"" + it->second.get_description() + "\"\n";
        res += "    }";
        if (std::next(it) != nodes.end()) res += ",";
        res += "\n";
    }
    res +="  ],\n";
    res += "  \"edges\": [\n";
    for (auto it = edges.begin(); it != edges.end(); ++it)
    {
        res += "    {\n";
        res += "      \"from\": " + std::to_string(it->first) + ",\n";
        res += "      \"to\": " + std::to_string(it->second) + "\n";
        res += "    }";
        if (std::next(it) != edges.end()) res += ",";
        res +=  "\n";
    }
    res += "  ]\n";
    res += "}";
    return res;
}
