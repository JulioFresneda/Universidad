# EJERCICIO 5.2 PRÁCTICA EC. JULIO ANTONIO FRESNEDA GARCÍA. 2B.


# Datos con los que vamos a trabajar---------------------------------------------------------------------------------------------------------

.section .data	

# Lista de datos a sumar
lista:		.int -1,-1,-1,-1,-1

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

	# Ha acabado el algoritmo, almacenando los primeros 32 bits de la solución en esi. Se pasa a resultado
	mov %esi, resultado

	# Los 32 bits de la izquierda de la solución (de 64 bits) se pasan a resultado+4, que estaba reservado también
	mov %edi, resultado+4

	# Fin del programa
	mov $1, %eax
	mov $0, %ebx
	int $0x80

inicio:

	# Haciendo push ebp, y poniéndolo a 0, junto esi y edi
	push %ebp
	
	mov $0, %edi
	mov $0, %ebp
	mov $0, %esi

	#Llamando a bucle
	call bucle
	
		
bucle:
	
	#Sumando todos los elementos (con signo) de la lista al registro esi
	add (%ebx,%ebp,4), %esi

	#Si el elemento de la lista que se ha sumado es negativo, salta a .NEG. Si es positivo, a .POS.
	js .NEG
	jmp .POS

.NEG:
	
	# Al ser negativo, hay que hacer una suma con acarreo del numero -1, a edi.
	adc $0xFFFFFFFF,%edi
	jmp .B2
.POS:

	# Al ser positivo, sólo hay que sumarle el acarreo a edi. Como adc nos pide otro argumento, ponemos 0.
	adc $0,%edi
.B2:

	# Se incrementa ebp y se compara con ecx. Si son iguales, acaba el bucle y salta a .FIN
	inc %ebp
	cmp %ebp, %ecx
	jne bucle
	jmp .FIN
	
	
