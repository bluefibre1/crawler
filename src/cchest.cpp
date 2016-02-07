#include "cchest.h"
#include "ccolors.h"
#include "crenderer.h"
#include "cwindow.h"

Chest::Chest()
    : m_ch(']')
    , m_color(Colors::BROWN())
    , m_items()
{

}

void Chest::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        r->draw(getX(), getY(), getZ(), m_color, Colors::INVALID(), m_ch);
    }
}

void Chest::addItem(const ItemSharedPtr& item)
{
    if (std::find(m_items.begin(), m_items.end(), item) == m_items.end())
    {
        m_items.push_back(item);
    }
    item->setOwner(this);
}

void Chest::addItems(const ItemSharedPtrs& items)
{
    m_items.reserve(m_items.size() + items.size());
    m_items.insert(m_items.end(), items.begin(), items.end());
}

void Chest::removeItem(const ItemSharedPtr& item)
{
    item->setOwner(nullptr);
    m_items.erase(std::remove(m_items.begin(), m_items.end(), item),
        m_items.end());
}

void Chest::removeAllItems()
{
    m_items.clear();
}

const ItemSharedPtrs& Chest::getItems() const
{
    return m_items;
}

bool Chest::hasHint() const
{
    return !m_items.empty();
}

void Chest::printHint(Window* w) const
{
    w->print(Colors::WHITE(), "Found ");
    w->print(Colors::GREEN(), "chest");
}
