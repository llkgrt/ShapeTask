#include <iostream>
#include <vector>
#include <memory>

const double PI = 3.1415926535;

class Shape
{
protected:
    std::string name_;

public:
    Shape(const std::string& name) : name_(name) {}
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual void draw() const = 0;

    const std::string& name() const { return name_; }
};

class Circle : public Shape
{
private:
    double radius_;

public:
    Circle(double radius) : Shape("Circle"), radius_(radius) {
        if (radius <= 0) throw std::invalid_argument("Radius must be > 0");
    }

    double area() const override {
        return PI * radius_ * radius_;
    }

    void draw() const override {
        //const int drawingArea = 12;
        //const int center = drawingArea / 2;
        //const double scale = 2.5;

        //std::cout << name() << " (r=" << radius_ << "):" << std::endl;

        //for (int y = 0; y < drawingArea; ++y) {
        //    for (int x = 0; x < drawingArea; ++x) {
        //        double dx = (x - center) / 2.0;
        //        double dy = (y - center) / 2.0;

        //        if (dx * dx + dy * dy <= (radius_ / scale) * (radius_ / scale)) {
        //            std::cout << "*";
        //        }
        //        else {
        //            std::cout << " ";
        //        }
        //    }
        //    std::cout << std::endl;
        //}
    }
};

class Rectangle : public Shape
{
private:
    double width_, height_;

public:
    Rectangle(double width, double height) : Shape("Rectangle"), width_(width), height_(height) {
        if (width <= 0 || height <= 0) throw std::invalid_argument("Sides must be > 0");
    }

    double area() const override {
        return width_ * height_;
    }

    void draw() const override {
        //std::cout << name() << " (w=" << width_ << ", h=" << height_ << "):" << std::endl;
        //for (int i = 0; i < height_; ++i) {
        //    for (int j = 0; j < width_; ++j)
        //        std::cout << "*";
        //    std::cout << std::endl;
        //}
    }
};

class Triangle : public Shape
{
private:
    double base_, height_;

public:
    Triangle(double base, double height) : Shape("Triangle"), base_(base), height_(height) {
        if (base <= 0 || height <= 0) throw std::invalid_argument("Sides must be > 0");
    }

    double area() const override {
        return 0.5 * base_ * height_;
    }

    void draw() const override {
        //std::cout << name() << " (b=" << base_ << ", h=" << height_ << "):" << std::endl;
        //for (int i = 0; i < height_; ++i) {
        //    int spaces = height_ - i - 1;
        //    for (int s = 0; s < spaces; ++s) std::cout << " ";
        //    for (int j = 0; j < (i * 2 + 1); ++j) std::cout << "*";
        //    std::cout << std::endl;
        //}
    }
};

class ShapeFactory {
public:
    virtual ~ShapeFactory() = default;

    virtual std::unique_ptr<Shape> createCircle(double radius) const = 0;
    virtual std::unique_ptr<Shape> createRectangle(double width, double height) const = 0;
    virtual std::unique_ptr<Shape> createTriangle(double base, double height) const = 0;
};

class SimpleShapeFactory : public ShapeFactory {
public:
    std::unique_ptr<Shape> createCircle(double radius) const override {
        return std::make_unique<Circle>(radius);
    }

    std::unique_ptr<Shape> createRectangle(double width, double height) const override {
        return std::make_unique<Rectangle>(width, height);
    }

    std::unique_ptr<Shape> createTriangle(double base, double height) const override {
        return std::make_unique<Triangle>(base, height);
    }
};

int main()
{
    std::unique_ptr<ShapeFactory> factory = std::make_unique<SimpleShapeFactory>();

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(factory->createCircle(6.0));
    shapes.push_back(factory->createRectangle(4.0, 2.0));
    shapes.push_back(factory->createTriangle(5.0, 3.0));
    shapes.push_back(factory->createTriangle(10.0, 5.0));

    double totalArea = 0;

    for (const auto& shape : shapes) {
        std::cout << "\nArea " << shape->name() << ": " << shape->area() << std::endl;
        shape->draw();
        totalArea += shape->area();
    }

    std::cout << "\nCommon area: " << totalArea << std::endl;
    return 0;
}