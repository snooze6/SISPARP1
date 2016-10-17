Sistemas Paralelos (G4011443)

Guía para estimar el coste de la comunicación en
programas paralelos MPI orientada a programadores
En esta práctica vamos a elaborar una guía sobre el coste de comunicaciones en programas paralelos MPI en
un sistema de computación de altas prestaciones. Será necesario programar y ejecutar una serie de
benchmarks para obtener datos que soporten el informe. Para llevar a cabo esta tarea tomaremos como
referencia la metodología descrita en el documento adjunto sobre “Intel MPI Benchmarks”.
Tareas a realizar:

1. Programa los benchmarks para algunos (o todos) los siguientes patrones de comunicación MPI1:
PingPong, SendRecv, Bcast, Scatter, Gather, Reduce, AlltoAll, and Barrier.
2. Sigue la metodología descrita en la sección “Benchmark Methodology” del documento "Intel MPI
Benchmarks". Puedes tener cada benchmark en un ejecutable diferente. Revisa algunos ejemplos
sobre la información que proporcionan los benchmarks de Intel. Si tiene dudas acerca de la
metodología, por favor pregunta, porque este es un tema muy importante para esta práctica.
3. Para los patrones de comunicación colectivos (incluyendo barrier) ejecuta el experimento con 4, 8 y
16 procesos.
4. Ejecuta los benchmarks y obtén la información en el sistema Finis Terrae II.
5. Realiza una guía basada en los datos obtenidos por los benchmarks.
• Incluye una descripción breve del sistema evaluado y de los benchmarks usados.
• Incluye gráficas para mostrar la latencia y el ancho de banda (cuando sea necesario, según los
Intel MPI Benchmarks). Intenta extraer ecuaciones analíticas que se ajusten al comportamiento
de las gráficas.
• Sería útil normalizar los tiempos a la computación. Por ejemplo, puedes hacer un programa
sencillo para ejecutar el producto interno de dos vectores de 1000 números de doble precisión y
obtener el tiempo medio de cálculo de una iteración del bucle. Usa ese tiempo como factor de
normalización.
6. Sube los resultados al Campus Virtual. Debes incluir el informe en formato pdf con el código fuente
como un apéndice en el propio documento.
7. Tiempo disponible: 5 sesiones prácticas – primera sesión 3 de Octubre de 2016.
8. Fecha límite de entrega: 16 de Diciembre de 2016, 23:55 horas.
Criterios de evaluación: número de benchmarks evaluados, aplicación técnica de la metodología presentada
en el documento de referencia de Intel, calidad en la presentación de la guía, en el sentido de que debe ser
realmente útil para los programadores de MPI. 


```bash
module load intel impi
```