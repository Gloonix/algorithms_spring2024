#include <iostream>
#include <vector>

template <typename T>
class BTree
{
public:
    struct Node
    {
        Node(bool leaf)
        : leaf(leaf)
        {
        }
        
        ~Node()
        {
            for (Node* child: children)
            {
                delete child;
            }
        }
        
        bool leaf;
        std::vector<T> keys;
        std::vector<Node*> children;
    };
    
    BTree(size_t min_degree)
    : t(min_degree), root(nullptr)
    {
    }
    
    ~BTree()
    {
        if (root)
            delete root;
    }
    
    void Insert(const T &key)
    {
        if (!root)
            root = new Node(true);
        
        // здесь и дальше: если при спуске по дереву находим
        // переполненный узел -- сначала разбиваем его, потом спускаемся
        if (isNodeFull(root))
        {
            Node *newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }
        
        // теперь корень точно не переполнен, можем вызвать insertNonFull
        insertNonFull(root, key);
    }
    
    void debugPrint()
    {
        debugPrintInternal(root, 0);
    }
    
private:
    
    void debugPrintInternal(Node *node, int indent)
    {
        std::cout << std::string(indent, ' ');
        std::cout << "keys: [";
        for (auto it = node->keys.begin(); it != node->keys.end(); it++)
        {
            std::cout << (*it);
            if (it + 1 != node->keys.end())
                std::cout << ", ";
        }
        std::cout << "]" << std::endl;
        
        for (auto child: node->children)
        {
            debugPrint(child, indent + 4);
        }
    }
    
    bool isNodeFull(Node *node)
    {
        return node->keys.size() == 2*t - 1;
    }
    
    // разбить переполненного потомка index узла node
    void splitChild(Node *node, size_t index);
    
    // вставить ключ key в гарантированно не переполненную ноду node
    void insertNonFull(Node *node, const T &key)
    {
        int pos = node->keys.size() - 1;
        
        // гарантированно не перепеполненный лист -- запишем новый ключ в него
        if (node->leaf)
        {
            // расширили вектор ключей для вставки нового
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos])
            {
                // обходим ключи справа налево, сдвигая вправо на 1
                node->keys[pos + 1] = node->keys[pos];
                pos--;
            }
            // вставляем новый ключ на освобожденное в цикле место
            node->keys[pos + 1] = key;
        }
        // не лист, значит есть потомки, пишем в один из них
        else
        {
            // ищем позицию потомка, в которого добавим ключ
            while (pos >= 0 && key < node->keys[pos])
            {
                pos--;
            }
            
            // если потомок и так полон, надо его сначала разбить
            if (isNodeFull(node->children[pos + 1]))
            {
                splitChild(node, pos + 1);
                // после разбиения потомка в текущий узел из него поднялся ключ
                // надо сравниться и с ним
                if (key > node->keys[pos + 1])
                    pos++;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }
    
    size_t t;
    Node *root;
    
    friend void test1();
};

// случаи вставки с иллюстраций в лекции
void test1()
{
    BTree<char> tree(3);
    
    tree.root = new BTree<char>::Node(false);
    tree.root->keys = {'G', 'M', 'P', 'X'};
    
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'A', 'C', 'D', 'E'};
        tree.root->children.push_back(child);
    }
    
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'J', 'K'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'N', 'O'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'R', 'S', 'T', 'U', 'V'};
        tree.root->children.push_back(child);
    }
    {
        auto child = new BTree<char>::Node(true);
        child->keys = {'Y', 'Z'};
        tree.root->children.push_back(child);
    }
    
    std::cout << "Initial tree:" << std::endl;
    tree.debugPrint();
    std::cout << std::endl;
    
    std::string insertKeys = "BQLF";
    // посимвольно добавляем в дерево ключи
    for (auto c: insertKeys)
    {
        tree.Insert(c);
        std::cout << "After inserting " << c << ":" << std::endl;
        tree.debugPrint();
        std::cout << std::endl;
    }
}

int main(int argc, const char * argv[]) {
    test1();
    return 0;
}
