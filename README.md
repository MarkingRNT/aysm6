## Especificaciones

Armar una librería de `I2C`. Esto va a consistir en completar las funciones que van a encontrar en el `I2C.c`:

- `I2C_Init`: Tiene que lograr configurar el I2C con 50KHz de frecuencia.
- `I2C_Wait`: Verifique los flags necesarios para asegurarse de que el periférico esté libre.
- `I2C_Start`: Fuerce la condición de start en el bus.
- `I2C_Stop`: Fuerce la condición de stop en el bus.
- `I2C_SendData`: Envíe un byte por el bus.
- `I2C_ReadDataAck`: Lea un byte del bus, lo devuelva y envíe un `ACK`.
- `I2C_ReadDataNotAck`: Lea un byte del bus, lo devuelva y no envíe un `ACK`.
- `I2C_SendSlaveAddress`: Envíe por el bus el address del slave junto con la instrucción de leer o escribir.
- `I2C_GetStatus`: Devuelva el estado de la comunicación.

La librería que hagan tiene que ser compatible con el código que esta dentro de `test`.

Luego, hacer un `README.md` con lo siguiente:

```markdown
# I2C

Alumno: Nombre y apellido
Curso: Curso
Materia: Computadoras y Sistemas de Control
```

## Consideraciones

- Cualquier duda sobre los registros o la comunicación, pueden leer mas en la hoja de datos del `ATmega328P` en el capítulo de `2-wire Serial Interface`.

## Como probar el código

En el repo, van a encontrar una carpeta que se llama `test`. Peguen una copia de `I2C.h` e `I2C.c` en ese directorio y corran en la terminal:

```
make -f makefile.mk
```

Si no hubo errores de compilación, vayan al directorio `sch` y abran el circuito. Carguen el `bmp180.hex` que se generó y, si todo anda bien, deberían ver en el LCD que se intercalan los mensajes `OK` seguido de la presión que indica el sensor.

## Como entregar

- Archivos que tienen que subir: `I2C.c` y `README.md`.
- Nombre de la rama: `aysm6/2021/i2c/lib`.
