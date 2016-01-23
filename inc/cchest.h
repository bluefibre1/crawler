#pragma once

#include "cobject.h"
#include "citem.h"
#include "ccolor.h"

class Chest : public Object
{
public:
    Chest();

    virtual void draw(Renderer* r) override;

    void addItem(const ItemSharedPtr& item);

    void addItems(const ItemSharedPtrs& items);

    void removeItem(const ItemSharedPtr& item);

    void removeAllItems();

    const ItemSharedPtrs& getItems() const;

    virtual bool isCollidable() const override { return false; }

    virtual ObjectType getObjectType() const override { return OBJECT_TYPE_CHEST; }

private:
    char m_ch;
    Color m_color;
    ItemSharedPtrs m_items;
};

typedef std::shared_ptr<Chest> ChestSharedPtr;
