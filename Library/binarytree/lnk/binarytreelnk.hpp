
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class BinaryTreeLnk : virtual public BinaryTree<Data>
  {

  private:
    // ...

  protected:
    struct NodeLnk : virtual public BinaryTree<Data>::Node
    {

    private:
      // ...

    protected:
    public:
      Data value;
      NodeLnk *leftptr = nullptr;
      NodeLnk *rightptr = nullptr;

      NodeLnk(const Data &);
      NodeLnk(Data &&) noexcept;
      virtual ~NodeLnk();

      Data &Element() noexcept override;
      const Data &Element() const noexcept override;
      inline bool HasLeftChild() const noexcept override;
      inline bool HasRightChild() const noexcept override;
      NodeLnk &LeftChild() const override;
      NodeLnk &RightChild() const override;
    };
    using BinaryTree<Data>::size;
    NodeLnk *root = nullptr;
    NodeLnk* InsertLevelOrder(const LinearContainer<Data> &, NodeLnk *, ulong, ulong);
    NodeLnk *GetRootFromCopyInOrder(NodeLnk *);

  public:
    // Default constructor
    BinaryTreeLnk() = default;

    /* ************************************************************************ */

    //Specific constructors
    BinaryTreeLnk(const LinearContainer<Data> &); // A binary tree obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    BinaryTreeLnk(const BinaryTreeLnk &);

    // Move constructor
    BinaryTreeLnk(BinaryTreeLnk &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~BinaryTreeLnk();

    /* ************************************************************************ */

    // Copy assignment
    BinaryTreeLnk &operator=(const BinaryTreeLnk &);

    // Move assignment
    BinaryTreeLnk &operator=(BinaryTreeLnk &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BinaryTreeLnk &) const noexcept;
    inline bool operator!=(const BinaryTreeLnk &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from BinaryTree)

    NodeLnk &Root() const override; // Override BinaryTree member (throw std::length_error when empty)

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member
  };

  /* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
