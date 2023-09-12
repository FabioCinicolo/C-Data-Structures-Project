
namespace lasd
{

    template <typename Data>
    inline const ulong &lasd::Matrix<Data>::RowNumber() const noexcept
    {
        return rows;
    }

    template <typename Data>
    inline const ulong &lasd::Matrix<Data>::ColumnNumber() const noexcept
    {
        return cols;
    }

}
