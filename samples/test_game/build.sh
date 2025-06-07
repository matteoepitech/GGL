#!/usr/bin/env bash

cd ../../
./build.sh
cd ./samples/test_game/

if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    echo "Building for macOS..."
    gcc main.c -o program -fsanitize=address -lglfw -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
elif [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # Linux
    echo "Building for Linux..."
    gcc main.c -o program -fsanitize=address -lglfw -lGL -lX11 -ldl -lpthread -lm
elif [[ "$OSTYPE" == "msys" ]] || [[ "$OSTYPE" == "cygwin" ]]; then
    # Windows (Git Bash/Cygwin)
    echo "Building for Windows..."
    gcc main.c -o program.exe -fsanitize=address -lglfw3 -lopengl32 -luser32 -lgdi32 -lshell32 -lws2_32
fi

./program
rm ./program
