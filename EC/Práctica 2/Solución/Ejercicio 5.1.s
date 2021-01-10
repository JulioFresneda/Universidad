# EJERCICIO 5.1 PRÁCTICA EC. JULIO ANTONIO FRESNEDA GARCÍA. 2B.


# Datos con los que vamos a trabajar---------------------------------------------------------------------------------------------------------

.section .data	

# Lista de datos a sumar
lista:		.int -1,1

# Longitud de lista		
longlista:	.int (.-lista)/4	

# Espacio de memoria reservado para guardar el resultado de la operación						
resultado:	.quad 0							


.section .text

# Inicio del programa------------------------------------------------------------------------------------------------------------------------

_start:	.global _start


	# Cargando lista en un registro, y longlista en otro
	mov    $lista, %ebx
	mov longlista, %ecx

	# Llamando a inicio
	call inicio
.FIN:

	# Ha acabado el algoritmo, almacenando los primeros 32 bits de la solución en eax. Se pasa a resultado
	mov %eax, resultado

	# Los 32 bits de la izquierda de la solución (de 64 bits) se pasan a resultado+4, que estaba reservado también
	mov %edx, resultado+4

	# Fin del programa
	mov $1, %eax
	mov $0, %ebx
	int $0x80

inicio:

	# Haciendo push a los registros edx y esi, y poniéndolos a 0, junto eax
	push %edx
	push %esi
	mov $0, %eax
	mov $0, %edx
	mov $0, %esi

	# Llamando a bucle
	call bucle
	
		
bucle:
	# Sumando todos los elementos de la lista al registro eax
	add (%ebx,%esi,4), %eax

	# Si hay acarreo, se salta a .AC
	jc .AC
.C:
	# Se incrementa esi y se compara con ecx. Si son iguales, acaba el bucle y salta a .FIN
	inc %esi
	cmp %esi,%ecx
	jne bucle

	pop %esi	
	jmp .FIN

.AC:
	# Se incrementa en una unidad edx y se salta a .C
	inc %edx
	jmp .C
	
