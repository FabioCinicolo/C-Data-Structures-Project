
#ifndef STACK_HPP
#define STACK_HPP
typedef unsigned long ulong;

#include "../container/container.hpp"

namespace lasd
{

  template <typename Data>
  class Stack : public virtual Container
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Destructor
    virtual ~Stack() = default;

    // Copy assignment
    Stack &operator=(const Stack &) = delete;

    // Move assignment
    Stack &operator=(Stack &&) noexcept = delete;

    // Comparison operators
    bool operator==(const Stack &) const noexcept = delete; // Comparison of abstract types might not be possible.
    bool operator!=(const Stack &) const noexcept = delete; // Comparison of abstract types might not be possible.

    // Specific member functions

    virtual void Push(const Data &) = 0;     // Copy of the value
    virtual void Push(Data &&) noexcept = 0; // Move of the value
    virtual Data &Top() const = 0;           // (concrete function must throw std::length_error when empty)
    virtual void Pop() = 0;                  // (concrete function must throw std::length_error when empty)
    virtual Data TopNPop() = 0;              // (concrete function must throw std::length_error when empty)
  };

}

#endif
