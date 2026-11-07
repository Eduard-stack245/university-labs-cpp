#pragma once
// ---------------------------------------------------------------------------
// myvec::Vector<T> - a dynamic array, the grown-up version of the Dynamic_Arr class from the
// "2-Lb_1_1 dynamic array" lab (see projects/dynamic-array-class).
//
//   * works for any element type (also types without a default constructor, and move-only types)
//   * rule of five: copy / move constructor, copy / move assignment, destructor - no leaks, no double delete
//   * grows by doubling, so push_back is amortised O(1)
//   * iterators are plain pointers: range-for and <algorithm> (std::sort, std::find, ...) work
//   * if an element's constructor throws while the array grows, the vector stays unchanged
//     (strong exception guarantee for push_back / emplace_back)
// ---------------------------------------------------------------------------
#include <algorithm>
#include <cstddef>
#include <initializer_list>
#include <iterator>
#include <new>
#include <stdexcept>
#include <utility>

namespace myvec {

template <class T>
class Vector
{
public:
    using value_type = T;
    using size_type = std::size_t;
    using iterator = T*;
    using const_iterator = const T*;

    // ---- construction / destruction -------------------------------------------
    Vector() noexcept = default;

    explicit Vector(size_type count)                          // `count` default-constructed elements
    {
        reserve(count);
        for (size_type i = 0; i < count; i++) emplace_back();
    }

    Vector(size_type count, const T& value)                   // `count` copies of `value`
    {
        reserve(count);
        for (size_type i = 0; i < count; i++) emplace_back(value);
    }

    Vector(std::initializer_list<T> items)
    {
        reserve(items.size());
        for (const T& x : items) emplace_back(x);
    }

    Vector(const Vector& other)
    {
        reserve(other.size_);
        for (size_type i = 0; i < other.size_; i++) emplace_back(other.data_[i]);
    }

    Vector(Vector&& other) noexcept : data_(other.data_), size_(other.size_), cap_(other.cap_)
    {
        other.data_ = nullptr; other.size_ = other.cap_ = 0;
    }

    // One assignment operator for copy and move (copy-and-swap): safe for self-assignment.
    Vector& operator=(Vector other) noexcept { swap(other); return *this; }

    ~Vector() { release(); }

    void swap(Vector& other) noexcept
    {
        std::swap(data_, other.data_); std::swap(size_, other.size_); std::swap(cap_, other.cap_);
    }

    // ---- size ------------------------------------------------------------------
    size_type size() const noexcept { return size_; }
    size_type capacity() const noexcept { return cap_; }
    bool empty() const noexcept { return size_ == 0; }

    void reserve(size_type new_cap) { if (new_cap > cap_) reallocate(new_cap); }
    void shrink_to_fit() { if (cap_ > size_) reallocate(size_); }

    // ---- element access ----------------------------------------------------------
    T& operator[](size_type i) { return data_[i]; }                 // no check (like std::vector)
    const T& operator[](size_type i) const { return data_[i]; }
    T& at(size_type i) { check(i); return data_[i]; }               // throws std::out_of_range
    const T& at(size_type i) const { check(i); return data_[i]; }
    T& front() { check(0); return data_[0]; }
    const T& front() const { check(0); return data_[0]; }
    T& back() { check(size_ ? size_ - 1 : 0); return data_[size_ - 1]; }
    const T& back() const { check(size_ ? size_ - 1 : 0); return data_[size_ - 1]; }
    T* data() noexcept { return data_; }
    const T* data() const noexcept { return data_; }

    iterator begin() noexcept { return data_; }
    iterator end() noexcept { return data_ + size_; }
    const_iterator begin() const noexcept { return data_; }
    const_iterator end() const noexcept { return data_ + size_; }
    const_iterator cbegin() const noexcept { return data_; }
    const_iterator cend() const noexcept { return data_ + size_; }

