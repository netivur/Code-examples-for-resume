#include <iostream>
#include <memory>

template <class T> class StackImpl {
protected:
    StackImpl(size_t size = 0);
    virtual ~StackImpl();
    void Swap(StackImpl& other) throw();
    T* v_;
    size_t vsize_;
    size_t vused_;
private:
    StackImpl(const StackImpl&);
    StackImpl& operator=(const StackImpl&);

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

template <class T> class Stack : private StackImpl<T> {
public:
    Stack(size_t size = 0);    
    Stack(const Stack& other) : StackImpl<T>(other.vused_) {
        while (this->vused_ < other.vused_) {
            std::construct_at(this->v_ + this->vused_, other.v_[this->vused_]);
            ++this->vused_;
        }
    }
    Stack& operator = (const Stack& other) {
        Stack temp(other);
        this->Swap(temp);
        return *this;
    }
    size_t Count() const {
        return this->vused_;
    }
    void Push(const T& t) {
        if (this->vused_ == this->vsize_) {
            Stack temp(this->vsize_ * 2 + 1);
            while (temp.Count() < this->vused_) {
                temp.Push(this->v_[temp.Count()]);
            }
            temp.Push(t);
            this->Swap(temp);
        }
        else {
            std::construct_at(this->v_ + this->vused_, t);
            ++this->vused_;
        }
    }
    T& Top() {
        if (this->vused_ == 0) {
            throw "empty stack";
        }
        return this->v_[this->vused_ - 1];
    }
    void Pop() {
        if (this->vused_ == 0) {
            throw "pop from empty stack";
        }
        else {
            --this->vused_;
            std::destroy(this->v_ + this->vused_);
        }
    }
};

template<class T>
Stack<T>::Stack(size_t size) : StackImpl<T>(size)
{
}

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
    
    Stack<test> mS(5);
    test t0{ 2, 3.3 };
    mS.Push(t0);
    test t1 = mS.Top();
    std::cout << t1;
    Stack<test> mS1 = mS;
    std::cout << mS1.Top();
    Stack<test> mS2(mS);
    std::cout << mS2.Top();
	return 0;
}
