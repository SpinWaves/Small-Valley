#include "world.h"
#include <graphics/matrixes.h>

float World::get_height(int x, int z) noexcept
{
    x = x < 0 ? 0 : x;
    z = z < 0 ? 0 : z;
    x = x >= _map.size() ? _map.size() - 1 : x;
    z = z >= _map.size() ? _map.size() - 1 : z;
    return _map[z][x];
}

Vec3<float> World::calculate_normal(int x, int z) noexcept
{
    float heightL = get_height(x - 1, z);
    float heightR = get_height(x + 1, z);
    float heightD = get_height(x, z - 1);
    float heightU = get_height(x, z + 1);
    Vec3<float> normal(heightL - heightR, 2.0f, heightD - heightU);
    normal.normalize();
    return std::move(normal);
}

World::map_type<Vec3<float>> World::generate_normals()
{
    World::map_type<Vec3<float>> normals;
    for(int z = 0; z < _world_size; z++)
    {
        for(int x = 0; x < _world_size; x++)
            normals[z][x] = calculate_normal(x, z);
    }
    return std::move(normals);
}

std::shared_ptr<World> World::create()
{
    std::shared_ptr<World> world(new World());

    World::map_type<int> temp = {
        std::array<int, 10>{8, 6, 5, 4, 2, 1, 2, 5, 9, 12},
        std::array<int, 10>{8, 5, 4, 2, 1, 0, 1, 4, 8, 13},
        std::array<int, 10>{7, 5, 3, 1, 0, 0, 0, 3, 7, 11},
        std::array<int, 10>{4, 4, 2, 0, 2, 0, 0, 2, 4, 8},
        std::array<int, 10>{3, 2, 1, 0, 1, 0, 1, 3, 5, 7},
        std::array<int, 10>{4, 3, 1, 0, 0, 0, 0, 2, 2, 4},
        std::array<int, 10>{5, 4, 3, 1, 1, 1, 1, 2, 5, 6},
        std::array<int, 10>{8, 7, 6, 4, 3, 2, 2, 3, 5, 8},
        std::array<int, 10>{12, 10, 8, 6, 4, 4, 3, 6, 7, 10},
        std::array<int, 10>{16, 14, 10, 8, 5, 5, 7, 8, 10, 11}
    };

    world->_map.swap(temp);
    world->_shader.create(MAIN_DIR"src/graphics/shaders/terrain/terrain.vert", MAIN_DIR"src/graphics/shaders/terrain/terrain.frag");

    world->load_meshes();

    return std::move(world);
}

int quantizeNormalized(float original, int highestLevel, bool is_signed)
{
    if(is_signed)
        original = original * 0.5f + 0.5f;

    return round(original * highestLevel);
}

int pack_int(float x, float y, float z, float w)
{
    int TEN_BITS_MAX = (int)(pow(2, 10) - 1);
	int TWO_BITS_MAX = (int)(pow(2, 2) - 1);

    int val = 0;
    val = val | (quantizeNormalized(w, TWO_BITS_MAX, false) << 30);
    val = val | (quantizeNormalized(z, TEN_BITS_MAX, true) << 20);
    val = val | (quantizeNormalized(y, TEN_BITS_MAX, true) << 10);
    val = val | quantizeNormalized(x, TEN_BITS_MAX, true);
    return val;
}

int storeQuad1(std::vector<int>& indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed)
{
    indices[pointer++] = topLeft;
    indices[pointer++] = bottomLeft;
    indices[pointer++] = mixed ? topRight : bottomRight;
    indices[pointer++] = bottomRight;
    indices[pointer++] = topRight;
    indices[pointer++] = mixed ? bottomLeft : topLeft;
    return pointer;
}

int storeQuad2(std::vector<int>& indices, int pointer, int topLeft, int topRight, int bottomLeft, int bottomRight, bool mixed)
{
    indices[pointer++] = topRight;
    indices[pointer++] = topLeft;
    indices[pointer++] = mixed ? bottomRight : bottomLeft;
    indices[pointer++] = bottomLeft;
    indices[pointer++] = bottomRight;
    indices[pointer++] = mixed ? topLeft : topRight;
    return pointer;
}

std::vector<int> generateIndexBuffer(int vertexCount)
{
    int indexCount = (vertexCount - 1) * (vertexCount - 1) * 6;
    std::vector<int> indices;
    indices.resize(indexCount);
    int pointer = 0;
    for(int col = 0; col < vertexCount - 1; col++)
    {
        for(int row = 0; row < vertexCount - 1; row++)
        {
            int topLeft = (row * vertexCount) + col;
            int topRight = topLeft + 1;
            int bottomLeft = ((row + 1) * vertexCount) + col;
            int bottomRight = bottomLeft + 1;
            if(row % 2 == 0)
                pointer = storeQuad1(indices, pointer, topLeft, topRight, bottomLeft, bottomRight, col % 2 == 0);
            else
                pointer = storeQuad2(indices, pointer, topLeft, topRight, bottomLeft, bottomRight, col % 2 == 0);
        }
    }
    return std::move(indices);
}

void World::load_meshes()
{
    std::vector<int> vertices;
    std::vector<float> normals;
    for(int z = 0; z < _world_size; z++)
    {
        for(int x = 0; x < _world_size; x++)
        {
            vertices.push_back(x);
            vertices.push_back(_map[z][x]);
            vertices.push_back(z);

            normals.push_back(pack_int(generate_normals()[z][x].X, generate_normals()[z][x].Y, generate_normals()[z][x].Z, 0.0f));
        }
    }
    std::vector<int> indices = std::move(generateIndexBuffer(_map.size()));

    glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

    if(glIsBuffer(_vbo) == GL_TRUE)
        glDeleteBuffers(1, &_vbo);
    if(glIsBuffer(_ebo) == GL_TRUE)
        glDeleteBuffers(1, &_ebo);

	glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);
    
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() + normals.size(), 0, GL_STATIC_DRAW);

    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size(), &vertices[0]);
    glBufferSubData(GL_ARRAY_BUFFER, vertices.size(), normals.size(), &normals[0]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(vertices)));
    glVertexAttribPointer(2, 4, GL_UNSIGNED_INT_2_10_10_10_REV, GL_TRUE, 0, (void*)vertices.size());
	
	glEnableVertexAttribArray(0); // vertices
	//glEnableVertexAttribArray(1); // color
	glEnableVertexAttribArray(2); // normals

    if(glIsBuffer(_vbo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Buffer Object (VBO) for the terrain mesh");
    if(glIsBuffer(_ebo) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Element Buffer Object (EBO) for the terrain mesh");
    if(glIsVertexArray(_vao) != GL_TRUE)
        log::report(log_type::fatal_error, "unable to generate a Vertex Array Object (VAO) for the terrain mesh");
        
    glBindVertexArray(0);
}

void World::render()
{
    _shader.bindShader();

    _shader.setMat4("model", Matrixes::get_matrix(matrix::model));
    _shader.setMat4("view", Matrixes::get_matrix(matrix::view));
    _shader.setMat4("proj", Matrixes::get_matrix(matrix::proj));

    glBindVertexArray(_vao);
  
    glDrawElements(GL_TRIANGLES, _map.size(), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);

    _shader.unbindShader();
}

World::~World()
{
    glDeleteVertexArrays(1, &_vao);
    glDeleteBuffers(1, &_vbo);
    glDeleteBuffers(1, &_ebo);
}
