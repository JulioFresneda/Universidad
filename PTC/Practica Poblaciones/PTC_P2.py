import csv
import numpy as np
import matplotlib.pyplot as plt
import re # Para buscar en strings



# Para mostrar los números completos
np.set_printoptions(suppress=True)


"""
Julio A. Fresneda García
49215154 - juliofresnedag@correo.ugr.es
Programación Técnica y Científica
"""


# Este código se divide en dos partes: Preparación de datos, y exportación a html (apartados que se piden)





###########################################################################################################
#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#

#                                          PREPARACIÓN DE DATOS                                           #

#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#
###########################################################################################################





###########################################################################################################
################################    DATOS DE CADA PROVINCIA    ############################################
###########################################################################################################

### Abrimos poblacionProvincias (CSV)
csvfile = open('./poblacionProvinciasHM2010-17.csv',"r", encoding="windows-1250") 
reader = csvfile.read()

# Nos quedamos con el texto entre estas dos palabras
primero = reader.find("Total Nacional")
ultimo = reader.find("Notas")

cadenaDatos = reader[primero:ultimo]

# Nuestra cabecera tiene el siguiente formato
cabecera="Provincia;T2017;T2016;T2015;T2014;T2013;T2012;T2011;T2010;H2017;H2016;H2015;H2014;H2013;H2012;H2011;H2010;M2017;M2016;M2015;M2014;M2013;M2012;M2011;M2010"

anios = cabecera.split(sep=';')
anios = anios[1:]

### Creamos el fichero con datos para trabajar con él 
ficheroDatos = open("./poblacionDatos.csv", "w",encoding="windows-1250")
ficheroDatos.write(cabecera + '\n' + cadenaDatos)
ficheroDatos.close()




### LISTA DE DICCIONARIOS DE POBLACIÓN EN PROVINCIAS: Lista de 53 diccionarios, uno para cada provincia (incluye el total)
# Cada diccionario contiene la población de esa provincia para cada año
### Creamos diccionarios con poblacion por provincias
with open('./poblacionDatos.csv', 'r', encoding="windows-1250") as csvarchivo:
    poblacionDict = csv.DictReader(csvarchivo, delimiter=';')
    poblacion_por_provincias=[]
    for regD in poblacionDict:
        poblacion_por_provincias.append(regD)



### DICCIONARIO DE NOMBRES DE PROVINCIAS: Diccionario con el código como clave, y nombre de la provincia como nombre
provincias = dict()
for dic in poblacion_por_provincias:
    provincias[dic['Provincia'][:2]] = dic['Provincia'][3:]
    if( dic['Provincia'][:2] != 'To'):
       dic['Provincia'] = dic['Provincia'][:2]

provincias.pop(str('To'))



###########################################################################################################
###########################   VARIACIÓN ABSOLUTA Y RELATIVA EN PROVINCIAS    ##############################
###########################################################################################################


### LISTAS DE DICCIONARIOS DE VARIACIÓN EN PROVINCIAS: Lista de 52 diccionarios, uno para cada provincia (no incluye el total)
# Haremos dos listas: Una contendrá los diccionarios para la variación absoluta de cada provincia, y la otra para la relativa.
### Creamos una lista de diccionarios con las varianzas absolutas
var_abs_provincias = []

for i in range(0,len(provincias)+1):
    var_abs_provincias.append(dict())
    var_abs_provincias[i]['Provincia'] = poblacion_por_provincias[i]['Provincia']
    for j in range(0,len(anios)-1):
        if ( anios[j].find('2010') == -1): # No nos interesa 2010
            var_abs_provincias[i][anios[j]] = int(float(poblacion_por_provincias[i][anios[j]]) - float(poblacion_por_provincias[i][anios[j+1]]))





### Creamos una lista de diccionarios con las varianzas relativas
var_rel_provincias = []

