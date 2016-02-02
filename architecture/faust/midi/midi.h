/************************************************************************
    FAUST Architecture File
    Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
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

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>

//----------------------------------------------------------------
//  MIDI processor definition
//----------------------------------------------------------------

class midi {
 
    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual void keyOn(double date, int channel, int pitch, int velocity)          {}
        virtual void keyOff(double date, int channel, int pitch, int velocity)         {}
        virtual void keyPress(double date, int channel, int pitch, int press)          {}
        virtual void chanPress(double date, int channel, int press)                    {}
        virtual void ctrlChange(double date, int channel, int ctrl, int value)         {}
        virtual void ctrlChange14bits(double date, int channel, int ctrl, int value)   {}
        virtual void pitchWheel(double date, int channel, int wheel)                   {}
        virtual void progChange(double date, int channel, int pgm)                     {}
        
        // MIDI sync
        virtual void start(double date)  {}
        virtual void stop(double date)   {}
        virtual void clock(double date)  {}
        
        // Standard MIDI API
        virtual void keyOn(int channel, int pitch, int velocity)        {}
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
       
};

//----------------------------------------------------------------
//  Base class for MIDI API handling
//----------------------------------------------------------------

class midi_handler : public midi {

    protected:
    
        enum MidiStatus {
	
            // channel voice messages
            MIDI_NOTE_OFF           = 0x80, 
            MIDI_NOTE_ON            = 0x90, 
            MIDI_CONTROL_CHANGE     = 0xB0,
            MIDI_PROGRAM_CHANGE     = 0xC0,
            MIDI_PITCH_BEND         = 0xE0,
            MIDI_AFTERTOUCH         = 0xD0,	// aka channel pressure
            MIDI_POLY_AFTERTOUCH    = 0xA0,	// aka key pressure
            MIDI_CLOCK              = 0xF8,
            MIDI_START              = 0xFA,
            MIDI_STOP               = 0xFC

        };
 
        std::vector<midi*> fMidiInputs;
        std::string fName;

    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}
        
        virtual void addMidiIn(midi* midi_dsp) { fMidiInputs.push_back(midi_dsp); }
        
        virtual bool start() {}
        virtual void stop() {}

};

/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#include <stdlib.h>
#include <string.h>

typedef struct {
    char *buf;
    size_t len;
}
midi_ringbuffer_data_t ;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
midi_ringbuffer_t ;

midi_ringbuffer_t *midi_ringbuffer_create(size_t sz);
void midi_ringbuffer_free(midi_ringbuffer_t *rb);
void midi_ringbuffer_get_read_vector(const midi_ringbuffer_t *rb,
                                         midi_ringbuffer_data_t *vec);
void midi_ringbuffer_get_write_vector(const midi_ringbuffer_t *rb,
                                          midi_ringbuffer_data_t *vec);
size_t midi_ringbuffer_read(midi_ringbuffer_t *rb, char *dest, size_t cnt);
size_t midi_ringbuffer_peek(midi_ringbuffer_t *rb, char *dest, size_t cnt);
void midi_ringbuffer_read_advance(midi_ringbuffer_t *rb, size_t cnt);
size_t midi_ringbuffer_read_space(const midi_ringbuffer_t *rb);
int midi_ringbuffer_mlock(midi_ringbuffer_t *rb);
void midi_ringbuffer_reset(midi_ringbuffer_t *rb);
void midi_ringbuffer_reset_size (midi_ringbuffer_t * rb, size_t sz);
size_t midi_ringbuffer_write(midi_ringbuffer_t *rb, const char *src,
                                 size_t cnt);
void midi_ringbuffer_write_advance(midi_ringbuffer_t *rb, size_t cnt);
size_t midi_ringbuffer_write_space(const midi_ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two.  */

midi_ringbuffer_t *
midi_ringbuffer_create (size_t sz)
{
	int power_of_two;
	midi_ringbuffer_t *rb;

	if ((rb = (midi_ringbuffer_t *) malloc (sizeof (midi_ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1; 1 << power_of_two < sz; power_of_two++);

	rb->size = 1 << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

void
midi_ringbuffer_free (midi_ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

int
midi_ringbuffer_mlock (midi_ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

void
midi_ringbuffer_reset (midi_ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

void
midi_ringbuffer_reset_size (midi_ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading.  This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

size_t
midi_ringbuffer_read_space (const midi_ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing.  This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

size_t
midi_ringbuffer_write_space (const midi_ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader.  Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

size_t
midi_ringbuffer_read (midi_ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = midi_ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance.  Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

size_t
midi_ringbuffer_peek (midi_ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = midi_ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer.  Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

size_t
midi_ringbuffer_write (midi_ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = midi_ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

void
midi_ringbuffer_read_advance (midi_ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

void
midi_ringbuffer_write_advance (midi_ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader.  `vec' is an array of two places.  Set
   the values at `vec' to hold the current readable data at `rb'.  If
   the readable data is in one segment the second segment has zero
   length.  */

void
midi_ringbuffer_get_read_vector (const midi_ringbuffer_t * rb,
				 midi_ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer.  `vec' is an array of two places.  Set
   the values at `vec' to hold the current writeable data at `rb'.  If
   the writeable data is in one segment the second segment has zero
   length.  */

void
midi_ringbuffer_get_write_vector (const midi_ringbuffer_t * rb,
				  midi_ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __midi__
