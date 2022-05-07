------------------------------------------------------------------
IN PURSUIT OF HAPPYNESS
Navigating Life in IIT Delhi

Designed & developed by: Spruce Gaming (c) 
Developers:
Samyak Jain (2020CS50667)
Viraj Agashe (2020CS10567)

------------------------------------------

INSTALLATION INSTRUCTIONS:

=============================
OS Details: Windows 10 + WSL2 
=============================
- SDL2:
>>>> sudo apt-get install libsdl2-dev

- SDL-Image 
>>>> sudo apt-get install libsdl2-image 

- SDL-TTF
>>>> sudo apt-get install libsdl2-ttf

Xming Software:
Download this software from the internet & install on Windows. 
This is for loading the screen as WSL2 does not have intrinsic 
access to device hardware (on Windows 10). Windows 11 users may
have a workaround. 

Note:
---------
To load the screen on WSL2, follow these steps:

- Run the following command in WSL2:
>>>> export DISPLAY=$(grep -m 1 nameserver /etc/resolv.conf | awk '{print $2}'):0.0

- Run any file requiring a screen (eg. xeyes)

- An error message will appear in the terminal. Open Xming logs.

- The last line should be, client 4 rejected from IP XXX.YY.ZZ.WWW. Copy this 
IP address into the file "X0.hosts" (present in the installation folder of Xming)

=============================
OS DETAILS 2
Ubuntu 20.04.3  - 64 bit 
=============================
- SDL2:
>>>> sudo apt-get install libsdl2-dev

- SDL-Image 
>>>> sudo apt-get install libsdl2-image 

- SDL-Image
>>>> sudo apt-get install libsdl2-mixer

- SDL-TTF
>>>> sudo apt-get install libsdl2-ttf

---------------------------------------

COMPILATION INSTRUCTIONS 

Run the client 1 & client 2 makefiles on each of the clients.
>>>> make 

Then each client should simply type:
>>>> ./a.out 

---------------------------------------

SOURCES REFERRED:

For the creation of the game, we referred to the following resources:

- LAZY FOO TUTORIALS: https://lazyfoo.net/tutorials
- LET'S MAKE GAMES YT PLAYLIST: https://www.youtube.com/watch?v=QQzAHcojEKg&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=1
- UDP SERVER-CLIENT IMPLEMENTATION: https://www.geeksforgeeks.org/udp-server-client-implementation-c/
- SOCKETS: https://www.linuxhowtos.org/C_C++/socket.htm

-------------------------------------------------------------------