# Blyss game engine thing I don't really know ask me later

## Building

The following dependencies need to be installed beforehand to bootstrap
the build process:

* [Python3](https://www.python.org/) must be installed and on your path.
* [Requests](https://docs.python-requests.org/en/master/index.html) python module must be installed.
* [Boost](https://www.boost.org/) must be installed somewhere on your system.
* [CMake](https://cmake.org/) must be installed.

There are two scripts you want to run first. First is `download_deps.py`.
This pulls all the other dependencies from github and writes them to the
`lib` folder. Git does not need to be installed, it just just making simple
GET requests on the project's build artifacts.

The second script is _optional_: `WriteShaders.py`. This script takes the
shaders in the `shaders` folder and writes them into c++ source files to
be used at runtime. Having the shader sources in program memory means
files don't need to be read at runtime. However, this means that whenever
changes are made to the shader files, this script _must_ be run again!
This script is optional because the files `WriteShaders.py` generates are
committed in git.

There is one CMake variable you will need to set, and that is `BOOST_ROOT`.
This variable should point to the path where you installed Boost.

Once you have run the scripts and set the boost root CMake variable,
you can now run CMake on the project like normal. There should not be any
other CMake variables you need to set.

Here is a full example that works for me to get a running version of Blyss:

1. `git clone https://github.com/MrZoraman/Blyss.git`
1. `cd Blyss`
1. `python download_deps.py`
1. `cd build`
1. `cmake -DBOOST_ROOT=C:\Lib\boost_1_71_0 ..`
1. `msbuild Blyss.sln /p:Configuration=Release`
1. `cd Release`
1. `blyss.exe`
