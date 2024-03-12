#include <iostream>
#include <cassert>
#include <sstream>

struct Node
{
    Node(int data)
    : data(data), next(nullptr)
    {
    }
    int data;
    Node *next;
};

class Queue
{
public:
    Queue()
    : head(nullptr), tail(nullptr)
    {
    }
    
    // правило "трех":
    // раз написали свой деструктор, то надо либо написать
    // нормальные конструктор копирования и оператор присваивания,
    // либо вообще от них отказаться
    Queue(const Queue &other) = delete;
    Queue& operator=(const Queue &other) = delete;
    
    ~Queue()
    {
        while (!IsEmpty())
        {
            Dequeue();
        }
    }
    
    void Enqueue(int data)
    {
        Node *node = new Node(data);
        if (IsEmpty())
        {
            head = tail = node;
            return;
        }
        tail->next = node;
        tail = node;
    }
    
    int Dequeue()
    {
        if (IsEmpty())
            return -1;
        
        int tmpData = head->data;
        Node *tmpNode = head;
        
        head = head->next;
        if (head == nullptr)
        {
            tail = nullptr;
        }
        
        delete tmpNode;
        return tmpData;
    }
    
    bool IsEmpty()
    {
        return head == nullptr && tail == nullptr;
    }
    
private:
    Node *head;
    Node *tail;
};

void testLogic()
{
    Queue queue;
    int sampleCount = 100;
    
    assert(queue.IsEmpty());
    
    for (int i = 0; i < sampleCount; i++)
    {
        queue.Enqueue(i);
    }
    
    assert(!queue.IsEmpty());
    
    for (int i = 0; i < sampleCount; i++)
    {
        assert(i == queue.Dequeue());
    }
    
    assert(queue.IsEmpty());
}

void run(std::istream &input, std::ostream &output)
{
    Queue queue;
    
    int n = 0;
    input >> n;
    
    for (int i = 0; i < n; i++)
    {
        int op = 0, val = 0;
        input >> op >> val;
        
        switch (op)
        {
            case 2:
            {
                int tmpVal = queue.Dequeue();
                if (tmpVal != val)
                {
                    output << "NO" << std::endl;
                    return;
                }
                break;
            }
            case 3:
            {
                queue.Enqueue(val);
                break;
            }
        }
    }
    output << "YES" << std::endl;
}

void testQueue()
{
    {
        std::stringstream input, output;
        input << "3" << std::endl;
        input << "3 111" << std::endl;
        input << "2 222" << std::endl;
        input << "3 333" << std::endl;
        run(input, output);
        assert(output.str() == "NO\n");
    }
    {
        std::stringstream input, output;
        input << "3" << std::endl;
        input << "3 111" << std::endl;
        input << "2 111" << std::endl;
        input << "3 333" << std::endl;
        run(input, output);
        assert(output.str() == "YES\n");
    }
}

int main(int argc, const char * argv[]) {
    //testLogic();
    run(std::cin, std::cout);
    //testQueue();
    return 0;
}
