//
// Created by 阮波 on 2023/7/3.
//

#include <vector>
#include <iostream>

using std::cout, std::endl, std::vector;


namespace optimize {

class PointItem {
private:
    int _x;
    int _y;

public:
    PointItem(int x, int y) : _x(x), _y(y) {
        cout << "PointItem(" << _x << ", " << _y << ")" << endl;
    };
    PointItem(const PointItem& rhs) {
        cout << "Copied PointItem" << endl;
        _x = rhs._x;
        _y = rhs._y;
    }
};


void vector_optimize() {

    if(false) {
        // 6 copies
        vector<PointItem> vecs;
        vecs.push_back(PointItem(1, 2));
        vecs.push_back(PointItem(3, 4));
        vecs.push_back(PointItem(5, 6));
    }

    if(false) {
        // 3 copies
        vector<PointItem> vecs;
        vecs.reserve(3);

        vecs.push_back(PointItem(1, 2));
        vecs.push_back(PointItem(3, 4));
        vecs.push_back(PointItem(5, 6));
    }


    if(true) {
        // 0 copies
        vector<PointItem> vecs;
        vecs.reserve(3);

        vecs.emplace_back(1, 2);
        vecs.emplace_back(3, 4);
        vecs.emplace_back(5, 6);
    }

}


} // end of optimize
