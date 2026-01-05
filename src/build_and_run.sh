#!/bin/bash

# --- Configuration ---
SFML_INC="-ISFML-2.6.0-windows-vc17-32-bit/SFML-2.6.0/include/SFML"
SFML_LIB_DIR="-LSFML-2.6.0-windows-vc17-32-bit/SFML-2.6.0/lib"

# Libraries to link: graphics, audio, window, and system.
# The linking order matters with g++: dependees must come after dependers.
SFML_LIBS="-lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system"

SOURCE_FILE="Parkour.cpp"
EXECUTABLE_NAME="Platformer"

# --- Build Command ---
echo "Building $SOURCE_FILE to $EXECUTABLE_NAME..."
g++ "$SOURCE_FILE" $SFML_INC $SFML_LIB_DIR $SFML_LIBS -o "$EXECUTABLE_NAME"

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Build successful. Running $EXECUTABLE_NAME..."
    # --- Run Command ---
    # Note: On Windows, you might need to copy the SFML DLLs to the executable's directory
    # or add the SFML bin directory to the PATH for the executable to run.
    ./"$EXECUTABLE_NAME"
else
    echo "Build failed."
fi