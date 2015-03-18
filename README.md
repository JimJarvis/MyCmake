Run `./gen_eclipse.sh` to generate a `project` folder that can be imported directly by Eclipse CDT 4.
Optionally, you can give the project folder a non-default name: `./gen_eclipse.sh <project_dir>`

`python patch_eclipse.py <project_dir>` patches the CMake generated files `.project` and `.cproject` to support multiple source directories in eclipse project explorer. Otherwise the syntax highlighting doesn't work correctly. 
Run `python patch_eclipse.py` without any argument to show more help. 

The provided cmake scripts support:

 - C++ 11 `<thread>`
 - Boost library
 - GTest
 - CTest (default cmake tests)'
