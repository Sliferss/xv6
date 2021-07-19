# xv6
Systems programming module, extension of xv6 operating system to include graphics modules and syscalls with batching for efficiency

Task 
In other modules on your course, you are used to using graphics routines provided by the operating
system that perform such functions as setting a pixel on the screen, drawing a line, etc. For this
assignment, you will be providing an implementation of such functions that operate on a VGA
display for the operating system being developed in this module. 
Because these functions will access video memory which is not mapped into the address space of
user programs (ring 3) and also need to access input and output ports, these functions need to be
implemented in ring 0 and, for this module, will form part of the kernel. However, they need to be
callable from programs running in ring 3, so new system calls need to be added in order for
programs to be able to access this functionality. 
The task is broken down into a series of stages. Implementation of more of the stages will result in
a higher grade being given for the assessment as long as all parts of earlier stages have been
implemented. The starting point for this assessment can be found on Github at
https://github.com/Kayomn/xv6-udo. 
Xv6 is an open standard that has been developed by MIT that has been used by numerous
institutions for teaching OS development. As such, you’ll find plenty of useful resources online.

Stage 1
Completed syscall
Completed graphical

Stage 2
Completed mode change
Completed screen save and load

Stage 3
Completed mode 12
Completed screen clear (efficient)

Stage 4
Completed batch struct
Completed batch syscall
Completed batch graphics call

Stage 5
Completed complicated batch calls of polygons 
