
namespace lasd
{

    /* ************************************************************************** */

    //Default costructor
    template <typename Data>
    MatrixCSR<Data>::MatrixCSR()
    {
        rowsvec.Resize(1);
        rowsvec[0] = &head;
    }

    //Specific costructor
    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(const ulong &r, const ulong &c)
    {
        rows = r;
        cols = c;
        rowsvec.Resize(rows + 1);
        for (ulong i = 0; i <= rows; i++)
        {
            rowsvec[i] = &head;
        }
    }

    //Copy costructor
    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(const MatrixCSR<Data> &mat) : MatrixCSR<Data>(mat.rows, mat.cols)
    {
        if (mat.size != 0)
        {
            for (ulong r = 0; r < rows; r++)
            {
                for (Node **c = mat.rowsvec[r]; c != mat.rowsvec[r + 1]; c = &((*c)->nextptr))
                {
                    (*this)(r, (*c)->data.second) = (*c)->data.first;
                }
            }
        }
    }

    //Move costructor
    template <typename Data>
    MatrixCSR<Data>::MatrixCSR(MatrixCSR<Data> &&mat) noexcept : MatrixCSR<Data>()
    {
        std::swap(rowsvec, mat.rowsvec);
        std::swap(size, mat.size);
        std::swap(rows, mat.rows);
        std::swap(cols, mat.cols);
        std::swap(head, mat.head);
        for (ulong i = 0; i <= rows && rowsvec[i] == &mat.head; i++)
        {
            rowsvec[i] = &head;
        }
        mat.rowsvec[0] = &mat.head;
    }

    //Destructor
    template <typename Data>
    MatrixCSR<Data>::~MatrixCSR()
    {
        List<std::pair<Data, ulong>>::Clear();
    }

    //Copy assignment
    template <typename Data>
    MatrixCSR<Data> &MatrixCSR<Data>::operator=(const MatrixCSR<Data> &mat)
    {
        rows = mat.rows;
        cols = mat.cols;
        rowsvec.Resize(rows + 1);
        for (ulong i = 0; i <= rows; i++)
        {
            rowsvec[i] = &head;
        }
        if (mat.size != 0)
        {
            for (ulong r = 0; r < rows; r++)
            {
                for (Node **c = mat.rowsvec[r]; c != mat.rowsvec[r + 1]; c = &((*c)->nextptr))
                {
                    (*this)(r, (*c)->data.second) = (*c)->data.first;
                }
            }
        }
        return *this;
    }

    //Move assignment
    template <typename Data>
    MatrixCSR<Data> &MatrixCSR<Data>::operator=(MatrixCSR<Data> &&mat) noexcept
    {
        std::swap(rowsvec, mat.rowsvec);
        std::swap(rows, mat.rows);
        std::swap(cols, mat.cols);
        std::swap(size, mat.size);
        std::swap(head, mat.head);
        for (ulong i = 0; i <= mat.rows && rowsvec[i] == &mat.head; i++)
        {
            rowsvec[i] = &head;
        }
        for (ulong i = 0; i <= rows && mat.rowsvec[i] == &head; i++)
        {
            mat.rowsvec[i] = &mat.head;
        }
        return *this;
    }

