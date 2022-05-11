/************************** BEGIN juce-midi.h ****************************
FAUST Architecture File
Copyright (C) 2003-2022 GRAME, Centre National de Creation Musicale
---------------------------------------------------------------------
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

EXCEPTION : As a special exception, you may create a larger work
that contains this FAUST architecture section and distribute
that work under terms of your choice, so long as this FAUST
architecture section is not modified.
***************************************************************************/

#ifndef __juce_midi__
#define __juce_midi__
 
#include "faust/midi/midi.h"

class FAUST_API MapUI;

/**
 *  MIDI input/output handling using JUCE framework: https://juce.com
 */
class juce_midi_handler : public midi_handler {
    
    protected:
    
        juce::MidiBuffer fOutputBuffer;
        juce::CriticalSection fMutex;
    
        void decodeMessage(const juce::MidiMessage& message)
        {
            const juce::uint8* data = message.getRawData();
            int channel = message.getChannel() - 1; // which MIDI channel, 0-15
            double time = message.getTimeStamp();
            
            if (message.isNoteOff()) {
                handleKeyOff(time, channel, data[1], data[2]);
            } else if (message.isNoteOn()) {
                handleKeyOn(time, channel, data[1], data[2]);
            } else if (message.isAftertouch()) {
                handlePolyAfterTouch(time, channel, data[1], data[2]);
            } else if (message.isController()) {
                handleCtrlChange(time, channel, data[1], data[2]);
            } else if (message.isProgramChange()) {
                handleProgChange(time, channel, data[1]);
            } else if (message.isChannelPressure()) {
                handleAfterTouch(time, channel, data[1]);
            } else if (message.isPitchWheel()) {
                handlePitchWheel(time, channel, data[1], data[2]);
            } else if (message.isMidiClock()) {
                handleClock(time);
            // We can consider start and continue as identical messages.
            } else if (message.isMidiStart() || message.isMidiContinue()) {
                handleStart(time);
            } else if (message.isMidiStop()) {
                handleStop(time);
            } else if (message.isSysEx()) {
                std::vector<unsigned char> sysex(data, data + message.getRawDataSize());
                handleSysex(time, sysex);
            } else {
                std::cerr << "Unused MIDI message" << std::endl;
            }
        }
    
    public:
    
        juce_midi_handler():midi_handler("JUCE")
        {}
    
        virtual ~juce_midi_handler() {}
    
        // Used with MidiBuffer (containing several messages)
        void encodeBuffer(juce::MidiBuffer& buffer)
        {
            const juce::ScopedTryLock lock(fMutex);
            if (lock.isLocked()) {
                buffer.swapWith(fOutputBuffer);
                fOutputBuffer.clear();
            } else {
                std::cerr << "encodeBuffer fails..." << std::endl;
            }
        }
        
        void decodeBuffer(juce::MidiBuffer& buffer)
        {
            juce::MidiMessage msg;
            int ignore;
            for (juce::MidiBuffer::Iterator it(buffer); it.getNextEvent(msg, ignore);) {
                decodeMessage(msg);
            }
            buffer.clear();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)), 0);
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)), 0);
        }
        
        void ctrlChange(int channel, int ctrl, int val)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)), 0);
        }
        
        void chanPress(int channel, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::channelPressureChange(channel + 1, press), 0);
        }
        
        void progChange(int channel, int pgm)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::programChange(channel + 1, pgm), 0);
        }
        
        void keyPress(int channel, int pitch, int press)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press), 0);
        }
        
        void pitchWheel(int channel, int wheel)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)), 0);
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
        
        void startSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStart(), 0);
        }
        
        void stopSync(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiStop(), 0);
        }
        
        void clock(double date)
        {
            fOutputBuffer.addEvent(juce::MidiMessage::midiClock(), 0);
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fOutputBuffer.addEvent(juce::MidiMessage(message.data(), (int)message.size()), 0);
        }

};

class juce_midi : public juce_midi_handler, public juce::MidiInputCallback {

    private:
    
        std::unique_ptr<juce::MidiInput> fMidiIn;
        std::unique_ptr<juce::MidiOutput> fMidiOut;
    
        void handleIncomingMidiMessage(juce::MidiInput*, const juce::MidiMessage& message)
        {
            decodeMessage(message);
        }
    
    public:
    
        juce_midi():juce_midi_handler()
        {}
    
        virtual ~juce_midi()
        {
            stopMidi();
        }
        
        bool startMidi()
        {
            if ((fMidiIn = juce::MidiInput::openDevice(juce::MidiInput::getDefaultDeviceIndex(), this)) == nullptr) {
                return false;
            }
            if ((fMidiOut = juce::MidiOutput::openDevice(juce::MidiOutput::getDefaultDeviceIndex())) == nullptr) {
                return false;
            }
            fMidiIn->start();
            return true;
        }
        
        void stopMidi()
        { 
            fMidiIn->stop();
        }
    
        // MIDI output API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOn(channel + 1, pitch, juce::uint8(velocity)));
            return nullptr;
        }
        
        void keyOff(int channel, int pitch, int velocity) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::noteOff(channel + 1, pitch, juce::uint8(velocity)));
        }
        
        void ctrlChange(int channel, int ctrl, int val) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::controllerEvent(channel + 1, ctrl, juce::uint8(val)));
        }
        
        void chanPress(int channel, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::channelPressureChange(channel + 1, press));
        }
        
        void progChange(int channel, int pgm) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::programChange(channel + 1, pgm));
        }
          
        void keyPress(int channel, int pitch, int press) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::aftertouchChange(channel + 1, pitch, press));
        }
   
        void pitchWheel(int channel, int wheel) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::pitchWheel(channel + 1, range(0, 16383, wheel)));
        }
        
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            // TODO
        }
    
        void startSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStart());
        }
       
        void stopSync(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiStop());
        }
        
        void clock(double date) 
        {
            fMidiOut->sendMessageNow(juce::MidiMessage::midiClock());
        }
    
        void sysEx(double date, std::vector<unsigned char>& message)
        {
            fMidiOut->sendMessageNow(juce::MidiMessage(message.data(), (int)message.size()));
        }
    
};

#endif // __juce_midi__

/**************************  END  juce-midi.h **************************/
