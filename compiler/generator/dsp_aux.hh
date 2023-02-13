/************************************************************************
 ************************************************************************
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale

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

 ************************************************************************
 ************************************************************************/

#ifndef DSP_AUX_H
#define DSP_AUX_H

#include <string.h>
#include <cassert>
#include <list>
#include <map>
#include <string>
#include <vector>

#ifdef WIN32
#pragma warning(disable : 4800)
#endif

#include "faust/export.h"
#include "faust/dsp/dsp.h"

#include "exception.hh"

/*!
    \brief the base class for smart pointers implementation

    Any object that want to support smart pointers should
    inherit from the smartable class which provides reference counting
    and automatic delete when the reference count drops to zero.
 */
class faust_smartable {
   private:
    unsigned refCount;

   public:
    //! gives the reference count of the object
    unsigned refs() const { return refCount; }
    //! addReference increments the ref count and checks for refCount overflow
    void addReference()
    {
        refCount++;
        faustassert(refCount != 0);
    }
    //! removeReference delete the object when refCount is zero
    void removeReference()
    {
        if (--refCount == 0) delete this;
    }

   protected:
    faust_smartable() : refCount(0) {}
    faust_smartable(const faust_smartable&) : refCount(0) {}
    //! destructor checks for non-zero refCount
    virtual ~faust_smartable() { faustassert(refCount == 0); }
    faust_smartable& operator=(const faust_smartable&) { return *this; }
};

/*!
    \brief the smart pointer implementation

    A smart pointer is in charge of maintaining the objects reference count
    by the way of pointers operators overloading. It supports class
    inheritance and conversion whenever possible.
    \n Instances of the SMARTP class are supposed to use \e smartable types (or at least
    objects that implements the \e addReference and \e removeReference
    methods in a consistent way).
 */
template <class T>
class faust_smartptr {
   private:
    //! the actual pointer to the class
    T* fSmartPtr;

   public:
    //! an empty constructor - points to null
    faust_smartptr() : fSmartPtr(0) {}
    //! build a smart pointer from a class pointer
    faust_smartptr(T* rawptr) : fSmartPtr(rawptr)
    {
        if (fSmartPtr) fSmartPtr->addReference();
    }
    //! build a smart pointer from an convertible class reference
    template <class T2>
    faust_smartptr(const faust_smartptr<T2>& ptr) : fSmartPtr((T*)ptr)
    {
        if (fSmartPtr) fSmartPtr->addReference();
    }
    //! build a smart pointer from another smart pointer reference
    faust_smartptr(const faust_smartptr& ptr) : fSmartPtr((T*)ptr)
    {
        if (fSmartPtr) fSmartPtr->addReference();
    }

    //! the smart pointer destructor: simply removes one reference count
    ~faust_smartptr()
    {
        if (fSmartPtr) fSmartPtr->removeReference();
    }

    //! cast operator to retrieve the actual class pointer
    operator T*() const { return fSmartPtr; }

    //! '*' operator to access the actual class pointer
    T& operator*() const
    {
        // checks for null dereference
        faustassert(fSmartPtr != 0);
        return *fSmartPtr;
    }

    //! operator -> overloading to access the actual class pointer
    T* operator->() const
    {
        // checks for null dereference
        faustassert(fSmartPtr != 0);
        return fSmartPtr;
    }

    //! operator = that moves the actual class pointer
    template <class T2>
    faust_smartptr& operator=(T2 p1_)
    {
        *this = (T*)p1_;
        return *this;
    }

    //! operator = that moves the actual class pointer
    faust_smartptr& operator=(T* p_)
    {
        // check first that pointers differ
        if (fSmartPtr != p_) {
            // increments the ref count of the new pointer if not null
            if (p_ != 0) p_->addReference();
            // decrements the ref count of the old pointer if not null
            if (fSmartPtr != 0) fSmartPtr->removeReference();
            // and finally stores the new actual pointer
            fSmartPtr = p_;
        }
        return *this;
    }
    //! operator < to support faust_smartptr map with Visual C++
    bool operator<(const faust_smartptr<T>& p_) const { return fSmartPtr < ((T*)p_); }
    //! operator = to support inherited class reference
    faust_smartptr& operator=(const faust_smartptr<T>& p_) { return operator=((T*)p_); }
    //! dynamic cast support
    template <class T2>
    faust_smartptr& cast(T2* p_)
    {
        return operator=(dynamic_cast<T*>(p_));
    }
    //! dynamic cast support
    template <class T2>
    faust_smartptr& cast(const faust_smartptr<T2>& p_)
    {
        return operator=(dynamic_cast<T*>(p_));
    }
};

//----------------------------------------------------------------
// Smart DSP factory table
//----------------------------------------------------------------

template <class T>
struct dsp_factory_table : public std::map<T, std::list<dsp*> > {
    typedef typename std::map<T, std::list<dsp*> >::iterator factory_iterator;

    dsp_factory_table() {}
    virtual ~dsp_factory_table() {}

    bool getFactory(const std::string& sha_key, factory_iterator& res)
    {
        for (factory_iterator it = this->begin(); it != this->end(); it++) {
            if ((*it).first->getSHAKey() == sha_key) {
                res = it;
                return true;
            }
        }

        return false;
    }

    void setFactory(T factory) { this->insert(std::pair<T, std::list<dsp*> >(factory, std::list<dsp*>())); }

    bool addDSP(T factory, dsp* dsp)
    {
        // Add 'dsp' in its factory
        factory_iterator it = this->find(factory);

        if (it != this->end()) {
            (*it).second.push_back(dsp);
            return true;
        } else {
            std::cerr << "WARNING : addDSP factory not found!" << std::endl;
            return false;
        }
    }

