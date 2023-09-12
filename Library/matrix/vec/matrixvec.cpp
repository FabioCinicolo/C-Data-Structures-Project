
namespace lasd
{

    // Specific Costructor
    template <typename Data>
    MatrixVec<Data>::MatrixVec(const ulong &r, const ulong &c) : Vector<Data>::Vector(r * c)
    {
        rows = r;
        cols = c;
    }

    // Copy costructor

    template <typename Data>
    MatrixVec<Data>::MatrixVec(const MatrixVec<Data> &mat) : Vector<Data>::Vector(mat)
    {
        rows = mat.rows;
        cols = mat.cols;
    }

    // Move costructor

    template <typename Data>
    MatrixVec<Data>::MatrixVec(MatrixVec<Data> &&mat) noexcept : Vector<Data>::Vector(std::move(mat))
    {
        std::swap(rows, mat.rows);
        std::swap(cols, mat.cols);
    }

    // Copy assignment

    template <typename Data>
    MatrixVec<Data> &MatrixVec<Data>::operator=(const MatrixVec<Data> &mat)
    {
        Vector<Data>::operator=(mat);
        rows = mat.rows;
        cols = mat.cols;
        return *this;
    }

    // Move assignment

    template <typename Data>
    MatrixVec<Data> &MatrixVec<Data>::operator=(MatrixVec<Data> &&mat) noexcept
    {
        Vector<Data>::operator=(std::move(mat));
        std::swap(rows, mat.rows);
        std::swap(cols, mat.cols);
        return *this;
    }

    // Comparison operators

    template <typename Data>
    bool MatrixVec<Data>::operator==(const MatrixVec<Data> &mat) const noexcept
    {
        return Vector<Data>::operator==(mat);
    }

    template <typename Data>
    inline bool MatrixVec<Data>::operator!=(const MatrixVec<Data> &mat) const noexcept
    {
        return !(*this == mat);
    }

    // Row resize

    template <typename Data>
    void MatrixVec<Data>::RowResize(const ulong &new_row_size)
    {
        if (new_row_size == 0)
        {
            Vector<Data>::Clear();
        }
        else
        {
            Vector<Data>::Resize(new_row_size * cols);
        }
        rows = new_row_size;
    }

    // Column resize

    template <typename Data>
    void MatrixVec<Data>::ColumnResize(const ulong &new_col_size)
    {
        if (new_col_size != cols)
        {
            Data *tmpElements = new Data[rows * new_col_size];
            if (new_col_size > cols)
            {
                for (ulong i = 0, k = 0; i < rows; i++)
                {
                    for (ulong j = 0; j < new_col_size; j++)
                    {
                        if (j < cols)
                        {
                            std::swap((tmpElements)[i * new_col_size + j], (*this)[k]);
                            k++;
                        }
                        else
                        {
                            Data el{};
                            std::swap((tmpElements)[i * new_col_size + j], el);
                        }
                    }
                }
            }
            else
            {
                for (ulong i = 0, k = 0; i < rows; i++, k = k + (cols - new_col_size))
                {
                    for (ulong j = 0; j < new_col_size; j++, k++)
                    {
                        std::swap((tmpElements)[i * new_col_size + j], (*this)[k]);
                    }
                }
            }
            std::swap(Elements, tmpElements);
            delete[] tmpElements;
            cols = new_col_size;
            size = rows * cols;
        }
    }

    // Operator() (const)

    template <typename Data>
    const Data &MatrixVec<Data>::operator()(const ulong &row, const ulong &col) const
    {
        if (ExistsCell(row, col))
        {
            return Elements[row * cols + col];
        }
        throw std::out_of_range("Out of range.");
    }

    // Operator() (not const)

    template <typename Data>
    Data &MatrixVec<Data>::operator()(const ulong &row, const ulong &col)
    {
        return const_cast<Data &>(static_cast<const MatrixVec<Data> *>(this)->operator()(row, col));
    }

    // Clear

    template <typename Data>
    void MatrixVec<Data>::Clear()
    {
        Vector<Data>::Clear();
        rows = 0;
        cols = 0;
    }

    // Exists
    template <typename Data>
    inline bool MatrixVec<Data>::ExistsCell(const ulong &row, const ulong &col) const noexcept
    {
        return ((row < rows) && (col < cols));
    }

}
