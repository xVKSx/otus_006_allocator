#pragma once

template<typename T, typename Allocator=std::allocator<T>>
class List {
public:
    struct Node {
        explicit Node(Node *next, T value) : next(next), value(std::move(value)) {}

        Node *next = nullptr;
        T value;
    };

    ~List();

    template<typename... Args>
    void push_front(Args &&... args);

    Node *get_head() { return head; }

    const Node *get_head() const { return head; }

private:
    Node *head = nullptr;
    typename Allocator::template rebind<Node>::other allocator_;
};

template<typename T, typename Allocator>
List<T, Allocator>::~List() {
    while (head != nullptr) {
        Node *tmp = head;
        head = head->next;
        allocator_.destroy(tmp);
        allocator_.deallocate(tmp, 1);
    }
}

template<typename T, typename Allocator>
template<typename... Args>
void List<T, Allocator>::push_front(Args &&... args) {
    auto p = allocator_.allocate(1);
    allocator_.construct(p, head, args...);
    head = p;
}
