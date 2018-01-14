#include "croom.h"
#include "crenderer.h"
#include "cworldcell.h"

Room::Room()
    : m_name()
    , m_cells(nullptr)
    , m_width(0)
    , m_height(0)
{

}

Room::~Room()
{
    delete [] m_cells;
}

void Room::setCells(int width, int height, WorldCell* cells)
{
    delete [] m_cells;
    m_cells = cells;
    m_width = width;
    m_height = height;
}

void Room::setName(const String& name)
{
    m_name = name;
}
