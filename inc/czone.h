#include "czone.h"

class Zone
{
public:
    Zone();

    void add(const ObjectSharedPtr& object);

    void remove(const ObjectSharedPtr& object);

private:
    ObjectSharedPtrs m_objects;
};
