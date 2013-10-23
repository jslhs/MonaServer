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
#include "Mona/AMF.h"
#include "Mona/DataWriter.h"
#include <list>
#include <map>

namespace Mona {

class ObjectRef;
class AMFWriter : public DataWriter {
public:
	AMFWriter();
	virtual ~AMFWriter();

	bool repeat(Mona::UInt32 reference);
	void clear();

	void beginObject(const std::string& type="",bool external=false);
	void endObject();

	void beginMap(Mona::UInt32 size,bool weakKeys=false);
	void endMap();

	void writePropertyName(const std::string& value);

	void beginArray(Mona::UInt32 size);
	void beginObjectArray(Mona::UInt32 size);
	void endArray();

	void writeDate(const Mona::Time& date);
	void writeNumber(double value);
	void writeString(const std::string& value);
	void writeBoolean(bool value);
	void writeNull();
	void writeBytes(const Mona::UInt8* data,Mona::UInt32 size);

	bool				amf0Preference;

private:
	void writeInteger(Mona::Int32 value);
	void writeText(const std::string& value);

	std::map<std::string,Mona::UInt32>	_stringReferences;
	std::vector<Mona::UInt8>			_references;
	bool								_amf3;
	std::list<ObjectRef*>				_lastObjectReferences;
};


inline void AMFWriter::beginArray(Mona::UInt32 size) {
	beginObjectArray(size);
	endObject();
}

inline void AMFWriter::endArray() {
	endObject();
}

inline void AMFWriter::endMap() {
	endObject();
}


class AMFWriterNull : public AMFWriter {
public:
	AMFWriterNull() {stream.setstate(std::ios_base::eofbit);}
};



} // namespace Mona