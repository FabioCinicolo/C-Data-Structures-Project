
#ifndef QUEUE_HPP
#define QUEUE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
typedef unsigned long ulong;
/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class Queue : public virtual Container
  {

  private:
    // ...

  protected:
  public:
    // Destructor
    virtual ~Queue() = default;

    /* ************************************************************************ */

    // Copy assignment
    Queue &operator=(const Queue &) = delete;

    // Move assignment
    Queue &operator=(Queue &&) noexcept = delete;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Queue &) const noexcept = delete;
    inline bool operator!=(const Queue &) const noexcept = delete;

    /* ************************************************************************ */

    // Specific member functions

    virtual void Enqueue(const Data &) = 0;     // Copy of the value
    virtual void Enqueue(Data &&) noexcept = 0; // Move of the value
    virtual Data &Head() const = 0;             // (concrete function must throw std::length_error when empty)
    virtual void Dequeue() = 0;                 // (concrete function must throw std::length_error when empty)
    virtual Data HeadNDequeue() = 0;            // (concrete function must throw std::length_error when empty)
  };

  /* ************************************************************************** */

}

#endif
