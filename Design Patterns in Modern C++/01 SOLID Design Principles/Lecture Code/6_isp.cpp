#include <vector>
/*
The idea of the interfacee segregation principle is basically to get you to NOT create interfaces which are too large and which require the implementors to maybe implement too much.

Suppose you have some document type:
*/
struct Document;

struct IMachine
{
  virtual void print(Document& doc) = 0;
  virtual void fax(Document& doc) = 0;
  virtual void scan(Document& doc) = 0;
};
/*
If you're making a machine, which is a multifunction printer, which can in fact print and scan and fax documents, there's no problem in using this interface.
*/

struct MFP : IMachine
{
  void print(Document& doc) override;
  void fax(Document& doc) override;
  void scan(Document& doc) override;
};
/*
Now, the problem that you typically encounter is what happens if you need to implement ONLY a printer/ ONLY a scanner / ONLY a fax machine? So let's say we want the scanner:
*/
struct Scanner: IMachine
{
    void print(Document& doc) override; // throw some exception? Leave them as null?
    void fax(Document& doc) override; // throw some exception? Leave them as null?
    void scan(Document& doc) override; // the only useful method!
};
/*
Either way you are telling a client that you are giving them a Scanner which can also print, which isn't true. But you're giving them the API anyway, simply because the interface that's been defined for handling all this stuff is just too big.

So what we really need to do is to segregate the interfaces because no client would require always all printing scanning and faxing.

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

So instead of this approach above, you would use the below which is more aligned to the Interface Segregation Principle (ISP)

*/
struct IPrinter //takes care of only printing the document
{
  virtual void print(Document& doc) = 0;
};

struct IScanner // takes care of only scanning the document
{
  virtual void scan(Document& doc) = 0;
};
struct IFax // takes care of only faxing the document.
{
    virtual void fax(Document& doc) = 0;
};

// Now to implement a printer...
struct Printer : IPrinter
{
  void print(Document& doc) override;
};
// to make a scanner...
struct Scanner : IScanner
{
  void scan(Document& doc) override;
};
// Now if you would like to make a more complex machine,
// IMachine should inherit from both the Iprinter and the Iscanner.

struct IMachine: IPrinter, IScanner
{
}; // keep these abstract (no body required. )

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner}
  {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }
  void scan(Document& doc) override;
};

// IPrinter --> Printer
// everything --> Machine

/*
The goal of the ISP is to make our interfaces smaller so that whenever a client uses one of these chunks of the interface, it's all coherent. They don't have to throw exceptions out of methods or anything of that sort.
*/
