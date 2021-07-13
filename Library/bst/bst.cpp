
namespace lasd
{

    /* ************************************************************************** */
    //Specific costructor
    template <typename Data>
    BST<Data>::BST(const LinearContainer<Data> &con)
    {
        for (ulong index = 0; index < con.Size(); index++)
        {
            Insert(con[index]);
        }
    }
    //Copy costructor
    template <typename Data>
    BST<Data>::BST(const BST<Data> &bst) : BinaryTreeLnk<Data>::BinaryTreeLnk(bst)
    {
    }
    //Move costructor
    template <typename Data>
    BST<Data>::BST(BST<Data> &&bst) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(bst))
    {
    }
    //Copy assignment
    template <typename Data>
    BST<Data> &lasd::BST<Data>::operator=(const BST<Data> &bst)
    {
        BinaryTreeLnk<Data>::operator=(bst);
        return *this;
    }
    //Move assignment
    template <typename Data>
    BST<Data> &lasd::BST<Data>::operator=(BST<Data> &&bst) noexcept
    {
        BinaryTreeLnk<Data>::operator=(std::move(bst));
        return *this;
    }
    //Comparison operators
    template <typename Data>
    bool BST<Data>::operator==(const BST<Data> &bst) const noexcept
    {
        if (size == bst.Size())
        {
            if (size == 0)
            {
                return true;
            }
            BTInOrderIterator<Data> it1(*this);
            BTInOrderIterator<Data> it2(bst);
            for (; !it1.Terminated(); ++it1, ++it2)
            {
                if (*it1 != *it2)
                {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
    template <typename Data>
    inline bool BST<Data>::operator!=(const BST<Data> &bst) const noexcept
    {
        return !(*this == bst);
    }
    //Specific member functions
    template <typename Data>
    void BST<Data>::Insert(const Data &data) noexcept
    {
        NodeLnk **node = &FindPointerTo(root, data);
        if (*node == nullptr)
        {
            *node = new NodeLnk(data);
            size++;
        }
    }

    template <typename Data>
    void BST<Data>::Insert(Data &&data) noexcept
    {
        NodeLnk **node = &FindPointerTo(root, data);
        if (*node == nullptr)
        {
            *node = new NodeLnk(std::move(data));
            size++;
        }
    }

    template <typename Data>
    void BST<Data>::Remove(const Data &data) noexcept
    {
        delete Detach(FindPointerTo(root, data));
    }

    template <typename Data>
    const Data &BST<Data>::Min() const
    {
        if (root != nullptr)
        {
            return FindPointerToMin(root)->value;
        }
        throw std::length_error("Access to an empty BST.");
    }

    template <typename Data>
    Data BST<Data>::MinNRemove()
    {
        if (root != nullptr)
        {
            return DataNDelete(DetachMin(root));
        }

        throw std::length_error("Access to an empty BST.");
    }

    template <typename Data>
    void BST<Data>::RemoveMin()
    {
        if (root != nullptr)
        {
            delete DetachMin(root);
        }
        else
        {
            throw std::length_error("Access to an empty BST.");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Max() const
    {
        if (root != nullptr)
        {
            return FindPointerToMax(root)->value;
        }
        throw std::length_error("Access to an empty BST.");
    }

    template <typename Data>
    Data BST<Data>::MaxNRemove()
    {
        if (root != nullptr)
        {
            return DataNDelete(DetachMax(root));
        }
        throw std::length_error("Access to an empty BST.");
    }

    template <typename Data>
    void BST<Data>::RemoveMax()
    {
        if (root != nullptr)
        {
            delete DetachMax(root);
        }
        else
        {
            throw std::length_error("Access to an empty BST.");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Predecessor(const Data &data) const
    {
        NodeLnk *const *pred = FindPointerToPredecessor(root, data);
        if (pred != nullptr)
        {
            return (*pred)->value;
        }
        throw std::length_error("Predecessor not found.");
    }

    template <typename Data>
    Data BST<Data>::PredecessorNRemove(const Data &data)
    {
        NodeLnk **pred = FindPointerToPredecessor(root, data);
        if (pred != nullptr)
        {
            return DataNDelete(Detach(*pred));
        }
        throw std::length_error("Predecessor not found.");
    }

    template <typename Data>
    void BST<Data>::RemovePredecessor(const Data &data)
    {
        NodeLnk **pred = FindPointerToPredecessor(root, data);
        if (pred != nullptr)
        {
            delete (Detach(*pred));
        }
        else
        {
            throw std::length_error("Predecessor not found.");
        }
    }

    template <typename Data>
    const Data &BST<Data>::Successor(const Data &data) const
    {
        NodeLnk *const *sux = FindPointerToSuccessor(root, data);
        if (sux != nullptr)
        {
            return (*sux)->value;
        }
        throw std::length_error("Successor not found.");
    }

    template <typename Data>
    Data BST<Data>::SuccessorNRemove(const Data &data)
    {
        NodeLnk **sux = FindPointerToSuccessor(root, data);
        if (sux != nullptr)
        {
            return DataNDelete(Detach(*sux));
        }
        throw std::length_error("Successor not found.");
    }

    template <typename Data>
    void BST<Data>::RemoveSuccessor(const Data &data)
    {
        NodeLnk **sux = FindPointerToSuccessor(root, data);
        if (sux != nullptr)
        {
            delete (Detach(*sux));
        }
        {
            throw std::length_error("Successor not found.");
        }
    }

    //Exists

    template <typename Data>
    bool BST<Data>::Exists(const Data &data) const noexcept
    {
        return (FindPointerTo(root, data) != nullptr);
    }

    //Auxiliary protected functions

    template <typename Data>
    Data BST<Data>::DataNDelete(NodeLnk *rt)
    {
        Data val{};
        std::swap(val, rt->value);
        delete rt;
        return val;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::Detach(NodeLnk *&rt) noexcept
    {
        if (rt != nullptr)
        {
            if (!rt->HasLeftChild())
            {
                return SkipOnRight(rt);
            }
            else if (!rt->HasRightChild())
            {
                return SkipOnLeft(rt);
            }
            else
            {
                NodeLnk *minptr = DetachMin(rt->rightptr); //Errore 1 Libreria 4(fixato) [Facevo DetachMin(rt)].
                std::swap(rt->value, minptr->value);
                return minptr;
            }
        }
        return nullptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMin(NodeLnk *&rt) noexcept
    {
        return SkipOnRight(FindPointerToMin(rt));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::DetachMax(NodeLnk *&rt) noexcept
    {
        return SkipOnLeft(FindPointerToMax(rt));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::SkipOnLeft(NodeLnk *&rt) noexcept
    {
        NodeLnk *node = nullptr;
        if (rt != nullptr)
        {
            std::swap(node, rt->leftptr);
            std::swap(node, rt);
            size--;
        }
        return node;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *BST<Data>::SkipOnRight(NodeLnk *&rt) noexcept
    {
        NodeLnk *node = nullptr;
        if (rt != nullptr)
        {
            std::swap(node, rt->rightptr);
            std::swap(node, rt);
            size--;
        }
        return node;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMin(NodeLnk *const &rt) const noexcept
    {
        NodeLnk *const *retptr = &rt;
        if ((*retptr) != nullptr)
        {
            while ((*retptr)->leftptr != nullptr)
            {
                retptr = &((*retptr)->leftptr);
            }
        }
        return *retptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMin(NodeLnk *&rt) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(rt));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerToMax(NodeLnk *&rt) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(rt));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerToMax(NodeLnk *const &rt) const noexcept
    {
        NodeLnk *const *retptr = &rt;
        if ((*retptr) != nullptr)
        {
            while ((*retptr)->rightptr != nullptr)
            {
                retptr = &((*retptr)->rightptr);
            }
        }
        return *retptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *&BST<Data>::FindPointerTo(NodeLnk *&rt, const Data &data) noexcept
    {
        return const_cast<NodeLnk *&>(static_cast<const BST<Data> *>(this)->FindPointerTo(rt, data));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const &BST<Data>::FindPointerTo(NodeLnk *const &rt, const Data &data) const noexcept
    {
        NodeLnk *const *retptr = &rt;
        while ((*retptr) != nullptr && (*retptr)->value != data)
        {
            if (data < (*retptr)->value)
            {
                retptr = &((*retptr)->leftptr);
            }
            else
            {
                retptr = &((*retptr)->rightptr);
            }
        }
        return *retptr;
    }

    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToPredecessor(NodeLnk *&rt, const Data &data) noexcept
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(rt, data));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToPredecessor(NodeLnk *const &rt, const Data &data) const noexcept
    {
        NodeLnk *const *searchptr = &rt;
        NodeLnk *const *predcand = nullptr;
        while ((*searchptr) != nullptr && (*searchptr)->value != data)
        {
            if ((*searchptr)->value < data)
            {
                predcand = searchptr;
                searchptr = &((*searchptr)->rightptr);
            }
            else if ((*searchptr)->value > data)
            {
                searchptr = &((*searchptr)->leftptr);
            }
        }
        if ((*searchptr) != nullptr && (*searchptr)->HasLeftChild())
        {
            predcand = &FindPointerToMax((*searchptr)->leftptr);
        }
        return predcand;
    }
    template <typename Data>
    typename BST<Data>::NodeLnk **BST<Data>::FindPointerToSuccessor(NodeLnk *&rt, const Data &data) noexcept
    {
        return const_cast<NodeLnk **>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(rt, data));
    }

    template <typename Data>
    typename BST<Data>::NodeLnk *const *BST<Data>::FindPointerToSuccessor(NodeLnk *const &rt, const Data &data) const noexcept
    {
        NodeLnk *const *searchptr = &rt;
        NodeLnk *const *suxcand = nullptr;
        while ((*searchptr) != nullptr && (*searchptr)->value != data)
        {
            if ((*searchptr)->value < data)
            {
                searchptr = &((*searchptr)->rightptr);
            }
            else if ((*searchptr)->value > data)
            {
                suxcand = searchptr;
                searchptr = &((*searchptr)->leftptr);
            }
        }
        if ((*searchptr) != nullptr && (*searchptr)->HasRightChild())
        {
            suxcand = &FindPointerToMin((*searchptr)->rightptr);
        }
        return suxcand;
    }
    /* ************************************************************************** */

}
