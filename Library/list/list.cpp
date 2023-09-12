
namespace lasd
{

    // NODE

    // Node specific constructor
    template <typename Data>
    List<Data>::Node::Node(const Data &dat)
    {
        data = dat;
    }

    // Node copy constructor
    template <typename Data>
    List<Data>::Node::Node(const List<Data>::Node &nod)
    {
        data = nod.data;
        nextptr = nod.nextptr;
    }

    // Node move constructor
    template <typename Data>
    List<Data>::Node::Node(List<Data>::Node &&nod) noexcept
    {
        std::swap(data, nod.data);
        std::swap(nextptr, nod.nextptr);
    }

    template <typename Data>
    List<Data>::Node::~Node()
    {
        delete nextptr;
    }

    // Node comparison operators
    template <class Data>
    bool List<Data>::Node::operator==(const List<Data>::Node &nod) const noexcept
    {
        if (data == nod.data)
        {
            return true;
        }
        return false;
    }

    template <class Data>
    inline bool List<Data>::Node::operator!=(const List<Data>::Node &nod) const noexcept
    {
        return !(*this == nod);
    }

    // LIST

    // Specific constructor
    template <typename Data>
    List<Data>::List(const LinearContainer<Data> &con)
    {
        for (ulong index = 0; index < con.Size(); index++)
        {
            InsertAtBack(con[index]);
        }
    }

    // Copy constructor
    template <typename Data>
    List<Data>::List(const List<Data> &list)
    {
        if (list.head != nullptr)
        {
            Node *tmp = list.head;
            while (tmp != nullptr)
            {
                InsertAtBack(tmp->data);
                tmp = tmp->nextptr;
            }
        }
    }

    // Move constructor
    template <typename Data>
    List<Data>::List(List &&list) noexcept
    {
        std::swap(size, list.size);
        std::swap(head, list.head);
        std::swap(tail, list.tail);
    }

    // Destructor
    template <typename Data>
    List<Data>::~List()
    {
        delete head;
    }

    // Copy assignment
    template <typename Data>
    List<Data> &List<Data>::operator=(const List<Data> &list)
    {
        List<Data> *tmplist = new List<Data>(list);
        std::swap(*tmplist, *this);
        delete tmplist;
        return *this;
    }

    // Move assignment
    template <class Data>
    List<Data> &List<Data>::operator=(List<Data> &&list) noexcept
    {
        std::swap(size, list.size);
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        return *this;
    }

    // Comparison operators

    template <typename Data>
    bool List<Data>::operator==(const List<Data> &list) const noexcept
    {
        Node *tmp1 = head;
        Node *tmp2 = list.head;
        if (tmp1 == tmp2)
        {
            return true;
        }
        if (size != list.size)
        {
            return false;
        }
        else
        {
            while (tmp1 != nullptr)
            {
                if (tmp1->data != tmp2->data)
                {
                    return false;
                }
                tmp1 = tmp1->nextptr;
                tmp2 = tmp2->nextptr;
            }
            return true;
        }
    }

    template <typename Data>
    inline bool List<Data>::operator!=(const List<Data> &list) const noexcept
    {
        return !((*this) == list);
    }

    // Insert at front (copy)

    template <typename Data>
    void List<Data>::InsertAtFront(const Data &dat)
    {
        Node *tmp = new Node(dat);
        if (head == nullptr)
        {
            head = tmp;
            tail = head;
        }
        else
        {
            tmp->nextptr = head;
            head = tmp;
        }
        size = size + 1;
    }

    // Insert at front (move)

    template <typename Data>
    void List<Data>::InsertAtFront(Data &&dat) noexcept
    {
        Node *tmp = new Node(std::move(dat));
        if (head == nullptr)
        {
            head = tmp;
            tail = head;
        }
        else
        {
            tmp->nextptr = head;
            head = tmp;
        }
        size = size + 1;
    }

    // Remove from front

    template <typename Data>
    void List<Data>::RemoveFromFront()
    {

        if (head != nullptr)
        {
            Node *tmp = head;
            head = head->nextptr;
            tmp->nextptr = nullptr;
            delete tmp;
            size = size - 1;
        }
        else
        {
            throw std::length_error("Access to an empty list");
        }
    }

    // Remove front and returns it

    template <typename Data>
    Data List<Data>::FrontNRemove()
    {
        Data front;
        if (head != nullptr)
        {
            front = head->data;
            RemoveFromFront();
            return front;
        }
        else
        {
            throw std::length_error("Access to an empty list");
        }
    }

    // Insert at back (copy)

    template <typename Data>
    void List<Data>::InsertAtBack(const Data &dat)
    {
        Node *tmp = new Node(dat);
        if (head == nullptr)
        {
            head = tmp;
            tail = head;
        }
        else
        {
            tail->nextptr = tmp;
            tail = tmp;
        }
        size = size + 1;
    }

    // Insert at back (move)

    template <typename Data>
    void List<Data>::InsertAtBack(Data &&dat) noexcept
    {
        Node *tmp = new Node(std::move(dat));
        if (head == nullptr)
        {
            head = tmp;
            tail = head;
        }
        else
        {
            tail->nextptr = tmp;
            tail = tmp;
        }
        size = size + 1;
    }

    // Clear method overridden from Container
    template <typename Data>
    void List<Data>::Clear()
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // Front
    template <typename Data>
    Data &List<Data>::Front() const
    {
        if (head != nullptr)
        {
            return head->data;
        }
        else
        {
            throw std::length_error("Access to an empty string.");
        }
    }

    // Back
    template <typename Data>
    Data &List<Data>::Back() const
    {
        if (head != nullptr)
        {
            return tail->data;
        }
        else
        {
            throw std::length_error("Access to an empty string.");
        }
    }

    // [] operator overridden from LinearContainer
    template <typename Data>
    Data &List<Data>::operator[](const ulong pos) const
    {
        if (pos >= size)
        {
            throw std::out_of_range("Out of range.");
        }
        else
        {
            Node *tmp = head;
            for (ulong index = 0; index < pos; index++)
            {
                tmp = tmp->nextptr;
            }
            return tmp->data;
        }
    }

    // Specific member functions (inherited from FoldableContainer)
    template <class Data>
    void List<Data>::MapPreOrder(const MapFunctor fun, void *par)
    {
        if (head != nullptr)
        {
            Node *tmp = head;
            while (tmp != nullptr)
            {
                fun(tmp->data, par);
                tmp = tmp->nextptr;
            }
        }
    }

    template <class Data>
    void List<Data>::MapPostOrder(const MapFunctor fun, void *par)
    {
        ulong index = size;
        while (index > 0)
        {
            fun((*this)[--index], par);
        }
    }

    // Auxiliary member functions (for MappableContainer)
    template <typename Data>
    void List<Data>::FoldPreOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        if (head != nullptr)
        {
            Node *tmp = head;
            while (tmp != nullptr)
            {
                fun(tmp->data, par, acc);
                tmp = tmp->nextptr;
            }
        }
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        ulong index = size;
        while (index > 0)
        {
            fun((*this)[--index], par, acc);
        }
    }

}
