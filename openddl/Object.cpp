#include "Object.h"

openddl::Object::Object() : tree(nullptr),index(0) {}
openddl::Object::Object(Tree * t,const unsigned int i)
: tree(t), index(i) {}

openddl::DataArrayList::DataArrayList(const Object & o)
: Object(o) 
{}
openddl::DataList::DataList(const Object & o)
: Object(o)
{}
openddl::Property::Property(const Object & o)
: Object(o)
{}
openddl::Structure::Structure(const Object & o)
: Object(o)
{}


openddl::DataArrayList::DataArrayList() {}
openddl::DataList::DataList() {}
openddl::Property::Property() {}
openddl::Structure::Structure() {}