for i in range(0,len(provincias)+1):
    var_rel_provincias.append(dict())
    var_rel_provincias[i]['Provincia'] = poblacion_por_provincias[i]['Provincia']
    for j in range(0,len(anios)-1):
        if ( anios[j].find('2010') == -1): # No nos interesa 2010
            var_rel_provincias[i][anios[j]] = np.round((int(float(poblacion_por_provincias[i][anios[j]]) - float(poblacion_por_provincias[i][anios[j+1]]))) / float(poblacion_por_provincias[i][anios[j+1]]) * 100,2)






###########################################################################################################
################################     COMUNIDADES AUTÓNOMAS     ############################################
###########################################################################################################




### Abrimos comunidadesAutonomas (HTM)
htmfile = open('./comunidadesAutonomas.htm',"r", encoding="windows-1250") 
reader = htmfile.read()

primero = reader.find("Literal")
ultimo = reader.find("Melilla")

cadenaDatos = reader[primero:ultimo+len("Melilla")]

result = re.findall('<td>(.*)</td>', cadenaDatos)
result.append("Melilla")


### DICCIONARIO DE NOMBRES DE CCAA: Diccionario con el código de la ccaa como clave, y nombre de la ccaa como valor
comunidades_autonomas = dict()
for i in range(0,len(result),2):
    comunidades_autonomas[result[i][:-1]] = result[i+1]




###########################################################################################################
################################  PROVINCIAS POR COMUNIDADES AUTÓNOMAS ####################################
###########################################################################################################



### Abrimos comunidadesAutonoma-Provincia (HTM)
htmfile = open('./comunidadAutonoma-Provincia.htm',"r", encoding="windows-1250") 
reader = htmfile.read()

primero = reader.find("CPRO")
ultimo = reader.find("Accesibilidad")

cadenaDatos = reader[primero:ultimo]

result = re.findall('<td>(.*)</td>', cadenaDatos)
result.remove('')
result.remove('')


### DICCIONARIO DE PROVINCIAS POR CCAA: Diccionario con el código de la ccaa como clave, y lista de nombres de las provincias que pertenecen a esa ccaa como valor
provincias_por_comunidad = dict()
for key in comunidades_autonomas:
    provincias_por_comunidad[key] = []

for i in range(0,len(result),4):
    provincias_por_comunidad[result[i]].append(result[i+2])






###########################################################################################################
################################  POBLACIÓN POR COMUNIDADES AUTÓNOMAS  ####################################
###########################################################################################################


### LISTAS DE DICCIONARIOS DE POBLACIÓN EN CCAA: Lista de 19 diccionarios, uno para cada ccaa (no incluye el total)
# Estos diccionarios contienen el total de población de cada ccaa en cada año
poblacion_por_ccaa = []
index = 0
for key_ccaa in comunidades_autonomas:  # Para cada comunidad autónoma:

    # Añadimos un diccionario, cuya clave es el código de la comunidad
    poblacion_por_ccaa.append(dict())
    poblacion_por_ccaa[index]['Comunidad Autonoma'] = key_ccaa
   
    # Al diccionario le metemos todos los años (T2017, M2014, etc) a 0
    for a in anios:
        poblacion_por_ccaa[index][a] = 0

    
    for dic_prov in poblacion_por_provincias: # Para cada provincia:
        current_prov = dic_prov['Provincia']

        if( current_prov in provincias_por_comunidad[key_ccaa] ):   # Si está en la ccaa que estamos rellenando:
            for a in anios: # Se le suma su población de cada año
                poblacion_por_ccaa[index][a] = float(float(poblacion_por_ccaa[index][a]) + float(dic_prov[a])) 


    index = index+1







###########################################################################################################
##############################  VAR ABS/REL POR COMUNIDADES AUTÓNOMAS  ####################################
###########################################################################################################



### LISTAS DE DICCIONARIOS DE VARIACIÓN EN CCAA: Lista de 52 diccionarios, uno para cada provincia (no incluye el total)
## Creamos una lista de diccionarios con las varianzas absolutas para ccaa
var_abs_ccaa = []

for i in range(0,len(comunidades_autonomas)):
    var_abs_ccaa.append(dict())
    var_abs_ccaa[i]['Comunidad Autonoma'] = poblacion_por_ccaa[i]['Comunidad Autonoma']
    for j in range(0,len(anios)-1):
        if ( anios[j].find('2010') == -1): # No nos interesa 2010
            var_abs_ccaa[i][anios[j]] = int(float(poblacion_por_ccaa[i][anios[j]]) - float(poblacion_por_ccaa[i][anios[j+1]]))





