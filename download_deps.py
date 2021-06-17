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

# This is a python script file instead of a shell script because other scripts
# require python, and I want to minimize the amount of stars you need to align
# on the build system for the project to be buildable.

import requests
import zipfile
import io
import os

BASIC_DEPENDENCIES = [
    {
        "Folder Name": "imgui",
        "Url": "https://github.com/ocornut/imgui/archive/refs/tags/v1.83.zip"
    },
    {
        "Folder Name": "glfw",
        "Url": "https://github.com/glfw/glfw/releases/download/3.3.4/glfw-3.3.4.zip"
    },
    {
        "Folder Name": "glad_builder",
        "Url": "https://github.com/Dav1dde/glad/archive/refs/tags/v0.1.34.zip"
    }
]

def install_basic_dependencies():
    for dependency in BASIC_DEPENDENCIES:
        folder_name = dependency["Folder Name"]
        url = dependency["Url"]

        # Don't download the file if it is already downloaded.
        # I don't want to unecessarily download stuff from servers. Tragedy
        # of the commons and all that. To force a re-download, the folder must
        # be deleted before running this script.
        if (os.path.isdir(folder_name)):
            print(f"{folder_name} already found, skipping.")
            continue

        r = requests.get(url)

        # This wraps the request data in a bytes io container so that it can be
        # fed straight into the zipfile without needing to write it to the disk
        # first.
        data = io.BytesIO(r.content)
        archive = zipfile.ZipFile(data)

        # It doesn't matter what entry we get. We just want to get the root
        # folder of the first entry. Zips from github all seem to be formatted
        # with the root folder being the project name + version number, and then
        # the actual stuff is in that folder.
        zip_entry = archive.namelist()[0]
        root_folder = zip_entry[:zip_entry.find("/")]

        archive.extractall()

        # I rename that root folder I got earlier to the name of the project
        # without the version in it. Now if I ever upgrade my dependencies it
        # doesn't break a bunch of stuff because file paths changed.
        os.rename(root_folder, folder_name)

def install_glad():
    os.chdir("glad_builder")

    # I don't want to overwrite the glad directory, since I'm worried in the
    # future if glad changes and has different files, the glad folder will
    # turn into a mess, because its no longer "overwriting", its just adding
    # new files to the folder with the old files.
    if (os.path.isdir("glad")):
        print("Glad is already configured, skipping.")
        return

    os.system("python -m glad --spec gl --generator c-debug --out-path ../glad --reproducible")
    os.chdir("..")

if __name__ == '__main__':
    os.chdir("lib")
    install_basic_dependencies()
    install_glad()