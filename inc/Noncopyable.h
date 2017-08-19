#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

class Noncopyable
{
protected:
  Noncopyable() {}
  ~Noncopyable() {}
private:
  Noncopyable(const Noncopyable& other);
  Noncopyable& operator=(const Noncopyable& rhs);
};

#endif