### Creamos una lista de diccionarios con las varianzas relativas para ccaa
var_rel_ccaa = []

for i in range(0,len(comunidades_autonomas)):
    var_rel_ccaa.append(dict())
    var_rel_ccaa[i]['Comunidad Autonoma'] = poblacion_por_ccaa[i]['Comunidad Autonoma']
    for j in range(0,len(anios)-1):
        if ( anios[j].find('2010') == -1): # No nos interesa 2010
            var_rel_ccaa[i][anios[j]] = np.round((int(float(poblacion_por_ccaa[i][anios[j]]) - float(poblacion_por_ccaa[i][anios[j+1]]))) / float(poblacion_por_ccaa[i][anios[j+1]]) * 100,2)




###########################################################################################################
###############################  MEDIA ORDENADA COMUNIDADES AUTÓNOMAS  ####################################
###########################################################################################################

# Vamos a obtener las medias de población de todos los años para cada ccaa
medias_ccaa = dict()

for dic in poblacion_por_ccaa:
    total = 0
    for a in anios:
        if( a[0] == 'T' ):
            total = total + dic[a]

    total = total / (len(anios)/3)
    medias_ccaa[ dic['Comunidad Autonoma'] ] = total




###########################################################################################################
###############################   DIBUJAR TOP10 COMUNIDADES AUTÓNOMAS  ####################################
###########################################################################################################


### Primero calculamos el top 10 de ccaa en población


num_barras = 10

# Lista de medias, de mayor a menor. Es temporal
list_medias = sorted(medias_ccaa.values()) # Ordenamos de menor a mayor
list_medias = list_medias[9:] # Nos quedamos con el top 10
list_medias.reverse() # Le damos la vuelta

# Listas de: Códigos de ccaa, población (hombres) y población (mujeres). Uso listas porque necesitaremos el orden correcto al dibujar
top_ccaa = []
top_ccaa_pob_h = []
top_ccaa_pob_m = []


while len(list_medias) > 0: # Mientras que la lista contenga elementos
    for key in medias_ccaa: # Para cada ccaa
        if( medias_ccaa[key] == list_medias[0] ): # Si es la ccaa con más población que no hayamos alanizado ya :
            top_ccaa.append( key ) # Añadimos el código de la ccaa a la lista de códigos de ccaa
            
            for dic in poblacion_por_ccaa: # Añadimos las poblaciones a la lista de hombres y a la de mujeres
                if( dic['Comunidad Autonoma'] == key ):
                    top_ccaa_pob_h.append(dic['H2017'])
                    top_ccaa_pob_m.append(dic['M2017'])

            list_medias.remove(list_medias[0]) # Borramos esa ccaa de la lista temporal
            break
          
        






## Dibujo de la gráfica de barras

# Dividimos los datos entre 1000 para que se vean mejor
top_ccaa_pob_h = [x / 1000 for x in top_ccaa_pob_h]
top_ccaa_pob_m = [x / 1000 for x in top_ccaa_pob_m]

ind = np.arange(num_barras)
width = 0.35
      
plt.bar(ind, top_ccaa_pob_h, width, label='Hombres')
plt.bar(ind + width, top_ccaa_pob_m, width, label='Mujeres')

plt.ylabel('Población, en miles')
plt.title('Comunidades Autónomas')

plt.xticks(ind + width / 2, top_ccaa)

plt.legend(loc='best')

plt.savefig("C:/top10.png") # Guardamos el archivo
plt.show()




###########################################################################################################
###############################   DIBUJAR EVOLUCIÓN TOP10 COMUNIDADES AUTÓNOMAS  ##########################
###########################################################################################################

### Primero obtenemos los datos de la evolución. El código es igual que el bloque anterior, solo que en vez de 
# quedarnos con la media, nos quedamos con los valores de cada año individiualemnte 


