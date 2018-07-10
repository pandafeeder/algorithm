#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <vector>



// BSF suits when the graph edge has no weight, finding the 
// shortest path meeting some criterion.
// caveats: there may have cirlced connection, so we need a
// list recording visited nodes in cases of infinite loop
// exampe:
// in the following graph, find the shortest path to whom whose
// name is Guile

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

Graph data = {
    {"Jim", {"Alex", "Bob", "Nancy", "Tom"}},
    {"Alex", {"Smith", "Chunli", "Ruy"}},
    {"Bob", {"Guile"}},
    {"Nancy", {"Akuma", "Lora"}},
    {"Tom", {}},
    {"Smith", {}},
    {"Chunli", {}},
    {"Ruy", {}}
};

std::vector<std::string> BSF(const Graph& g, const std::string& start, const std::string& end)
{
    std::vector<std::string> result;
    std::deque<std::vector<std::string>> search_deque;
    std::unordered_map<std::string, bool> visited;
    
    search_deque.push_back(g.at(start));

    while (search_deque.size() > 0) {
        auto node = search_deque.front();
        search_deque.pop_front();
        for (const auto &i : node) {
            if (visited.find(i) == visited.end()) {
                visited.insert({i, true});
            } else {
                continue;
            }
            if (i == end) {
                std::cout << "found\n";
            } else {
                if (g.find(i) != g.end()) {
                    search_deque.push_back(g.at(i));
                }
            }
        }
    }

    return result;
}


int main() {
    BSF(data, "Jim", "Guile");
}
