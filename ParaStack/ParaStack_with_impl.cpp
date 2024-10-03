#include <iostream>
#include <memory>

template <class T> class StackImpl {
public:
    StackImpl(size_t size = 0);
    virtual ~StackImpl();
    void Swap(StackImpl& other) throw();
    T* v_;
    size_t vsize_;
    size_t vused_;
private:
    StackImpl(const StackImpl&);
    StackImpl& operator =(const StackImpl&);

};

template <class T> StackImpl<T>::StackImpl(size_t size) :
    v_(static_cast<T*>
        (size == 0 ? 0 : operator new(sizeof(T) * size))),
    vsize_(size),
    vused_(0) {}
template <class T> StackImpl<T>::~StackImpl() {
    std::destroy(v_, v_ + vused_);
    operator delete(v_);
}
template <class T> void StackImpl<T>::Swap(StackImpl& other) throw() {
    std::swap(v_, other.v_);
    std::swap(vsize_, other.vsize_);
    std::swap(vused_, other.vused_);
}

template <class T> class Stack {
public:
    Stack(size_t size = 0) :impl_(size) {}
    Stack(const Stack& other) : impl_(other.impl_.vused_) {
        while (impl_.vused_ < other.impl_.vused_) {
            std::construct_at(impl_.v_ + impl_.vused_, other.impl_.v_[impl_.vused_]);
            ++impl_.vused_;
        }
    }
    Stack& operator = (const Stack& other) {
        Stack temp(other);
        impl_.Swap(temp.impl_);
        return *this;
    }
    size_t Count() const {
        return impl_.vused_;
    }
    void Push(const T& t) {
        if (impl_.vused_ == impl_.vsize_) {
            Stack temp(impl_.vsize_ * 2 + 1);
            while (temp.Count() < impl_.vused_) {
                temp.Push(impl_.v_[temp.Count()]);
            }
            temp.Push(t);
            impl_.Swap(temp.impl_);
        }
        else {
            std::construct_at(impl_.v_ + impl_.vused_, t);
            ++impl_.vused_;
        }
    }
    T& Top() {
        if (impl_.vused_ == 0) {
            throw "empty stack";
        }
        return impl_.v_[impl_.vused_ - 1];
    }
    void Pop() {
        if (impl_.vused_ == 0) {
            throw "pop from empty stack";
        }
        else {
            --impl_.vused;
            std::destroy(impl_.v_ + impl_.vused_);
        }
    }
private:
    StackImpl<T> impl_;
};

struct test {
    int a;
    double d;
    test() : a(1), d(2.2) {};
    test(const int& v1, const double& v2) : a(v1), d(v2) {}
    test(const test& other) {
        a = other.a;
        d = other.d;
    }
};
std::ostream& operator<<(std::ostream& os, const test& t) {
    os << t.a << " " << t.d << '\n';
    return os;
};
int main() {

    Stack<test> mS(1);
    test t0{ 2, 3.3 };
    mS.Push(t0);
    mS.Push(t0);
    mS.Push(t0);
    Stack<test> mS1(mS);
    test t1 = mS1.Top();
    std::cout << t1;
    return 0;
}
