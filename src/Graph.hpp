#include <list>
#include <map>
#include <queue>
#include <iostream>
#include <string>

const int VERTICES = 2;

class Graph
{
private:
	typedef std::map<int, int> VertexMap; // key - destination Edge, value - weight
	typedef std::map<int, VertexMap> EdgeMap; // key - Edge id, value - list of edge vertexes;
	
	EdgeMap data;
public:
	Graph() 
		: data()
	{}

	void insert_edge(const int id)
	{		
		if (data.contains(id) || id < 0)
			return;

		data.insert(std::make_pair(id, VertexMap()));
	}

	void delete_edge(const int id)
	{
		if (!data.contains(id))
			return;

		for (auto&& it_edge : data)
			delete_vertex(it_edge.first, id);
		data.erase(id);
	}

	void insert_vertex(const int src, const int dest, const int weight)
	{
		if (!data.contains(src) || !data.contains(dest) || data[src].contains(dest) || src < 0 || dest < 0 || weight < 0)
			return;

		data[src].insert(std::make_pair(dest, weight));
	}

	void delete_vertex(const int src, const int dest)
	{
		if (!data.contains(src) || !data.contains(dest))
			return;

		data[src].erase(dest);
	}

	void print() const
	{
		for (auto&& it_edge : data)
		{
			std::cout << "EDGE [" << it_edge.first << ']' << std::endl;
			for (auto&& it_vertex : it_edge.second)
				std::cout << "dst: " << it_vertex.first << " | weight: " << it_vertex.second << std::endl;
			std::cout << std::endl;
		}
	}

	int operator()(const int src, const int dest) const
	{        
        for (auto&& it_vertex : data.find(src)->second)
            if (it_vertex.first == dest)
                return it_vertex.second;

		return 0;
	}

    void find_shortest_way(const int src) const
    {
        if (!data.contains(src))
            return;

        std::map<int, bool> visited;
        std::map<int, int> distances;
        unsigned min_weight, min_index;

        for (auto&& it : data)
        {
            visited.insert(std::make_pair(it.first, false));
            distances.insert(std::make_pair(it.first, INT_MAX));
        }
        distances[src] = 0;

        do
        {
            min_index = INT_MAX;
            min_weight = INT_MAX;

            for (auto&& it : data)
            {
                if (!visited[it.first] && distances[it.first] < min_weight)
                {
                    min_index = it.first;
                    min_weight = distances[it.first];
                }
            }

            if (min_index != INT_MAX)
            {
                for (auto&& it : data)
                {
                    if ((*this)(min_index, it.first))
                    {
                        unsigned temp = min_weight + (*this)(min_index, it.first);

                        if (temp < distances[it.first])
                            distances[it.first] = temp;
                    }
                }

                visited[min_index] = true;
            }
        } while (min_index < INT_MAX);

        for (auto&& it_i : data)
        {
            if (distances[it_i.first] != INT_MAX)
            {
                std::cout << '[' << it_i.first << "] Weight = " << std::left << distances[it_i.first] << "\t";

                unsigned end = it_i.first;
                unsigned weight = distances[end];
                std::string way = std::to_string(end) + " >- ";

                while (end != src)
                {
                    for (auto&& it_j : data)
                    {
                        if ((*this)(it_j.first, end))
                        {
                            int temp = weight - (*this)(it_j.first, end);

                            if (temp == distances[it_j.first])
                            {
                                end = it_j.first;
                                weight = temp;
                                way += std::to_string(it_j.first) + " >- ";
                            }
                        }
                    }
                }

                std::cout << " | Path: ";

                for (int j = way.length() - 5; j >= 0; --j)
                    std::cout << way[j];

                std::cout << std::endl;
            }
            else
                std::cout << '[' << it_i.first << "] path unnable" << std::endl;
        }

    }
};

