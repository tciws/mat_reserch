program ex3;
var i, rand, ca, cm, pi, qpi, x, y;
begin
   i := 0;
   qpi := 0;
   rand := 3827;
   ca := 8358;
   cm := 3797;
   rand := (rand + ca) * cm - (((rand + ca) * cm) div 100000) * 100000;
   rand := rand div 10;
   x := rand div 10;
     write rand,x
end.