    //Comparison operators
    template <typename Data>
    bool MatrixCSR<Data>::operator==(const MatrixCSR<Data> &mat) const noexcept
    {
        if (size == mat.size && rows == mat.rows && cols == mat.cols)
        {
            if (size == 0)
            {
                return true;
            }
            Node **scroll1;
            Node **scroll2;
            for (ulong r = 0; r < rows; r++)
            {
                scroll1 = rowsvec[r];
                scroll2 = mat.rowsvec[r];
                while (scroll1 != rowsvec[r + 1] && scroll2 != mat.rowsvec[r + 1])
                {
                    if ((*scroll1)->data.first != (*scroll2)->data.first || (*scroll1)->data.second != (*scroll2)->data.second)
                    {
                        return false;
                    }
                    scroll1 = &(*scroll1)->nextptr;
                    scroll2 = &(*scroll2)->nextptr;
                }
                if ((scroll1 == rowsvec[r + 1] && scroll2 != mat.rowsvec[r + 1]) || (scroll1 != rowsvec[r + 1] && scroll2 == mat.rowsvec[r + 1]))
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }

    template <typename Data>
    inline bool MatrixCSR<Data>::operator!=(const MatrixCSR<Data> &mat) const noexcept
    {
        return !(*this == mat);
    }

    //Row resize
    template <typename Data>
    void MatrixCSR<Data>::RowResize(const ulong &new_row_size)
    {
        if (new_row_size == 0)
        {
            List<std::pair<Data, ulong>>::Clear();
            rowsvec.Resize(1);
            rowsvec[0] = &head;
        }
        else
        {
            if (rows < new_row_size)
            {
                rowsvec.Resize(new_row_size + 1);
                Node **copy = rowsvec[rows];
                for (ulong i = rows + 1; i <= new_row_size; i++)
                {
                    rowsvec[i] = copy;
                }
            }
            else if (rows > new_row_size)
            {
                Node *node = *rowsvec[new_row_size];
                for (; node != nullptr; node = node->nextptr)
                {
                    size--;
                }
                delete *rowsvec[new_row_size];
                *rowsvec[new_row_size] = nullptr;
                rowsvec.Resize(new_row_size + 1);
            }
        }
        rows = new_row_size;
    }

    //Column resize
    template <typename Data>
    void MatrixCSR<Data>::ColumnResize(const ulong &new_col_size)
    {
        if (new_col_size < cols)
        {
            if (new_col_size == 0)
            {
                List<std::pair<Data, ulong>>::Clear();
                for (ulong i = 0; i <= rows; i++)
                {
                    rowsvec[i] = &head;
                }
            }
            else
            {
                Node **start = &head;
                ulong r = 1;
                while (r <= rows)
                {
                    Node **stop = rowsvec[r];
                    while (start != stop && (*start)->data.second < new_col_size)
                    {
                        start = &((*start)->nextptr);
                    }
                    if (start != stop)
                    {
                        Node *tmp = *start;
                        *start = *stop;
                        *stop = nullptr;
                        for (Node *scroll = tmp; scroll != nullptr; scroll = scroll->nextptr)
                        {
                            size--;
                        }
                        delete tmp;
                    }
                    for (; r <= rows && rowsvec[r] == stop; r++)
                    {
                        rowsvec[r] = start;
                    }
                }
            }
        }
        cols = new_col_size;
    }

    //Exists cell
    template <typename Data>
    bool MatrixCSR<Data>::ExistsCell(const ulong &r, const ulong &c) const noexcept
    {
        if (r < rows && c < cols && size != 0)
        {
            for (Node **node = rowsvec[r]; node != rowsvec[r + 1] && *node != nullptr; node = &((*node)->nextptr))
            {
                if ((*node)->data.second == c)
                {
                    return true;
                }
            }
        }
        return false;
    }

    //Operator() (non const)
    template <typename Data>
    Data &MatrixCSR<Data>::operator()(const ulong &r, const ulong &c)
    {
        if (r >= rows || c >= cols)
        {
            throw std::out_of_range("Out of range.");
        }
        Node **node = rowsvec[r];
        for (; node != rowsvec[r + 1] && (*node)->data.second <= c; node = &(*node)->nextptr)
        {
            if ((**node).data.second == c)
            {
                return (**node).data.first;
            }
        }
        std::pair<Data, ulong> pair;
        pair.second = c;
        Node *new_node = new Node(pair);
        if (*node == nullptr)
        {
            new_node->nextptr = nullptr;
        }
        else
        {
            new_node->nextptr = &(**node);
        }
        *node = new_node;
        if (node == rowsvec[r + 1]) //Inserisco in riga vuota oppure alla fine
        {
            ulong i = 0;
            Node **copy = rowsvec[r + 1];
            rowsvec[r + 1] = &(new_node->nextptr);
            while (r + i + 2 <= rows && copy == rowsvec[r + i + 2])
            {
                rowsvec[r + i + 2] = &(new_node->nextptr);
                i++;
            }
        }
        size++;
        return new_node->data.first;
    }

    //Operator() (const)
    template <typename Data>
    const Data &MatrixCSR<Data>::operator()(const ulong &r, const ulong &c) const
    {
        if (r >= rows || c >= cols)
        {
            throw std::out_of_range("Out of range.");
        }
        for (Node **node = rowsvec[r]; node != rowsvec[r + 1] && (*node)->data.second <= c; node = &((*node)->nextptr))
        {
            if ((**node).data.second == c)
            {
                return (**node).data.first;
            }
        }
        throw std::length_error("Length error.");
    }

    //Clear (from Container)
    template <typename Data>
    void MatrixCSR<Data>::Clear()
    {
        List<std::pair<Data, ulong>>::Clear();
        rowsvec.Resize(1);
        rowsvec[0] = &head;
        rows = 0;
        cols = 0;
    }

    //Map functions (pre, post) inherited from MappableContainer
    template <typename Data>
    void MatrixCSR<Data>::MapPreOrder(const MapFunctor fun, void *par)
    {
        List<std::pair<Data, ulong>>::MapPreOrder([&fun](std::pair<Data, ulong> &datx, void *parx)
                                                  { fun(datx.first, parx); },
                                                  par);
    }

    template <typename Data>
    void MatrixCSR<Data>::MapPostOrder(const MapFunctor fun, void *par)
    {
        List<std::pair<Data, ulong>>::MapPostOrder([&fun](std::pair<Data, ulong> &datx, void *parx)
                                                   { fun(datx.first, parx); },
                                                   par);
    }

    //Fold functions (pre, post) inherited from FoldableContainer
    template <typename Data>
    void MatrixCSR<Data>::FoldPreOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        List<std::pair<Data, ulong>>::FoldPreOrder([&fun](const std::pair<Data, ulong> &datx, const void *parx, void *accx)
                                                   { fun(datx.first, parx, accx); },
                                                   par, acc);
    }

    template <typename Data>
    void MatrixCSR<Data>::FoldPostOrder(const FoldFunctor fun, const void *par, void *acc) const
    {
        List<std::pair<Data, ulong>>::FoldPostOrder([&fun](const std::pair<Data, ulong> &datx, const void *parx, void *accx)
                                                    { fun(datx.first, parx, accx); },
                                                    par, acc);
    }

    /* ************************************************************************** */
}
