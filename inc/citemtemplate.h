#pragma once

#include "ccolor.h"
#include "cstring.h"

#include <vector>

class ItemTemplate
{
public:

    ItemTemplate(
        int probabylityWeight,
        const String& name);

    virtual ~ItemTemplate() {}

    enum class Type
    {
        NONE,
            WEAPON,
            POTION
    };

    virtual Type getType() const { return Type::NONE; }

    int getProbabilityWeight() const { return m_probabilityWeight; }

    const String& getName() const { return m_name; }

private:
    int m_probabilityWeight;
    String m_name;
};

typedef std::shared_ptr<ItemTemplate> ItemTemplateSharedPtr;
typedef std::vector<ItemTemplateSharedPtr> ItemTemplateSharedPtrs;