    bool removeDSP(T factory, dsp* dsp)
    {
        // Remove 'dsp' from its factory
        factory_iterator it = this->find(factory);
        faustassert(it != this->end());

        if (it != this->end()) {
            (*it).second.remove(dsp);
            return true;
        } else {
            std::cerr << "WARNING : removeDSP factory not found!" << std::endl;
            return false;
        }
    }

    std::vector<std::string> getAllDSPFactories()
    {
        factory_iterator         it;
        std::vector<std::string> sha_key_list;

        for (it = this->begin(); it != this->end(); it++) {
            sha_key_list.push_back((*it).first->getSHAKey());
        }

        return sha_key_list;
    }

    dsp_factory* getDSPFactoryFromSHAKey(const std::string& sha_key)
    {
        factory_iterator it;

        if (getFactory(sha_key, it)) {
            T sfactory = (*it).first;
            sfactory->addReference();
            return sfactory;
        } else {
            std::cerr << "WARNING : getDSPFactoryFromSHAKey factory not found!" << std::endl;
            return 0;
        }
    }

    bool deleteDSPFactory(T factory)
    {
        factory_iterator it;

        if ((it = this->find(factory)) != this->end()) {
            std::list<dsp*> dsp_list = (*it).second;
            if (factory->refs() == 2) {  // Function argument + the one in table...
                // Possibly delete remaining DSP
                for (const auto& it1 : dsp_list) {
                    delete it1;
                }
                // Last use, remove from the global table, pointer will be deleted
                this->erase(factory);
                return true;
            } else {
                factory->removeReference();
                return false;
            }
        } else {
            std::cerr << "WARNING : deleteDSPFactory factory not found!" << std::endl;
            return false;
        }
    }

    void deleteAllDSPFactories()
    {
        factory_iterator it;

        for (it = this->begin(); it != this->end(); it++) {
            // Decrement counter up to one...
            while (((*it).first)->refs() > 1) {
                ((*it).first)->removeReference();
            }
        }
        // Then clear the table thus finally deleting all ref = 1 smart pointers
        this->clear();
    }
};

// Compute SHA1 key from name_app, dsp_content and compilations arguments, and returns the dsp_content
std::string sha1FromDSP(const std::string& name_app, const std::string& dsp_content, int argc, const char* argv[], std::string& sha_key);

class CTree;
typedef CTree* Tree;
typedef std::vector<Tree> tvec;

tvec boxesToSignalsAux(Tree box);

#ifdef __cplusplus
extern "C" {
#endif

LIBFAUST_API const char* expandCDSPFromFile(const char* filename, int argc, const char* argv[], char* sha_key,
                                      char* error_msg);

LIBFAUST_API const char* expandCDSPFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[],
                                        char* sha_key, char* error_msg);

LIBFAUST_API bool generateCAuxFilesFromFile(const char* filename, int argc, const char* argv[], char* error_msg);

LIBFAUST_API bool generateCAuxFilesFromString(const char* name_app, const char* dsp_content, int argc, const char* argv[],
                                        char* error_msg);

#ifdef __cplusplus
}
#endif

#define BUFFER_SIZE 1024
#define SAMPLE_RATE 44100
#define MAX_CHAN 64
#define MAX_SOUNDFILE_PARTS 256

#ifdef _MSC_VER
#define PRE_PACKED_STRUCTURE __pragma(pack(push, 1))
#define POST_PACKED_STRUCTURE \
;                         \
__pragma(pack(pop))
#else
#define PRE_PACKED_STRUCTURE
#define POST_PACKED_STRUCTURE __attribute__((__packed__))
#endif

PRE_PACKED_STRUCTURE
struct Soundfile {
    enum { kBuffers, kLength, kSR, kOffset };
    double** fBuffers; // use the largest size to cover 'float' and 'double' cases
    int* fLength;      // length of each part
    int* fSR;          // sample rate of each part
    int* fOffset;      // offset of each part in the global buffer
    int fChannels;     // max number of channels of all concatenated files
    int fParts;        // the total number of loaded parts
    bool fIsDouble;    // keep the sample format (float or double)
    
    Soundfile(int max_chan)
    {
        fBuffers = new double*[max_chan];
        fLength  = new int[MAX_SOUNDFILE_PARTS];
        fSR      = new int[MAX_SOUNDFILE_PARTS];
        fOffset  = new int[MAX_SOUNDFILE_PARTS];
        
        for (int part = 0; part < MAX_SOUNDFILE_PARTS; part++) {
            fLength[part] = BUFFER_SIZE;
            fSR[part]     = SAMPLE_RATE;
            fOffset[part] = 0;
        }
        
        // Allocate 1 channel
        fChannels = 1;
        fParts = 0;
        fBuffers[0] = new double[BUFFER_SIZE];
        faustassert(fBuffers[0]);
        fIsDouble = true;
        memset(fBuffers[0], 0, BUFFER_SIZE * sizeof(double));
        
        // Share the same buffer for all other channels so that we have max_chan channels available
        for (int chan = fChannels; chan < max_chan; chan++) {
            fBuffers[chan] = fBuffers[0];
        }
    }
    
    ~Soundfile()
    {
        // Free the real channels only
        for (int chan = 0; chan < fChannels; chan++) {
            delete[] fBuffers[chan];
        }
        delete[] fBuffers;
        delete[] fLength;
        delete[] fSR;
        delete[] fOffset;
    }
    
} POST_PACKED_STRUCTURE;

typedef std::map<std::string, Soundfile*> soundTable;

#endif