num_ccaa = 10

# Lista de medias, de mayor a menor. Es temporal
list_medias = sorted(medias_ccaa.values())
list_medias = list_medias[9:]
list_medias.reverse()

# Listas de: Códigos de ccaa, población (total) y nombres de las ccaa. Uso listas porque necesitaremos el orden correcto al dibujar
top_ccaa = []
top_ccaa_pob = []
top_ccaa_nombres = []

while len(list_medias) > 0: # Si quedan ccaa en  la lista
    for key in medias_ccaa: # Para cada ccaa
        if( medias_ccaa[key] == list_medias[0] ):
            top_ccaa.append( key )
            
            for dic in poblacion_por_ccaa:
                if( dic['Comunidad Autonoma'] == key ):
                    temp = []

                    for a in anios: # Guardamos los valores de la ccaa para cada año
                        if( a[0] == 'T' ):
                            temp.append(dic[a])

                    top_ccaa_pob.append(temp.copy())    
                    top_ccaa_nombres.append(comunidades_autonomas[key])


            list_medias.remove(list_medias[0])
            break
          
        






## Dibujo
top_ccaa_pob_reducido = []
for ccaa in top_ccaa_pob:
    top_ccaa_pob_reducido.append([x / 1000 for x in ccaa])


anios_totales = []
for a in anios:
    if( a[0] == 'T' ):
        anios_totales.append(a[1:])

anios_totales.reverse()

# Estilo
plt.style.use('seaborn-darkgrid')
 
# Paleta de colores
palette = plt.get_cmap('Set1')






# Múltiples line plot
ax = plt.subplot(111)
for i in range(num_ccaa):

    plt.plot(top_ccaa_pob_reducido[i])
    

plt.xticks([0,1,2,3,4,5,6,7,8],anios_totales)


box = ax.get_position()
ax.set_position([box.x0, box.y0, box.width * 0.8, box.height])


ax.legend(top_ccaa_nombres,loc='center left', bbox_to_anchor=(1, 0.5))

# Añadimos títulos
plt.title("Evolución de la población de las CCAA", loc='left', fontsize=12, fontweight=0, color='orange')
plt.xlabel("Años")
plt.ylabel("Población, en miles")
plt.savefig("C:/evolucionTop10.png")
plt.show()










###########################################################################################################
#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#

#                              EXPORTACIÓN A HTML Y REALIZACIÓN DE APARTADOS                              #

#XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX#
###########################################################################################################










###########################################################################################################
###############################                     HTML R1                      ##########################
###########################################################################################################

# R1. La variación de la población por provincias desde el año 2011 a 2017 en términos absolutos y
# relativos generando una página web 1 (fichero variacionProvincias.htm)





R1 = open('./variacionProvincias.htm','w', encoding="utf-8") # Creamos un archivo htm


# Introducimos cabeceras para la tabla
paginaR1 = """<table class="egt">
<colgroup>
<colgroup span="7" style="background: rgba(128, 255, 0, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(255, 128, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
  <tr>
    <th></th>
    <th colspan="7">Variacion Absoluta de población por provincias</th>
    <th colspan="7">Variacion relativa de población por provincias</th>
  </tr>
  <tr>
  """

# Introducimos cabeceras de los años, ignorando 2010 pues no hay variaciones para ese año
paginaR1 = paginaR1 + """<th></th>""" 
for a in anios:
    if( a[0] == 'T' ):
        if( a != 'T2010' ): paginaR1 = paginaR1 + """<th>%s</th>""" % (a[1:])
for a in anios:
    if( a[0] == 'T' ):
        if( a != 'T2010' ): paginaR1 = paginaR1 + """<th>%s</th>""" % (a[1:])

paginaR1 = paginaR1 + """</tr>""" 


