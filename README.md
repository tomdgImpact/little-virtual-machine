# little-virtual-machine
Creation of a little virtual machine capable of executing assembly code, in C.

## What is a Virtual Machine ?
A VM is a program that will simulate the hardware of a omputer.
For example, emulators of old video games consoles are VM that simulate all the hardware and behaviour of the old consoles.
It can understand a mcahine langage which you can use to program it.
Each CPU has its own assembly language. VM can help software development. If you want your program to be portable on each architecture and don't have any compiler that can compile in this arhcitecture, a VM, which would behave the same way on each architecture, would make your program portable on any device.
The most famous VM is the JVM (Java Virtual Machine).

There still one major drawback from VM, the overhead at runtime. As you emulate a program, in the VM, that is also running on the laying down operating system.

## Use case of VM
One major use case of VM nowadays is to execute a program in a secure and isolated operating system (docker, kubernetes).
Also, garbage collection is a really good example of how VMs are usefull. Indeed, a program can access memory but cannot see its own stack and variables. But a VM that is running on an OS can see every memory chunk.
 Blockchain is another use case of VMs. In fact, in the Etherum plateform, we can run smart contract, that trigger on specific actions. Smart contract are programs written by complete stranger and that run over the whole Etherum network. To prevent any code to execute malicious commands, attack or anything, every smart contract run in a dedicated VM and is isolated. If any error occurs or anything, the program can be automatically stopped without impacting the whole blockchain.
 
 ## Our achitecture
 We will use a fictional computer that has an architecture called LC-3. LC-3 is used in some university to teach assembly language with the smaller set of instruction compared to x86.
 
documentation I used to code the project :
[explanation of the lc-3 architecture](http://www.cs.binghamton.edu/~tbarten1/CS120_Summer_2015/ClassNotes/L10-LC3_Intro.pdf)
[instruction set and documentation](https://www.jmeiners.com/lc3-vm/supplies/lc3-isa.pdf)

#How to use

```shell=
cd little-vm/src/c-vm/
gcc -g3 *.c -o lc3-vm
# dowload the 2048 games here https://github.com/rpendleton/lc3-2048
./lc-3 2048.obj
```
