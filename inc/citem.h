#pragma once

#include "cobject.h"

#include <string>

class Item : public Object
{
public:
    Item();

    void setName(const std::string& name);

    const std::string& getName() const;

private:
    std::string m_name;
};
