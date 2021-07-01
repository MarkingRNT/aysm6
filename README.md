# Especificaciones

Escribir el código necesario para que las funciones de `UART.c` cumplan con lo siguiente:
- `UART_Init` debe inicializar el UART para trabajar a la velocidad que se le pase como parámetro. Debe tener:
  - Un `stop` bit.
  - Sin `parity` bits.
  - Ocho bits de datos.
  - Tx y Rx habilitados.
  - Interrupcion de Rx habilitada.
  - Polaridad normal.
  - Velocidad doble.
- `UART_Putc` debe ser capaz de enviar un **único** byte por UART, verificando los flags apropiados. Igual que en la actividad anterior. 
- `UART_Prints` debe poder enviar una cadena de caracteres por UART. Igual que en la actividad anterior.
- `ISR(USART_RX_vect)` es la interrupción que sucede cuando llega un byte por USART. Solo debe pasar el byte entrante a una nueva variable.

En el `main.cpp`, se debe analizar el byte entrante. Si es el caracter `t`, se debe imprimir por la terminal `Temperatura: ` junto con el valor. Si el caracter es `s`, se debe imprimir por la terminal `Setpoint: ` junto con su valor.

Luego, crear un archivo un `README.md`. El archivo debe tener este contenido:

```markdown
# UART - RX

Alumno: Nombre y apellido
Curso: Curso
Materia: Computadoras y Sistemas de Control

[Imagen del circuito simulado]
```

## Consideraciones

- Para poder enviar un byte por UART, no pierdan de vista los flags `UDRE0` y `TXC0`.
- Para poder enviar una cadena, piensen en la actividad de punteros, pueden aprovecharlos.
- En cuanto a como calcular el valor que va en el registro `UBRR0` para elegir la velocidad, tienen esta ecuación que pueden usar:

<div align="center">
  <img src="https://render.githubusercontent.com/render/math?math=BAUD=\frac{f_{osc}}{8(UBRR0+1)}-1">
</div>

- Las dudas que tengan sobre los registros pueden aclararlas en la hoja de datos en el capítulo 17. 

## Como probar el código

Una vez que lo tengan resuelto, ejecuten en la terminal:

```
make -f makefile.mk
```

Si no ven errores, van a tener el `.hex` para cargar en el micro en el Proteus. La simulación debería comportarse según las especificaciones de arriba.

## Como entregar

Pongan el `README.md`,  `UART.c` y la imagen del circuito en una carpeta, abran una terminal y corran los comandos:

```
git init
git add UART.c README.md img.png
git commit -m "Initial commit"
git checkout -b aysm6/2021/uart/rx
git push https://github.com/trq20/USERNAME.git aysm6/2021/uart/rx
```

Recuerden cambiar `USERNAME` por su nombre de usuario en GitHub. Pueden verificar si la entrega se hizo visitando el repositorio en `https://github.com/trq20/USERNAME/tree/aysm6/2021/uart/rx`.