# Introducimos los datos de la tabla
for dic_a in var_abs_provincias:

    
    for dic_r in var_rel_provincias:
        if( dic_a['Provincia'] == dic_r['Provincia'] ): # Buscamos dic relativo asociado
            paginaR1 = paginaR1 + """<tr>""" 
            if( dic_a['Provincia'] != 'Total Nacional' ): paginaR1 = paginaR1 + """<th>%s</th>""" % (provincias[dic_a['Provincia']])    
            else: paginaR1 = paginaR1 + """<th>%s</th>""" % (dic_a['Provincia']) 
            for a in anios:
                if( a[0] == 'T'  ):
                    if( a != 'T2010' ): paginaR1 = paginaR1 + """<th>%s</th>""" % (dic_a[a])    # Añadimos los datos absolutos de esa provincia

            for a in anios:
                if( a[0] == 'T' ):
                    if( a != 'T2010' ): paginaR1 = paginaR1 + """<th>%s</th>""" % (dic_r[a])    # Añadimos los datos relativos de esa provincia

            paginaR1 = paginaR1 + """</tr>""" 



# Cerramos el archivo htm

R1.write(paginaR1)
R1.close()








###########################################################################################################
###############################                     HTML R2                      ##########################
###########################################################################################################
# R2. Usando el listado de comunidades autónomas que podemos obtener de los datos de entrada, así
# como de las provincias de cada comunidad autónoma, generar una página web 2 (fichero
# poblacionComAutonomas.htm) con una tabla con los valores de población de cada comunidad
# autónoma en cada año de 2010 a 2017 indicando también los valores desagregados por sexos (de
# manera semejante a como aparece en el fichero poblacionProvinciasHM2010-17.csv)


R2 = open('./poblacionComAutonomas.htm','w', encoding="utf-8") # Creamos un archivo htm

# Añadimos las cabeceras
paginaR2 = """<table class="egt">
<colgroup>
<colgroup span="8" style="background: rgba(128, 255, 0, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="8" style="background: rgba(255, 128, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
<colgroup span="8" style="background: rgba(255, 0, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
  <tr>
    <th></th>
    <th colspan="24">Población por CCAA</th>
  </tr>
  <tr>
    <th></th>
    <th colspan="8">Total</th>
    <th colspan="8">Hombres</th>
    <th colspan="8">Mujeres</th>
  </tr>
  <tr>
  """


# Añadimos los años
paginaR2 = paginaR2 + """<th></th>""" 
for a in anios:
        paginaR2 = paginaR2 + """<th>%s</th>""" % (a[1:])


paginaR2 = paginaR2 + """</tr>""" 


# Añadimos los datos a la tabla
for dic in poblacion_por_ccaa:

    paginaR2 = paginaR2 + """<tr>""" 
    paginaR2 = paginaR2 + """<th>%s</th>""" % (comunidades_autonomas[dic['Comunidad Autonoma']])    
    for a in anios:
        paginaR2 = paginaR2 + """<th>%s</th>""" % (dic[a])


    paginaR2 = paginaR2 + """</tr>""" 




paginaR2 = paginaR2 + """</colgroup></table>""" 

# NO CERRAMOS EL ARCHIVO: SEGUIMOS EN R3


###########################################################################################################
###############################                     HTML R3                      ##########################
###########################################################################################################

# R3. Para las 10 comunidades con más población media de 2010 a 2017, generar un gráfico de
# columnas que indique la población de hombres y mujeres en el año 2017, salvar el gráfico a fichero
# e incorporarlo a la página web 2 del punto R2.


# Añadimos el gráfico antes generado, junto con una leyenda de códigos de ccaa y nombre de ccaa correspondiente

paginaR2 = paginaR2 + """<div style="float: left;"><IMG SRC="top10.png"></div>"""

paginaR2 = paginaR2 + """<br></br><br></br><br></br>""" 
paginaR2 = paginaR2 + """<table class="egt">
<colgroup>
<colgroup span="1" style="background: rgba(128, 255, 0, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="1" style="background: rgba(255, 128, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
  <tr>
    <th></th>
    <th colspan="1">Codigo</th>
    <th colspan="1">Comunidad Autonoma</th>
  </tr>
  <tr>
  """

