;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Belkan
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (domain BELKAN)
  (:requirements :adl :strips :typing)
  (:types personaje objeto zona jugador orientacion - object
    princesa principe bruja profesor dicaprio - personaje
    manzana rosa algoritmo oro oscar - objeto 

  )

  (:predicates 
            ( connected ?zona1 ?zona2 - zona )
            ( personaje_en ?personaje1 - personaje ?zona1 - zona )
            ( objeto_en ?objeto1 - objeto ?zona1 - zona )
            ( jugador_en ?j - jugador ?zona1 - zona )
            ( mano_vacia )
            ( mano_ocupada ?obj - objeto )
            ( personaje_tiene_objeto ?personaje1 - personaje )

            ( jugador_orientado_n ?j - jugador  )
            ( jugador_orientado_s ?j - jugador  )
            ( jugador_orientado_e ?j - jugador  )
            ( jugador_orientado_o ?j - jugador  )

            ( zona_orientada_n ?z1 - zona ?z2 - zona  )
            ( zona_orientada_s ?z1 - zona ?z2 - zona  )
            ( zona_orientada_e ?z1 - zona ?z2 - zona  )
            ( zona_orientada_o ?z1 - zona ?z2 - zona  )
  )

  (:action coger-objeto
	     :parameters ( ?obj - objeto ?z - zona ?j - jugador )
	     :precondition ( and (mano_vacia) (objeto_en ?obj ?z) (jugador_en ?j ?z) )
	     :effect ( and (not(mano_vacia)) (not(objeto_en ?obj ?z)) (mano_ocupada ?obj) )
  )

  (:action dejar-objeto
	     :parameters ( ?obj - objeto ?z - zona ?j - jugador )
	     :precondition ( and (mano_ocupada ?obj) (jugador_en ?j ?z) )
	     :effect ( and (not(mano_ocupada ?obj)) (mano_vacia) (objeto_en ?obj ?z) )
  )

  (:action entregar-objeto
	     :parameters ( ?obj - objeto ?z - zona ?p - personaje ?j - jugador )
	     :precondition ( and (personaje_en ?p ?z) (jugador_en ?j ?z) (mano_ocupada ?obj) )
         :effect ( and (mano_vacia) (not(mano_ocupada ?obj)) (personaje_tiene_objeto ?p ))

  )

  (:action girar-derecha 
         :parameters ( ?j - jugador      )

         :effect ( and

        ( when (and( jugador_orientado_n ?j  ))
            (and(not(jugador_orientado_n ?j  )) (jugador_orientado_e ?j  ) )
        )
        ( when (and( jugador_orientado_e ?j  ))
            (and(not(jugador_orientado_e ?j  )) (jugador_orientado_s ?j  ) )
        )
        ( when (and( jugador_orientado_s ?j  ))
            (and(not(jugador_orientado_s ?j  )) (jugador_orientado_o ?j ) )
        )
        ( when (and( jugador_orientado_o ?j ))
            (and(not(jugador_orientado_o ?j )) (jugador_orientado_n ?j  ) )
        )
            
         )
  )

  (:action girar-izquierda
         :parameters ( ?j - jugador      )

         :effect ( and

        ( when (and( jugador_orientado_n ?j  ))
            (and(not(jugador_orientado_n ?j  )) (jugador_orientado_o ?j ) )
        )
        ( when (and( jugador_orientado_o ?j ))
            (and(not(jugador_orientado_o ?j )) (jugador_orientado_s ?j  ) )
        )
        ( when (and( jugador_orientado_s ?j  ))
            (and(not(jugador_orientado_s ?j  )) (jugador_orientado_e ?j  ) )
        )
        ( when (and( jugador_orientado_e ?j  ))
            (and(not(jugador_orientado_e ?j  )) (jugador_orientado_n ?j  ) )
        )
            
         )
    
  )


  (:action ir
         :parameters ( ?origen - zona ?destino - zona ?j - jugador     )
         :precondition( 
                            and 
                                (jugador_en ?j ?origen)
                            
                            ( or (connected ?destino ?origen) (connected ?origen ?destino) ) 
                            
                            ( or (and ( jugador_orientado_n  ?j  ) ( zona_orientada_n ?destino ?origen  ) ) 
                                (and ( jugador_orientado_e  ?j   ) ( zona_orientada_e ?destino ?origen  ) )
                                (and ( jugador_orientado_s ?j  ) ( zona_orientada_s ?destino ?origen  ) )
                                (and ( jugador_orientado_o ?j ) ( zona_orientada_o ?destino ?origen ) )       
                            )  
                            
         )
         :effect( and (not( jugador_en ?j ?origen )) (jugador_en ?j ?destino) ) 
    )   
  

)