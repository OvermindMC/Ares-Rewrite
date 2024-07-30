#include "Category.h"

Category::Category(Manager* mgr, CategoryType type) : miPtr(mgr), cType(type) {
    //
};

Category::~Category() {
    //
};

CategoryType Category::getType() const {
    return this->cType;
};