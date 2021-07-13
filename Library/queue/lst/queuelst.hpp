
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd
{

  /* ************************************************************************** */

  template <typename Data>
  class QueueLst : public virtual Queue<Data>, protected virtual List<Data>
  {

  private:
    // ...

  protected:
    // ...

  public:
    // Default constructor
    QueueLst() = default;

    /* ************************************************************************ */

    // Specific constructor
    QueueLst(const LinearContainer<Data> &); // A queue obtained from a LinearContainer

    /* ************************************************************************ */

    // Copy constructor
    QueueLst(const QueueLst &);

    // Move constructor
    QueueLst(QueueLst &&) noexcept;

    /* ************************************************************************ */

    // Destructor
    virtual ~QueueLst() = default;

    /* ************************************************************************ */

    // Copy assignment
    QueueLst &operator=(const QueueLst &);

    // Move assignment
    QueueLst &operator=(QueueLst &&) noexcept;

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const QueueLst &) const noexcept;
    inline bool operator!=(const QueueLst &) const noexcept;

    /* ************************************************************************ */

    // Specific member functions (inherited from Queue)

    void Enqueue(const Data &) override;     // Override Queue member (copy of the value)
    void Enqueue(Data &&) noexcept override; // Override Queue member (move of the value)
    Data &Head() const override;             // Override Queue member (must throw std::length_error when empty)
    void Dequeue() override;                 // Override Queue member (must throw std::length_error when empty)
    Data HeadNDequeue() override;            // Override Queue member (must throw std::length_error when empty)
    /* ************************************************************************ */

    // Specific member functions (inherited from Container)

    void Clear() override; // Override Container member
  };

  /* ************************************************************************** */

}

#include "queuelst.cpp"

#endif
