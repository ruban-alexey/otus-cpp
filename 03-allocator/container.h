#pragma once

template <typename T, class Allocator = std::allocator<T>>
class MyContainer {
    struct Node {
        explicit Node(T* data) : data(data) {};
        T* data;
//        Node* prev{nullptr};
        Node* next{nullptr};
    };
  public:
    ~MyContainer() {
        Node* next = begin_;
        while(next != nullptr) {
            Node* tmp = next->next;
            allocator_.deallocate(next->data, 1);
            delete next;
            next = tmp;
        }
    }
    void push(const T& value) {
        T* p = allocator_.allocate(1);
        *p = value;
        if (begin_ == nullptr) {
            begin_ = new Node(p);
            end_ = begin_;
        } else {
            end_->next = new Node(p);
            end_ = end_->next;
        }
    }
    Node* begin() const {
        return begin_;
    }
    Node* end() const {
        return end_;
    }
  private:
    Node* begin_{nullptr};
    Node* end_{nullptr};
    Allocator allocator_;
};
