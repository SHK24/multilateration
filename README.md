```markdown
# PseudorangeMultilateration

## Требования

- CMake (версия 3.10 или выше)
- GCC (для Linux) или другой компилятор C++ (для Windows)
- Библиотеки:
  - Eigen3
  - LAPACK
  - BLAS

## Установка

### Для Linux

1. Установите необходимые пакеты:
   ```bash
   sudo apt update
   sudo apt install cmake g++ libeigen3-dev liblapack-dev libblas-dev
   ```

2. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/SHK24/multilateration.git
   cd multilateration
   ```

3. Перейдите в директорию для сборки:
   ```bash
   cd build
   ```

4. Запустите CMake для конфигурации проекта:
   ```bash
   cmake ..
   ```

5. Соберите проект:
   ```bash
   make
   ```

### Для Windows

1. Установите CMake и GCC (например, MinGW):
   - [CMake](https://cmake.org/download/)
   - [MinGW](http://www.mingw.org/)

2. Установите необходимые библиотеки:
   - Убедитесь, что у вас установлены библиотеки Eigen3, LAPACK и BLAS. Их можно установить через vcpkg или скачать и установить вручную.

3. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/SHK24/multilateration.git
   cd multilateration
   ```

4. Перейдите в директорию для сборки:
   ```bash
   cd build
   ```

5. Запустите CMake для конфигурации проекта:
   ```bash
   cmake ..
   ```

6. Соберите проект:
   ```bash
   mingw32-make
   ```

## Использование

После установки вы можете запустить приложение из командной строки:

```bash
./PseudorangeMultilateration
```

Возможно использование аргементов командной строки для выбора алгоритмов решения. Можно указать список с помощью имен алгоритмов:
"Bancroft"
"Beck"
"Grad"
"Linear"
"LSQ" 
"RTK"
"Simple"