// Animal Shelter: An animal shelter, which holds only dogs and cats, operates
// on a strictly "first in, first out" basis. People must adopt either the
// "oldest" (based on arrival time) of all animals at the shelter, or they can
// select whether they would prefer a dog or a cat (and will receive the oldest
// animal of that type). They cannot select which specific animal they would
// like. Create the data structures to maintain this system and implement
// operations such as enqueue, dequeueAny, dequeueDog, and dequeueCat. You may
// use the built-in Linked list data structure.

#include <iostream>
#include <list>
#include <string>
#include <variant>

struct Cat {
  std::string name;
};

struct Dog {
  std::string name;
};

class AnimalShelter {
 public:
  void Enqueue(Cat cat) { cats.push_back({cat, monotonic_id++}); }

  void Enqueue(Dog dog) { dogs.push_back({dog, monotonic_id++}); }

  std::variant<Cat, Dog> Dequeue() {
    const auto dog = dogs.front();
    const auto cat = cats.front();
    if (dog.timestamp < cat.timestamp) {
      dogs.pop_front();
      return dog.animal;
    }
    cats.pop_front();
    return cat.animal;
  }

  Dog DequeueDog() {
    auto dog = dogs.front();
    dogs.pop_front();
    return dog.animal;
  }

  Cat DequeueCat() {
    auto cat = cats.front();
    cats.pop_front();
    return cat.animal;
  }

 private:
  template <typename TAnimal>
  struct TimestampedAnimal {
    TAnimal animal;
    uint64_t timestamp;
  };

  std::list<TimestampedAnimal<Cat>> cats;
  std::list<TimestampedAnimal<Dog>> dogs;
  uint64_t monotonic_id;
};

int main() {
  AnimalShelter shelter;
  shelter.Enqueue(Cat{"Flakes"});
  shelter.Enqueue(Dog{"Rex"});
  shelter.Enqueue(Cat{"Fluffy"});
  shelter.Enqueue(Dog{"Doggy"});
  shelter.Enqueue(Cat{"Katzi"});
  shelter.Enqueue(Dog{"Dogso"});


  std::visit([](const auto animal){
    std::cout << animal.name << std::endl;
  }, shelter.Dequeue());
  std::visit([](const auto animal){
    std::cout << animal.name << std::endl;
  }, shelter.Dequeue());
  std::visit([](const auto animal){
    std::cout << animal.name << std::endl;
  }, shelter.Dequeue());
  return 0;
}
