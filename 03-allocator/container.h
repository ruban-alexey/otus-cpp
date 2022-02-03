#pragma once

template<typename T, class Allocator = std::allocator<T>>
class MyContainer {
    struct Node {
        explicit Node(T* data) : data(data) {};
        T* data{nullptr};
        Node* next{nullptr};
    };
    struct Iterator {
        Node* node;
        explicit Iterator(Node* nd) : node(nd) {}
        T& operator*() {
            return *node->data;
        }
        Iterator operator++() {
            node = node->next;
            return *this;
        }
        Iterator operator++(int) {
            Node tmp = *this;
            ++(*this);
            return tmp;
        }
        bool operator==(Iterator b) const { return node == b.node; }
        bool operator!=(Iterator b) const { return node != b.node; }
    };
  public:
    ~MyContainer() {
        Node* next = begin_;
        while (next != nullptr) {
            Node* tmp = next->next;
            allocator_.deallocate(next->data, 1);
            delete next;
            next = tmp;
        }
    }
    void push(const T& value) {
        T* p = allocator_.allocate(1);
        *p = value;
        size_++;
        if (begin_ == nullptr) {
            begin_ = new Node(p);
            end_ = begin_;
            begin_->next = last_;
        } else {
            end_->next = new Node(p);
            end_ = end_->next;
            last_ = end_->next;
        }
    }
    Iterator begin() const {
        return Iterator(begin_);
    }
    Iterator end() const {
        return Iterator(last_);
    }
    bool empty() const {
        return begin() == end();
    }
    size_t size() const {
        return size_;
    }
    T& front() const {
        return *begin_->data;
    }
    T& back() const {
        return *end_->data;
    }
  private:
    Node* begin_{nullptr};
    Node* end_{nullptr};
    Node* last_{nullptr};
    size_t size_{0};
    Allocator allocator_;
};
