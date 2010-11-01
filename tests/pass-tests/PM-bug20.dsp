 // replace 
 
replace (x,y,(u:v)) = replace(x,y,u) : replace(x,y,v);
replace (x,y,(u,v)) = replace(x,y,u) , replace(x,y,v);
replace (x,y,(u<:v)) = replace(x,y,u) <: replace(x,y,v);
replace (x,y,(u:>v)) = replace(x,y,u) :> replace(x,y,v);
replace (x,y,(u~v)) = replace(x,y,u) ~ replace(x,y,v);
replace (x,y,x) = y;
replace (x,y,u) = u;
 


process = replace(1,2,(0,0,1,0,1));

