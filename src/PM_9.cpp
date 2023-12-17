#include "Graph.hpp"
#include <string>
#include <conio.h>

bool is_value(const std::string& str)
{
    for (auto it : str)
        if (!isdigit(it))
            return false;
    return !str.empty();
}

int get_int(const std::string& text)
{
    while (true)
    {
        std::cout << text;
        std::string input_string;
        getline(std::cin, input_string);

        if (is_value(input_string))
            return std::stoi(input_string);
        else
            std::cout << "Incorrect input. Try again." << std::endl;
    }
}

int get_key()
{
    int key = _getch();
    if ((key == 0) || (key == 224))
        key = _getch();
    return key - 48;
}

int main_menu()
{
    std::cout << "[1] Insert edge" << std::endl;
    std::cout << "[2] Insert vertex" << std::endl;
    std::cout << "[3] Print" << std::endl;
    std::cout << "[4] Find shortest way" << std::endl;
    std::cout << "[5] Exit" << std::endl;

    while (true)
    {
        int key = get_key();
        if (key == 1 || key == 2 || key == 3 || key == 4 || key == 5)
            return key;
    }
}

int main()
{
    Graph graph;
    std::string buffer;
    while (true)
    {
        int key = main_menu();
        system("cls");
        if (key == 5)
            return 0;
        else if (key == 1)
        {
            key = get_int("Add edge (id): ");
            graph.insert_edge(key);
        }
        else if (key == 2)
        {
            struct Vertex 
            {
                int src, dest, weight;
            } vertex(0, 0, 0);
            vertex.src = get_int("Enter source edge (id): ");
            vertex.dest = get_int("Enter destination edge (id): ");
            vertex.weight = get_int("Enter vertex weight: ");
            graph.insert_vertex(vertex.src, vertex.dest, vertex.weight);
        }
        else if (key == 3)
        {
            graph.print();
            system("pause");
        }
        else if (key == 4)
        {
            key = get_int("Find shortest ways from edge (id): ");
            graph.find_shortest_way(key);
            system("pause");
        }
        system("cls");
    }
}