paginaR2 = paginaR2 + """<th></th>""" 
for ccaa in top_ccaa:
    paginaR2 = paginaR2 + "<tr>"
    paginaR2 = paginaR2 + """<th></th>"""
    paginaR2 = paginaR2 + """<th>%s</th>""" % (ccaa)
    paginaR2 = paginaR2 + """<th>%s</th>""" % (comunidades_autonomas[ccaa])
    paginaR2 = paginaR2 + "</tr>"


paginaR2 = paginaR2 + """</tr>""" 



paginaR2 = paginaR2 + """</colgroup></table>""" 



# Cerramos el archivo htm

R2.write(paginaR2)
R2.close()












###########################################################################################################
###############################                     HTML R4                      ##########################
###########################################################################################################

# R4. Generar una página web 3 (fichero variacionComAutonomas.htm) con una tabla con la
# variación de población por comunidades autónomas desde el año 2011 a 2017, indicando variación
# absoluta, relativa y desagregando dicha información por sexos, es decir, variación absoluta
# (hombres, mujeres) y relativa (hombres, mujeres).


# Creamos el fichero
R4 = open('./variacionComAutonomas.htm','w', encoding="utf-8")

# Añadimos cabeceras
paginaR4 = """<table class="egt">
<colgroup>
<colgroup span="7" style="background: rgba(0, 128, 255, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(0, 64, 255, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(0, 0, 255, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(255, 128, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(255, 64, 0, 0.3); border: 1px solid rgba(100, 200, 0, 0.3);"></colgroup>
<colgroup span="7" style="background: rgba(255, 0, 0, 0.3); border: 1px solid rgba(200, 100, 0, 0.3);"></colgroup>
  <tr>
    <th></th>
    <th colspan="21">Variacion Absoluta en población de cada CCAA</th>
    <th colspan="21">Variacion Relativa en población de cada CCAA</th>
  </tr>
  <tr>
    <th></th>
    <th colspan="7">Total</th>
    <th colspan="7">Hombres</th>
    <th colspan="7">Mujeres</th>
    <th colspan="7">Total</th>
    <th colspan="7">Hombres</th>
    <th colspan="7">Mujeres</th>
  </tr>
  <tr>
  """

# Añadimos años
paginaR4 = paginaR4 + """<th></th>""" 
for a in anios:
    if( a[1:] != '2010' ): paginaR4 = paginaR4 + """<th>%s</th>""" % (a[1:])
for a in anios:
    if( a[1:] != '2010' ): paginaR4 = paginaR4 + """<th>%s</th>""" % (a[1:])



paginaR4 = paginaR4 + """</tr>""" 


# Añadimos datos
for dic_a in var_abs_ccaa:

    
    for dic_r in var_rel_ccaa:
        if( dic_a['Comunidad Autonoma'] == dic_r['Comunidad Autonoma'] ): # Buscamos dic relativo asociado
            paginaR4 = paginaR4 + """<tr>""" 
            if( dic_a['Comunidad Autonoma'] != 'Total Nacional' ): paginaR4 = paginaR4 + """<th>%s</th>""" % (comunidades_autonomas[dic_a['Comunidad Autonoma']])    
            else: paginaR4 = paginaR4 + """<th>%s</th>""" % (dic_a['Comunidad Autonoma']) 
            for a in anios:
                    if( a[1:] != '2010' ): paginaR4 = paginaR4 + """<th>%s</th>""" % (dic_a[a])

            for a in anios:
                    if( a[1:] != '2010' ): paginaR4 = paginaR4 + """<th>%s</th>""" % (dic_r[a])

            paginaR4 = paginaR4 + """</tr>""" 


paginaR4 = paginaR4 + """</colgroup></table>""" 




###########################################################################################################
###############################                     HTML R5                      ##########################
###########################################################################################################

# R5. Para las 10 comunidades elegidas en el punto R3 generar un gráfico de líneas que refleje la
# evolución de la población total de cada comunidad autónoma desde el año 2010 a 2017, salvar el
# gráfico a fichero e incorporarlo a la página web 3 del punto R4.



# Añadimos la imagen
paginaR4 = paginaR4 + """<div style="float: left;"><IMG SRC="evolucionTop10.png"></div>"""






# Cerramos el archivo

R4.write(paginaR4)
R4.close()



