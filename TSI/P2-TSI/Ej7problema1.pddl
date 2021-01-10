(define ( problem ejercicio1 )
    (:domain BELKAN )
    (:objects z1 z2 z3 z4 z5 z6 z7 z8 z9 z10 z11 z12 z13 z14 z15 z16 z17 z18 z19 z20 z21 z22 z23 z24 z25 - zona 
              manzana1 - manzana
              rosa1 - rosa
              oro1 - oro
              algoritmo1 - algoritmo
              oscar1 - oscar
              jugador1 - jugador_coge
              princesa1 - princesa
              principe1 - principe 
              dicaprio1 - dicaprio 
              bruja1 - bruja
              profesor1 - profesor
              bikini1 bikini2 - bikini
            
              zapas1 zapas2 - zapatilla

              jugador2 - jugador_entrega

          
    )



    (:init
        
            
        ;; make e these are constants or objects:
        ;; z1 z6 z11 z16 z21 z2 z12 z22 z23 z24 z25 z20 z15 z10 z5 z9 z19 z3 z13 z8 z18
        (connected z1 z6)
        (connected z6 z1)
        (connected z6 z11)
        (connected z11 z6)
        (connected z11 z16)
        (connected z16 z11)
        (connected z16 z21)
        (connected z21 z16)
        (connected z1 z2)
        (connected z2 z1)
        (connected z11 z12)
        (connected z12 z11)
        (connected z21 z22)
        (connected z22 z21)
        (connected z22 z23)
        (connected z23 z22)
        (connected z23 z24)
        (connected z24 z23)
        (connected z24 z25)
        (connected z25 z24)
        (connected z25 z20)
        (connected z20 z25)
        (connected z20 z15)
        (connected z15 z20)
        (connected z15 z10)
        (connected z10 z15)
        (connected z10 z5)
        (connected z5 z10)
        (connected z9 z10)
        (connected z10 z9)
        (connected z19 z20)
        (connected z20 z19)
        (connected z2 z3)
        (connected z3 z2)
        (connected z12 z13)
        (connected z13 z12)
        (connected z8 z9)
        (connected z9 z8)
        (connected z18 z19)
        (connected z19 z18)
        (connected z4 z5)
        (connected z5 z4 )
        (connected z6 z7)
        (connected z7 z6)
        (connected z14 z15)
        (connected z15 z14)
        (connected z16 z17)
        (connected z17 z16)

        
        ( jugador_en jugador1 z1 )
        ( jugador_en jugador2 z1 )

        ( objeto_en manzana1 z3 )
        ( objeto_en oro1 z10 )
        ( objeto_en rosa1 z21 )
        ( objeto_en algoritmo1 z13 )
        ( objeto_en oscar1 z19 )
        
        ( personaje_en princesa1 z23 )
        ( personaje_en principe1 z13 )
        ( personaje_en profesor1 z2 )
        ( personaje_en bruja1 z16 )
        ( personaje_en dicaprio1 z25 )
        
        ( mano_vacia jugador1 )
        ( mano_vacia jugador2 )
        ( jugador_orientado_n jugador1  )
        ( jugador_orientado_n jugador2 )
        
        ( zona_orientada_n z1 z6  )
        ( zona_orientada_n z6 z11 )
        ( zona_orientada_n z11 z16 )
        ( zona_orientada_n z16 z21 )
        ( zona_orientada_n z5 z10 )
        ( zona_orientada_n z10 z15 )
        ( zona_orientada_n z15 z20 )
        ( zona_orientada_n z20 z25 )
        
        ( zona_orientada_s z6 z1  )
        ( zona_orientada_s z11 z6 )
        ( zona_orientada_s z16 z11 )
        ( zona_orientada_s z21 z16 )
        ( zona_orientada_s z10 z5 )
        ( zona_orientada_s z15 z10 )
        ( zona_orientada_s z20 z15 )
        ( zona_orientada_s z25 z20 )
        
        ( zona_orientada_e z2 z1 )
        ( zona_orientada_e z3 z2 )
        ( zona_orientada_e z9 z8 )
        ( zona_orientada_e z10 z9 )
        ( zona_orientada_e z13 z12 )
        ( zona_orientada_e z12 z11 )
        ( zona_orientada_e z20 z19 )
        ( zona_orientada_e z19 z18 )
        ( zona_orientada_e z22 z21 )
        ( zona_orientada_e z23 z22 )
        ( zona_orientada_e z24 z23 )
        ( zona_orientada_e z25 z24 )
        ( zona_orientada_e z5 z4 )
        ( zona_orientada_e z7 z6 )
        ( zona_orientada_e z15 z14 )
        ( zona_orientada_e z17 z16 )
        ( zona_orientada_e z20 z19 )
        
        ( zona_orientada_o z1 z2 )
        ( zona_orientada_o z2 z3 )
        ( zona_orientada_o z8 z9 )
        ( zona_orientada_o z9 z10 )
        ( zona_orientada_o z12 z13 )
        ( zona_orientada_o z11 z12 )
        ( zona_orientada_o z19 z20 )
        ( zona_orientada_o z18 z19 )
        ( zona_orientada_o z21 z22 )
        ( zona_orientada_o z22 z23 )
        ( zona_orientada_o z23 z24 )
        ( zona_orientada_o z24 z25 )
        ( zona_orientada_o z4 z5 )
        ( zona_orientada_o z6 z7 )
        ( zona_orientada_o z14 z15 )
        ( zona_orientada_o z16 z17 )
        ( zona_orientada_o z19 z20 )


        (= ( distancia_total ) 0 )

        (= ( distancia z1 z6) 1 )
        (= ( distancia z6 z1) 1 )
        (= ( distancia z6 z11) 1 )
        (= ( distancia z11 z6) 1 )
        (= ( distancia z11 z16) 1 )
        (= ( distancia z16 z11) 1 )
        (= ( distancia z16 z21) 1 )
        (= ( distancia z21 z16) 1 )
        (= ( distancia z1 z2) 1 )
        (= ( distancia z2 z1) 1 )
        (= ( distancia z11 z12) 1 )
        (= ( distancia z12 z11) 1 )
        (= ( distancia z21 z22) 1 )
        (= ( distancia z22 z21) 1 )
        (= ( distancia z22 z23) 1 )
        (= ( distancia z23 z22) 1 )
        (= ( distancia z23 z24) 1 )
        (= ( distancia z24 z23) 1 )
        (= ( distancia z24 z25) 1 )
        (= ( distancia z25 z24) 1 )
        (= ( distancia z25 z20) 1 )
        (= ( distancia z20 z25) 1 )
        (= ( distancia z20 z15) 1 )
        (= ( distancia z15 z20) 1 )
        (= ( distancia z15 z10) 1 )
        (= ( distancia z10 z15) 1 )
        (= ( distancia z10 z5) 1 )
        (= ( distancia z5 z10) 1 )
        (= ( distancia z9 z10) 1 )
        (= ( distancia z10 z9) 1 )
        (= ( distancia z19 z20) 1 )
        (= ( distancia z20 z19) 1 )
        (= ( distancia z2 z3) 1 )
        (= ( distancia z3 z2) 1 )
        (= ( distancia z12 z13) 1 )
        (= ( distancia z13 z12) 1 )
        (= ( distancia z8 z9) 1 )
        (= ( distancia z9 z8) 1 )
        (= ( distancia z18 z19) 1 )
        (= ( distancia z19 z18) 1 )
        (= ( distancia z4 z5) 1 )
        (= ( distancia z5 z4 ) 1 )
        (= ( distancia z6 z7) 1 )
        (= ( distancia z7 z6) 1 )
        (= ( distancia z14 z15) 1 )
        (= ( distancia z15 z14) 1 )
        (= ( distancia z16 z17) 1 )
        (= ( distancia z17 z16) 1 )

        
        ( zona_piedra z1 )
        ( zona_piedra z2 )
        ( zona_piedra z7 )
        ( zona_piedra z6 )
        ( zona_piedra z11 )
        ( zona_piedra z12 )

        ( zona_arena z16 )
        ( zona_arena z17 )
        ( zona_arena z21 )
        ( zona_arena z18 )
        ( zona_arena z15 )
        ( zona_arena z19 )

        ( zona_bosque z22 )
        ( zona_bosque z23 )
        ( zona_bosque z24 )
        ( zona_bosque z25 )
        ( zona_bosque z20 )

        ( zona_agua z13 )
        ( zona_agua z14 )
        ( zona_agua z9 )
        ( zona_agua z10 )
        ( zona_agua z3 )
        ( zona_agua z4 )
        ( zona_agua z5 )

        ( zona_precipicio z8 )

        ( objeto_en bikini1 z18)
        ( es_bikini bikini1 )
        ( objeto_en bikini2 z24)
        ( es_bikini bikini2 )
        ( objeto_en zapas1 z7)
        ( es_zapas zapas1 )
        ( objeto_en zapas1 z4)
        ( es_zapas zapas2 )


        (= ( puntos oscar1 dicaprio1 ) 10 )
        (= ( puntos oscar1 princesa1 ) 5 )
        (= ( puntos oscar1 bruja1 ) 4 )
        (= ( puntos oscar1 profesor1 ) 3 )
        (= ( puntos oscar1 principe1 ) 1 )

        (= ( puntos rosa1 dicaprio1 ) 1 )
        (= ( puntos rosa1 princesa1 ) 10 )
        (= ( puntos rosa1 bruja1 ) 5 )
        (= ( puntos rosa1 profesor1 ) 4 )
        (= ( puntos rosa1 principe1 ) 3 )

        (= ( puntos manzana1 dicaprio1 ) 3 )
        (= ( puntos manzana1 princesa1 ) 1 )
        (= ( puntos manzana1 bruja1 ) 10 )
        (= ( puntos manzana1 profesor1 ) 5 )
        (= ( puntos manzana1 principe1 ) 4 )

        (= ( puntos algoritmo1 dicaprio1 ) 4 )
        (= ( puntos algoritmo1 princesa1 ) 3 )
        (= ( puntos algoritmo1 bruja1 ) 1 )
        (= ( puntos algoritmo1 profesor1 ) 10 )
        (= ( puntos algoritmo1 principe1 ) 5 )

        (= ( puntos oro1 dicaprio1 ) 5 )
        (= ( puntos oro1 princesa1 ) 4 )
        (= ( puntos oro1 bruja1 ) 3 )
        (= ( puntos oro1 profesor1 ) 1 )
        (= ( puntos oro1 principe1 ) 10 )

        (= ( puntos_totales ) 0 )


        (= ( bolsillo_capacidad_total dicaprio1 ) 1 )
        (= ( bolsillo_capacidad_total princesa1 ) 1 )
        (= ( bolsillo_capacidad_total principe1 ) 2 )
        (= ( bolsillo_capacidad_total bruja1 ) 1 )
        (= ( bolsillo_capacidad_total profesor1 ) 3 )

        (= ( bolsillo_num_objetos dicaprio1 ) 0 )
        (= ( bolsillo_num_objetos princesa1 ) 0 )
        (= ( bolsillo_num_objetos principe1 ) 0 )
        (= ( bolsillo_num_objetos bruja1 ) 0 )
        (= ( bolsillo_num_objetos profesor1 ) 0 )

    )
    
    
    (:goal
        ( and ( personaje_tiene_objeto princesa1 ) (personaje_tiene_objeto principe1 ) )
    )

    

)


