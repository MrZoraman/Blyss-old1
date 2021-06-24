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
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "StaticGeometry.hpp"
#include "wrappers/opengl/ShaderProgram.hpp"

namespace blyss
{
    std::unique_ptr<StaticGeometry> LoadGeometry(std::shared_ptr<ShaderProgram> program, const std::string& path)
    {
        Assimp::Importer importer;
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

        aiMesh* mesh = scene->mMeshes[0];
        std::vector<float> vertex_data(mesh->mNumVertices * 3);
        
        for (auto ii = 0; ii < mesh->mNumVertices; ++ii)
        {
            aiVector3D v = mesh->mVertices[ii];
            vertex_data[ii * 3 + 0] = v.x;
            vertex_data[ii * 3 + 1] = v.y;
            vertex_data[ii * 3 + 2] = v.z;
        }

        std::vector<std::uint32_t> index_data(mesh->mNumFaces * 3);
        for (auto ii = 0; ii < mesh->mNumFaces; ++ii)
        {
            aiFace f = mesh->mFaces[ii];
            for (auto kk = 0; kk < f.mNumIndices; ++kk)
            {
                index_data[ii * 3 + kk] = f.mIndices[kk];
            }
        }

        return std::make_unique<StaticGeometry>(vertex_data, index_data, std::move(program));
    }
}
