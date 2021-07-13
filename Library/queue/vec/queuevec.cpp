
namespace lasd
{

    /* ************************************************************************** */

    // Specific constructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const LinearContainer<Data> &con) : Vector<Data>::Vector(con)
    {
        if (!con.Empty())
        {
            front = 0;
            rear = con.Size() - 1;
        }
    }

    // Copy costructor
    template <typename Data>
    QueueVec<Data>::QueueVec(const QueueVec<Data> &queue)
    {
        size = queue.size;
        Elements = new Data[size]{};
        if (!queue.Empty())
        {
            long scroll = queue.front;
            for (ulong index = 0; index < queue.Size(); index++)
            {
                Elements[index] = queue.Elements[scroll];
                scroll = (scroll + 1) % size;
            }
            front = 0;
            rear = queue.Size() - 1;
        }
    }

    //Move costructor
    template <typename Data>
    QueueVec<Data>::QueueVec(QueueVec<Data> &&queue) noexcept : Vector<Data>::Vector(std::move(queue))
    {
        std::swap(front, queue.front);
        std::swap(rear, queue.rear);
    }

    //Copy assignment
    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(const QueueVec<Data> &queue)
    {
        QueueVec<Data> *tmpque = new QueueVec<Data>(queue);
        std::swap(*tmpque, *this);
        delete tmpque;
        return *this;
    }

    //Move assignment
    template <typename Data>
    QueueVec<Data> &QueueVec<Data>::operator=(QueueVec<Data> &&queue) noexcept
    {
        Vector<Data>::operator=(std::move(queue));
        std::swap(front, queue.front);
        std::swap(rear, queue.rear);
        return *this;
    }

    //Comparison operators
    template <typename Data>
    bool QueueVec<Data>::operator==(const QueueVec<Data> &queue) const noexcept
    {
        long scroll = front;
        long scroll2 = queue.front;
        if (Size() == queue.Size())
        {
            if (Empty())
            {
                return true;
            }
            for (ulong index = 0; index < Size(); index++)
            {
                if (Elements[scroll] != queue.Elements[scroll2])
                {
                    return false;
                }
                scroll2 = (scroll2 + 1) % queue.size;
                scroll = (scroll + 1) % size;
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    inline bool QueueVec<Data>::operator!=(const QueueVec<Data> &queue) const noexcept
    {
        return !(*this == queue);
    }

    //Enqueue
    template <typename Data>
    void QueueVec<Data>::Enqueue(const Data &dat)
    {
        if (size == 0)
        {
            Elements = new Data[10]{};
            size = 10;
            front = 0;
        }
        else if (Full())
        {
            Resize(2 * Size());
        }
        else if (Empty())
        {
            front = 0;
        }
        rear = (rear + 1) % size;
        Elements[rear] = dat;
    }

    template <typename Data>
    void QueueVec<Data>::Enqueue(Data &&dat) noexcept
    {
        if (size == 0)
        {
            Elements = new Data[10]{};
            size = 10;
            front = 0;
        }
        else if (Full())
        {
            Resize(2 * Size());
        }
        else if (Empty())
        {
            front = 0;
        }
        rear = (rear + 1) % size;
        std::swap(Elements[rear], dat);
    }

    //Head

    template <typename Data>
    Data &QueueVec<Data>::Head() const
    {
        if (Empty())
        {
            throw std::length_error("Access to an empty queue.");
        }
        return Elements[front];
    }

    //Dequeue

    template <typename Data>
    void QueueVec<Data>::Dequeue()
    {
        if (Empty())
        {
            throw std::length_error("Access to an empty queue.");
        }
        if (front == rear)
        {
            front = -1;
            rear = -1;
        }
        else
        {
            if (size >= Size() * 4)
            {
                Resize(size / 2);
            }
            front = (front + 1) % size;
        }
    }

    //HeadNDequeue

    template <typename Data>
    Data QueueVec<Data>::HeadNDequeue()
    {
        if (Empty())
        {
            throw std::length_error("Access to an empty queue.");
        }
        else
        {
            Data val = Elements[front];
            Dequeue();
            return val;
        }
    }

    //Check emptiness
    template <typename Data>
    inline bool QueueVec<Data>::Empty() const noexcept
    {
        return (front == -1);
    }

    template <typename Data>
    inline bool QueueVec<Data>::Full() const noexcept
    {
        return ((rear + 1) % size == front);
    }

    //Size
    template <typename Data>
    ulong QueueVec<Data>::Size() const noexcept
    {
        if (!Empty())
            return (front > rear) ? (size - front + rear + 1) : (rear - front + 1);
        else
            return 0;
    }

    //Resize
    template <typename Data>
    void QueueVec<Data>::Resize(const ulong &newsize)
    {
        Data *TmpElements = new Data[newsize]{};
        long scroll = front;
        for (ulong index = 0; index < Size(); index++)
        {
            std::swap(Elements[scroll], TmpElements[index]);
            scroll = (scroll + 1) % size;
        }
        std::swap(Elements, TmpElements);
        rear = Size() - 1;
        front = 0;
        size = newsize;
        delete[] TmpElements;
    }

    template <typename Data>
    void QueueVec<Data>::Clear()
    {
        Vector<Data>::Clear();
        front = -1;
        rear = -1;
    }

    /* ************************************************************************** */
}
