#
# Copyright (c) MrZoraman 2021
#
# This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#

OUT_FILE = "src/ShaderSources.cpp"

IN_FRAG = "shaders/shader.frag"
IN_VERT = "shaders/shader.vert"
IN_LICENSE = "license_comments.txt"

if __name__ == '__main__':
    with open(OUT_FILE, "w") as out_file:
        with open(IN_LICENSE, "r") as license_file:
            for line in license_file:
                out_file.write(line)
        out_file.write("\n")
        out_file.write("#include \"ShaderSources.hpp\"\n\n")
        out_file.write("namespace blyss\n")
        out_file.write("{\n")
        out_file.write("    const char* const kVertexShaderSource =")
        with open(IN_VERT, "r") as vertex_file:
            for line in vertex_file:
                out_file.write(f"\n        \"{line.strip()}\\n\"")
        out_file.write(";\n\n")
        out_file.write("    const char* const kFragmentShaderSource =")
        with open(IN_FRAG, "r") as fragment_file:
            for line in fragment_file:
                out_file.write(f"\n        \"{line.strip()}\\n\"")
        out_file.write(";\n")
        out_file.write("}\n")
