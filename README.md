# Especificaciones

Escribir el código necesario para que las funciones de `UART.c` cumplan con lo siguiente:
- `UART_Init` debe inicializar el UART para trabajar a la velocidad que se le pase como parámetro. Debe tener:
  - Un `stop` bit.
  - Sin `parity` bits.
  - Ocho bits de datos.
  - Tx habilitado pero Rx deshabilitado.
  - Polaridad normal.
  - Sin interrupciones.
  - Velocidad doble.
- `UART_Putc` debe ser capaz de enviar un **único** byte por UART, verificando los flags apropiados. 
- `UART_Prints` debe poder enviar una cadena de caracteres por UART.

Además, en la interrupción de `GPIO.c` el micro debe:
- Enviar por USART la temperatura seguido del setpoint indicado por el potenciómetro con este formato:

```
temperatura & setpoint |
```

Luego, crear un archivo un `README.md`. El archivo debe tener este contenido:

```markdown
# UART

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
  <img src="https://render.githubusercontent.com/render/math?math=BAUD=\frac{f_{osc}}{8(UBRR0+1)}">
</div>

- En `GPIO.c` tienen las variables `temp` y `sp` que tienen guardadas la temperatura y el valor del setpoint respectivamente.
- Las dudas que tengan sobre los registros pueden aclararlas en la hoja de datos en el capítulo 17. 

## Como probar el código

Una vez que lo tengan resuelto, ejecuten en la terminal:

```
make -f makefile.mk
```

Si no ven errores, van a tener el `.hex` para cargar en el micro en el Proteus. La simulación debería comportarse según las especificaciones de arriba.

## Como entregar

Pongan el `README.md`, `GPIO.c`, `UART.c` y la imagen del circuito en una carpeta, abran una terminal y corran los comandos:

```
git init
git add UART.c GPIO.c README.md img.png
git commit -m "Initial commit"
git checkout -b aysm6/2021/uart/uart
git push https://github.com/trq20/USERNAME.git aysm6/2021/uart/uart
```

Recuerden cambiar `USERNAME` por su nombre de usuario en GitHub. Pueden verificar si la entrega se hizo visitando el repositorio en `https://github.com/trq20/USERNAME/tree/aysm6/2021/uart/uart`.
