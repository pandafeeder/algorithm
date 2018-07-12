#include <iostream>
#include <deque>
#include <unordered_map>
#include <string>
#include <vector>
#include <algorithm>



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
    std::unordered_map<std::string, std::string> pre;
    
    search_deque.push_back(g.at(start));

    for (const auto &i : g.at(start)) {
        if (pre.find(i) == pre.end()) {
            pre.insert({i, start});
        }
    }

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
                result.push_back(i);
                auto p = i;
                while (true) {
                    auto iter = pre.find(p);
                    if (iter == pre.end()) {
                        break;
                    }
                    p = (*iter).second;
                    result.push_back(p);
                }
                std::reverse(result.begin(), result.end());
                return result;
            } else {
                if (g.find(i) != g.end()) {
                    search_deque.push_back(g.at(i));
                    for (const auto &j : g.at(i)) {
                        if (pre.find(j) == pre.end()) {
                            pre.insert({j, i});
                        }
                    }
                }
            }
        }
    }

    return result;
}


int main() {
    auto path = BSF(data, "Jim", "Guile");
    for (const auto &i : path) {
        std::cout << i << '\n';
    }
}
