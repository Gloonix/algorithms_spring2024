#include <iostream>

// дописать компаратор
template <typename T>
class AvlTree
{
  struct Node
  {
      Node(const T &data)
      : data(data), left(nullptr), right(nullptr), height(1)
      {
      }
      
      T data;
      Node *left;
      Node *right;
      size_t height;
  };
    
public:
    AvlTree()
    : root(nullptr)
    {
    }
    
    ~AvlTree()
    {
        destroyTree(root);
    }
    
    void Add(const T &data)
    {
        root = addInternal(root, data);
    }
    
    bool Has(const T &data)
    {
        Node *tmp = root;
        while (tmp)
        {
            if (tmp->data == data)
                return true;
            else if (tmp->data < data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }
    void Delete(const T &data)
    {
        root = deleteInternal(root, data);
    }
private:
    
    void destroyTree(Node *node)
    {
        if (node)
        {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }
    
    Node* deleteInternal(Node *node, const T &data)
    {
        if (!node)
            return nullptr;
        if (node->data < data)
            node->right = deleteInternal(node->right, data);
        else if (node->data > data)
            node->left = deleteInternal(node->left, data);
        else
        {
            Node *left = node->left;
            Node *right = node->right;
            
            delete node;
            
            if (!right)
                return left;
            
            // поддерево, из которого берем элемент взамен удаляемого, выбираем на основе сравнения глубин.
            // (берем из более глубокого)
            
            // findMin и removeMin объединить в один метод findAndRemoveMin/findAndRemoveMax
            Node *min = findMin(right); // возвращает минимальный элемент в дереве
            min->right = removeMin(right); // возвращает дерево, из которого удалили минимальный элемент
            min->left = left;
            
            return doBalance(min);
        }
        
        return doBalance(node);
    }
    
    Node* findMin(Node *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }
    
    Node* removeMin(Node *node)
    {
        if (!node->left)
            return node->right;
        node->left = removeMin(node->left);
        return doBalance(node);
    }
    
    Node* addInternal(Node *node, const T &data)
    {
        if (!node)
            return new Node(data);
        if (node->data <= data)
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);
        
        return doBalance(node);
    }
    
    size_t getHeight(Node *node)
    {
        return node ? node->height : 0;
    }
    
    void fixHeight(Node *node)
    {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
    
    int getBalance(Node *node)
    {
        return getHeight(node->right) - getHeight(node->left);
    }
    
    Node* rotateLeft(Node *node)
    {
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }
    
    Node* rotateRight(Node *node)
    {
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }
    
    Node* doBalance(Node *node)
    {
        fixHeight(node);
        switch (getBalance(node))
        {
            case 2:
            {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
    
    Node *root;
};

int main(int argc, const char * argv[]) {
    return 0;
}
