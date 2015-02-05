CheReNE-lib
=======

##### PROJECT NAME:	CheReNE-lib (Chemical Reaction Networks Equations - library)  
##### STATUS:		On development    
##### AUTOR:		Daniel M.
##### E-MAIL:		[danielmejia55@gmail.com](mailto:danielmejia55@gmail.com)  
##### SHORT DESCRIPTION:  
C++ classes to manipulate strings containing information related to biochemical reaction networks,  
such as _A+B->C_. Using a set of strings as an input, the library parses the code to a set of  
differential equations to be solved using libraries as [GSL](http://www.gnu.org/software/gsl/) or  
[boost::odenint](http://www.boost.org/doc/libs/1_55_0b1/libs/numeric/odeint/doc/html/index.html) 
This code is inherited from my old repository cppBioCheN(A transtional repository)

##### DESCRIPTION   
###### Introduction   
Dealing with Biochemical Reaction Networks (BcRN) can be exhausting. BcRN can be modeled by many 
ways, one of them by using ordinary differential equations. There's the Michaelis-Menten approach,  
which could be derived from the differential equations that describe the network and apply equilibrium   
criterion. When looking for the complete description of the BcRN, one must reduce the assumptions  
made in order to get the more information that one can get.  
  
Using the differential equations approach, the analytical steps on deriving the set of equations   
for the BcRN takes lots of time and errors propagate faster in the process.   
If the more when the model have to be changed or modified, the task becomes so exhausting.   
Given the fact that the differential equations can get so complex and the involved   
chemical species can get to high levels of coupling among the equations that describe the network,  
I found the need of developing a computational tool for deriving the differential equations, by now  
using the _mass action law_ kinetics.

This library exploits the _vector space_ like features that _chemical reaction networks_ theorist have developed   
since the works of James Wei _et al._ on the 60's.

(more to be coming...)

#####

##### USAGE NOTES:  

(more to be coming...)

##### TO DO:
* Add doxygen documentation.  **DONE**
* Add cmake oriented structure. **DONE**  
* Update readme with usage notes.  

##### EVENTS:
>* 26-Feb-2014	Repository created  

##### LICENSE
    
The CheReNE-lib project consist of an  implementation of STL containers and lib BOOST libraries
to generate differential equations for reaction networks by only using a set of strings as an input
Copyright (C) 2013-2014  Daniel Mejía R. [danielmejia55@gmail.com](mailto:danielmejia55@gmail.com) 

"CheReNE-lib" is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

"CheReNE-lib" is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
