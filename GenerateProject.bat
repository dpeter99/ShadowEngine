cd ShadowEngine\dependencies\assimp
cmake CMakeLists.txt
cd ..\..\..

call dependencies\premake\bin\premake5.exe clean
call dependencies\premake\bin\premake5.exe vs2019
PAUSE