Star Trek Voyager : Elite Force Single Player Game Source (expansion version)

Much like the game SDK for Multiplayer, this SDK will allow you to modify the menus and game behavior of Elite Force Single Player.

SDK Includes:

BaseEF\		- folder contains weapons.dat and npc configs
cgame\		- folder contains client side game source (this code handles the rendering)
client\		- folder contains some headers for force feedback and keys
game\		- folder contains game source ( this is where the AI runs )
icarus\		- folder contains the script parser/executor
qcommon\	- folder contains common headers
renderer\	- folder contains renderer definition header
ui\		- folder contains all the menus and menu rendering code
ReadMe.txt	- this file
EF_SPMod.dsw	- workspace project for Microsoft Visual Studio 6.0 (can be opened in VC .Net as well)
STEF Game Source License.doc - Legal text telling you to play nice with the code and don't make Paramount regret this release. :)

Since this SDK is only the game source, you will not be able to change any features of the executable, like rendering or map loading.
The DLLs you build with this source should work with the Expansion Pack EF Exe. 
The single player executable was not designed to read DLLs from base folders for mods.
So you will have to put your modified DLLs in their own folders, along with the stvoy.exe and add the command line +set fs_basepath [original install folder]
This has not been tested in any way, but I wanted to get the source out there as quickly as possible.


Special thanks to "The Dark Project", who have been diligently producing the modifcation "Voyager: Insurrection", for pointing out the need for this SDK.
 * Watch http://www.darkproject.org closely in the next few weeks for important news! *


