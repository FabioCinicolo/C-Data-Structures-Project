
#ifndef ITERATOR_HPP
#define ITERATOR_HPP
typedef unsigned long ulong;
/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Iterator {

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~Iterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  Iterator& operator=(const Iterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Iterator& operator=(Iterator&&) noexcept = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  inline bool operator!=(const Iterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual Data& operator*()const = 0; // (concrete function must throw std::out_of_range when terminated)

  virtual bool Terminated() const noexcept = 0; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class ForwardIterator : virtual public Iterator<Data>{

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~ForwardIterator() = default;

  /* ************************************************************************ */

  // Copy assignment
  ForwardIterator& operator=(const ForwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  ForwardIterator& operator=(ForwardIterator&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  inline bool operator!=(const ForwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual ForwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)

};

/* ************************************************************************** */

template <typename Data>
class BackwardIterator : virtual public Iterator<Data>{ 

private:

  // ...

protected:

  // ...

public:

  // Destructor
  virtual ~BackwardIterator() = default;

  /* ************************************************************************ */

   // Copy assignment
  BackwardIterator& operator=(const BackwardIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BackwardIterator& operator=(BackwardIterator&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  inline bool operator!=(const BackwardIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  virtual BackwardIterator& operator++() = 0; // (concrete function must throw std::out_of_range when terminated)
};

/* ************************************************************************** */

template <typename Data>
class BidirectionalIterator { // Must extend ForwardIterator and BackwardIterator

private:

  // ...

protected:

  // ...

public:

 // Destructor
  virtual ~BidirectionalIterator() = default;

  /* ************************************************************************ */

   // Copy assignment
  BidirectionalIterator& operator=(const BidirectionalIterator&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BidirectionalIterator& operator=(BidirectionalIterator&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.
  inline bool operator!=(const BidirectionalIterator&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions

  bool Terminated() const noexcept override; // (concrete function should not throw exceptions)

  bool ForwardTerminated() const noexcept; // (concrete function should not throw exceptions)

  bool BackwardTerminated() const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

}

#endif
