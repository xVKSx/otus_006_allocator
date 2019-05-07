#pragma once

template<typename T, size_t BatchSize>
class FixAllocator {
public:
    T *allocate(size_t n) {
        if (reserve_count_ + n > BatchSize) {
            throw std::bad_alloc();
        }
        if (current_point_ == nullptr) {
            auto p = std::malloc(BatchSize * sizeof(T));
            if (!p) {
                throw std::bad_alloc();
            }
            current_point_ = reinterpret_cast<T *>(p);
        }
        auto point = current_point_ + reserve_count_;
        reserve_count_ += n;
        return point;
    }

    template<typename U>
    struct rebind {
        using other = FixAllocator<U, BatchSize>;
    };

    void deallocate(T *p, std::size_t n) {
        reserve_count_--;
        if (reserve_count_ == 0) {
            std::free(p);
        }
    }

    template<typename U, typename ...Args>
    void construct(U *p, Args &&...args) {
        new(p) U(std::forward<Args>(args)...);
    }

    void destroy(T *p) {
        p->~T();
    }

    using value_type = T;
private:
    size_t reserve_count_ = 0;
    T *current_point_ = nullptr;
};