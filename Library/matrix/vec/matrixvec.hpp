
#ifndef MATRIXVEC_HPP
#define MATRIXVEC_HPP

/* ************************************************************************** */

#include "../matrix.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class MatrixVec : virtual public Matrix<Data>, virtual protected Vector<Data>
  {
  private:
    // ...

  protected:
    using Matrix<Data>::rows;
    using Matrix<Data>::cols;
    using Vector<Data>::Elements;
    using Vector<Data>::size;

  public:
    // Specific constructor
    MatrixVec(const ulong &, const ulong &);

    /* ************************************************************************ */

    // Default constructors
    MatrixVec() = default;

    /* ************************************************************************ */

    // Copy constructor
    MatrixVec(const MatrixVec &);

    // Move constructor
    MatrixVec(MatrixVec &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~MatrixVec() = default;

    /* ************************************************************************ */

    // Copy assignment
    MatrixVec &operator=(const MatrixVec &);

    // Move assignment
    MatrixVec &operator=(MatrixVec &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const MatrixVec &) const noexcept;
    inline bool operator!=(const MatrixVec &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Matrix)

    void RowResize(const ulong &) override;    // Override Matrix member
    void ColumnResize(const ulong &) override; // Override Matrix member

    inline bool ExistsCell(const ulong &, const ulong &) const noexcept override; // Override Matrix member (should not throw exceptions)

    Data &operator()(const ulong &, const ulong &) override;             // Override Matrix member (mutable access to the element; throw out_of_range when out of range)
    const Data &operator()(const ulong &, const ulong &) const override; // Override Matrix member (immutable access to the element; throw out_of_range when out of range)
    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from MappableContainer)

    using Vector<Data>::MapPreOrder;
    using Vector<Data>::MapPostOrder;
    // type MapPreOrder(arguments) specifiers; // Override MappableContainer member
    // type MapPostOrder(arguments) specifiers; // Override MappableContainer member

    /* ************************************************************************ */

    // Specific member functions (inherited from FoldableContainer)
    using Vector<Data>::FoldPreOrder;
    using Vector<Data>::FoldPostOrder;
    // type FoldPreOrder(arguments) specifiers; // Override FoldableContainer member
    // type FoldPostOrder(arguments) specifiers; // Override FoldableContainer member
  };

  /* ************************************************************************** */

}

#include "matrixvec.cpp"

#endif
