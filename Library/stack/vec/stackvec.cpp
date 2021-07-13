
namespace lasd
{

    /* ************************************************************************** */

    //Specific costructor
    template <typename Data>
    StackVec<Data>::StackVec(const LinearContainer<Data> &con) : Vector<Data>::Vector(con)
    {
        effective_size = con.Size();
    }

    //Copy costructor
    template <typename Data>
    StackVec<Data>::StackVec(const StackVec<Data> &stack)
    {
        size = stack.size;
        effective_size = stack.effective_size;
        Elements = new Data[size]{};
        std::copy(stack.Elements, stack.Elements + effective_size, Elements);
    }

    //Move costructor
    template <typename Data>
    StackVec<Data>::StackVec(StackVec<Data> &&stack) noexcept : Vector<Data>::Vector(std::move(stack))
    {
        std::swap(effective_size, stack.effective_size);
    }

    //Copy assignment
    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(const StackVec<Data> &stack)
    {
        StackVec<Data> *tmpstk = new StackVec<Data>(stack);
        std::swap(*tmpstk, *this);
        delete tmpstk;
        return *this;
    }

    //Move assignment
    template <typename Data>
    StackVec<Data> &StackVec<Data>::operator=(StackVec<Data> &&stack) noexcept
    {
        Vector<Data>::operator=(std::move(stack));
        std::swap(effective_size, stack.effective_size);
        return *this;
    }

    //Comparison operators

    template <typename Data>
    bool StackVec<Data>::operator==(const StackVec<Data> &stack) const noexcept
    {
        if (effective_size == stack.effective_size)
        {
            for (ulong index = 0; index < stack.effective_size; index++)
            {
                if (Elements[index] != stack.Elements[index])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    inline bool StackVec<Data>::operator!=(const StackVec<Data> &stack) const noexcept
    {
        return !(*this == stack);
    }

    // Specific member functions (inherited from Stack)

    template <typename Data>
    void StackVec<Data>::Push(const Data &dat)
    {
        if (size == 0)
        {
            Elements = new Data[10]{};
            size = 10;
        }
        else if (effective_size >= size)
        {
            this->Resize(2 * effective_size);
        }
        Elements[effective_size] = dat;
        effective_size++;
    }

    template <typename Data>
    void StackVec<Data>::Push(Data &&dat) noexcept
    {
        if (size == 0)
        {
            Elements = new Data[10]{};
            size = 10;
        }
        else if (effective_size >= size)
        {
            this->Resize(2 * effective_size);
        }
        std::swap(Elements[effective_size], dat);
        effective_size++;
    }

    template <typename Data>
    Data &StackVec<Data>::Top() const
    {
        if (!Empty())
        {
            return Elements[effective_size - 1];
        }
        else
        {
            throw std::length_error("Access to an empty vector.");
        }
    }

    template <typename Data>
    void StackVec<Data>::Pop()
    {
        if (!Empty())
        {
            if (size >= 4 * effective_size)
            {
                this->Resize(size / 2);
            }
            effective_size--;
        }
        else
        {
            throw std::length_error("Access to an empty vector.");
        }
    }

    template <typename Data>
    Data StackVec<Data>::TopNPop()
    {
        if (Empty())
        {
            throw std::length_error("Access to an empty vector.");
        }
        else
        {
            Data val = Elements[effective_size - 1];
            Pop();
            return val;
        }
    }

    // Specific member functions (inherited from Container)

    template <typename Data>
    inline bool StackVec<Data>::Empty() const noexcept
    {
        return (effective_size == 0);
    }

    template <typename Data>
    inline ulong StackVec<Data>::Size() const noexcept
    {
        return effective_size;
    }

    template <typename Data>
    void StackVec<Data>::Clear()
    {
        Vector<Data>::Clear();
        effective_size = 0;
    }

    // Auxiliary member functions

    /* ************************************************************************** */

}
