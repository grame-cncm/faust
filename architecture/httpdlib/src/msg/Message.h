/*

  Copyright (C) 2011  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __Message__
#define __Message__

#include <string>
#include <vector>
#include <iostream>
#include "smartpointer.h"

namespace httpdfaust
{

template <typename T> class MsgParam;
class baseparam;
typedef SMARTP<baseparam>	Sbaseparam;

//--------------------------------------------------------------------------
/*!
	\brief base class of a message parameters
*/
class baseparam : public smartable
{
	public:
		virtual ~baseparam() {}

		/*!
		 \brief utility for parameter type checking
		*/
		template<typename X> bool isType() const { return dynamic_cast<const MsgParam<X>*> (this) != 0; }
		/*!
		 \brief utility for parameter convertion
		 \param errvalue the returned value when no conversion applies
		 \return the parameter value when the type matches
		*/
		template<typename X> X	value(X errvalue) const 
			{ const MsgParam<X>* o = dynamic_cast<const MsgParam<X>*> (this); return o ? o->getValue() : errvalue; }
		/*!
		 \brief utility for parameter comparison
		*/
		template<typename X> bool	equal(const baseparam& p) const 
			{ 
				const MsgParam<X>* a = dynamic_cast<const MsgParam<X>*> (this); 
				const MsgParam<X>* b = dynamic_cast<const MsgParam<X>*> (&p);
				return a && b && (a->getValue() == b->getValue());
			}
		/*!
		 \brief utility for parameter comparison
		*/
		bool operator==(const baseparam& p) const 
			{ 
				return equal<float>(p) || equal<int>(p) || equal<std::string>(p);
			}
		bool operator!=(const baseparam& p) const
			{ 
				return !equal<float>(p) && !equal<int>(p) && !equal<std::string>(p);
			}
			
		virtual SMARTP<baseparam> copy() const = 0;
};

//--------------------------------------------------------------------------
/*!
	\brief template for a message parameter
*/
template <typename T> class MsgParam : public baseparam
{
	T fParam;
	public:
				 MsgParam(T val) : fParam(val)	{}
		virtual ~MsgParam() {}
		
		T	getValue() const { return fParam; }
		
		virtual SMARTP<baseparam> copy() const { return new MsgParam<T>(fParam); }
};

//--------------------------------------------------------------------------
/*!
	\brief a message description
	
	A message is composed of an address (actually the path of an url)
	a message string that may be viewed as a method name
	and a list of message parameters.
*/
class Message
{
	public:
		typedef SMARTP<baseparam>		argPtr;		///< a message argument ptr type
		typedef std::vector<argPtr>		argslist;	///< args list type

	private:
		std::string	fAddress;			///< the message destination address
		std::string	fMIME;				///< the message MIME type
		argslist	fArguments;			///< the message arguments
	
	public:
			/*!
				\brief an empty message constructor
			*/
			 Message() : fMIME("text/plain") {}
			/*!
				\brief a message constructor
				\param address the message destination address
			*/
			 Message(const std::string& address) : fAddress(address), fMIME("text/plain") {}

	virtual ~Message() {}

	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	template <typename T> void add(T val)	{ fArguments.push_back(new MsgParam<T>(val)); }
	
	/*!
		\brief adds a parameter to the message
		\param val the parameter
	*/
	void	add( argPtr val )				{ fArguments.push_back( val ); }

	/*!
		\brief sets the message address
		\param addr the address
	*/
	void				setAddress(const std::string& addr)		{ fAddress = addr; }

	/*!
		\brief sets the message MIME type
		\param mime the MIME type
	*/
	void				setMIMEType(const std::string& mime)	{ fMIME = mime; }
	/*!
		\brief print the message
		\param out the output stream
	*/
	void				print(std::ostream& out) const;

	/// \brief gives the message address
	const std::string&	address() const		{ return fAddress; }
	/// \brief gives the message address
	const std::string&	mimetype() const	{ return fMIME; }
	/// \brief gives the message parameters list
	const argslist&		params() const		{ return fArguments; }
	/// \brief gives the message parameters list
	argslist&			params()			{ return fArguments; }
	/// \brief gives the message parameters count
	int					size() const		{ return (int)fArguments.size(); }
	
	bool operator == (const Message& other) const;	


	/*!
		\brief gives a message parameter
		\param i the parameter index (0 <= i < size())
		\param val on output: the parameter value when the parameter type matches
		\return false when types don't match
	*/
	template <typename T> bool	param(int i, T& val) const	{ val = params()[i]->value<T>(val); return params()[i]->isType<T>(); }
};


} // end namespoace

#endif
