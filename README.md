# Tarea 8

[![Binder](https://mybinder.org/badge_logo.svg)](https://mybinder.org/v2/gh/L4rralde/books_db/HEAD?labpath=main.ipynb)
## Dependencias

- gnuplot
- g++


## Compilación

```sh
g++ include/database/database.cpp src/main.cpp -o output/main.o -lm
```

## Uso

El siguiente comando ejecutará todos las operaciones descritas en la tarea.

```sh
./output/main.o data/libros2022.txt data/libros2023.txt
```

Recomiendo que redirijas la salida a un archivo de texto para poder visualizar todo.

```sh
./output/main.o data/libros2022.txt data/libros2023.txt > logs.txt
```

### Notas

- En lugar de mostrar las gráficas, las guardo. Esto porque la terminal gráfica (xquartz en mi caso) puede ser diferente.