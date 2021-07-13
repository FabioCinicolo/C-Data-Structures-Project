
#ifndef CONTAINER_HPP
#define CONTAINER_HPP

/* ************************************************************************** */

#include <stdexcept>
#include <functional>
typedef unsigned long ulong;
/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  class Container
  {

  private:
    // ...

  protected:
    ulong size = 0;

  public:
    // Destructor
    virtual ~Container() = default;

    /* ************************************************************************ */

    // Copy assignment
    Container &operator=(const Container &) = delete;

    // Move assignment
    Container &operator=(Container &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Container &) const noexcept = delete;
    bool operator!=(const Container &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions
    virtual inline bool Empty() const noexcept
    {
      return (size == 0);
    }

    virtual inline ulong Size() const noexcept
    {
      return size;
    }

    virtual void Clear() = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : virtual public Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~LinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    LinearContainer &operator=(const LinearContainer &) = delete;

    // Move assignment
    LinearContainer &operator=(LinearContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const LinearContainer &) const noexcept = delete;
    bool operator!=(const LinearContainer &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions
    virtual Data &Front() const = 0;
    virtual Data &Back() const = 0;

    virtual Data &operator[](const ulong) const = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : virtual public Container
  { 

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~TestableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    TestableContainer &operator=(const TestableContainer &) = delete;

    // Move assignment
    TestableContainer &operator=(TestableContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const TestableContainer &) const noexcept = delete;
    bool operator!=(const TestableContainer &) const noexcept = delete;
    /* ************************************************************************ */

    // Specific member functions
    virtual bool Exists(const Data &) const noexcept = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class MappableContainer : virtual public Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~MappableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    MappableContainer &operator=(const MappableContainer &) = delete;

    // Move assignment
    MappableContainer &operator=(MappableContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const MappableContainer &) const noexcept = delete;
    bool operator!=(const MappableContainer &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    typedef std::function<void(Data &, void *)> MapFunctor;

    virtual void MapPreOrder(const MapFunctor, void *) = 0;
    virtual void MapPostOrder(const MapFunctor, void *) = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class FoldableContainer : virtual public TestableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~FoldableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    FoldableContainer &operator=(const FoldableContainer &) = delete;

    // Move assignment
    FoldableContainer &operator=(FoldableContainer &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const FoldableContainer &) const noexcept = delete;
    bool operator!=(const FoldableContainer &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    typedef std::function<void(const Data &, const void *, void *) noexcept> FoldFunctor;

    virtual void FoldPreOrder(const FoldFunctor, const void *, void *) const = 0;
    virtual void FoldPostOrder(const FoldFunctor, const void *, void *) const = 0;

    virtual bool Exists(const Data &) const noexcept override;
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderMappableContainer : virtual public MappableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~InOrderMappableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    InOrderMappableContainer &operator=(const InOrderMappableContainer &) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    InOrderMappableContainer &operator=(InOrderMappableContainer &&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const InOrderMappableContainer &) const noexcept = delete;        // Comparison of abstract types might not be possible.
    inline bool operator!=(const InOrderMappableContainer &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapInOrder(const MapFunctor, void *) = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class InOrderFoldableContainer : virtual public FoldableContainer<Data>
  { 

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~InOrderFoldableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    InOrderFoldableContainer &operator=(const InOrderFoldableContainer &) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    InOrderFoldableContainer &operator=(InOrderFoldableContainer &&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const InOrderFoldableContainer &) const noexcept = delete;        // Comparison of abstract types might not be possible.
    inline bool operator!=(const InOrderFoldableContainer &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldInOrder(const FoldFunctor, const void *, void *) const = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthMappableContainer : virtual public MappableContainer<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~BreadthMappableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    BreadthMappableContainer &operator=(const BreadthMappableContainer&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    BreadthMappableContainer &operator=(BreadthMappableContainer &&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BreadthMappableContainer &) const noexcept = delete;        // Comparison of abstract types might not be possible.
    inline bool operator!=(const BreadthMappableContainer &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    using typename MappableContainer<Data>::MapFunctor;

    virtual void MapBreadth(const MapFunctor, void *) = 0;
  };

  /* ************************************************************************** */

  template <typename Data>
  class BreadthFoldableContainer : virtual public FoldableContainer<Data>
  { 

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~BreadthFoldableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    BreadthFoldableContainer &operator=(const BreadthFoldableContainer &) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    BreadthFoldableContainer &operator=(BreadthFoldableContainer &&) noexcept = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const BreadthFoldableContainer &) const noexcept = delete;        // Comparison of abstract types might not be possible.
    inline bool operator!=(const BreadthFoldableContainer &) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions

    using typename FoldableContainer<Data>::FoldFunctor;

    virtual void FoldBreadth(const FoldFunctor, const void *, void *) const = 0;
  };

  /* ************************************************************************** */

}

#include "container.cpp"

#endif
