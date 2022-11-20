#include <iostream>
#include <memory>
#include <vector>

class Letter {
 public:
  template <typename T>
  Letter(T&& object)
      : wrapper_{std::make_unique<LetterWrapper<T>>(std::forward<T>(object))} {}

  void print() const { wrapper_->print(); }

 private:
  struct LetterInterface {
   public:
    virtual ~LetterInterface(){};

    virtual void print() = 0;
  };

  template <typename T>
  class LetterWrapper : public LetterInterface {
   public:
    LetterWrapper(const T& obj) : obj_{obj} {}

    void print() override { obj_.print(); }

   private:
    T obj_;
  };
  std::unique_ptr<LetterInterface> wrapper_;
};

struct A {
  void print() { std::cout << "Class A" << std::endl; }
};

struct B {
  void print() { std::cout << "Class B" << std::endl; }
};

struct C {
  void print() { std::cout << "Class C" << std::endl; }
};

int main() {
  std::vector<Letter> letters;
  letters.push_back(Letter(A()));
  letters.push_back(Letter(A()));
  letters.push_back(Letter(B()));
  letters.push_back(Letter(C()));
  letters.push_back(Letter(C()));

  for (const auto& l : letters) {
    l.print();
  }
  return 0;
}
