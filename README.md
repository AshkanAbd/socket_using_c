[![Build status](https://dev.azure.com/kotksthegame/web_server_c/_apis/build/status/web_server_c-CI)](https://dev.azure.com/kotksthegame/web_server_c/_build/latest?definitionId=-1)
## Simple project with C that contains:
1) a web server
2) http-like transfer protocol
3) backend framework
4) client and frontend framework
5) sqlite3 database connection
6) html pages support

## Requirements:
1) Windows OS
2) C version >= 99
3) cmake version >= 3.14
4) winsock2 and pthread libraries

## How to run:
### Socket server:
1) cd socket_server
2) mkdir cmake
3) cd cmake
4) cmake ..
5) make
6) run socket_server.exe binary file

<b>Note: Run socket_server.exe with "-h" flag for help.</b>

### Socket client:
1) cd socket_client
2) mkdir cmake
3) cd cmake
4) cmake ..
5) make
6) run socket_client.exe binary file

<b>Note: Run socket_client.exe with "-h" flag for help.</b>

##### You can test it just now :) 
##### Also check Build folder for executables.
##### Some sub projects are available in other branches
