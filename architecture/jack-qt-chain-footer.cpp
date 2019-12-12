/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

int main(int argc, char* argv[])
{
    char name[256];
    char rcfilename[256];
    char* home = getenv("HOME");
    
    snprintf(name, 256, "%s", basename(argv[0]));
    snprintf(rcfilename, 256, "%s/.%src", home, name);
    
    QApplication myApp(argc, argv);
    
    QTGUI interface;
    FUI finterface;
    
    // Add add DSP
    addAllDSP();
    
    // Combine QTUI
    combineUI(dsp_chain, &interface);
    
    // Combine FUI
    combineUI(dsp_chain, &finterface);
    
#ifdef HTTPCTRL
    // Combine httpdUI
    httpdUI httpdinterface(name, 1, 1, argc, argv);
    std::cout << "HTTPD is on" << std::endl;
    combineUI(dsp_chain, &httpdinterface);
#endif
    
#ifdef OSCCTRL
    // Combine OSCUI
    OSCUI oscinterface(name, argc, argv);
    std::cout << "OSC is on" << std::endl;
    combineUI(dsp_chain, &oscinterface);
#endif
    
    std::vector<audio*> audio_chain = initJACKClients(dsp_chain);
    
    startJACKClients(audio_chain);
    
#ifdef HTTPCTRL
    httpdinterface.run();
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
    
    // After the allocation of controllers
    finterface.recallState(rcfilename);
    interface.run();
    
    myApp.setStyleSheet(interface.styleSheet());
    myApp.exec();
    
    interface.stop();
    
    stopJACKClients(audio_chain);
    
    finterface.saveState(rcfilename);
    
    return 0;
}
