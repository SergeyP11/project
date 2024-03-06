#include <iostream>

class DynVec {
    double *p_coord;
    int size;
public:
    DynVec(double *data, int count);
    DynVec operator+(const DynVec& ob);
    DynVec& operator+=(const DynVec& ob);
    ~DynVec();
    double getCoord(int index) const;
};

DynVec::DynVec(double *data, int count) {
    size = count;
    p_coord = new double[size];
    for (int i = 0; i < size; ++i) {
        p_coord[i] = data[i];
    }
}

DynVec DynVec::operator+(const DynVec& ob) {
    DynVec result(new double[size], size);
    for (int i = 0; i < size; ++i) {
        result.p_coord[i] = p_coord[i] + ob.p_coord[i];
    }
    return result;
}


// DynVec DynVec::operator+(const DynVec& ob) {
//     for (int i = 0; i < size; ++i) {
//         p_coord[i] = p_coord[i] + ob.p_coord[i];
//     }
//     return *this;
// }

DynVec& DynVec::operator+=(const DynVec& ob) {
    for (int i = 0; i < size; ++i) {
        p_coord[i] += ob.p_coord[i];
    }
    return *this;
}

DynVec::~DynVec() {
    delete[] p_coord;
}

double DynVec::getCoord(int index) const {
    return p_coord[index];
}

int main() {
    double data1[] = {1.0, 2.0, 3.0};
    double data2[] = {4.0, 5.0, 6.0};

    DynVec vec1(data1, 3);
    DynVec vec2(data2, 3);

    DynVec vec3 = vec1 + vec2;

    std::cout << "Result of addition: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << vec3.getCoord(i) << " ";
    }
    std::cout << std::endl;

    vec1 += vec2;

    std::cout << "Result of in-place addition: ";
    for (int i = 0; i < 3; ++i) {
        std::cout << vec1.getCoord(i) << " ";
    }
    std::cout << std::endl;

    return 0;
}
