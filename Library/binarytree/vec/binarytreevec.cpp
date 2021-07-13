
namespace lasd
{

    /* ************************************************************************** */

    template <typename Data>
    Data &BinaryTreeVec<Data>::NodeVec::Element() noexcept
    {
        return value;
    }

    template <typename Data>
    const Data &BinaryTreeVec<Data>::NodeVec::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept
    {
        return ((2 * index + 1) < vecptr->Size());
    }

    template <typename Data>
    inline bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept
    {
        return ((2 * index + 2) < vecptr->Size());
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::LeftChild() const
    {
        if (!HasLeftChild())
        {
            throw std::out_of_range("Out of range.");
        }
        return *(*vecptr)[2 * index + 1];
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::NodeVec::RightChild() const
    {
        if (!HasRightChild())
        {
            throw std::out_of_range("Out of range.");
        }
        return *(*vecptr)[2 * index + 2];
    }

    template <typename Data>
    BinaryTreeVec<Data>::NodeVec::NodeVec(const Data &dat, const ulong &ind, Vector<BinaryTreeVec<Data>::NodeVec *> *ptr)
    {
        value = dat;
        index = ind;
        vecptr = ptr;
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data> &con)
    {
        size = con.Size();
        btreevecptr = new Vector<NodeVec *>(size);
        for (ulong i = 0; i < size; i++)
        {
            (*btreevecptr)[i] = new NodeVec(con[i], i, btreevecptr);
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data> &btree)
    {
        size = btree.size;
        btreevecptr = new Vector<NodeVec *>(size);
        for (ulong i = 0; i < size; i++)
        {
            (*btreevecptr)[i] = new NodeVec(((*btree.btreevecptr)[i])->Element(), i, btreevecptr);
        }
    }

    template <typename Data>
    BinaryTreeVec<Data>::BinaryTreeVec(lasd::BinaryTreeVec<Data> &&btree) noexcept
    {
        std::swap(size, btree.size);
        std::swap(btreevecptr, btree.btreevecptr);
    }

    template <typename Data>
    BinaryTreeVec<Data>::~BinaryTreeVec()
    {
        Clear();
        delete btreevecptr;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data> &btree)
    {
        BinaryTreeVec<Data> *tmpbtree = new BinaryTreeVec<Data>(btree);
        std::swap(*tmpbtree, *this);
        delete tmpbtree;
        return *this;
    }

    template <typename Data>
    BinaryTreeVec<Data> &BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data> &&btree) noexcept
    {
        std::swap(size, btree.size);
        std::swap(btreevecptr, btree.btreevecptr);
        return *this;
    }

    template <typename Data>
    bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data> &btree) const noexcept
    {
        if (size == btree.size)
        {
            for (ulong i = 0; i < size; ++i)
            {
                if (((*btreevecptr)[i])->Element() != ((*btree.btreevecptr)[i])->Element())
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
    inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data> &btree) const noexcept
    {
        return !(*this == btree);
    }

    template <typename Data>
    typename BinaryTreeVec<Data>::NodeVec &BinaryTreeVec<Data>::Root() const
    {
        if (size == 0)
        {
            throw std::length_error("Access to an empty btree.");
        }
        return *(*btreevecptr)[0];
    }

    template <typename Data>
    void BinaryTreeVec<Data>::Clear()
    {
        for (ulong i = 0; i < size; i++)
        {
            delete (*btreevecptr)[i];
        }
        size = 0;
    }

    template <class Data>
    void BinaryTreeVec<Data>::MapBreadth(const typename MappableContainer<Data>::MapFunctor fun, void *par)
    {
        for (ulong i = 0; i < size; i++)
        {
            fun(((*btreevecptr)[i])->Element(), par);
        }
    }

    template <typename Data>
    void BinaryTreeVec<Data>::FoldBreadth(const typename FoldableContainer<Data>::FoldFunctor fun, const void *par, void *acc) const
    {
        for (ulong i = 0; i < size; i++)
        {
            fun(((*btreevecptr)[i])->Element(), par, acc);
        }
    }

    /* ************************************************************************** */

}
