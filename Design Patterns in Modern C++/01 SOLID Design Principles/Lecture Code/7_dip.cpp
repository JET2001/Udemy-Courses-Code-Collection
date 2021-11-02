#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;
/*
DEPENDENCY INVERSION PRINCIPLE
(not the same as depeendency injection)
It specifies the best way to form dependencies between different objects. So the DIP is split into 2 different ideas:

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details.
//    Details should depend on abstractions.

What is an abstraction? generally when we talk about abstractions, we talk about interfaces or base classes. So essentially instead of depending on a concrete type, what you REALLY want is you want to be as general as possible.

You want to take in an interface which provides you the necessary functionality, but you don't want to depend on the concrete type more than you need to because then, you are depending on the implementation details. For example, if some class has a vector inside, you start taking that vector and iterating it, you might be in trouble if the class decides later on to change it to something else. So that's why we have abstractions in the first place so that we can change the underlying implementation.


let's model relationships between people:
*/

enum class Relationship // different relationships
{
  parent,
  child,
  sibling
};

struct Person
{
  string name;
};
// We want to get a low level construct for actually storing the relationships.
// this is an abstraction!!
struct RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};
// We want to get a low level construct for actually storing the relationships.
struct Relationships : RelationshipBrowser // low-level module
// note that relationships inherits the relationshipbrowser interface.
// low level construct in our design.
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};
// if you want to perform research on relationships, then this is a HIGH LEVEL module.
struct Research // high-level
{
    // Implementation A: What you SHOULD NOT DO (According to DIP)
    // Remember that high level modules should not depend on low level modules?
    // So we're going to use here to access the details:
     Research(const Relationships& relationships)
     {
       auto& relations = relationships.relations; // the high level module is now dependent on the low level module.
       // If I want to find all the relations of John, we can certainly do it:
       for (auto&& [first, rel, second] : relations)
       {
         if (first.name == "John" && rel == Relationship::parent)
         {
           cout << "John has a child called " << second.name << endl;
         }
       }
     }
/* Note that this produces the results that we want!
However, let's imagine what happens if, for example the low level module decide to change the storage of relations: so what happens if it makes the relations member variable private? So it tries to hide it completely.

In this case, the high level code is completely broken, unfortunately.
So how do you fix this in this situation? Typically we use abstractions -
so instead of havign the direct dependency on some low level module, you would introduce an abstraction - you would introduce some sort of interface, but that's only a part of the problem.

The other part of the problem is really if you want to find all the children of a particular person, I would argue that the single responsibility principle still puts this responsibility as part of the relationships class.

So your research doesn't really have to delve into, you know, finding the children of somebody. You can move the finding children method into a lower level module, or by introducing an abstraction.

So this abstraction is going to be called a RelationshipBrowser. So our RelationshipBrowser is going to provide a few useful bits of funtionality for searching for all the children of a particular person.

So now, instead of depending on low level modules, we will depend on just an abstraction - the RelationshipBrowser
*/
// IMPLEMENTATION B: Using the DIP
  Research(RelationshipBrowser& browser) // constructor
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      cout << "John has a child called " << child.name << endl;
    }
  }
};
/*
We hope to have dependencies on interfaces rather than concrete implementations. And you don't want to delve into other classes details and start depending on their details, because remember, at some point in time, relationships might decide to replace the vector by some kind of map or something. And in this case, you're going to be really screwed because you're iterating over a vector of tuples and there's no longer a vector of tuples for you to iterate.

Dependency Injection allows you to specify certain defaults. For instance, it will allow you to specify that whenever someone wants a RelationshipBrowser, they SHOULD be provided a copy or a reference to the Relationships class. This is how dependency injection plays ON TOP of the dependency inversion principle, but the inversion principle just basically says that both of the high level and low level modules should be depending on ABSTRACTIONS and you should not depend on details of somebody else's implementation.
*/

int main()
{
  Person parent{"John"};
  Person child1{"Chris"};
  Person child2{"Matt"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships);

  return 0;
}
