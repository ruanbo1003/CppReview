//
// Created by 阮波 on 2023/1/29.
//

#include <memory>
#include "comm/log.h"


namespace cpp11 {

class TestPointer1 {
private:
    std::string _name;

public:
    TestPointer1(): _name("") {
        Log("PointItem()");
    }
    TestPointer1(const std::string& name) : _name(name) {
        Log("PointItem(%s)", _name.c_str());
    }
    ~TestPointer1() {
        Log("~PointItem(%s)", _name.c_str());
    }

public:
    void display() const {
        Log("name:%s", _name.c_str());
    }
};
using TestPointer1Ptr = TestPointer1*;


static void class_reference_parameter(const TestPointer1& pointer) {
    pointer.display();
}

static void unique_ptr_test() {
    Log("when use raw pointer, we must release(delete) resource manual");
    {
        TestPointer1Ptr p1 = new TestPointer1("raw pointer 1");
        p1->display();  //

        // if not delete p1 manual, there will be a memory leak.
        delete p1;

        TestPointer1Ptr p2 = new TestPointer1("raw pointer 2");
        // the `delete p2` do not be called, so the destructor of TestPointer1 not called.
    }

    Log("\nuse std::unique_ptr to hold the allocated resource");
    {
        std::unique_ptr<TestPointer1> p(new TestPointer1(std::string("unique ptr 1")));
        p->display();  //

        // the destructor of p will be automatically called out of the scope.
    }

    Log("assignment of unique_ptr");
    {
        std::unique_ptr<TestPointer1> p1(new TestPointer1(std::string("unique ptr 1")));

        // std::unique_ptr<> object cannot be copied or assigned to another object.
        //std::unique_ptr<TestPointer1> p2(p1);  // error: call to implicitly-deleted copy constructor of `std::unique_pt`
        //std::unique_ptr<TestPointer1> p3;
        //p3 = p1;  // error: object of type `std::unique_ptr` cannot be assigned because its copy assignment operator is implicitly deleted.

        std::unique_ptr<TestPointer1> p4;
        if(p4) {
            Log("p4 is not empty");
        } else {
            // empty
            Log("p4 is empty");
        }

        p4 = std::move(p1);
        if(p4) {
            // not empty
            Log("p4 is not empty after std::move assignment of p1");
        } else {
            Log("p4 is empty after std::move assignment of p1");
        }

        if(p1) {
            Log("p1 is not empty after std::move assignment to p4");
        } else {
            // empty
            Log("p1 is empty after std::move assignment to p4");
        }

        std::unique_ptr<TestPointer1> p5(std::move(p4));
        p5->display(); // unique ptr 1

        // use reset() when we want to free the memory owned by the smart pointer before the
        // smart pointer goes out of scope.
        p5.reset();  // reset() will call the destructor of p5.
    }

    Log("\nthe usage of std::unique release");
    {
        std::unique_ptr<TestPointer1> p(new TestPointer1(std::string("release")));
        auto p0 = p.release();
        if(p) {
            Log("p is not empty after release()");
        } else {
            // empty
            Log("p is empty after release()")
        }

        // after release, we should call the `delete p0` manually.
        delete p0;
    }
    Log("\nout of scope, to see the release point of std::unique_ptr");

    Log("\naccess the encapsulated raw pointer and pass the reference to function. Using * operation");
    {
        std::unique_ptr<TestPointer1> p(new TestPointer1("access raw pointer"));
        class_reference_parameter(*p);
    }

    Log("\nuse std::make_unique to create a unique_ptr");
    {
        std::unique_ptr<TestPointer1> p = std::make_unique<TestPointer1>(TestPointer1("make_unique"));
        p->display();
    }
}


static void shared_ptr_test();
static void weak_ptr_test();

void smart_pointer_test() {
//    unique_ptr_test();

    shared_ptr_test();

//    weak_ptr_test();
}

static void shared_ptr_as_parameter(const std::shared_ptr<TestPointer1>& p) {
    p->display();
    Log("in function scope, use_count:%ld", p.use_count());
}

class CircularItem {
private:
    std::shared_ptr<CircularItem> _next;

public:
    CircularItem() {
        Log("CircularItem()");
    }
    ~CircularItem() {
        Log("~CircularItem()");
    }

public:
    void set_next(std::shared_ptr<CircularItem>& next) {
        _next = next;
    }
};

class CircularItemWeak {
private:
    int _data;
    std::weak_ptr<CircularItemWeak> _next;

public:
    CircularItemWeak() : _data{0}, _next{} {
        Log("CircularItemWeak()");
    }
    ~CircularItemWeak() {
        Log("~CircularItemWeak()");
    }

public:
    void set_next(std::weak_ptr<CircularItemWeak>& next) {
        _next = next;
    }

