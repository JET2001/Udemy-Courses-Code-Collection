// open closed principle
// open for extension, closed for modification

#include <string>
#include <vector>
#include <iostream>
using namespace std;
/* Let's suppose you are making a website which sells certain products and your manager wants you to filter each of your products. Let's also suppose that each of the products has certain traits like , for example, colour and size like so:
*/
enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product
{
  string name;
  Color color;
  Size size;
};

struct ProductFilter
{
  typedef vector<Product*> Items;
  // Colour filter
  Items by_color(Items items, const Color color)
  {
    Items result;
    for (auto& i : items)
      if (i->color == color)
        result.push_back(i);
    return result;
  }
  /*
  Let's suppose that your manager comes back to you and says
  'Can you also filter by size?'
  And what you do is you end up basically copying the code that you've written and you end up making yet another copy where you specify filtering by size.

  So this is a workable solution, but the problem is you've had to go back into a chunk of code that you've already tested. And perhaps, you not only have tested it, maybe you've already shipped it to a client. This means you have to introduce a BINARY INCOMPATIBILITY by adding another interface member to ProductFilter, which isn't great.
  */
  Items by_size(Items items, const Size size)
  {
    Items result;
    for (auto& i : items)
      if (i->size == size)
        result.push_back(i);
    return result;
  }
/*
  And somewhere down the line of course, your boss is going to come back to you once again and say: can you please make sure that our clients can filter by both size AND colour?

  Then you go back to your existing code and start replicating code again.
*/
  Items by_size_and_color(Items items, const Size size, const Color color)
  {
    Items result;
    for (auto& i : items)
      if (i->size == size && i->color == color)
        result.push_back(i);
    return result;
  }
};
/*
Hmm so you can begin to see how this is problematic, because we have two criteria and we have three functions, if we had three criteria, we would have 8 functions. Generally, it doesn't scale and you don't really want to go into an existing code.

OPEN-CLOSED PRINCIPLE
The OCP states that your systems should be open to extensions, this means that you should be able to extend systems BY INHERITANCE, for example, but closed for modification. And unfortunately what we did above is modifying existing code instead of inheriting and thereby extending the system.

So let's see if we can build a better filter (BetterFilter) and we're going to use the specification pattern - which is an enterprise pattern, a pattern related to data and working with data.

We will define interfaces called Specification and Filter.



*/
template <typename T> struct AndSpecification;

// Specification class declaration
template <typename T> struct Specification
{
  virtual ~Specification() = default;

  // Some item satisfies a particular specification and the specification is once again to be defined via inheritance.
  virtual bool is_satisfied(T* item) const = 0;

  // new: breaks OCP if you add it post-hoc
  /*AndSpecification<T> operator&&(Specification<T>&& other)
  {
    return AndSpecification<T>(*this, other);
  }*/
};

// new:
template <typename T> AndSpecification<T> operator&&
  (const Specification<T>& first, const Specification<T>& second)
{
  return { first, second };
}

template <typename T> struct Filter
{
    // Returns a vector of tree pointers.
  virtual vector<T*> filter(vector<T*> items,
                            Specification<T>& spec) = 0;
};
// Inheritance!!
/* Okay so we'll be really really generic here:
*/
struct BetterFilter : Filter<Product> // note that this is a Product
{
  vector<Product*> filter(vector<Product*> items,
                           Specification<Product> &spec) override
  {
    vector<Product*> result;
    for (auto& p : items)
      if (spec.is_satisfied(p))
        result.push_back(p);
    return result;
  }
};
/*
Now that's done, we would like to specify the different metrics which we would like to search by: for instance (By colour):

So if we want to do a colour specification, define it as follows:
*/
struct ColorSpecification : Specification<Product> // specialising template
{
  Color color;

  ColorSpecification(Color color) : color(color) {}

  bool is_satisfied(Product *item) const override {
    return item->color == color; //
  }
};

 // Same thing for Size
struct SizeSpecification : Specification<Product>
{
  Size size;

  explicit SizeSpecification(const Size size)
    : size{ size }
  {
  }


  bool is_satisfied(Product* item) const override {
    return item->size == size;
  }
};
// Create a Combinator
// Create the template first
// Combinator will inherit functionality from Specification <T>
template <typename T> struct AndSpecification : Specification<T>
{
  const Specification<T>& first; //first metric
  const Specification<T>& second; // second metric
  // Constructor
  AndSpecification(const Specification<T>& first, const Specification<T>& second)
    : first(first), second(second) {}

  bool is_satisfied(T *item) const override {
      // Note you already overrided these is_satisfieds below.
    return first.is_satisfied(item) && second.is_satisfied(item);
  }
};

// new:

int main()
{
  Product apple{"Apple", Color::green, Size::small};
  Product tree{"Tree", Color::green, Size::large};
  Product house{"House", Color::blue, Size::large};

  const vector<Product*> all { &apple, &tree, &house };

  BetterFilter bf;
  ColorSpecification green(Color::green);
  auto green_things = bf.filter(all, green);
  for (auto& x : green_things)
    cout << x->name << " is green\n";


  SizeSpecification large(Size::large);
  // You need to write the product name
  AndSpecification<Product> green_and_large(green, large);

  //auto big_green_things = bf.filter(all, green_and_large);

  // use the operator instead (same for || etc.)
  auto spec = green && large;
  for (auto& x : bf.filter(all, spec))
    cout << x->name << " is green and large\n";

  // warning: the following will compile but will NOT work
  // auto spec2 = SizeSpecification{Size::large} &&
  //              ColorSpecification{Color::blue};

  getchar();
  return 0;
}
/*
The goal of the open close principle is to avoid having to jump into code that you've already written. That's it.

- open for extension - meaning that you can always make a new specification by extending, by inheriting effectively,
- but closed for modification, which means that in the context of the specification pattern, you will never have to go back into the filter interface or the Specification interface, you wouldn't have to change those, and you would extend them by inheritance and then you would create maybe these combinators like the AndSpecification.

- also note that we have templated arguments, so we are not constrained ourselves to products. We can also have other kinds of items here, and its all very nice and flexible and very usable as well.

*/
