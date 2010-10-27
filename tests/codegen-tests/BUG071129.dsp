//-------------------------------------------------
// Bug 20071129 : generation de code recursif complexe.
// Les calculs ne sont pas ordonnés correctement
// Le bug se produit deja dans la version 0.9.8.7
// en mode scalaire normal.
//--------------------------------------------------

// fonctions mutuellement recursives
// BUG dans faust0993a1

//import("music.lib");

route(rx,ry,x,y) = x,rx,ry,y,ry,rx;
foo(x, rx, ry) = x + 0.9*rx + 0.1*ry;
faa(y, ry, rx) = y + 0.2*rx - 0.8*ry;

goo = +~sqrt;
gaa = +~sin;

process = ((route : foo, faa)~(_,_) : *(11), *(13)) ~ (goo, gaa);
