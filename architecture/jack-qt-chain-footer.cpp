
int main(int argc, char *argv[])
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
    
    finterface.recallState(rcfilename);
    
    startJACKClients(audio_chain);
 
#ifdef HTTPCTRL
    httpdinterface.run();
#endif
    
#ifdef OSCCTRL
    oscinterface.run();
#endif
    
    interface.run();
    
    myApp.setStyleSheet(interface.styleSheet());
    myApp.exec();
    
    interface.stop();
    
    stopJACKClients(audio_chain);
    
    finterface.saveState(rcfilename);
    
    return 0;
}
