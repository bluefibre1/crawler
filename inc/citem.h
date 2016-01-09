#pragma once

#include "cobject.h"

#include <string>

class Item : public Object
{
public:
    Item();

    void setName(const std::string& name);

private:
    std::string m_name;
};
