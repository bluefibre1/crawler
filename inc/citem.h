#pragma once

#include "cobject.h"
#include "cdirection.h"
#include "cstring.h"

#include <memory>

class Item : public Object
{
public:
    Item();

    void setName(const String& name);

    const String& getName() const;

    enum Action
    {
        ACTION_NONE = 0,
        ACTION_EQUIPPABLE,
        ACTION_USABLE
    };

    Action getAction() const;

    enum Type
    {
        TYPE_NONE = 0,
        TYPE_WEAPON,
        TYPE_ARMOR
    };

    Type getType() const;

    virtual void use(Direction /*dir*/) {}

    Object* getOwner() const;

    void setOwner(Object* owner);

protected:
    Object* m_owner;
    Action m_action;
    Type m_type;
    String m_name;
};

typedef std::shared_ptr<Item> ItemSharedPtr;
typedef std::vector<ItemSharedPtr> ItemSharedPtrs;
