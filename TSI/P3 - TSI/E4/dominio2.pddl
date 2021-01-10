(define (domain zeno-travel)


(:requirements
  :typing
  :fluents
  :derived-predicates
  :negative-preconditions
  :universal-preconditions
  :disjuntive-preconditions
  :conditional-effects
  :htn-expansion

  ; Requisitos adicionales para el manejo del tiempo
  :durative-actions
  :metatags
 )

(:types aircraft person city - object)
(:constants slow fast - object)
(:predicates (at ?x - (either person aircraft) ?c - city)
             (in ?p - person ?a - aircraft)
             (different ?x ?y) (igual ?x ?y)
             (hay-fuel ?a ?c1 ?c2)
             (hay-fuel-zoom ?a ?c1 ?c2)
             (destino ?p - person ?c - city)
             )
(:functions (fuel ?a - aircraft)
            (distance ?c1 - city ?c2 - city)
            (slow-speed ?a - aircraft)
            (fast-speed ?a - aircraft)
            (slow-burn ?a - aircraft)
            (fast-burn ?a - aircraft)
            (capacity ?a - aircraft)
            (refuel-rate ?a - aircraft)
            (total-fuel-used ?a - aircraft)
            (boarding-time)
            (debarking-time)
            (fuel-limit ?a - aircraft)

            (pasajeros-a-bordo ?a - aircraft)
            (aforo-maximo ?a - aircraft)

            (tiempo-vuelo ?a - aircraft )
            (tiempo-maximo ?a - aircraft)
            )

;; el consecuente "vac�o" se representa como "()" y significa "siempre verdad"
(:derived
  (igual ?x ?x) ())

(:derived 
  (different ?x ?y) (not (igual ?x ?y)))



;; este literal derivado se utiliza para deducir, a partir de la información en el estado actual, 
;; si hay fuel suficiente para que el avión ?a vuele de la ciudad ?c1 a la ?c2
;; el antecedente de este literal derivado comprueba si el fuel actual de ?a es mayor que 1. 
;; En este caso es una forma de describir que no hay restricciones de fuel. Pueden introducirse una
;; restricción más copleja  si en lugar de 1 se representa una expresión más elaborada (esto es objeto de
;; los siguientes ejercicios).
(:derived 
  (hay-fuel ?a - aircraft ?c1 - city ?c2 - city)
  (>= (fuel ?a) (* (distance ?c1 ?c2) (slow-burn ?a) ) )
)

(:derived 
  (hay-fuel-zoom ?a - aircraft ?c1 - city ?c2 - city)
  (>= (fuel ?a) (* (distance ?c1 ?c2) (fast-burn ?a) ) )
)





(:task transport-person
	:parameters (?p - person ?c - city)
	
  (:method Case1 ; si la persona está en la ciudad no se hace nada
	 :precondition (at ?p ?c)
	 :tasks ()
  )
	 
  (:method Case2 ; si la persona está en el avion y el avión en la ciudad de destino
   :precondition (and(in ?p - person ?a - aircraft)(destino ?p ?c)(at ?a ?c))
   :tasks(
     (debark-todos ?a ?c)
   )
  )

  (:method Case3 ;si no está en la ciudad destino, pero avion y persona est�n en la misma ciudad
  :precondition (and (at ?p - person ?c1 - city)
                      (at ?a - aircraft ?c1 - city)
                      (not (= ?c1 ?c)))       
  :tasks ( 
          (board-todos ?a ?c1)
          (transport-person ?p ?c))    
  )


  (:method Case4 ; si el avión y la persona están en distintas ciudades, y la persona no está en el destino
  :precondition (and (at ?p - person ?c1 - city)
                      (at ?a - aircraft ?c2 - city)
                      (not(= ?c1 ?c2))
                      (not(= ?c1 ?c )))
  :tasks ( 
            (mover-avion ?a ?c2 ?c1 )
            (transport-person ?p ?c)
  ) 
  )

  (:method Case5 ; si no hay ninguna persona para embarcar (ya están todas embarcadas) 
    :precondition (and( at ?a - aircraft ?c1 - city)(not(= ?c1 ?c)))
    :tasks(
          (mover-avion ?a ?c1 ?c)
          (debark-todos ?a ?c)   
    )
  )
    

  )

(:task board-todos 
 :parameters (?a - aircraft ?c - city )

 (:method embarcar
  :precondition (and( at ?p - person ?c  )(not(destino ?p ?c)))
  :tasks (
    (board ?p ?a ?c)
    (board-todos ?a ?c)
  )
  )

  (:method fin
   :precondition()
   
   :tasks())
)

(:task debark-todos 
 :parameters (?a - aircraft ?c - city )

 (:method desembarcar
  :precondition (and( in ?p - person ?a  )(destino ?p ?c))
  :tasks (
    (debark ?p ?a ?c)
    (debark-todos ?a ?c)
  )
  )

  (:method fin
   :precondition()
   
   :tasks())
)

(:task mover-avion
 :parameters (?a - aircraft ?c1 - city ?c2 -city)
 
  (:method fuel-suficiente-zoom
  :precondition ( and  (hay-fuel-zoom ?a ?c1 ?c2)  (<= (+(*(distance ?c1 ?c2)(fast-burn ?a))(total-fuel-used ?a))(fuel-limit ?a)))
    
  :tasks (
          (zoom ?a ?c1 ?c2)
         )
  )

  (:method fuel-insuficiente-zoom
  :precondition (and (not(hay-fuel-zoom ?a ?c1 ?c2)) (<= (+(*(distance ?c1 ?c2)(fast-burn ?a))(total-fuel-used ?a))(fuel-limit ?a)))
  :tasks (
          (refuel ?a ?c1)
          (zoom ?a ?c1 ?c2)
         )
   )

  (:method fuel-suficiente-fly
  :precondition ( and(hay-fuel ?a ?c1 ?c2)  (<= (+(*(distance ?c1 ?c2)(slow-burn ?a))(total-fuel-used ?a))(fuel-limit ?a))  )
    
  :tasks (
          (fly ?a ?c1 ?c2)
         )
  )

  (:method fuel-insuficiente-fly
  :precondition ( and(not(hay-fuel ?a ?c1 ?c2)) (<= (+(*(distance ?c1 ?c2)(slow-burn ?a))(total-fuel-used ?a))(fuel-limit ?a))  )
  :tasks (
          (refuel ?a ?c1)
          (fly ?a ?c1 ?c2)
         )
   )



  
  )
 
(:import "Primitivas-Zenotravel.pddl") 


)
