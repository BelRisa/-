template <typename T>

class Node
{
    Node<T>* next = nullptr;
    T value;
};

template <class T>
class List
{
public:
	Node<T>* head;

    List<T>()
	{
		head = 0;
	}

    ~List<T>()
	{
		this->erase();
	}

    void addNode(int d)       //метод, добавляющий новый узел в список
    {
        Node<T>* nd = new Node<T>();
        nd->value = d;       
        nd->next = 0;     
        if(head == 0)     
        {
            head = nd;
        }    
        else                
        {
            Node<T>* current = head;
            while(current->next != 0)
                {
                    current = current->next;
                }
            current->next = nd;
        }
    }

    int length()    //метод, возвращающий длину списка
    {
        if (!head)
        {
            return 0;
        }

        int len = 0;
        Node<T>* current = head;
		while (current != 0)
		{
			current = current->next;
			len++;
		}
		return len;
        
    }

    void pushFront(T* value1)
	{
		Node<T>* nd = new Node<T>();
		nd->value = value1;
		nd->next = head;
		head = nd;
	}

	T* popFront()
	{
		assert(head);
		Node<T>* head1 = head->next;
		T* value1 = head->value;
		delete head;
		head = head1;

		return value1;
	}

    void remove() //удаление головного узла
    {
        if(head)
        {
            Node<T>* newHead = head->next;
            delete head;
            head = newHead;
        }
    } 
}

    
}