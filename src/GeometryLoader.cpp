/*
 * Copyright (c) MrZoraman 2021
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include "GeometryLoader.hpp"

#include <cstdint>
#include <exception>
#include <memory>
#include <stdexcept>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <gsl/span>

#include "StaticGeometry.hpp"
#include "wrappers/opengl/ShaderProgram.hpp"

namespace blyss
{
    std::unique_ptr<StaticGeometry> LoadGeometry(std::shared_ptr<ShaderProgram> program, const std::string& path)
    {
        // Create importer.
        Assimp::Importer importer;

        // Load the file.
        const aiScene* scene = importer.ReadFile(
            path,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType);

        if (!scene)
        {
            throw std::exception("Unable to load file!");
        }

        // Grab the first mesh in the scene. We are assuming the scene only has one mesh.
        gsl::span<aiMesh*> meshes(scene->mMeshes, scene->mNumMeshes);
        aiMesh* mesh = meshes[0];

        // Create the vertex data buffer. The vertex data is a list of floats strung together,
        // so we multiply the number of vertices by 3 (x, y, z is 3 data points).
        const size_t data_points_per_vertex = 3;
        std::vector<float> vertex_data(mesh->mNumVertices * data_points_per_vertex);

        // Span provides safety with bounds checking.
        gsl::span<aiVector3D> vertices(mesh->mVertices, mesh->mNumVertices);

        // Fill up the vertex data buffer.
        for (size_t ii = 0; ii < vertices.size(); ++ii)
        {
            aiVector3D v = vertices[ii];
            vertex_data[ii * data_points_per_vertex + 0] = v.x;
            vertex_data[ii * data_points_per_vertex + 1] = v.y;
            vertex_data[ii * data_points_per_vertex + 2] = v.z;
        }

        // Create the index data buffer. The index data is a list of ints strung together,
        // so we multiply the number of indices by 3 (3 points per triangle).
        const size_t sides_per_triangle = 3;
        std::vector<std::uint32_t> index_data(mesh->mNumFaces * sides_per_triangle);

        // Span provides safety with bounds checking.
        gsl::span<aiFace> faces(mesh->mFaces, mesh->mNumFaces);

        // Fill up the index data buffer.
        for (size_t ii = 0; ii < faces.size(); ++ii)
        {
            aiFace f = faces[ii];

            // Span provides safety with bounds checking.
            gsl::span<unsigned> indices(f.mIndices, f.mNumIndices);

            // We are assuming that each face has three vertices. If the mesh contains quads
            // or something else for whatever reason, this won't work. So, we're going to bail
            // out if this assumption isn't right.
            if (indices.size() != sides_per_triangle)
            {
                throw std::logic_error("Mesh had a face that does not have exactly three vertices!");
            }


            // We can safely iterate, knowing that this face has exactly three vertices.
            for (size_t kk = 0; kk < indices.size(); ++kk)
            {
                index_data[ii * sides_per_triangle + kk] = indices[kk];
            }
        }

        // Construct and return the static geometry instance.
        return std::make_unique<StaticGeometry>(vertex_data, index_data, std::move(program));
    }
}
