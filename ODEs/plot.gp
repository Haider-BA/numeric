set term png enhanced
set output "ode.png"
set size 1.0,1.0
set xlabel 'x'
set ylabel 'y'  
set title "Projectile trajectory"
plot [0:1500] [-100:500] \
     	  "ODE.output" u 2:3 w p title  'data' 
	    
