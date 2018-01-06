#include "cchestfactory.h"

#include "citemfactory.h"
#include "citemtemplates.h"
#include "cmath.h"

ChestSharedPtr ChestFactory::create()
{
    ChestSharedPtr c(new Chest());

    ItemTemplateSharedPtrs items;
    items.push_back(ItemTemplates::SPELL());
    items.push_back(ItemTemplates::SWORD());

    int n = Math::ceilRandom(3) + 1;
    for (int i = 0; i < n; i++)
    {
        int wIdx = Math::ceilRandom(items.size());
        ItemSharedPtr w(ItemFactory::create(items[wIdx]));
        c->addItem(w);
    }
    return c;
}