    // ---- modifiers -------------------------------------------------------------
    template <class... Args>
    T& emplace_back(Args&&... args)
    {
        if (size_ == cap_) {
            // Build the new element FIRST (the arguments may refer to an element of this vector),
            // then move the old ones over. Any exception leaves the vector as it was.
            const size_type new_cap = cap_ ? cap_ * 2 : 4;
            T* fresh = allocate(new_cap);
            try { ::new (static_cast<void*>(fresh + size_)) T(std::forward<Args>(args)...); }
            catch (...) { deallocate(fresh); throw; }
            size_type done = 0;
            try { for (; done < size_; done++) ::new (static_cast<void*>(fresh + done)) T(std::move_if_noexcept(data_[done])); }
            catch (...) { destroy(fresh, fresh + done); fresh[size_].~T(); deallocate(fresh); throw; }
            destroy(data_, data_ + size_);
            deallocate(data_);
            data_ = fresh;
            cap_ = new_cap;
        }
        else ::new (static_cast<void*>(data_ + size_)) T(std::forward<Args>(args)...);
        ++size_;
        return data_[size_ - 1];
    }

    void push_back(const T& value) { emplace_back(value); }
    void push_back(T&& value) { emplace_back(std::move(value)); }

    void pop_back() { check(size_ ? size_ - 1 : 0); data_[--size_].~T(); }

    void clear() noexcept { destroy(data_, data_ + size_); size_ = 0; }

    // Inserts before `pos`; returns an iterator to the new element.
    iterator insert(const_iterator pos, T value)
    {
        const size_type index = static_cast<size_type>(pos - data_);
        if (index > size_) throw std::out_of_range("Vector::insert: position out of range");
        emplace_back(std::move(value));
        std::rotate(data_ + index, data_ + size_ - 1, data_ + size_);
        return data_ + index;
    }

    // Removes the element at `pos`; returns an iterator to the element that followed it.
    iterator erase(const_iterator pos)
    {
        const size_type index = static_cast<size_type>(pos - data_);
        check(index);
        std::move(data_ + index + 1, data_ + size_, data_ + index);
        data_[--size_].~T();
        return data_ + index;
    }

    void resize(size_type count)
    {
        if (count < size_) { destroy(data_ + count, data_ + size_); size_ = count; return; }
        reserve(count);
        while (size_ < count) emplace_back();
    }

    void resize(size_type count, const T& value)
    {
        if (count < size_) { destroy(data_ + count, data_ + size_); size_ = count; return; }
        T copy(value);                                   // `value` might live inside this vector
        reserve(count);
        while (size_ < count) emplace_back(copy);
    }

private:
    static T* allocate(size_type n) { return n ? static_cast<T*>(::operator new(n * sizeof(T))) : nullptr; }
    static void deallocate(T* p) noexcept { ::operator delete(p); }
    static void destroy(T* first, T* last) noexcept { for (; first != last; ++first) first->~T(); }

    void release() noexcept { destroy(data_, data_ + size_); deallocate(data_); data_ = nullptr; size_ = cap_ = 0; }

    void check(size_type i) const { if (i >= size_) throw std::out_of_range("Vector: index out of range"); }

    void reallocate(size_type new_cap)                   // new_cap >= size_
    {
        T* fresh = allocate(new_cap);
        size_type done = 0;
        try { for (; done < size_; done++) ::new (static_cast<void*>(fresh + done)) T(std::move_if_noexcept(data_[done])); }
        catch (...) { destroy(fresh, fresh + done); deallocate(fresh); throw; }
        destroy(data_, data_ + size_);
        deallocate(data_);
        data_ = fresh;
        cap_ = new_cap;
    }

    T* data_ = nullptr;
    size_type size_ = 0;
    size_type cap_ = 0;
};

template <class T> bool operator==(const Vector<T>& a, const Vector<T>& b) { return a.size() == b.size() && std::equal(a.begin(), a.end(), b.begin()); }
template <class T> bool operator!=(const Vector<T>& a, const Vector<T>& b) { return !(a == b); }
template <class T> void swap(Vector<T>& a, Vector<T>& b) noexcept { a.swap(b); }

} // namespace myvec
