#include "croom.h"
#include "crenderer.h"


// {
//     Strings graph;
//     graph.push_back("##########");
//     graph.push_back("#........#");
//     graph.push_back("#...--...#");
//     graph.push_back("#........#");
//     graph.push_back("####..####");

//     House h();
//     h.setGraph(graph);
//     h.setName("Potion Shop");

//     CharacterTemplates mandoryTemplates;
//     mandoryTemplates.push_back(&Characters::POTION_SELLER);
//     h.setMandatoryCharacterTemplates(mandoryTemplates);

//     CharacterTemplates randomTemplates;
//     randomTemplates.push_back(&Characters::KID);
//     h.setRandomCharacterTemplates(randomTemplates);
//     h.setMinCharacter(1);
//     h.setMaxCharacter(2);


// }


Room::Room()
    : m_surface()
{

}

void Room::setTilePtrSurface(const TilePtrSurface& surface)
{
    m_surface = surface;
}

void Room::draw(Renderer* r)
{
    if (r->isVisible(this))
    {
        std::for_each(
            m_surface.begin(), m_surface.end(), [this](const TilePtrs& tiles)
            {
                std::for_each(
                    tiles.begin(), tiles.end(), [](const Tile* tile)
                    {

                    });
            });
    }
}
