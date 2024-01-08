rem Change Name of Output file here
set PROJECT_NAME=game

set mypath=%~dp0
cd "%mypath%"


call emsdk activate latest
call emcc -o %PROJECT_NAME%.html ../src/main.cpp -Os -Wall --preload-file ../assets/graphics --preload-file ../assets/sounds ../lib/libraylib.a -I ../include -L ../lib/libraylib.a -s USE_GLFW=3 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS -s ASSERTIONS --shell-file shell.html -DPLATFORM_WEB
call emrun %PROJECT_NAME%.html