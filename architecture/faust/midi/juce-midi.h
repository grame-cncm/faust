/************************************************************************
    FAUST Architecture File
    Copyright (C) 2016 GRAME, Centre National de Creation Musicale
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

 ************************************************************************
 ************************************************************************/
 
#ifndef __juce_midi__
#define __juce_midi__
 
#include "faust/midi/midi.h"

class MapUI;

class juce_midi_handler : public midi_handler {
    
    protected:
    
        MidiBuffer fOutputBuffer;
        CriticalSection fMutex;
    
        void decodeMessage(const MidiMessage& message)
        {
            const uint8* data = message.getRawData();
            
            if (message.isNoteOff()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOff(0, message.getChannel(), data[1], data[2]);
                }
            } else if (message.isNoteOn()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    if (data[1] != 0) {
                        fMidiInputs[i]->keyOn(0, message.getChannel(), data[1], data[2]);
                    } else {
                        fMidiInputs[i]->keyOff(0, message.getChannel(), data[1], data[2]);
                    }
                }
            } else if (message.isAftertouch()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyPress(0, message.getChannel(), data[1], data[2]);
                }
            } else if (message.isController()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(0, message.getChannel(), data[1], data[2]);
                }
            } else if (message.isProgramChange()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->progChange(0, message.getChannel(), data[1]);
                }
            } else if (message.isChannelPressure()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->chanPress(0, message.getChannel(), data[1]);
                }
            } else if (message.isPitchWheel()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->pitchWheel(0, message.getChannel(), ((data[1] * 128.0 + data[2]) - 8192) / 8192.0);
                }
            } else if (message.isMidiClock()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->clock(message.getTimeStamp());
                }
            } else if (message.isMidiStart()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->start_sync(message.getTimeStamp());
                }
            } else if (message.isMidiStop()) {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->stop_sync(message.getTimeStamp());
                }
            } else {
                std::cerr << "Unused MIDI message" << std::endl;
            }
        }
    
    public:
    
        juce_midi_handler():midi_handler("JUCE")
        {}
        
        void encodeBuffer(MidiBuffer& buffer)
        {
            const ScopedTryLock lock(fMutex);
            if (lock.isLocked()) {
                buffer.swapWith(fOutputBuffer);
                fOutputBuffer.clear();
            } else {
                std::cerr << "encodeBuffer fails..." << std::endl;
            }
        }
        
        void decodeBuffer(MidiBuffer& buffer)
        {
            MidiMessage msg;
            int ignore;

            for (MidiBuffer::Iterator it(buffer); it.getNextEvent(msg, ignore);) {
                decodeMessage(msg);
            }
            
            buffer.clear();
        }
    
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(MidiMessage::noteOn(channel + 1, pitch, uint8(velocity)), 0);
            return 0;
        }
        
        void keyOff(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(MidiMessage::noteOff(channel + 1, pitch, uint8(velocity)), 0);
        }
        
        void ctrlChange(int channel, int ctrl, int val)
        {
            fOutputBuffer.addEvent(MidiMessage::controllerEvent(channel + 1, ctrl, uint8(val)), 0);
        }
        
        void chanPress(int channel, int press)
        {
            fOutputBuffer.addEvent(MidiMessage::channelPressureChange(channel + 1, press), 0);
        }
        
        void progChange(int channel, int pgm)
        {
            fOutputBuffer.addEvent(MidiMessage::programChange(channel + 1, pgm), 0);
        }
        
        void keyPress(int channel, int pitch, int press)
        {
            fOutputBuffer.addEvent(MidiMessage::aftertouchChange(channel + 1, pitch, press), 0);
        }
        
        void pitchWheel(int channel, int wheel)
        {
            // Deactivated for now
            // fOutputBuffer.addEvent(MidiMessage::pitchWheel(channel + 1, wheel), 0);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
        
        void start_sync(double date)
        {
            fOutputBuffer.addEvent(MidiMessage::midiStart(), 0);
        }
        
        void stop_sync(double date)
        {
            fOutputBuffer.addEvent(MidiMessage::midiStop(), 0);
        }
        
        void clock(double date)
        {
            fOutputBuffer.addEvent(MidiMessage::midiClock(), 0);
        }

};

class juce_midi : public juce_midi_handler, public MidiInputCallback {

    private:
    
        MidiInput* fMidiIn;
        MidiOutput* fMidiOut;
    
        void handleIncomingMidiMessage(MidiInput*, const MidiMessage& message)
        {
            decodeMessage(message);
        }
    
    public:
    
        virtual ~juce_midi()
        {
            stop_midi();
        }
        
        bool start_midi()
        {
            if ((fMidiIn = MidiInput::openDevice(MidiInput::getDefaultDeviceIndex(), this)) == nullptr) {
                return false;
            }
            if ((fMidiOut = MidiOutput::openDevice(MidiOutput::getDefaultDeviceIndex())) == nullptr) {
                return false;
            }
            
            fMidiIn->start();
            return true;
        }
        
        void stop_midi()
        { 
            fMidiIn->stop();
            delete fMidiIn;
            delete fMidiOut;
        }
        
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fMidiOut->sendMessageNow(MidiMessage::noteOn(channel + 1, pitch, uint8(velocity)));
            return 0;
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            fMidiOut->sendMessageNow(MidiMessage::noteOff(channel + 1, pitch, uint8(velocity)));
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            fMidiOut->sendMessageNow(MidiMessage::controllerEvent(channel + 1, ctrl, uint8(val)));
        }
        
        void chanPress(int channel, int press) 
        {
            fMidiOut->sendMessageNow(MidiMessage::channelPressureChange(channel + 1, press));
        }
        
        void progChange(int channel, int pgm) 
        {
            fMidiOut->sendMessageNow(MidiMessage::programChange(channel + 1, pgm));
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            fMidiOut->sendMessageNow(MidiMessage::aftertouchChange(channel + 1, pitch, press));
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            // Deactivated for now
            // fMidiOut->sendMessageNow(MidiMessage::pitchWheel(channel + 1, wheel));
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value) {}
         
        void start_sync(double date) 
        {
            fMidiOut->sendMessageNow(MidiMessage::midiStart());
        }
       
        void stop_sync(double date) 
        {
            fMidiOut->sendMessageNow(MidiMessage::midiStop());
        }
        
        void clock(double date) 
        {
           fMidiOut->sendMessageNow(MidiMessage::midiClock());
        }
        
};

#endif // __juce_midi__

