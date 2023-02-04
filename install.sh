#!/bin/bash

git submodule update --init --recursive

# Установка переменных окружения
BUILD_DIR=build
SRC_DIR=$PWD

# Удаление существующего каталога сборки
rm -rf $BUILD_DIR

# Создание каталога сборки
mkdir $BUILD_DIR

# Переход в каталог сборки
cd $BUILD_DIR

# Вызов CMake
cmake $SRC_DIR

# Сборка проекта с помощью Make
make

# Выход из каталога сборки
cd ..

exit 0