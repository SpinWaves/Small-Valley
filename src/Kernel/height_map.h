#ifndef __HEIGHT_MAP__
#define __HEIGHT_MAP__

#include <pch.h>

class HeightMap
{
    public:
        HeightMap() = default;
        void load_map(const char* path, float ratio = 1);
        inline std::vector<std::vector<int>> get_data() { return _map; }
        ~HeightMap() = default;

    private:
        std::vector<std::vector<int>> _map;
};

#endif // __HEIGHT_MAP__