    int get_data() const {
        return _data;
    }

    void display() const {
        Log("data:%d", _data);
        auto p = _next.lock();
        if(p) {
            Log("data:%d, next data:%d", _data, p->_data);
        }
    }
};

static void shared_ptr_test() {
    Log("\nautomatically free memory when std::shared_ptr goes out of scope");
    {
        std::shared_ptr<TestPointer1> p1(new TestPointer1("shared_ptr 1"));
        p1->display();
        auto use_count = p1.use_count();
        Log("p1 use count:%ld", use_count);
    }  // the destructor will be called.
    Log("p1 goes of out scope.");

    Log("\nmultiple owner of raw-pointer");
    {
        std::shared_ptr<TestPointer1> p1(new TestPointer1("multiple owner"));
        std::shared_ptr<TestPointer1> p2 = p1;
        p2->display();

        // after assign p1 to p2, both p1 and p2 owns the same raw-pointer.
        bool is_equal = p1.get() == p2.get();
        Log("raw pointer is equal:%d", is_equal);  // 1

        // the use_count is the same, which is the count which raw-pointer
        // owned by std::shared_ptr.
        long use_count_1 = p1.use_count();
        long use_count_2 = p2.use_count();
        Log("use_count:%ld, %ld", use_count_1, use_count_2);  // 2, 2

        // p1 and p2 are not unique.
        Log("unique p1:%d, p2:%d", p1.unique(), p2.unique()); // 0, 0

        p1.reset();  // reset std::shared_ptr p1

        // after reset, p1 owns nothing.
        // so p1 is empty, and use_count count-down to 1.
        use_count_1 = p1.use_count();
        use_count_2 = p2.use_count();
        Log("use count:%ld, %ld", use_count_1, use_count_2); // 0, 1

        if(p1) {
            Log("p1 is not empty");
        } else {
            // empty
            Log("p1 is empty");
        }

        // now, only p2 owns the raw-pointer, so p2 is unique.
        Log("unique p2:%d", p2.unique());  // 1
    }

    Log("\nshared_ptr as a function parameter");
    {
        std::shared_ptr<TestPointer1> p(new TestPointer1("parameter"));
        Log("before pass to parameter, use_count:%ld", p.use_count());

        // the function parameter is a reference of std::shared_ptr,
        // so the use_count does not increase.
        shared_ptr_as_parameter(p);  // 1
        Log("after function return, use_count:%ld", p.use_count());
    }

    Log("\ncircular reference of std::shared_ptr instances");
    {
        std::shared_ptr<CircularItem> p1(new CircularItem());
        std::shared_ptr<CircularItem> p2(new CircularItem());

        p1->set_next(p2);
        p2->set_next(p1);
    }  // because p1 and p2 is circular reference, no destructor call when go out of scope.

    Log("\nuse std::make_shared_ptr to create a std::shared_ptr");
    {
        std::shared_ptr<TestPointer1> p = std::make_shared<TestPointer1>(TestPointer1("std::make_shared"));
        p->display();
    }
}

static void weak_ptr_test() {
    Log("\ndeclare weak_ptr");
    {
        std::shared_ptr<TestPointer1> p0(new TestPointer1("weak test"));
        std::weak_ptr<TestPointer1> p1;
        if(p1.expired()) {
            // expired
            Log("p1 expired")
        }
        Log("use count, p0:%ld, p1:%ld", p0.use_count(), p1.use_count());  // 1, 0

        p1 = p0;
        if(p1.expired()) {
            Log("p1 expired");
        } else {
            // not expired
            Log("p1 not expired");
        }
        // after assign shared_ptr to weak_ptr, the use_count will not increase.
        Log("use count, p0:%ld, p1:%ld", p0.use_count(), p1.use_count());  // 1, 1

        auto p2 = p1.lock();
        if(p2) {
            // not empty
            Log("p2 is not empty");
        } else {
            Log("p2 is empty");
        }

        auto p3 = p1.lock();
        if(p3) {
            // not emtpy
            Log("p3 is not empty");
        } else {
            Log("p3 is empty");
        }
    }
}

}  // end of namespace
