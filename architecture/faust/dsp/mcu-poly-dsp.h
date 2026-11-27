/************************** BEGIN mcu-poly-dsp.h ***********************
 FAUST Architecture File
 Copyright (C) 2026 Arev Imer
 ---------------------------------------------------------------------
 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation; either version 2.1 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

// The voices of a standard FAUST polyphonic program ('declare options
// "[nvoices:N]"', parameters freq/key, gain/vel/velocity, gate; an optional
// 'effect' after the voice mix), like FAUST's poly-dsp.h but for
// microcontrollers (Teensy, Daisy, ESP32, ...):
//
// - the voices come from the program's create()/destroy() (-mem: the
//   architecture's memory manager), so a program can be freed completely;
// - no std::map, std::string, MapUI or RTTI: a voice keeps pointers to its
//   zones only (FAUST's dsp_voice is a MapUI: tens of kB of heap per voice
//   for a program with many parameters);
// - the voices share their other parameters: the UI shows the first voice's
//   (and the effect's), copied to the others before every block;
// - silent voices are skipped: a voice is computed from its note on until
//   its output stayed below kStopLevel (-66 dB peak) for 10 ms after
//   the note off (poly-dsp.h: one block below -90 dB rms);
// - a new note takes the free voice unused longest (notes rotate through
//   the voices), else the oldest releasing one, else the oldest playing
//   one. A voice that still sounds fades out in 3 ms with its gate
//   off, takes the new note and fades in over 3 ms: no jump in pitch or
//   level at full volume; the envelopes go on from their level, as a
//   retrigger (poly-dsp.h: fades over half a block);
// - assign modes (a parameter with [poly:mode], 0..2, or setAssignMode()):
//   ROTATE (0) as above, release tails ring on; REUSE (1) takes the lowest
//   free or releasing voice and stops the other release tails, so only the
//   last notes played together keep their release; UNISON (2) puts every
//   voice on the last note held (legato over held keys, a new start after
//   all were up);
// - a parameter with [poly:voice] gets the voice's number (0, 1, ..; not
//   shared), e.g. for a fixed place in the stereo field per voice; in
//   FAUST's own poly-dsp.h it keeps its default.
//
// MIDI, as poly-dsp.h: the class is a FAUST 'midi' receiver. Built with a
// MidiUI (a midi_interface), it registers itself where the build has RTTI
// (without RTTI, e.g. on a Teensy: setMidiHandler()); notes can
// also be sent directly: keyOn(channel, pitch, velocity), keyOff(..). A note
// off releases the oldest voice playing that note on that channel (a note
// played again while held restarts its voice: setRetrigger()); CC 123
// (all notes off) releases the channel's voices, CC 120 (all sound off)
// stops them (a 3 ms fade); allNotesOff(hard), the "Panic" button. The
// program's [midi:..] parameters are the MidiUI's (or the architecture's)
// job: they are set on the first voice and so reach all.
//
// The UI as poly-dsp.h's grouped mode: "Polyphonic" / "Voices" with "Panic"
// and the first voice's parameters (without freq/key/gain/vel/gate and
// [poly:voice]: they belong to the voice allocation); with an effect inside
// "Sequencer" / "DSP1", the effect in "DSP2" (as dsp_sequencer).
//
// Not here: individual voice UIs (poly-dsp.h 'group' false), newVoice() /
// deleteVoice(), clone().

#ifndef __mcu_poly_dsp__
#define __mcu_poly_dsp__

#include <math.h>
#include <stdint.h>
#include <string.h>

#include "faust/dsp/dsp.h"
#include "faust/gui/UI.h"
#include "faust/midi/midi.h"

class mcu_dsp_poly : public dsp, public midi {

    public:
        typedef void (*destroy_fn)(dsp*);

        static constexpr float kStopLevel = 0.0005f;  // -66 dB
        static constexpr int MAX_VOICES = 16;
        static constexpr int MAX_CHANNELS = 16;
        static constexpr int MAX_SHARED = 256;  // parameters copied to all voices

    private:
        enum { FREE = -1 };

        struct Voice {
            dsp* fDSP = nullptr;
            FAUSTFLOAT* fFreq = nullptr;
            FAUSTFLOAT* fKey = nullptr;
            FAUSTFLOAT* fGain = nullptr;
            FAUSTFLOAT* fVel = nullptr;
            FAUSTFLOAT* fGate = nullptr;
            FAUSTFLOAT* fIndex = nullptr;   // [poly:voice]
            int fNote = FREE;         // the note it plays (also while releasing)
            int fChannel = 0;         // MIDI channel 0..15 of that note (of the next one while stolen)
            bool fHeld = false;       // gate on
            int fNextNote = FREE;     // stolen: the note after the fade out
            int fNextVel = 0;
            int fFadeOut = 0;         // samples left of the fade out (stolen or stopped)
            int fFadeIn = 0;          // samples left of the fade in (after a steal)
            uint32_t fAge = 0;        // note on order
            int fQuiet = 0;           // samples below kStopLevel after the note off
        };

        // a voice's zones in the order of its UI: the same order in every voice
        struct ZoneList : public UI {
            FAUSTFLOAT** fZones;
            int fMax;
            int fCount = 0;
            Voice* fVoice;
            FAUSTFLOAT* fIndexZone = nullptr;   // declared [poly:voice]
            FAUSTFLOAT* fModeZone = nullptr;    // declared [poly:mode] (stays shared: a setting)
            ZoneList(FAUSTFLOAT** zones, int max, Voice* voice) : fZones(zones), fMax(max), fVoice(voice) {}

            static bool is(const char* label, const char* name) { return strcmp(label, name) == 0; }
            void add(const char* label, FAUSTFLOAT* zone)
            {
                // FAUST's poly-dsp.h finds them by the end of the path
                if (is(label, "freq")) fVoice->fFreq = zone;
                else if (is(label, "key")) fVoice->fKey = zone;
                else if (is(label, "gain")) fVoice->fGain = zone;
                else if (is(label, "vel") || is(label, "velocity")) fVoice->fVel = zone;
                else if (is(label, "gate")) fVoice->fGate = zone;
                else if (zone == fIndexZone) fVoice->fIndex = zone;
                else if (fZones && fCount < fMax) fZones[fCount++] = zone;
                else fCount++;
            }
            void openTabBox(const char*) override {}
            void openHorizontalBox(const char*) override {}
            void openVerticalBox(const char*) override {}
            void closeBox() override {}
            void addButton(const char* l, FAUSTFLOAT* z) override { add(l, z); }
            void addCheckButton(const char* l, FAUSTFLOAT* z) override { add(l, z); }
            void addVerticalSlider(const char* l, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { add(l, z); }
            void addHorizontalSlider(const char* l, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { add(l, z); }
            void addNumEntry(const char* l, FAUSTFLOAT* z, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT, FAUSTFLOAT) override { add(l, z); }
            void addHorizontalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
            void addVerticalBargraph(const char*, FAUSTFLOAT*, FAUSTFLOAT, FAUSTFLOAT) override {}
            void addSoundfile(const char*, const char*, Soundfile**) override {}
            void declare(FAUSTFLOAT* zone, const char* key, const char* value) override
            {
                if (zone && strcmp(key, "poly") == 0 && strcmp(value, "voice") == 0) fIndexZone = zone;
                if (zone && strcmp(key, "poly") == 0 && strcmp(value, "mode") == 0) fModeZone = zone;
            }
        };

        // the first voice's UI without its note parameters (they belong to
        // the voice allocation): left out with their metadata, so any UI
        // (MapUI, GUIs, the MidiUI) only sees zones it may write
        struct HideNotes : public UI {
            UI* fUI;
            const Voice* fVoice;
            HideNotes(UI* ui, const Voice* voice) : fUI(ui), fVoice(voice) {}
            bool hidden(FAUSTFLOAT* z) const
            {
                return z && (z == fVoice->fFreq || z == fVoice->fKey || z == fVoice->fGain || z == fVoice->fVel ||
                             z == fVoice->fGate || z == fVoice->fIndex);
            }
            void openTabBox(const char* l) override { fUI->openTabBox(l); }
            void openHorizontalBox(const char* l) override { fUI->openHorizontalBox(l); }
            void openVerticalBox(const char* l) override { fUI->openVerticalBox(l); }
            void closeBox() override { fUI->closeBox(); }
            void addButton(const char* l, FAUSTFLOAT* z) override { if (!hidden(z)) fUI->addButton(l, z); }
            void addCheckButton(const char* l, FAUSTFLOAT* z) override { if (!hidden(z)) fUI->addCheckButton(l, z); }
            void addVerticalSlider(const char* l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) override { if (!hidden(z)) fUI->addVerticalSlider(l, z, i, a, b, s); }
            void addHorizontalSlider(const char* l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) override { if (!hidden(z)) fUI->addHorizontalSlider(l, z, i, a, b, s); }
            void addNumEntry(const char* l, FAUSTFLOAT* z, FAUSTFLOAT i, FAUSTFLOAT a, FAUSTFLOAT b, FAUSTFLOAT s) override { if (!hidden(z)) fUI->addNumEntry(l, z, i, a, b, s); }
            void addHorizontalBargraph(const char* l, FAUSTFLOAT* z, FAUSTFLOAT a, FAUSTFLOAT b) override { fUI->addHorizontalBargraph(l, z, a, b); }
            void addVerticalBargraph(const char* l, FAUSTFLOAT* z, FAUSTFLOAT a, FAUSTFLOAT b) override { fUI->addVerticalBargraph(l, z, a, b); }
            void addSoundfile(const char* l, const char* f, Soundfile** s) override { fUI->addSoundfile(l, f, s); }
            void declare(FAUSTFLOAT* z, const char* k, const char* v) override { if (!hidden(z)) fUI->declare(z, k, v); }
#ifdef DAISY_NO_RTTI
            bool isSoundUI() const override { return fUI->isSoundUI(); }
            bool isMidiInterface() const override { return fUI->isMidiInterface(); }
#endif
        };

        Voice fVoices[MAX_VOICES];
        int fCount;
        int fLimit;               // voices in use (setVoiceLimit)
        bool fControl;            // false: every voice always runs (poly-dsp.h 'control')
        bool fRetrigger = true;   // a held note played again restarts its voice
        // assign mode: ROTATE, REUSE, UNISON; from a [poly:mode]
        // parameter if the program has one, else setAssignMode()
        FAUSTFLOAT* fModeZone = nullptr;
        int fAssign = 0;
        int fMode = 0;            // the mode the voices are in
        uint8_t fStack[16];       // unison: held notes, the last on top
        int fStackCount = 0;
        int fUnisonVel = 100;
        destroy_fn fDestroyVoice;
        dsp* fEffect;
        destroy_fn fDestroyEffect;
        FAUSTFLOAT** fShared;     // [voice * fSharedCount + i]
        int fSharedCount;
        int fBlock;               // largest block size
        int fVoiceOutputs;
        FAUSTFLOAT* fVoiceOut[MAX_CHANNELS];   // one voice's output
        FAUSTFLOAT* fMix[MAX_CHANNELS];        // the sum of the voices (the effect's input)
        uint32_t fClock = 0;
        int fFade;                // fade length in samples (3 ms)
        FAUSTFLOAT fPanic = 0;    // the "Panic" button
        FAUSTFLOAT fPanicBefore = 0;
        midi_interface* fMidiHandler = nullptr;

        // as poly-dsp.h (in double: the same frequency to the last bit)
        static double noteHz(int note) { return 440.0 * pow(2.0, (note - 69.0) / 12.0); }

        void start(Voice& v, int note, int velocity)
        {
            v.fNote = note;
            v.fHeld = true;
            v.fAge = ++fClock;
            v.fQuiet = 0;
            v.fFadeOut = 0;
            if (v.fFreq) *v.fFreq = noteHz(note);
            if (v.fKey) *v.fKey = note;
            if (v.fGain) *v.fGain = velocity / 127.0f;
            if (v.fVel) *v.fVel = velocity;
            if (v.fGate) *v.fGate = 1;
        }

        // a voice fading out to free (stopped: Panic, CC 120, a mode change)
        static bool stopping(const Voice& v) { return v.fFadeOut > 0 && v.fNextNote == FREE; }

        Voice* allocate()
        {
            Voice* free = nullptr;
            Voice* stop = nullptr;
            Voice* releasing = nullptr;
            Voice* playing = nullptr;
            for (int i = 0; i < fLimit; i++) {
                Voice& v = fVoices[i];
                if (v.fNote == FREE && v.fNextNote == FREE) {
                    if (!free || v.fAge < free->fAge) free = &v;  // unused longest
                    continue;
                }
                if (stopping(v)) { if (!stop) stop = &v; continue; }  // free in < 3 ms: next best
                if (v.fFadeOut > 0) continue;  // already being stolen
                if (!v.fHeld) { if (!releasing || v.fAge < releasing->fAge) releasing = &v; }
                else if (!playing || v.fAge < playing->fAge) playing = &v;
            }
            return free ? free : stop ? stop : releasing ? releasing : playing;
        }

        void release(Voice& v)
        {
            v.fHeld = false;
            v.fQuiet = 0;
            if (v.fGate) *v.fGate = 0;
        }

        // gate off and a 3 ms fade out (from its level), then the voice is
        // free, or plays fNextNote if one is set
        void fadeOut(Voice& v)
        {
            if (v.fGate) *v.fGate = 0;
            v.fHeld = false;
            v.fFadeOut = fFade - v.fFadeIn;
            v.fFadeIn = 0;
        }

        // the voices of a channel (-1: all), released or stopped
        void notesOff(int channel, bool hard)
        {
            for (int i = 0; i < fCount; i++) {
                Voice& v = fVoices[i];
                if (channel >= 0 && v.fChannel != channel) continue;
                if (hard) {
                    v.fNextNote = FREE;
                    if (v.fNote != FREE && v.fFadeOut == 0) fadeOut(v);
                } else {
                    v.fNextNote = FREE;   // a stolen voice's new note doesn't start
                    if (v.fHeld) release(v);
                }
            }
        }

        int wantedMode() const
        {
            int m = fModeZone ? int(*fModeZone + FAUSTFLOAT(0.5)) : fAssign;
            return m < ROTATE ? ROTATE : m > UNISON ? UNISON : m;
        }
        // a new mode: every voice stopped first
        void checkMode()
        {
            int m = wantedMode();
            if (m == fMode) return;
            notesOff(-1, true);
            fStackCount = 0;
            fMode = m;
        }

        // REUSE: the lowest voice that is free or only releasing (else the
        // oldest playing one); the other release tails stop, so only the
        // last notes played together keep their release
        Voice* allocateReuse()
        {
            Voice* v = nullptr;
            Voice* playing = nullptr;
            for (int i = 0; i < fLimit && !v; i++) {
                Voice& w = fVoices[i];
                if (w.fNote == FREE && w.fNextNote == FREE) v = &w;
                else if (!w.fHeld && (w.fFadeOut == 0 || stopping(w))) v = &w;
                else if (w.fHeld && w.fFadeOut == 0 && (!playing || w.fAge < playing->fAge)) playing = &w;
            }
            if (!v) v = playing;
            for (int i = 0; i < fCount; i++) {
                Voice& w = fVoices[i];
                if (&w != v && !w.fHeld && w.fNote != FREE && w.fFadeOut == 0) { w.fNextNote = FREE; fadeOut(w); }
            }
            return v;
        }

        // plays a note on a voice: at once if it is free, else after a 3 ms
        // fade out of what it plays
        void play(Voice& v, int channel, int pitch, int velocity)
        {
            if (v.fNote != FREE) {
                v.fNextNote = pitch;
                v.fNextVel = velocity;
                if (v.fFadeOut == 0) fadeOut(v);
                v.fAge = ++fClock;
            } else {
                v.fFadeIn = 0;
                start(v, pitch, velocity);
            }
            v.fChannel = channel;
        }

        // unison: every voice on the stack's top note; held keys glide over
        // (legato: the pitch changes, the envelopes go on), a note played
        // after all keys were up starts them again
        void unisonTo(int channel, int pitch, bool restart)
        {
            for (int i = 0; i < fLimit; i++) {
                Voice& v = fVoices[i];
                if (restart || (!v.fHeld && v.fNextNote == FREE)) {
                    play(v, channel, pitch, fUnisonVel);
                } else if (v.fNextNote != FREE) {
                    v.fNextNote = pitch;   // still fading out: its next note
                } else {
                    v.fNote = pitch;
                    if (v.fFreq) *v.fFreq = noteHz(pitch);
                    if (v.fKey) *v.fKey = pitch;
                }
                v.fChannel = channel;
            }
        }
        void unisonOn(int channel, int pitch, int velocity)
        {
            bool restart = fStackCount == 0;
            int n = 0;
            for (int i = 0; i < fStackCount; i++) if (fStack[i] != pitch) fStack[n++] = fStack[i];
            fStackCount = n < 16 ? n : 15;
            fStack[fStackCount++] = uint8_t(pitch);
            fUnisonVel = velocity;
            unisonTo(channel, pitch, restart);
        }
        void unisonOff(int channel, int pitch)
        {
            bool top = fStackCount > 0 && fStack[fStackCount - 1] == pitch;
            int n = 0;
            for (int i = 0; i < fStackCount; i++) if (fStack[i] != pitch) fStack[n++] = fStack[i];
            fStackCount = n;
            if (fStackCount == 0) {
                for (int i = 0; i < fCount; i++) {
                    Voice& v = fVoices[i];
                    v.fNextNote = FREE;
                    if (v.fHeld) release(v);
                }
            } else if (top) {
                unisonTo(channel, fStack[fStackCount - 1], false);
            }
        }

        void registerMidi(UI* ui)
        {
#if defined(__GXX_RTTI) || defined(_CPPRTTI) || defined(__cpp_rtti)
            if (midi_interface* handler = dynamic_cast<midi_interface*>(ui)) setMidiHandler(handler);
#else
            (void)ui;  // no RTTI: call setMidiHandler()
#endif
        }

        void buildVoicesUI(UI* ui)
        {
            ui->openTabBox("Polyphonic");
            ui->openVerticalBox("Voices");
            ui->addButton("Panic", &fPanic);
            HideNotes hide(ui, &fVoices[0]);
            fVoices[0].fDSP->buildUserInterface(&hide);
            ui->closeBox();
            ui->closeBox();
        }

    public:
        // voices: count instances made by the program's create(), destroyed
        // with destroy_voice; effect (or null): runs once on the voice mix;
        // control false: all voices always run (no allocation by notes)
        mcu_dsp_poly(dsp** voices, int count, destroy_fn destroy_voice, dsp* effect, destroy_fn destroy_effect, int block,
                     bool control = true)
            : fCount(count < MAX_VOICES ? count : MAX_VOICES), fLimit(fCount), fControl(control),
              fDestroyVoice(destroy_voice), fEffect(effect), fDestroyEffect(destroy_effect), fBlock(block)
        {
            for (int i = 0; i < fCount; i++) fVoices[i].fDSP = voices[i];
            // the shared parameters, in UI order (the same in every voice)
            ZoneList counter(nullptr, 0, &fVoices[0]);
            fVoices[0].fDSP->buildUserInterface(&counter);
            fModeZone = counter.fModeZone;
            fSharedCount = counter.fCount < MAX_SHARED ? counter.fCount : MAX_SHARED;
            fShared = new FAUSTFLOAT*[fCount * fSharedCount + 1];
            for (int i = 0; i < fCount; i++) {
                ZoneList list(fShared + i * fSharedCount, fSharedCount, &fVoices[i]);
                fVoices[i].fDSP->buildUserInterface(&list);
            }
            fFade = 144;  // 3 ms at 48 kHz, set again by instanceInit()
            setIndices();
            fVoiceOutputs = fVoices[0].fDSP->getNumOutputs();
            if (fVoiceOutputs > MAX_CHANNELS) fVoiceOutputs = MAX_CHANNELS;
            for (int c = 0; c < fVoiceOutputs; c++) {
                fVoiceOut[c] = new FAUSTFLOAT[fBlock];
                fMix[c] = new FAUSTFLOAT[fBlock];
            }
        }

        virtual ~mcu_dsp_poly()
        {
            if (fMidiHandler) fMidiHandler->removeMidiIn(this);
            for (int i = 0; i < fCount; i++) fDestroyVoice(fVoices[i].fDSP);
            if (fEffect) fDestroyEffect(fEffect);
            delete[] fShared;
            for (int c = 0; c < fVoiceOutputs; c++) {
                delete[] fVoiceOut[c];
                delete[] fMix[c];
            }
        }

        // the MIDI handler sending notes here (registered by buildUserInterface()
        // with a MidiUI where the build has RTTI)
        void setMidiHandler(midi_interface* handler)
        {
            if (fMidiHandler == handler) return;
            if (fMidiHandler) fMidiHandler->removeMidiIn(this);
            fMidiHandler = handler;
            if (fMidiHandler) fMidiHandler->addMidiIn(this);
        }

        // MIDI (channel 0..15, as FAUST's midi layer)

        MapUI* keyOn(int channel, int pitch, int velocity) override
        {
            if (velocity == 0) { keyOff(channel, pitch, 0); return nullptr; }
            checkMode();
            if (fMode == UNISON) { unisonOn(channel, pitch, velocity); return nullptr; }
            Voice* v = nullptr;
            if (fRetrigger) {
                // the note is already held on this channel: its voice starts
                // again, so a repeated note on can't leave a voice hanging
                for (int i = 0; i < fCount && !v; i++)
                    if (fVoices[i].fHeld && fVoices[i].fNote == pitch && fVoices[i].fChannel == channel) v = &fVoices[i];
            }
            if (!v) v = fMode == REUSE ? allocateReuse() : allocate();
            if (!v) return nullptr;
            // still sounding (playing or releasing): fade out with the gate
            // off, then the new note fades in
            play(*v, channel, pitch, velocity);
            return nullptr;  // no MapUI per voice here
        }

        // the oldest voice playing this note on this channel (poly-dsp.h)
        void keyOff(int channel, int pitch, int velocity = 0) override
        {
            (void)velocity;
            checkMode();
            if (fMode == UNISON) { unisonOff(channel, pitch); return; }
            Voice* oldest = nullptr;
            for (int i = 0; i < fCount; i++) {
                Voice& v = fVoices[i];
                if (v.fChannel != channel) continue;
                bool playing = v.fHeld && v.fNote == pitch;
                bool waiting = v.fNextNote == pitch && v.fFadeOut > 0;  // stolen, not started yet
                if ((playing || waiting) && (!oldest || v.fAge < oldest->fAge)) oldest = &v;
            }
            if (!oldest) return;
            if (oldest->fNextNote == pitch && oldest->fFadeOut > 0) oldest->fNextNote = FREE;  // the fade out goes on, then free
            else release(*oldest);
        }

        void ctrlChange(int channel, int ctrl, int value) override
        {
            (void)value;
            if (ctrl == ALL_NOTES_OFF) notesOff(channel, false);
            else if (ctrl == ALL_SOUND_OFF) notesOff(channel, true);
        }

        enum { ROTATE = 0, REUSE = 1, UNISON = 2 };
        // the assign mode when the program has no [poly:mode] parameter
        void setAssignMode(int mode) { fAssign = mode; }
        int assignMode() const { return fMode; }

        // true (default): a note on for a note held on that channel restarts
        // its voice; false: it takes another voice, as poly-dsp.h (then
        // every note on needs its own note off)
        void setRetrigger(bool retrigger) { fRetrigger = retrigger; }

        // all voices released, or stopped (hard: a 3 ms fade)
        void allNotesOff(bool hard = false) { notesOff(-1, hard); fStackCount = 0; }

        int getNumActiveVoices() const
        {
            int n = 0;
            for (int i = 0; i < fCount; i++) n += (fVoices[i].fNote != FREE || fVoices[i].fNextNote != FREE);
            return n;
        }

        int voices() const { return fCount; }
        // only the first n voices take notes (e.g. fewer at a higher sample
        // rate); the others finish their notes
        void setVoiceLimit(int n) { fLimit = n < 1 ? 1 : n > fCount ? fCount : n; }
        int voiceLimit() const { return fLimit; }
        // the note of a voice, -1 free, -2 releasing
        int voiceNote(int i) const
        {
            const Voice& v = fVoices[i];
            return v.fNote == FREE ? -1 : v.fHeld ? v.fNote : -2;
        }

        // dsp

        int getNumInputs() override { return fVoices[0].fDSP->getNumInputs(); }
        int getNumOutputs() override { return fEffect ? fEffect->getNumOutputs() : fVoiceOutputs; }
        void buildUserInterface(UI* ui) override
        {
            registerMidi(ui);
            if (fEffect) {
                // as dsp_sequencer(poly, effect)
                ui->openTabBox("Sequencer");
                ui->openVerticalBox("DSP1");
                buildVoicesUI(ui);
                ui->closeBox();
                ui->openVerticalBox("DSP2");
                fEffect->buildUserInterface(ui);
                ui->closeBox();
                ui->closeBox();
            } else {
                buildVoicesUI(ui);
            }
        }
        int getSampleRate() override { return fVoices[0].fDSP->getSampleRate(); }
        // as dsp::init(): the static tables too (classInit, through the first
        // voice's and the effect's init()), then every instance
        void init(int sample_rate) override
        {
            if (fCount > 0) fVoices[0].fDSP->init(sample_rate);
            if (fEffect) fEffect->init(sample_rate);
            instanceInit(sample_rate);
        }
        // the voices' numbers (instanceInit and instanceResetUserInterface set the defaults)
        void setIndices()
        {
            for (int i = 0; i < fCount; i++)
                if (fVoices[i].fIndex) *fVoices[i].fIndex = i;
        }

        void instanceInit(int sample_rate) override
        {
            fFade = sample_rate * 3 / 1000 > 0 ? sample_rate * 3 / 1000 : 1;
            for (int i = 0; i < fCount; i++) fVoices[i].fDSP->instanceInit(sample_rate);
            if (fEffect) fEffect->instanceInit(sample_rate);
            fPanic = fPanicBefore = 0;
            resetVoices();
            setIndices();
        }
        void instanceConstants(int sample_rate) override
        {
            fFade = sample_rate * 3 / 1000 > 0 ? sample_rate * 3 / 1000 : 1;
            for (int i = 0; i < fCount; i++) fVoices[i].fDSP->instanceConstants(sample_rate);
            if (fEffect) fEffect->instanceConstants(sample_rate);
        }
        void instanceResetUserInterface() override
        {
            for (int i = 0; i < fCount; i++) fVoices[i].fDSP->instanceResetUserInterface();
            if (fEffect) fEffect->instanceResetUserInterface();
            fPanic = fPanicBefore = 0;
            setIndices();
        }
        void instanceClear() override
        {
            for (int i = 0; i < fCount; i++) fVoices[i].fDSP->instanceClear();
            if (fEffect) fEffect->instanceClear();
            resetVoices();
        }
        // every voice free, its gate off (poly-dsp.h: in instanceClear)
        void resetVoices()
        {
            for (int i = 0; i < fCount; i++) {
                Voice& v = fVoices[i];
                v.fNote = v.fNextNote = FREE;
                v.fHeld = false;
                v.fFadeOut = v.fFadeIn = v.fQuiet = 0;
                v.fChannel = 0;
                v.fAge = 0;
                if (v.fGate) *v.fGate = 0;
            }
            fClock = 0;
        }
        dsp* clone() override { return nullptr; }
        void metadata(Meta* m) override { fVoices[0].fDSP->metadata(m); }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) override
        {
            if (count > fBlock) count = fBlock;
            // the "Panic" button: every voice stopped
            checkMode();
            if (fPanic != fPanicBefore) {
                if (fPanic > FAUSTFLOAT(0.5)) allNotesOff(true);
                fPanicBefore = fPanic;
            }
            // the first voice's parameters (set by the UI) to the others
            for (int i = 1; i < fCount; i++) {
                FAUSTFLOAT** to = fShared + i * fSharedCount;
                for (int k = 0; k < fSharedCount; k++) *to[k] = *fShared[k];
            }
            FAUSTFLOAT** mix = fEffect ? fMix : outputs;
            for (int c = 0; c < fVoiceOutputs; c++) memset(mix[c], 0, count * sizeof(FAUSTFLOAT));
            for (int i = 0; i < fCount; i++) {
                Voice& v = fVoices[i];
                if (fControl && v.fNote == FREE && v.fNextNote == FREE) continue;  // silent: skipped
                v.fDSP->compute(count, inputs, fVoiceOut);
                // fades: out before a stolen voice's new note, in after it
                bool fading = v.fFadeOut > 0 || v.fFadeIn > 0;
                int fadeOut = v.fFadeOut, fadeIn = v.fFadeIn;
                float peak = 0.0f;
                for (int c = 0; c < fVoiceOutputs; c++) {
                    const FAUSTFLOAT* in = fVoiceOut[c];
                    FAUSTFLOAT* out = mix[c];
                    if (fading) {
                        int fo = fadeOut, fi = fadeIn;
                        const float step = 1.0f / fFade;
                        for (int s = 0; s < count; s++) {
                            float g = 1.0f;
                            if (fadeOut > 0) { g = fo > 0 ? fo * step : 0.0f; if (fo > 0) fo--; }
                            else if (fi > 0) { g = 1.0f - fi * step; fi--; }
                            float x = in[s] * g;
                            out[s] += x;
                            float a = fabsf(x);
                            if (a > peak) peak = a;
                        }
                        if (c == fVoiceOutputs - 1) { v.fFadeOut = fo; v.fFadeIn = fi; }
                    } else {
                        for (int s = 0; s < count; s++) {
                            out[s] += in[s];
                            float a = fabsf(in[s]);
                            if (a > peak) peak = a;
                        }
                    }
                }
                if (fadeOut > 0 && v.fFadeOut == 0) {
                    // faded out (the rest of the block was silent)
                    if (v.fNextNote != FREE) {
                        int note = v.fNextNote;
                        v.fNextNote = FREE;
                        start(v, note, v.fNextVel);
                        v.fFadeIn = fFade;
                    } else {
                        v.fNote = FREE;  // stopped, or its new note was released before it started
                    }
                } else if (v.fFadeOut > 0) {
                    // still fading out
                } else if (!v.fHeld && v.fNote != FREE) {
                    v.fQuiet = peak < kStopLevel ? v.fQuiet + count : 0;
                    if (v.fQuiet >= getSampleRate() / 100) v.fNote = FREE;  // 10 ms quiet
                }
            }
            if (fEffect) fEffect->compute(count, fMix, outputs);
        }
};

#endif
/************************** END mcu-poly-dsp.h **************************/
