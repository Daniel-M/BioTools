kd-calculator
=============

This is part of the "muskin" protocol

Code to calculate the Kd for the reaction Calcium-MagFluo4 by using the fittin parameters obtained from  
the normalized fluorescence maxima. Those maxima created a Lorentzian/Sigmoid curved that its fitted to  

F(x) = A2 + (A1-A2)/(1+ exp((x-x0)/dx)) 


These parameters are used to calculate Kd, by passing a file with the contents as:  

A1=9.4444e-1  
A2=3.476e-3  
dx=3.5845e-1  
x0=4.6004  
dA1=1.9667e-2  
dA2=1.8693e-2  
ddx=3.7739e-2  
dx0=4.19038e-2 

Where for the each parameter J the error is expresed as dJ. So taking dx above, the error is ddx

The default input filename is "kd-params.txt", but other files can be passed as argv[1]: 

    ./kd-calculator.out parameters_are_here.txt
