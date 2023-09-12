
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

#include "../stack.hpp"
#include "../../vector/vector.hpp"

namespace lasd
{

  template <typename Data>
  class StackVec : public virtual Stack<Data>, protected virtual Vector<Data>
  {

  private:
    // ...

  protected:
    using Vector<Data>::Elements;
    using Vector<Data>::size;
    unsigned long effective_size = 0;

  public:
    // Default constructor
    StackVec() = default;

    // Specific constructor
    StackVec(const LinearContainer<Data> &); // A stack obtained from a LinearContainer

    // Copy constructor
    StackVec(const StackVec &);

    // Move constructor
    StackVec(StackVec &&) noexcept;

    // Destructor
    virtual ~StackVec() = default;

    // Copy assignment
    StackVec &operator=(const StackVec &);

    // Move assignment
    StackVec &operator=(StackVec &&) noexcept;

    // Comparison operators
    bool operator==(const StackVec &) const noexcept;
    inline bool operator!=(const StackVec &) const noexcept;

    // Specific member functions (inherited from Stack)

    void Push(const Data &) override;     // Override Stack member (copy of the value)
    void Push(Data &&) noexcept override; // Override Stack member (move of the value)
    Data &Top() const override;           // Override Stack member (must throw std::length_error when empty)
    void Pop() override;                  // Override Stack member (must throw std::length_error when empty)
    Data TopNPop() override;              // Override Stack member (must throw std::length_error when empty)

    // Specific member functions (inherited from Container)

    inline bool Empty() const noexcept override; // Override Container member

    inline ulong Size() const noexcept override; // Override Container member

    void Clear() override; // Override Container member

  protected:
  };

}

#include "stackvec.cpp"

#endif
