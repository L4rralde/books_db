# Tarea 8

## Dependencias

- gnuplot
- g++


## Compilación

```sh
g++ include/database/database.cpp src/main.cpp -o output/main.o -lm
```

## Uso

```sh
./output/main.o data/libros2022.txt data/libros2023.txt
```

Recomiendo que redirijas la salida a un archivo de texto para poder visualizar todo.

```sh
./output/main.o data/libros2022.txt data/libros2023.txt > logs.txt
```

### Notas

- En lugar de mostrar las gráficas, las guardo. Esto porque la terminal gráfica (xquartz en mi caso) puede ser diferente.