/************************** BEGIN voice.h **************************
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
*********************************************************************/

#ifndef __VST_VOICE_H__
#define __VST_VOICE_H__

class Voice : public vstUI {
    
    public:
        Voice(int sample_rate)
            : vstUI(), m_dsp() 
        {
            m_dsp.init(sample_rate);
            m_dsp.buildUserInterface(this);
        }

        mydsp m_dsp;
    
}; //end of Voice class

#endif
/**************************  END  voice.h **************************/
