#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
using namespace std;

struct Journal //you create a journal class
{
  string title;
  vector<string> entries;
  // Constructor
  explicit Journal(const string& title)
    : title{title}
  {
  }
  // Adding entries to journal
  void add(const string& entry);

  // persistence is a separate concern
  void save(const string& filename);
};

// Implementation here:
// Add entries to journal
void Journal::add(const string& entry)
{
  static int count = 1;
  // lexical_cast can convert numbers from strings to numeric types like int or double and vice versa.
  entries.push_back(boost::lexical_cast<string>(count++)
    + ": " + entry);
}

/* The problem with this is that you have ANOTHER CONCERN, a problem regarding persistence - so you are adding persistence to your journal.

Now imagine if you have, in addition to a journal, you also have a dozen other domain objects that you're working with and you give every one of them a function called SAVE and a function called LOAD etc etc. The problem with this is that when you want to change PERSISTENCE, you would have to change persistent in 10 to 20 classes which are actually using it.

For example, if one day you decide to stop using files and decide to use databases instead, you realise that you have to change this EVERYWHERE, which is not good. So essentially what we do is called a separation of concerns.


So the Journal should take care of the journal entries and the journal title and its kind of storage mechanism with the strings and the counter, but if you want to PERSIST things, you NEED to have a separate component, a separate class.

// So you have a PersistenceManager like Implementation B
*/
// Implementation A - Non-SRP
void Journal::save(const string& filename)
{
  ofstream ofs(filename);
  for (auto& s : entries)
    ofs << s << endl;
}

// Implementation B - SRP!
struct PersistenceManager
{
  static void save(const Journal& j, const string& filename)
  {
    ofstream ofs(filename);
    for (auto& s : j.entries)
      ofs << s << endl;
  }
};

void main()
{
  Journal journal{"Dear Diary"};
  journal.add("I ate a bug");
  journal.add("I cried today");

  //journal.save("diary.txt"); // non-SRP

  PersistenceManager pm;
  pm.save(journal, "diary.txt"); // SRP
}
