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

#include <string>
#include <cassert>
#include <map>
#include <list>
#include <vector>

#include "faust/dsp/dsp.h"
#include "export.hh"
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
        unsigned refs() const         { return refCount; }
        //! addReference increments the ref count and checks for refCount overflow
        void addReference()           { refCount++; faustassert(refCount != 0); }
        //! removeReference delete the object when refCount is zero
        void removeReference()		  { if (--refCount == 0) delete this; }
        
    protected:
        faust_smartable() : refCount(0) {}
        faust_smartable(const faust_smartable&): refCount(0) {}
        //! destructor checks for non-zero refCount
        virtual ~faust_smartable()    { faustassert(refCount == 0); }
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
template<class T> class faust_smartptr {
    
    private:
        
        //! the actual pointer to the class
        T* fSmartPtr;
        
    public:
        
        //! an empty constructor - points to null
        faust_smartptr()	: fSmartPtr(0) {}
        //! build a smart pointer from a class pointer
        faust_smartptr(T* rawptr) : fSmartPtr(rawptr)              { if (fSmartPtr) fSmartPtr->addReference(); }
        //! build a smart pointer from an convertible class reference
        template<class T2>
        faust_smartptr(const faust_smartptr<T2>& ptr) : fSmartPtr((T*)ptr) { if (fSmartPtr) fSmartPtr->addReference(); }
        //! build a smart pointer from another smart pointer reference
        faust_smartptr(const faust_smartptr& ptr) : fSmartPtr((T*)ptr)     { if (fSmartPtr) fSmartPtr->addReference(); }
        
        //! the smart pointer destructor: simply removes one reference count
        ~faust_smartptr()  { if (fSmartPtr) fSmartPtr->removeReference(); }
        
        //! cast operator to retrieve the actual class pointer
        operator T*() const  { return fSmartPtr;	}
        
        //! '*' operator to access the actual class pointer
        T& operator*() const {
            // checks for null dereference
            faustassert(fSmartPtr != 0);
            return *fSmartPtr;
        }
        
        //! operator -> overloading to access the actual class pointer
        T* operator->() const	{
            // checks for null dereference
            faustassert(fSmartPtr != 0);
            return fSmartPtr;
        }
        
        //! operator = that moves the actual class pointer
        template <class T2>
        faust_smartptr& operator=(T2 p1_)	{ *this=(T*)p1_; return *this; }
        
        //! operator = that moves the actual class pointer
        faust_smartptr& operator=(T* p_)	{
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
        bool operator<(const faust_smartptr<T>& p_)	const			  { return fSmartPtr < ((T *) p_); }
        //! operator = to support inherited class reference
        faust_smartptr& operator=(const faust_smartptr<T>& p_)                { return operator=((T *) p_); }
        //! dynamic cast support
        template<class T2> faust_smartptr& cast(T2* p_)               { return operator=(dynamic_cast<T*>(p_)); }
        //! dynamic cast support
        template<class T2> faust_smartptr& cast(const faust_smartptr<T2>& p_) { return operator=(dynamic_cast<T*>(p_)); }
};

//----------------------------------------------------------------
// Smart DSP factory table
//----------------------------------------------------------------

template <class T>
struct dsp_factory_table : public std::map<T, std::list<dsp*> >
{
    typedef typename std::map<T, std::list<dsp*> >::iterator factory_iterator;
    
    dsp_factory_table()
    {}
    virtual ~dsp_factory_table()
    {}
    
    bool getFactory(const std::string& sha_key, factory_iterator& res)
    {
        factory_iterator it;
        
        for (it = this->begin(); it != this->end(); it++) {
            if ((*it).first->getSHAKey() == sha_key) {
                res = it;
                return true;
            }
        }
        
        return false;
    }
    
    void setFactory(T factory)
    {
        this->insert(std::pair<T, std::list<dsp*> >(factory, std::list<dsp*>()));
    }
    
    bool addDSP(T factory, dsp* dsp)
    {
        // Remove 'dsp' from its factory
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
        factory_iterator it;
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
            if (factory->refs() == 2) { // Function argument + the one in table...
                // Possibly delete remaining DSP
                std::list<dsp*>::iterator it;
                for (it = dsp_list.begin(); it != dsp_list.end(); it++) { delete (*it); }
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
            while (((*it).first)->refs() > 1) { ((*it).first)->removeReference(); }
        }
        // Then clear the table thus finally deleting all ref = 1 smart pointers
        this->clear();
    }
    
};

// Code by: B-Con (http://b-con.us)
// Released under the GNU GPL
// MD5 Hash Digest implementation (little endian byte order)

// Signed variables are for wimps
#define uchar unsigned char
#define uint unsigned int

// DBL_INT_ADD treats two unsigned ints a and b as one 64-bit integer and adds c to it
#define ROTLEFT(a,b) ((a << b) | (a >> (32-b)))
#define DBL_INT_ADD(a,b,c) if (a > 0xffffffff - c) ++b; a += c;

typedef struct {
    uchar data[64];
    uint datalen;
    uint bitlen[2];
    uint state[5];
    uint k[4];
} SHA1_CTX;

static void sha1_transform(SHA1_CTX* ctx, uchar data[])
{
    uint a,b,c,d,e,i,j,t,m[80];
    
    for (i = 0,j = 0; i < 16; ++i, j += 4) {
        m[i] = (data[j] << 24) + (data[j+1] << 16) + (data[j+2] << 8) + (data[j+3]);
    }
    for ( ; i < 80; ++i) {
        m[i] = (m[i-3] ^ m[i-8] ^ m[i-14] ^ m[i-16]);
        m[i] = (m[i] << 1) | (m[i] >> 31);
    }
    
    a = ctx->state[0];
    b = ctx->state[1];
    c = ctx->state[2];
    d = ctx->state[3];
    e = ctx->state[4];
    
    for (i=0; i < 20; ++i) {
        t = ROTLEFT(a,5) + ((b & c) ^ (~b & d)) + e + ctx->k[0] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 40; ++i) {
        t = ROTLEFT(a,5) + (b ^ c ^ d) + e + ctx->k[1] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 60; ++i) {
        t = ROTLEFT(a,5) + ((b & c) ^ (b & d) ^ (c & d))  + e + ctx->k[2] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    for ( ; i < 80; ++i) {
        t = ROTLEFT(a,5) + (b ^ c ^ d) + e + ctx->k[3] + m[i];
        e = d;
        d = c;
        c = ROTLEFT(b,30);
        b = a;
        a = t;
    }
    
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
}

static void sha1_init(SHA1_CTX* ctx)
{
    ctx->datalen = 0;
    ctx->bitlen[0] = 0;
    ctx->bitlen[1] = 0;
    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
    ctx->k[0] = 0x5a827999;
    ctx->k[1] = 0x6ed9eba1;
    ctx->k[2] = 0x8f1bbcdc;
    ctx->k[3] = 0xca62c1d6;
}

static void sha1_update(SHA1_CTX* ctx, uchar data[], uint len)
{
    uint i;
    
    for (i = 0; i < len; ++i) {
        ctx->data[ctx->datalen] = data[i];
        ctx->datalen++;
        if (ctx->datalen == 64) {
            sha1_transform(ctx, ctx->data);
            DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 512);
            ctx->datalen = 0;
        }
    }
}

static void sha1_final(SHA1_CTX *ctx, uchar hash[])
{
    uint i;
    
    i = ctx->datalen;
    
    // Pad whatever data is left in the buffer.
    if (ctx->datalen < 56) {
        ctx->data[i++] = 0x80;
        while (i < 56) {
            ctx->data[i++] = 0x00;
        }
    } else {
        ctx->data[i++] = 0x80;
        while (i < 64) {
            ctx->data[i++] = 0x00;
        }
        sha1_transform(ctx, ctx->data);
        memset(ctx->data,0,56);
    }
    
    // Append to the padding the total message's length in bits and transform.
    DBL_INT_ADD(ctx->bitlen[0], ctx->bitlen[1], 8 * ctx->datalen);
    ctx->data[63] = ctx->bitlen[0];
    ctx->data[62] = ctx->bitlen[0] >> 8;
    ctx->data[61] = ctx->bitlen[0] >> 16;
    ctx->data[60] = ctx->bitlen[0] >> 24;
    ctx->data[59] = ctx->bitlen[1];
    ctx->data[58] = ctx->bitlen[1] >> 8;
    ctx->data[57] = ctx->bitlen[1] >> 16;
    ctx->data[56] = ctx->bitlen[1] >> 24;
    sha1_transform(ctx,ctx->data);
    
    // Since this implementation uses little endian byte ordering and MD uses big endian,
    // reverse all the bytes when copying the final state to the output hash.
    for (i = 0; i < 4; ++i) {
        hash[i]    = (ctx->state[0] >> (24-i*8)) & 0x000000ff;
        hash[i+4]  = (ctx->state[1] >> (24-i*8)) & 0x000000ff;
        hash[i+8]  = (ctx->state[2] >> (24-i*8)) & 0x000000ff;
        hash[i+12] = (ctx->state[3] >> (24-i*8)) & 0x000000ff;
        hash[i+16] = (ctx->state[4] >> (24-i*8)) & 0x000000ff;
    }
}

static std::string generateSHA1(const std::string& dsp_content)
{
    SHA1_CTX ctx;
    unsigned char obuf[20] = {0};
    
    // Hash one
    sha1_init(&ctx);
    sha1_update(&ctx, (unsigned char*)dsp_content.c_str(), int(dsp_content.size()));
    sha1_final(&ctx, obuf);
    
    // convert SHA1 key into hexadecimal string
    std::string sha1key;
    for (int i = 0; i < 20; i++) {
        const char* H = "0123456789ABCDEF";
        char c1 = H[(obuf[i] >> 4)];
        char c2 = H[(obuf[i] & 15)];
        sha1key += c1;
        sha1key += c2;
    }
    
    return sha1key;
}

#endif
