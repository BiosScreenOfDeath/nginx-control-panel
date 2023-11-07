# nginx-control-panel
A mini command-line based NGINX control panel to turn on and off NGINX along with PHP-CGI.

The program runs instances of PHP-CGI (with your preferred IP:port) and NGINX (or kills both instances with "-k" or "--kill") and instances. 
Currently supports nginx-1.25.2. 

Compile: g++ -I C:\Users\User\Documents\nginx_control_panel .\nginx_control_panel.cpp -o nginx_control_panel.exe

Run: .\nginx_control_panel.exe
