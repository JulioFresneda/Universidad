# -*- coding: utf-8 -*-
"""
Created on Thu Oct  4 10:45:44 2018

@author: Julio
"""
import math


## Ejercicio 1

precio_bruto = int(input("Precio bruto: "))
porc_ganancia = int(input("Porcentaje de ganancia del vendedor: "))
iva = int(input("IVA: "))

precio_base = precio_bruto + precio_bruto*(porc_ganancia/100)
precio_final = precio_base + precio_base*(iva/100)

print("El precio final es de ", precio_final, "€")



## Ejercicio 2

def desviacion( x1, x2, x3):
    media = (x1+x2+x3)/3
    suma = (x1-media)**2 + (x2-media)**2 + (x3-media)**2
    suma = suma/3
    
    desviacion = math.sqrt(suma)
    return desviacion

n1 = int(input("Introduce primer numero: "))
n2 = int(input("Introduce segundo numero: "))
n3 = int(input("Introduce tercer numero: "))

print("La desviacion es",desviacion(n1,n2,n3))




## Ejercicio 3

def transformar(h=None,m=None,s=None):
    
    if( h == None ):
        h = int(input("Introduce horas: "))
        m = int(input("Introduce minutos: "))
        s = int(input("Introduce segundos: "))
        
    m = m + s//60
    s = s%60
    
    h = h + m//60
    m = m%60
    
    print(h,"horas,",m,"minutos, y",s,"segundos")
    
    
    
transformar()




## Ejercicio 4

def cambio():
    
    cantidad = float(input("Introduce cantidad dada por el cliente: "))
    precio = float(input("Introduce precio del producto: "))
    
    if( cantidad >= precio ):
        cambio = cantidad - precio
        monedas1e = 0
        monedas50c = 0
        monedas10c = 0
        monedas1c = 0
        
        
        monedas1e = cambio // 1
        cambio = cambio % 1
        
        monedas50c = cambio // 0.5
        cambio = cambio % 0.5
        
        monedas10c = cambio // 0.1
        cambio = cambio % 0.1
        
        monedas1c = cambio // 0.01
        
      
        if( cambio > 0.0 ): monedas1c = monedas1c + 1    
        
        print("Cambio:")
        if( monedas1e > 0 ): print(int(monedas1e),"monedas de 1€")
        if( monedas50c > 0 ): print(int(monedas50c),"monedas de 50 cent.")
        if( monedas10c > 0 ): print(int(monedas10c),"monedas de 10 cent.")
        if( monedas1c > 0 ): print(int(monedas1c),"monedas de 1 cent.")
    
    else:
        print("La cantidad entregada por el cliente no es suficiente")


cambio()






## Ejercicio 5

def diferencia(h1=None,m1=None,s1=None,h2=None,m2=None,s2=None):
    
    if( h1=None):
        h1 = int(input("Introduce horas del primer instante: "))
        m1 = int(input("Introduce minutos del primer instante: "))
        s1 = int(input("Introduce segundos del primer instante: "))
        
        h2 = int(input("Introduce horas del segundo instante: "))
        m2 = int(input("Introduce minutos del segundo instante: "))
        s2 = int(input("Introduce segundos del segundo instante: "))
        
    
    total1 = h1*3600+m1*60+s1
    total2 = h2*3600+m2*60+s2
    
    dif = abs(total1-total2)
    
    print("La diferencia es de:")
    transformar(0,0,dif)
    
    
diferencia(1,40,30,2,20,15)



## Ejercicio 6

def maxmin():
    x1 = int(input("Introduce primer numero: "))
    x2 = int(input("Introduce segundo numero: "))
    x3 = int(input("Introduce tercer numero: "))
    
    minimo = x1
    if( x2 < x1 ): minimo = x2
    if( x3 < minimo ): minimo = x3
    
    maximo = x1
    if( x2 > x1 ): maximo = x2
    if( x3 > maximo ): maximo = x3
    
    print("Minimo:",minimo)
    print("Maximo:",maximo)
    
    
maxmin()


## Ejercicio 7

def descomponer():
    nombre = input("Nombre:")
    primer_ap = input("Primer apellido:")
    segundo_ap = input("Segundo apellido:")
    
    completo = nombre + " " + primer_ap + " " + segundo_ap
    print("Nombre completo:",completo)
    
    invertido = completo[::-1]
    print("Nombre completo invertido:",invertido)
    
    print("Nombre:",nombre)
    print("Primer apellido:",primer_ap)
    print("Segundo apellido:",segundo_ap)
    
    
descomponer()



    
    
    