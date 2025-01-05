# Día 5: Reglas de Precedencia con Grafos

## Elección del problema
Este problema aborda la validación y ordenación de listas según reglas de precedencia, ideal para representar como un grafo dirigido.

## Técnicas y estructuras de datos empleadas
- Grafos: Representados mediante un 'unordered_map'.
- Algoritmos de ordenación topológica: Implícitamente implementados para ordenar listas según las reglas.
- Vectores: Para almacenar las listas y las reglas.

## Enfoque de la solución
1. Se construye un grafo a partir de las reglas de precedencia.
2. Se verifican listas de actualizaciones contra el grafo.
3. Las listas que no cumplen las reglas se ordenan según las precedencias, y su valor intermedio se acumula en un resultado final.

