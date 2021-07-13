
namespace lasd
{

    /* ************************************************************************** */
    //NODE LNK
    template <typename Data>
    Data &BinaryTreeLnk<Data>::NodeLnk::Element() noexcept
    {
        return value;
    }

    template <class Data>
    const Data &BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept
    {
        return value;
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept
    {
        return (leftptr != nullptr);
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept
    {
        return (rightptr != nullptr);
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data &&dat) noexcept
    {
        value = std::move(dat);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::LeftChild() const
    {
        if (HasLeftChild())
        {
            return *leftptr;
        }
        throw std::out_of_range("Out of range.");
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::NodeLnk::RightChild() const
    {
        if (HasRightChild())
        {
            return *rightptr;
        }
        throw std::out_of_range("Out of range.");
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data &data)
    {
        value = data;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::NodeLnk::~NodeLnk()
    {
        delete leftptr;
        delete rightptr;
    }

    //BINARY TREE LNK
    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data> &con)
    {
        if (con.Size() != 0)
        {
            size = con.Size();
            root = InsertLevelOrder(con, root, 0, con.Size());
        }
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BinaryTreeLnk<Data>::InsertLevelOrder(const LinearContainer<Data> &con, BinaryTreeLnk<Data>::NodeLnk *rt, ulong start, ulong size)
    {
        if (start < size)
        {
            NodeLnk *temp = new NodeLnk(con[start]);
            rt = temp;
            rt->leftptr = InsertLevelOrder(con, rt->leftptr, 2 * start + 1, size);
            rt->rightptr = InsertLevelOrder(con, rt->rightptr, 2 * start + 2, size);
        }
        return rt;
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data> &btree)
    {
        size = btree.size;
        if (size != 0) //Errore 2 Libreria 4(fixato).
        {
            root = GetRootFromCopyInOrder(&btree.Root());
        }
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk *BinaryTreeLnk<Data>::GetRootFromCopyInOrder(BinaryTreeLnk<Data>::NodeLnk *node)
    {
        if (node == nullptr)
        {
            return nullptr;
        }
        else
        {
            NodeLnk *temp = new NodeLnk(node->value);
            temp->leftptr = GetRootFromCopyInOrder(node->leftptr);
            temp->rightptr = GetRootFromCopyInOrder(node->rightptr);
            return temp;
        }
    }

    template <typename Data>
    BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data> &&btree) noexcept
    {
        std::swap(size, btree.size);
        std::swap(root, btree.root);
    }

    template <typename Data>
    BinaryTreeLnk<Data>::~BinaryTreeLnk()
    {
        delete root;
    }

    template <class Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data> &btree)
    {
        BinaryTreeLnk<Data> *tmpbtree = new BinaryTreeLnk<Data>(btree);
        std::swap(*tmpbtree, *this);
        delete tmpbtree;
        return *this;
    }

    template <typename Data>
    BinaryTreeLnk<Data> &BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data> &&btree) noexcept
    {
        std::swap(size, btree.size);
        std::swap(root, btree.root);
        return *this;
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data> &btree) const noexcept
    {
        return BinaryTree<Data>::operator==(btree);
    }

    template <typename Data>
    inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data> &btree) const noexcept
    {
        return !(*this == btree);
    }

    template <typename Data>
    typename BinaryTreeLnk<Data>::NodeLnk &BinaryTreeLnk<Data>::Root() const
    {
        if (size != 0)
        {
            return *root;
        }
        throw std::length_error("Access to an empty Binary tree.");
    }

    template <typename Data>
    void BinaryTreeLnk<Data>::Clear()
    {
        if (size != 0)
        {
            delete root;
            size = 0;
            root = nullptr;
        }
    }
    /* ************************************************************************** */

}
