#ifndef NULLABLE_H
#define NULLABLE_H

#include "sqlutil2_global.h"

template<class T>
class SQLUTIL2SHARED_EXPORT Nullable
{
public:
    Nullable(T val) {
        this->value = val;
        this->valIsNull = false;
    }

    Nullable() {
        this->valIsNull = true;
    }

    ~Nullable(){

    }

//    static Nullable<int> integer(int val) {
//       return Nullable<int>(val);
//    }

//    static Nullable<int> integer(const QVariant& val) {
//       return val.isNull() ? Nullable<int>() : Nullable<int>(val.toInt());
//    }
protected:
    bool valIsNull;

 T value;
 public:

 bool isNull() {
     return valIsNull;
 }

    void setNull() {
        valIsNull = true;
    }

    void setVal(T val) {
        valIsNull = false;
        this->value = val;
    }

    T val() const {
        return value;
    }
};



#endif // NULLABLE_H
