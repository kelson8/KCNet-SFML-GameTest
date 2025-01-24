# KCNet-SFML-GameTest
I will be working on a basic game in SFML using C++ in this repo

I would like to thank the author of this youtube series for this:
* https://www.youtube.com/playlist?list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up

Currently on this guide in the playlist (Creating the window): https://www.youtube.com/watch?v=C06eGdy7C6k&list=PL6xSOsbVA1eb_QqMTTcql_3PdOiE928up&index=4

# To build
1. Open this project in Visual Studio 2022
2. Add sfml to additional include directories and additional linker directories: 
```
Include dirs for Release and Debug: 
 $(SolutionDir)include\
 $(SolutionDir)src\

Linker dirs for Release and Debug: 
 $(SolutionDir)lib

Linker additional dependencies for Release:
 sfml-graphics.lib
 sfml-window.lib
 sfml-audio.lib
 sfml-network.lib
 sfml-system.lib

Linker additional dependencies for Debug:
 sfml-graphics-d.lib
 sfml-window-d.lib
 sfml-audio-d.lib
 sfml-network-d.lib
 sfml-system-d.lib
```

# To Run
If downloading from the source:
1. Download SFML from here for the DLLs on Windows: https://www.sfml-dev.org/download/sfml/2.6.1/
2. Extract that file somewhere
3. 
```
If using Debug build mode, copy the sfml-d.dll files to ./x64/Debug, 

if using Release build mode.copy the files without the -d to ./x64/Release
```

You can also use my DLL's that I have in this project.

The dlls are also in a folder named DLL's in the root of the project, those can be copied to the ./x64/Release and ./x64/Debug folders.


### Info
So far this doesn't do anything besides display some text to the console. I am going to try to make this into a basic Asteroids clone or something from scratch.

# License
This project is licensed under the MIT license.

# Credits
None of this would be possible without the team at SFML, this is using their libraries and window system:
* https://github.com/SFML/SFML/

I have included the zlib license in the include/SFML folder
