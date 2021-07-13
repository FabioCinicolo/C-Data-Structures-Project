
namespace lasd
{

    /* ************************************************************************** */

    // Specific costructor
    template <typename Data>
    StackLst<Data>::StackLst(const LinearContainer<Data> &con) : List<Data>::List(con)
    {
    }

    //Copy costructor
    template <typename Data>
    StackLst<Data>::StackLst(const StackLst<Data> &stack) : List<Data>::List(stack)
    {
    }

    //Move costructor
    template <typename Data>
    StackLst<Data>::StackLst(StackLst<Data> &&stack) noexcept : List<Data>::List(std::move(stack))
    {
    }

    //Copy assignement
    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(const StackLst<Data> &stack)
    {
        List<Data>::operator=(stack);
        return *this;
    }

    //Move assignement
    template <typename Data>
    StackLst<Data> &StackLst<Data>::operator=(StackLst<Data> &&stack) noexcept
    {
        List<Data>::operator=(std::move(stack));
        return *this;
    }
    //Comparison operators
    template <typename Data>
    bool StackLst<Data>::operator==(const StackLst<Data> &stack) const noexcept
    {
        return List<Data>::operator==(stack);
    }

    template <class Data>
    inline bool StackLst<Data>::operator!=(const StackLst<Data> &stack) const noexcept
    {
        return !(*this == stack);
    }

    //Specific member functions (inherited from Stack)

    template <typename Data>
    void StackLst<Data>::Push(const Data &dat)
    {
        this->InsertAtFront(dat);
    }

    template <typename Data>
    void StackLst<Data>::Push(Data &&dat) noexcept
    {
        this->InsertAtFront(std::move(dat));
    }

    template <typename Data>
    Data &StackLst<Data>::Top() const
    {
        return this->Front();
    }

    template <typename Data>
    void StackLst<Data>::Pop()
    {
        this->RemoveFromFront();
    }

    template <typename Data>
    Data StackLst<Data>::TopNPop()
    {
        return this->FrontNRemove();
    }

    template <typename Data>
    void lasd::StackLst<Data>::Clear()
    {
        List<Data>::Clear();
    }

    /* ************************************************************************** */
}
