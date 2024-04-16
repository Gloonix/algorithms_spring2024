#include <iostream>
#include <vector>

const size_t DEFAULT_SIZE = 8;

template <typename T>
struct HashtableNode
{
    HashtableNode()
    : next(nullptr)
    {
    }
    
    HashtableNode(const T &data, HashtableNode<T> *next)
    : data(data), next(next)
    {
    }
    
    T data;
    HashtableNode<T> *next;
};

class StringHasher
{
public:
    StringHasher(size_t prime = 71)
    : prime(prime)
    {
    }
    
    size_t operator()(const std::string &str)
    {
        size_t hash = 0;
        for (int i = 0; i < str.size(); i++)
        {
            hash = hash * prime + str[i];
        }
        return hash;
    }
    
private:
    size_t prime;
};

template <typename T, typename Hasher>
class Hashtable
{
public:
    Hashtable(size_t initial_size = DEFAULT_SIZE)
    : size(0), table(initial_size, nullptr)
    {
    }
    
    ~Hashtable()
    {
        for (int i = 0; i < table.size(); i++)
        {
            HashtableNode<T> *node = table[i];
            
            while (node != nullptr)
            {
                HashtableNode<T> *next = node->next;
                delete node;
                node = next;
            }
        }
    }
    
    bool Add(const T &key)
    {
        if (size > table.size() * 2)
        {
            grow();
        }
        
        size_t hash = hasher(key) % table.size();
        HashtableNode<T> *node = table[hash];
        
        while (node != nullptr)
        {
            if (node->data == key)
            {
                return false;
            }
            node = node->next;
        }
        
        table[hash] = new HashtableNode<T>(key, table[hash]);
        size++;
        return true;
    }
    
    bool Has(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        HashtableNode<T> *node = table[hash];
        
        while (node != nullptr)
        {
            if (node->data == key)
            {
                return true;
            }
            node = node->next;
        }
        return false;
    }
    
    bool Delete(const T &key)
    {
        size_t hash = hasher(key) % table.size();
        
        HashtableNode<T> *node = table[hash];
        HashtableNode<T> *prev = nullptr;
        
        while (node != nullptr)
        {
            if (node->data == key)
            {
                break;
            }
            prev = node;
            node = node->next;
        }
        
        if (node == nullptr)
            return false;
        
        if (prev == nullptr)
        {
            table[hash] = node->next;
        }
        else
        {
            prev->next = node->next;
        }
        
        delete node;
        size--;
        return true;
    }
    
private:
    void grow()
    {
        std::vector<HashtableNode<T>*> newTable(table.size() * 2, nullptr);
        
        for (int i = 0; i < table.size(); i++)
        {
            HashtableNode<T> *node = table[i];
            
            while (node != nullptr)
            {
                HashtableNode<T> *next = node->next;
                size_t newHash = hasher(node->data) % newTable.size();
                node->next = newTable[newHash];
                newTable[newHash] = node;
                node = next;
            }
        }
        
        std::swap(table, newTable);
    }
    
    std::vector<HashtableNode<T>*> table;
    size_t size;
    Hasher hasher;
};

int main(int argc, const char * argv[]) {
    Hashtable<std::string, StringHasher> table;
    
    char op;
    std::string key;

    while (std::cin >> op >> key)
    {
        switch (op)
        {
            case '?':
            {
                std::cout << (table.Has(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '+':
            {
                std::cout << (table.Add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-':
            {
                std::cout << (table.Delete(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '!':
            {
                return 0;
            }
                
        }
    }
    return 0;
}
