//
// Created by 阮波 on 2023/1/13.
//

#include <iostream>
#include <list>
#include <algorithm>

namespace stl {

static void basic_test() {
    {
        std::list<int> l;
        l.push_back(10);
        l.push_front(1);
        l.push_front(2);
        l.push_back(11);

        // 2 1 10 11
        std::for_each(l.begin(), l.end(), [](int elem){ std::cout << elem << " ";} );
        std::cout << std::endl;

        l.emplace_back(12);
        l.emplace_front(3);

        // 3 2 1 10 11 12
        std::for_each(l.begin(), l.end(), [](int elem){ std::cout << elem << " "; } );
        std::cout << std::endl;

        // is_sorted
        std::cout << std::is_sorted(l.begin(), l.end()) << std::endl;  // 0

        // sort
        l.sort();
        std::cout << std::is_sorted(l.begin(), l.end()) << std::endl;  // 1

        // 1 2 3 10 11 12
        std::for_each(l.begin(), l.end(), [](int elem) { std::cout << elem << " "; } );
        std::cout << std::endl;

        // reverse sort
        l.sort([](int x, int y) {return x > y; });
        // 12 11 10 3 2 1
        std::for_each(l.begin(), l.end(), [](int elem) { std::cout << elem << " "; } );
        std::cout << std::endl;

        l.sort([](int x, int y) -> bool {return x <= y; });
        // 1 2 3 10 11 12
        std::for_each(l.begin(), l.end(), [](int elem) -> void { std::cout << elem << " "; });
        std::cout << std::endl;

        // remove
        l.remove(10);

        // 1 2 3 11 12
        std::for_each(l.begin(), l.end(), [](auto elem) -> void {std::cout << elem << " "; } );
        std::cout << std::endl;

        // remove_if, remove one element
        l.remove_if([](auto elem){ return elem==3; });

        // 1 2 11 12
        std::for_each(l.begin(), l.end(), [](int elem) -> void {std::cout << elem << " ";} );
        std::cout << std::endl;

        // remove_if, remove multiple element
        l.remove_if([](auto elem) -> bool { return elem > 1; } );

        // 1
        std::for_each(l.begin(), l.end(), [](auto elem) -> void { std::cout << elem << " "; } );
        std::cout << std::endl;

        // empty
        std::cout << l.empty() << std::endl; // 0

        // clear
        l.clear();

        // []
        std::for_each(l.begin(), l.end(), [](auto elem) { std::cout << elem << " "; });
        std::cout << std::endl;

        // empty
        std::cout << l.empty() << std::endl; // 1

        // merge
        {
            std::list<int> l1 = {1, 3, 2};
            std::list<int> l2 = {8, 9, 10};
            l1.merge(l2);

            std::cout << "after merge:" << std::endl << "l1:";
            // 1 3 2 8 9 10
            std::for_each(l1.begin(), l1.end(), [](auto elem){ std::cout << elem << " "; });
            std::cout << std::endl << "l2:";
            // []
            std::for_each(l2.begin(), l2.end(), [](auto elem) {std::cout << elem << " "; });
            std::cout << std::endl;
        }
    }
}

class ListItem {
private:
    int _data;

public:
    ListItem(): _data(0) {
        std::cout << "ListItem()" << std::endl;
    }
    ListItem(int data): _data(data) {
        std::cout << "ListItem(" << this->_data << ")" << std::endl;
    }
    ListItem(const ListItem& rhs) : _data(rhs._data) {
        std::cout << "ListItem(const ListItem& rhs)" << std::endl;
    }
    ListItem& operator=(const ListItem& other) {
        _data = other._data;
        std::cout << "ListItem operator=(const ListItem& other)" << std::endl;
        return *this;
    }
    ~ListItem() {
        std::cout << "~ListItem()" << std::endl;
    }

public:
    int get_data() const {
        return this->_data;
    }
};

void list_class_object_element_test() {
    std::cout << "\npush_back a new object" << std::endl;
    {
        std::list<ListItem> l;

        // ListItem() call the default-constructor(ListItem()) to create an instance and psss the
        // instance to push_back function.
        // Inside the push_back function, call the copy-constructor(ListItem(const ListItem& rhs)
        // and push the instance to the end of the list.
        l.push_back(ListItem(1));
        for(auto& elem: l) {
            std::cout << elem.get_data() << " ";
        }  // 1
        std::cout << std::endl;
    }

    std::cout << "\nemplace_back a new object" << std::endl;
    {
        std::list<ListItem> l;
        // The call of default-constructor(ListItem()) and copy-constructor(ListItem(const ListItem& other))
        // is the same as push_back() above.
        l.emplace_back(ListItem(10));
        for(auto& elem: l) {
            std::cout << elem.get_data() << " ";
        } // 10

        std::cout << std::endl;
    }

    std::cout << "passing element class's constructor parameter to emplace_back function to avoid extra constructor calling" << std::endl;
    {
        std::list<ListItem> l;

        // The emplace_back function call accept argument and pass the argument to
        // the element class's constructor function to create a new instance of element class.
        // By doing this, only one element is created (only one constructor is called).
        l.emplace_back(11);
        for(auto& elem: l) {
            std::cout << elem.get_data() << " ";
        } // 11
        std::cout << std::endl;
    }
}

void list_test() {
//    basic_test();

    list_class_object_element_test();

}

}  // end of namespace
