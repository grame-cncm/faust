### faustgen~ Xcode project for Max/MSP SDK 7.3.3

- copy the faustgen~ folder in max-sdk-7.3.3/source/audio
- since the Xcode project is located in SDK folder, you'll have to describe where the faust sources are located. In the faustgen~.xcodeproj folder, opens the project.pbxproj file and correct the **path = "../../../../../../../../Documents/faust-github-faust2/embedded/faustgen/src";** line to reflect your faust2 folder location 
- open the faustgen~.xcodeproj Xcode project and build it
- the faustgen~.mxo binary is generated in max-sdk-7.3.3/externals 
