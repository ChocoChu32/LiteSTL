#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

template <typename T> class Vector {
private:
    T* elements;     // 指向动态数组的指针
    size_t capacity; // 数组的容量
    size_t size;     // 数组中元素的个数

public:
    // 构造函数：初始化 Vector 实例
    Vector() : elements(nullptr), capacity(0), size(0) {}

    // 析构函数：清理资源，确保无内存泄露
    ~Vector() { delete[] elements; }

    // 拷贝构造函数：允许通过现有的 myVector 实例来创建一个新实例
    Vector(const Vector& other) : capacity(other.capacity), size(other.size) {
        elements = new T[capacity];
        std::copy(other.elements, other.elements + size, elements);
    }

    // 拷贝赋值操作符：实现 myVector 实例之间的赋值功能
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] elements;
            capacity = other.capacity;
            size = other.size;
            elements = new T[capacity];
            std::copy(other.elements, other.elements + size, elements);
        }
        return *this;
    }

    // 添加元素到末尾：允许在 Vector 的末尾添加新元素
    void push_back(const T& value) {
        if (size == capacity) reserve(capacity == 0 ? 1 : 2 * capacity);
        elements[size++] = value;
    }

    // 获取元素个数：返回 Vector 当前包含的元素数量
    size_t getSize() const { return size; }

    // 获取容量：返回 Vector 可以容纳的元素总数
    size_t getCapacity() const { return capacity; }

    // 访问指定索引处的元素：通过索引访问特定位置的元素
    T& operator[](size_t index) {
        // 检查索引是否越界
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }

    // const版本的访问指定索引处的元素
    const T& operator[](size_t index) const {
        // 检查索引是否越界
        if (index >= size) throw std::out_of_range("Index out of range");
        return elements[index];
    }

    // 在指定位置插入元素：在 Vector 的特定位置插入一个新元素
    void insert(size_t index, const T& value) {
        if (index > size) throw std::out_of_range("Index out of range");
        if (size == capacity) reserve(capacity == 0 ? 1 : capacity * 2);
        for (size_t i = size; i > index; --i)
            elements[i] = elements[i - 1];
        elements[index] = value;
        ++size;
    }

    // 删除数组末尾元素：移除 Vector 末尾的元素
    void pop_back() {
        if (size > 0) --size;
    }

    // 清空数组：删除 Vector 中的所有元素，重置其状态
    void clear() { size = 0; }

    // 使用迭代器遍历数组的开始位置
    T* begin() { return elements; }

    // 使用迭代器遍历数组的结束位置
    T* end() { return elements + size; }

    // 使用迭代器遍历数组的开始位置（const版本）
    const T* begin() const { return elements; }

    // 使用迭代器遍历数组的结束位置（const版本）
    const T* end() const { return elements + size; }

    // 遍历并打印数组元素：提供一个函数，通过迭代器遍历并打印出所有元素
    void printElements() const {
        for (size_t i = 0; i < size; ++i)
            std::cout << elements[i] << " ";
        std::cout << std::endl;
    }

private:
    // 容器扩容：当前容量不足以容纳更多元素时，自动扩展 Vector 的容量以存储更多元素
    void reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            T* newElements = new T[newCapacity];
            std::copy(elements, elements + size, newElements);
            delete[] elements;
            elements = newElements;
            capacity = newCapacity;
        }
    }
};

int main() {
    // 创建一个 Vector 对象
    Vector<int> myVector;

    int N;
    std::cin >> N;
    // 读走回车
    getchar();

    std::string line;
    for (int i = 0; i < N; i++) {
        // 读取整行
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "push") {
            int value;
            iss >> value;
            myVector.push_back(value);
        } else if (command == "size") {
            std::cout << myVector.getSize() << std::endl;
        } else if (command == "get") {
            int index;
            iss >> index;
            std::cout << myVector[index] << std::endl;
        } else if (command == "insert") {
            int index, value;
            iss >> index >> value;
            myVector.insert(index, value);
        } else if (command == "pop") {
            myVector.pop_back();
        } else if (command == "clear") {
            myVector.clear();
        } else if (command == "print") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            myVector.printElements();
        } else if (command == "iterator") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (auto it = myVector.begin(); it != myVector.end(); ++it)
                std::cout << *it << " ";
            std::cout << std::endl;
        } else if (command == "foreach") {
            if (myVector.getSize() == 0) {
                std::cout << "empty" << std::endl;
                continue;
            }
            for (const auto& element : myVector)
                std::cout << element << " ";
            std::cout << std::endl;
        }
    }
    return 0;
}