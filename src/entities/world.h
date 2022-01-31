#ifndef __WORLD__
#define __WORLD__

#include <pch.h>
#include <graphics/shaders.h>

#define WORLD_SIZE 60

class World : public std::enable_shared_from_this<World>
{
    public:
        static std::shared_ptr<World> create();
        inline std::shared_ptr<World> get_ptr() { return shared_from_this(); }

        void render(Shader& shader);
        inline int get_block(int x, int y, int z) noexcept { return _map[x][y][z]; }
        inline void set_block(int x, int y, int z, int type) noexcept { _map[x][y][z] = type; }
        inline constexpr const unsigned int get_planet_size() const noexcept { return _planet_size; }

        ~World() = default;

    private:
        World() = default; // placing constructor here so the create function can access it, but not the user

        std::array<std::array<std::array<int, WORLD_SIZE>, WORLD_SIZE>, WORLD_SIZE> _map;
        inline static constexpr const unsigned int _planet_size = 20;
        std::shared_ptr<class Cube> _cube;
};

#endif // __WORLD__
