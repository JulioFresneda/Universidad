create table ventas  (
  codpro char(3)  references  proveedor(codpro),
  codpie char(3) references  pieza(codpie),
  codpj char(3) references proyecto(codpj),
  cantidad number(4),
  constraint clave_primaria primary key (codpro,codpie,codpj)
);


insert into proveedor values( 'S5',  'MARIA REYES',  5, 'ROMA');


insert into pieza values( 'P5', 'ALCAYATA', 'BLANCO', 10, 'ROMA' );



insert into proyecto values( 'J1', 'PROYECTO 1', 'LONDRES' );

J2  Proyecto 2         Londres
J3  Proyecto 3         Paris
J4  Proyecto 4         Roma

SELECT * FROM ventas;

alter table ventas add( fecha date );

insert into ventas (SELECT * FROM opc.ventas);

