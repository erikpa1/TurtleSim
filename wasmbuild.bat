
REM C:\emsdk\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake

REM cmake -S . -B ./out -DCMAKE_TOOLCHAIN_FILE=%WASM_DCMAKE_TOOLCHAIN%


emcc main.cpp -o SimStudio.js


echo "Press something to close console"
pause