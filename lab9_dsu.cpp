#include <iostream>
#include <vector>
#include <stack>
#include <map>

class DSU
{
public:
    DSU(size_t size)
    : parent(size), rank(size, 1)
    {
        for (int i = 0; i < size; i++)
        {
            parent[i] = i;
        }
    }
    
    size_t find_set(size_t u)
    {
        std::stack<size_t> stack;
        stack.push(u);
        
        while (parent[u] != u)
        {
            stack.push(parent[u]);
            u = parent[u];
        }
        
        size_t &root = u;
        
        while (!stack.empty())
        {
            parent[stack.top()] = root;
            stack.pop();
        }
        
        return root;
    }
    
    void union_set(size_t u, size_t v)
    {
        u = find_set(u);
        v = find_set(v);
        
        if (u != v)
        {
            if (rank[u] < rank[v])
                std::swap(u, v);
            
            parent[v] = u;
            rank[u] += rank[v];
        }
    }
    
private:
    std::vector<size_t> parent;
    std::vector<size_t> rank;
    
    friend std::ostream& operator<<(std::ostream &out, DSU &dsu);
};

std::ostream& operator<<(std::ostream &out, DSU &dsu)
{
    std::map<size_t, std::vector<size_t>> sets;
    
    for (auto i = 0; i < dsu.parent.size(); i++)
    {
        sets[dsu.find_set(i)].push_back(i);
    }
    
    for (auto &kv: sets)
    {
        out << kv.first << " [rank = " << dsu.rank[kv.first] << "]: ";
        for (auto i = 0; i < kv.second.size(); i++)
        {
            out << kv.second[i];
            if (i != kv.second.size() - 1)
                out << ", ";
        }
        out << std::endl;
    }
    
    return out;
}

int main(int argc, const char * argv[]) {
    DSU dsu(10);
    std::cout << dsu << std::endl;
    
    dsu.union_set(2, 7);
    std::cout << dsu << std::endl;
    
    dsu.union_set(3, 9);
    std::cout << dsu << std::endl;
    
    dsu.union_set(9, 7);
    std::cout << dsu << std::endl;
    
    dsu.union_set(6, 8);
    std::cout << dsu << std::endl;
    
    dsu.union_set(0, 1);
    std::cout << dsu << std::endl;
    return 0;
}
