// Objects in a program should be replaceable with instances of their subtypes
// Subtypes should be immediately substitutable for their base types
// w/o altering the correctness of the program

#include <iostream>

class Rectangle
{
protected: // cannot be accessed outside class, can be accessed by child class
  int width, height;
public:
  Rectangle(const int width, const int height) // Constructor
    : width{width}, height{height} { }

    // Create getters and setters
  int get_width() const { return width; }
  virtual void set_width(const int width) { this->width = width; }
  int get_height() const { return height; }
  virtual void set_height(const int height) { this->height = height; }

  int area() const { return width * height; }
};
/*
Now somewhere down the line, I decide that I want to extend this model, but before I do, let's suppose I'm already using some sort of API for working with Rectangle. So let's suppose there is some function called process which takes a rectangle reference to a rectangle.
*/
void process(Rectangle& r)
{
  int w = r.get_width();
  r.set_height(10); // sets height to 10

  std::cout << "expected area = " << (w * 10)
    << ", got " << r.area() << std::endl; // expects area equal to width * 10.

}
/*
So let's say somewhere along the workflow you decide to use inheritance to inherit from rectangle if you use a square
*/
class Square : public Rectangle
{
public:
  Square(int size): Rectangle(size,size) {} // constructor
  void set_width(const int width) override {
    this->width = height = width;
  }
  void set_height(const int height) override {
    this->height = width = height;
  }
};
/*
And by doing this we actually violated the LSP. It states that if you have a function which takes a base class, any derived class should be able to be substituted into this function without any problems.

The lecturer's argument of inheriting a square from a rectangle is not a good idea, despite a square being a special case of a rectangle, BUT you can do it differently.

You can create a boolean variable within the class rectangle for instance and set it to true if its a square, and false if not.
*/
struct RectangleFactory
{
  static Rectangle create_rectangle(int w, int h); // returns a rectangle
  static Rectangle create_square(int size); // returns a square.
}; // doesn't break the LSP!!

int main()
{
  Rectangle r{ 5,5 };
  process(r);

  Square s{ 5 };
  process(s);

  getchar();
  return 0;
}
