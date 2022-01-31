#include "world.h"
#include "cube.h"

std::shared_ptr<World> World::create()
{
    std::shared_ptr<World> world(new World());

    std::array<int, WORLD_SIZE> temp;
    temp.fill(0);
    std::array<std::array<int, WORLD_SIZE>, WORLD_SIZE> temp_2;
    temp_2.fill(std::move(temp));
   
    world->_map.fill(std::move(temp_2));
    world->_cube = std::move(std::make_shared<Cube>(std::move(world->get_ptr())));

    return world;
}

void World::render(Shader& shader)
{
    for(int i = 1; i <= _planet_size; i++)
    {
        for(int j = 1; j <= _planet_size; j++)
        {
            for(int k = 1; k <= _planet_size; k++)
            {
                _cube->set_pos(i, j, k);
                _cube->render(shader);
            }
        }
    }
}
