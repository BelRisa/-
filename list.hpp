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
	    Node<T>* current = head;
		while (current)
		{
			Node<T>* newcurrent = current->next;
			delete current;
			current = newcurrent;
		}
	
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
            Node<T>* head1 = head->next;
            delete head;
            head = head1;
        }
    } 

    int searchByValue(T* value) 
    {
        int index = 0;
        Node<T>* temp = new Node<T>;
        temp->value = value;
        temp = head;
        while (temp->value != value)
        {
            index++;
            temp = temp->next;
        }
        return index;
    }

    void insert(T* value, int index, int len)
    {
        Node<T>* newElem = new Node<T>;
        newElem->value = value;
        newElem->next = nullptr;
        Node<T>* node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }
        newElem->next = node->next;
        node->next = newElem;
        len++;
    }

    void removeByIndex(int index)
	{
		Node<T>* current = head;

		for (int i = 0; i < index - 1; ++i)
		{
			assert(current);
			current = current->next;
		}
		if (current->next != nullptr)
		{
			Node<T>* head1 = current->next->next; 
			T newList = current->next->value; 
			delete current->next;
			current->next = head1;
			return newList;		
		}
		else
		{
			Node<T>* head1 = 0;
			T len = 0; 
			delete current->next;
			current->next = head1;
		}			
	}

};
