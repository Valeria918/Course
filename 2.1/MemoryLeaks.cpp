#include <functional>
#include <iostream>
#include <string>
#include <memory>
#include <vector>

int globalResourceCount = 0;

class Resource {
    std::string name;
public:
    Resource(const std::string& n) : name(n) {
        std::cout << "Resource " << name << " created\n";
        globalResourceCount++;
    }
    ~Resource() {
        std::cout << "Resource " << name << " destroyed\n";
        globalResourceCount--;
    }
    const std::string& getName() const { return name; }
};

void printNameStack() {
    Resource resource("Stack");
    std::cout << "Resource name: " << resource.getName() << std::endl;
}

void printNameHeap() {
    Resource* resource = new Resource("Heap");
    std::cout << "Resource name: " << resource->getName() << std::endl;
    delete resource;
}

std::function<void()> getPrintNameFunction() {
    std::shared_ptr<Resource> resource = std::make_shared<Resource>("Heap in lambda");
    return [resource]() {
        std::cout << "Resource name: " << resource->getName() << std::endl;
    };
}

void printResourceNames(const std::vector<std::shared_ptr<Resource>>& resources) {
    for (const auto& resource : resources) {
        std::cout << "Resource name: " << resource->getName() << std::endl;
    }
}

int main() {
    printNameStack();
    printNameHeap();
    getPrintNameFunction()();

    {
        std::vector<std::shared_ptr<Resource>> resources = { std::make_shared<Resource>("Resource 1"), std::make_shared<Resource>("Resource 2"), std::make_shared<Resource>("Resource 3") };
        printResourceNames(resources);
    } // shared_ptr-ы уничтожаются здесь, до вывода счётчика

    std::cout << std::endl << "Global used resources count: " << globalResourceCount << std::endl;
    return 0;
}