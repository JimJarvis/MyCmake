Run `./gen_eclipse.sh` to generate a `project` folder that can be imported directly by Eclipse CDT 4.
Optionally, you can give the project folder a non-default name: `./gen_eclipse.sh <project_dir>`

`python patch_eclipse.py <project_dir>` patches the CMake generated files `.project` and `.cproject` to support multiple source directories in eclipse project explorer. Otherwise the syntax highlighting doesn't work correctly. 
Run `python patch_eclipse.py` without any argument to show more help. 

Note that Nsight eclispe (3.x) indexer is so outdated that it doesn't support split source folder well. Every time you change CMakeLists.txt and rebuild, the patched file will break and the indexer will get confused and swamp the editor with false errors. 

One way around Nsight is to move `test` folder into `src` and keep the top level CMakeLists.txt inside `src`. Please refer to project Cadenza's directory organization. Then you need to run `patch_eclipse_nvcc_macro.py` instead of `patch_eclipse.py`

Even for eclipse 4.x, you will have to run `gen_eclipse.sh` again after rebuilding, though the indexer will not break. 

The provided cmake scripts support:

 - C++ 11 `<thread>`
 - Boost library
 - GTest
 - CTest (default cmake tests)'
