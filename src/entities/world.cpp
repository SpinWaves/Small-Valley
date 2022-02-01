#include "world.h"

World::World() : _cube(new Cube(std::move(get_ptr()))) {}

std::shared_ptr<World> World::create()
{
    std::shared_ptr<World> world(new World());

    std::array<int, WORLD_SIZE> temp;
    temp.fill(0);
   
    world->_map.fill(std::move(temp));

    return std::move(world);
}

void World::render(Shader& shader)
{
    for(int i = 1; i <= _planet_size; i++)
    {
        for(int j = 1; j <= _planet_size; j++)
        {
            _cube->set_pos(i, j, 0);
            _cube->render(shader);
        }
    }
}
