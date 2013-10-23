/* 
	Copyright 2013 Mona - mathieu.poux[a]gmail.com
 
	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License received along this program for more
	details (or else see http://www.gnu.org/licenses/).

	This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/DataReader.h"
#include "Mona/Time.h"


namespace Mona {


class JSONReader : public DataReader {
public:
	JSONReader(MemoryReader& reader);
	virtual ~JSONReader();

	static bool			IsValid(MemoryReader& reader);

	void				readString(std::string& value);
	double				readNumber();
	bool				readBoolean();
	void				readTime(Mona::Time& time);
	void				readNull();

	bool				readObject(std::string& type,bool& external);
	bool				readArray(Mona::UInt32& size);
	Type				readItem(std::string& name);
	
	Type				followingType();

	void				reset();

private:
	const Mona::UInt8*	readBytes(Mona::UInt32& size);

	const Mona::UInt8*	current();

	Mona::UInt32		_pos;
	std::string			_text;
	Mona::Time			_date;
	bool				_bool;
	Mona::UInt8			_last;
};

inline void JSONReader::readNull() {
	reader.next(4);
}




} // namespace Mona