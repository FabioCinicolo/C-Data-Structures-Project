
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd
{

  template <typename Data>
  class BinaryTreeVec : virtual public BinaryTree<Data>
  {

  private:
    // ...

  protected:
    struct NodeVec : virtual public BinaryTree<Data>::Node
    {

    private:
      // ...

    protected:
      Data value;
      ulong index = 0;
      Vector<NodeVec *> *vecptr = nullptr;
    public:
      NodeVec(const Data &, const ulong &, Vector<NodeVec *> *);
      virtual ~NodeVec() = default;

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;
      inline bool HasLeftChild() const noexcept override;
      inline bool HasRightChild() const noexcept override;
      NodeVec &LeftChild() const override;
      NodeVec &RightChild() const override;
    };
    using BinaryTree<Data>::size;
    Vector<NodeVec *> *btreevecptr = nullptr;

  public:
    // Default constructor
    BinaryTreeVec() = default;

    /* ************************************************************************ */

    // Specific constructors
    BinaryTreeVec(const LinearContainer<Data> &); // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BinaryTreeVec(const BinaryTreeVec &);

    // Move constructor
    BinaryTreeVec(BinaryTreeVec &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~BinaryTreeVec();

    /* ************************************************************************ */

    // Copy assignment
    BinaryTreeVec &operator=(const BinaryTreeVec &);

    // Move assignment
    BinaryTreeVec &operator=(BinaryTreeVec &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTreeVec &) const noexcept;
    inline bool operator!=(const BinaryTreeVec &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    NodeVec &Root() const override; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member

    // Specific member functions (inherited and from MappableContainer and FoldableContainer)
    void MapBreadth(const typename MappableContainer<Data>::MapFunctor, void *) override;

    void FoldBreadth(const typename FoldableContainer<Data>::FoldFunctor, const void *, void *) const override;
  };

  /* ************************************************************************** */

}

#include "binarytreevec.cpp"

#endif
