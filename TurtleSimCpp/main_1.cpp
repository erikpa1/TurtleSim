#include <iostream>
#include <memory> // For std::shared_ptr and std::make_shared

// Define class A
class A {
public:
    A(int x, double y) : x_(x), y_(y) {
        std::cout << "A created with x: " << x_ << " and y: " << y_ << std::endl;
    }

    void display() const {
        std::cout << "x: " << x_ << ", y: " << y_ << std::endl;
    }

private:
    int x_;
    double y_;
};

// Function template to create a std::shared_ptr to an instance of T
template <typename T, typename... Args>
std::shared_ptr<T> Share(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

int main() {
    // Create a shared_ptr to an instance of A using the Share function template
    std::shared_ptr<A> aPtr = Share<A>(10, 20.5);

    // Use the shared pointer
    aPtr->display();

    return 0;
}