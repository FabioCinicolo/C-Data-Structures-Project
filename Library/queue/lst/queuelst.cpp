
namespace lasd
{

    // Specific costructor

    template <typename Data>
    QueueLst<Data>::QueueLst(const LinearContainer<Data> &con) : List<Data>::List(con)
    {
    }

    // Copy costructor

    template <typename Data>
    QueueLst<Data>::QueueLst(const QueueLst<Data> &queue) : List<Data>::List(queue)
    {
    }

    // Move costructor

    template <typename Data>
    QueueLst<Data>::QueueLst(QueueLst<Data> &&queue) noexcept : List<Data>::List(std::move(queue))
    {
    }

    // Copy assignment

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(const QueueLst<Data> &queue)
    {
        List<Data>::operator=(queue);
        return *this;
    }

    // Move assignment

    template <typename Data>
    QueueLst<Data> &QueueLst<Data>::operator=(QueueLst<Data> &&queue) noexcept
    {
        List<Data>::operator=(std::move(queue));
        return *this;
    }

    // Comparison operators

    template <typename Data>
    bool lasd::QueueLst<Data>::operator==(const QueueLst<Data> &queue) const noexcept
    {
        return List<Data>::operator==(queue);
    }

    template <typename Data>
    inline bool lasd::QueueLst<Data>::operator!=(const QueueLst<Data> &queue) const noexcept
    {
        return !(*this == queue);
    }

    // Enqueue

    template <typename Data>
    void QueueLst<Data>::Enqueue(const Data &dat)
    {
        this->InsertAtBack(dat);
    }

    template <typename Data>
    void QueueLst<Data>::Enqueue(Data &&dat) noexcept
    {
        this->InsertAtBack(std::move(dat));
    }

    // Head

    template <typename Data>
    Data &QueueLst<Data>::Head() const
    {
        return this->Front();
    }

    // Dequeue

    template <typename Data>
    void QueueLst<Data>::Dequeue()
    {
        this->RemoveFromFront();
    }

    // HeadNDequeue

    template <typename Data>
    Data lasd::QueueLst<Data>::HeadNDequeue()
    {
        return this->FrontNRemove();
    }

    // Clear

    template <typename Data>
    void QueueLst<Data>::Clear()
    {
        List<Data>::Clear();
    }

}
