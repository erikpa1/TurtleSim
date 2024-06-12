

if not exist "./build" (
    REM If it doesn't exist, create it
    mkdir "build"
    build_full.bat
)



cd /d "./build"

cmake --build .

cd /d "./Debug"

Simstudio.exe