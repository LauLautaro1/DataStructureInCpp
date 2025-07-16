#!/bin/bash

# Directorios
SRC_DIR="src"
INCLUDE_DIR="includes"
BIN_NAME="Prueba"

# Compilar todos los archivos .cpp
echo "Compilando proyecto..."
g++ -I$INCLUDE_DIR \
    $SRC_DIR/*.cpp \
    -o $BIN_NAME

# Verificar si la compilación fue exitosa
if [ $? -eq 0 ]; then
    echo "✅ Compilación exitosa. Ejecutable en: $BIN_NAME"
else
    echo "❌ Error durante la compilación."
fi
