#ifndef MOVE_ONLY_CLASS_H
#define MOVE_ONLY_CLASS_H

namespace cpp_exercises {

class move_only
{
public:
    move_only();
    move_only(move_only&&);
    move_only(move_only const&) = delete;
    move_only& operator=(move_only&&);
    move_only& operator=(move_only const&) = delete;
    void operator()();
};


class MoveOnlyClass {
public:

    MoveOnlyClass();
    ~MoveOnlyClass();
    MoveOnlyClass(MoveOnlyClass&&);
    MoveOnlyClass(const MoveOnlyClass&) = delete;
    MoveOnlyClass& operator=(MoveOnlyClass&&);
    MoveOnlyClass& operator=(const MoveOnlyClass&) = delete;
    void operator()() {}
    double operator() (double d);
private:
    int id;
    int* pointer;
    double m_d;
};

}

#endif // MOVE_ONLY_CLASS_H
