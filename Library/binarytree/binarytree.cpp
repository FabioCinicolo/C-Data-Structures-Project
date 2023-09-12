
#include "../queue/vec/queuevec.hpp"

namespace lasd
{
    template <typename Data>
    bool BinaryTree<Data>::Node::operator==(const BinaryTree<Data>::Node &node) const noexcept
    {
        if (Element() == node.Element())
        {
            if (HasLeftChild() && node.HasLeftChild() && HasRightChild() && node.HasRightChild())
            {
                return LeftChild() == node.LeftChild() && RightChild() == node.RightChild();
            }
            else if (HasLeftChild() && node.HasLeftChild())
            {
                return LeftChild() == node.LeftChild();
            }
            else if (HasRightChild() && node.HasRightChild())
            {
                return RightChild() == node.RightChild();
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }

    template <typename Data>
    inline bool BinaryTree<Data>::Node::operator!=(const BinaryTree<Data>::Node &node) const noexcept
    {
        return !(*this == node);
    }

    template <typename Data>
    inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept
    {
        return ((!HasLeftChild()) && (!HasRightChild()));
    }

    template <typename Data>
    bool BinaryTree<Data>::operator==(const BinaryTree<Data> &btree) const noexcept
    {
        if (size == btree.size)
        {
            if (size == 0)
            {
                return true;
            }
            return (Root() == btree.Root());
        }
        return false;
    }

    template <typename Data>
    inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data> &btree) const noexcept
    {
        return !(*this == btree);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void *par, Node &node)
    {
        fun(node.Element(), par);
        if (node.HasLeftChild())
        {
            MapPreOrder(fun, par, node.LeftChild());
        }
        if (node.HasRightChild())
        {
            MapPreOrder(fun, par, node.RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPreOrder(const MapFunctor fun, void *par)
    {
        if (size != 0)
        {
            MapPreOrder(fun, par, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void *par, Node &node)
    {
        if (node.HasLeftChild())
        {
            MapPostOrder(fun, par, node.LeftChild());
        }
        if (node.HasRightChild())
        {
            MapPostOrder(fun, par, node.RightChild());
        }
        fun(node.Element(), par);
    }

    template <typename Data>
    void BinaryTree<Data>::MapPostOrder(const MapFunctor fun, void *par)
    {
        if (size != 0)
        {
            MapPostOrder(fun, par, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void *par)
    {
        if (size != 0)
        {
            MapInOrder(fun, par, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapInOrder(const MapFunctor fun, void *par, Node &node)
    {
        if (node.HasLeftChild())
        {
            MapInOrder(fun, par, node.LeftChild());
        }
        fun(node.Element(), par);
        if (node.HasRightChild())
        {
            MapInOrder(fun, par, node.RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::MapBreadth(const MapFunctor fun, void *par)
    {
        QueueLst<Node *> queue;
        Node *node;
        if (size != 0)
        {
            queue.Enqueue(&Root());
        }
        while (!queue.Empty())
        {
            node = queue.HeadNDequeue();
            fun(node->Element(), par);
            if (node->HasLeftChild())
            {
                queue.Enqueue(&node->LeftChild());
            }
            if (node->HasRightChild())
            {
                queue.Enqueue(&node->RightChild());
            }
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        if (size != 0)
        {
            FoldPreOrder(fun, par, acc, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPreOrder(const FoldFunctor fun, const void *par, void *acc, Node &node) const
    {
        fun(node.Element(), par, acc);
        if (node.HasLeftChild())
        {
            FoldPreOrder(fun, par, acc, node.LeftChild());
        }
        if (node.HasRightChild())
        {
            FoldPreOrder(fun, par, acc, node.RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        if (size != 0)
        {
            FoldPostOrder(fun, par, acc, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldPostOrder(const FoldFunctor fun, const void *par, void *acc, Node &node) const
    {
        if (node.HasLeftChild())
        {
            FoldPostOrder(fun, par, acc, node.LeftChild());
        }
        if (node.HasRightChild())
        {
            FoldPostOrder(fun, par, acc, node.RightChild());
        }
        fun(node.Element(), par, acc);
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        if (size != 0)
        {
            FoldInOrder(fun, par, acc, Root());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldInOrder(const FoldFunctor fun, const void *par, void *acc, Node &node) const
    {
        if (node.HasLeftChild())
        {
            FoldInOrder(fun, par, acc, node.LeftChild());
        }
        fun(node.Element(), par, acc);
        if (node.HasRightChild())
        {
            FoldInOrder(fun, par, acc, node.RightChild());
        }
    }

    template <typename Data>
    void BinaryTree<Data>::FoldBreadth(const FoldFunctor fun, const void *par, void *acc) const
    {
        QueueLst<Node *> queue;
        Node *node;
        if (size != 0)
        {
            queue.Enqueue(&Root());
        }
        while (!queue.Empty())
        {
            node = queue.HeadNDequeue();
            fun(node->Element(), par, acc);
            if (node->HasLeftChild())
            {
                queue.Enqueue(&node->LeftChild());
            }
            if (node->HasRightChild())
            {
                queue.Enqueue(&node->RightChild());
            }
        }
    }

    // BREADTH ITERATOR

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data> &btree)
    {
        if (!btree.Empty())
            node = &btree.Root();
    }

    template <typename Data>
    lasd::BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator<Data> &it)
    {
        node = it.node;
        queue = it.queue;
    }

    template <typename Data>
    BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(queue, it.queue);
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(const BTBreadthIterator<Data> &it)
    {
        node = it.node;
        queue = it.queue;
        return *this;
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator=(BTBreadthIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(queue, it.queue);
        return *this;
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data> &it) const noexcept
    {
        return ((node == it.node) && (queue == it.queue));
    }

    template <typename Data>
    inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data> &it) const noexcept
    {
        return !(*this == it);
    }

    template <typename Data>
    Data &BTBreadthIterator<Data>::operator*() const
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        return node->Element();
    }

    template <typename Data>
    bool BTBreadthIterator<Data>::Terminated() const noexcept
    {
        return (node == nullptr);
    }

    template <typename Data>
    BTBreadthIterator<Data> &BTBreadthIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        if (node->HasLeftChild())
        {
            queue.Enqueue(&node->LeftChild());
        }
        if (node->HasRightChild())
        {
            queue.Enqueue(&node->RightChild());
        }
        if (!queue.Empty())
        {
            node = queue.HeadNDequeue();
        }
        else
        {
            node = nullptr;
        }
        return *this;
    }

    // PRE ORDER ITERATOR

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data> &btree)
    {
        if (!btree.Empty())
            node = &btree.Root();
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
    }

    template <typename Data>
    BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
        return *this;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator=(BTPreOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
        return *this;
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data> &it) const noexcept
    {
        return ((node == it.node) && (stack == it.stack));
    }

    template <typename Data>
    inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data> &it) const noexcept
    {
        return !(*this == it);
    }

    template <typename Data>
    Data &BTPreOrderIterator<Data>::operator*() const
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        return node->Element();
    }

    template <typename Data>
    bool BTPreOrderIterator<Data>::Terminated() const noexcept
    {
        return node == nullptr;
    }

    template <typename Data>
    BTPreOrderIterator<Data> &BTPreOrderIterator<Data>::operator++()
    {

        if (Terminated())
            throw std::out_of_range("Out of range.");

        if (node->HasLeftChild())
        {
            if (node->HasRightChild())
                stack.Push(&node->RightChild());
            node = &node->LeftChild();
        }
        else if (node->HasRightChild())
            node = &node->RightChild();
        else if (!stack.Empty())
            node = stack.TopNPop();
        else
            node = nullptr;
        return *this;
    }

    // IN ORDER ITERATOR
    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data> &btree)
    {
        if (!btree.Empty())
            UpdateCurrWithLeftMostNode(&btree.Root());
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
    }

    template <typename Data>
    BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(const BTInOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
        return *this;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator=(BTInOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
        return *this;
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data> &it) const noexcept
    {
        return ((node == it.node) && (stack == it.stack));
    }

    template <typename Data>
    inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data> &it) const noexcept
    {
        return !(*this == it);
    }

    template <typename Data>
    Data &BTInOrderIterator<Data>::operator*() const
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        return node->Element();
    }

    template <typename Data>
    bool BTInOrderIterator<Data>::Terminated() const noexcept
    {
        return node == nullptr;
    }

    template <typename Data>
    BTInOrderIterator<Data> &BTInOrderIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        if (!node->HasRightChild())
        {
            if (!stack.Empty())
            {
                node = stack.TopNPop();
            }
            else
            {
                node = nullptr;
            }
        }
        else
        {
            UpdateCurrWithLeftMostNode(&node->RightChild());
        }
        return *this;
    }

    template <typename Data>
    void BTInOrderIterator<Data>::UpdateCurrWithLeftMostNode(typename BinaryTree<Data>::Node *rt)
    {
        node = rt;
        while (node->HasLeftChild())
        {
            stack.Push(node);
            node = &node->LeftChild();
        }
    }

    // POST ORDER ITERATOR
    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data> &btree)
    {
        if (!btree.Empty())
            UpdateCurrWithLeftMostLeaf(&btree.Root());
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
    }

    template <typename Data>
    BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator<Data> &it)
    {
        node = it.node;
        stack = it.stack;
        return *this;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator=(BTPostOrderIterator<Data> &&it) noexcept
    {
        std::swap(node, it.node);
        std::swap(stack, it.stack);
        return *this;
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data> &it) const noexcept
    {
        return (node == it.node && stack == it.stack);
    }

    template <typename Data>
    inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data> &it) const noexcept
    {
        return !(*this == it);
    }

    template <class Data>
    Data &BTPostOrderIterator<Data>::operator*() const
    {
        if (Terminated())
        {
            throw std::out_of_range("Out of range.");
        }
        return node->Element();
    }

    template <typename Data>
    bool BTPostOrderIterator<Data>::Terminated() const noexcept
    {
        return node == nullptr;
    }

    template <typename Data>
    BTPostOrderIterator<Data> &BTPostOrderIterator<Data>::operator++()
    {
        if (Terminated())
        {
            throw std::out_of_range("BTPostOrderIterator out of range.");
        }

        if (!stack.Empty())
        {

            if (stack.Top()->HasRightChild())
            {
                if (node == &stack.Top()->RightChild()) // A leaf is reached
                    node = stack.TopNPop();
                else
                {
                    node = &stack.Top()->RightChild();
                    LeftMostLeaf(node);
                }
            }
            else
                node = stack.TopNPop();
        }
        else
        {
            node = nullptr;
        }

        return *this;
    }

    template <typename Data>
    void BTPostOrderIterator<Data>::UpdateCurrWithLeftMostLeaf(typename BinaryTree<Data>::Node *rt)
    {
        node = rt;
        while (!node->IsLeaf())
        {
            if (node->HasLeftChild())
            {
                stack.Push(node);
                node = &node->LeftChild();
            }
            else if (node->HasRightChild())
            {
                stack.Push(node);
                node = &node->RightChild();
            }
        }
    }
}
