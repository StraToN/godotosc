/* sumator.h */
#ifndef SUMATOR_H
#define SUMATOR_H

#include "reference.h"

#include "include/oscpkt.hh"

typedef enum { OK_NO_ERROR=0,
               // errors raised by the Message class:
               MALFORMED_ADDRESS_PATTERN, MALFORMED_TYPE_TAGS, MALFORMED_ARGUMENTS, UNHANDLED_TYPE_TAGS,
               // errors raised by ArgReader
               TYPE_MISMATCH, NOT_ENOUGH_ARG, PATTERN_MISMATCH,
               // errors raised by PacketReader/PacketWriter
               INVALID_BUNDLE, INVALID_PACKET_SIZE, BUNDLE_REQUIRED_FOR_MULTI_MESSAGES } ErrorCode;

class OSCMessage : public Reference {
	OBJ_TYPE(OSCMessage,Reference);
private:
	 oscpkt::Message message;

protected:
	static void _bind_methods();
public:

	OSCMessage() {};
	OSCMessage(oscpkt::Message* msg) : message(*msg) {}
	virtual ~OSCMessage();

	OSCMessage& init(const String& s);
	OSCMessage& pushBool(bool b);
	OSCMessage& pushInt32(int32_t i);
	OSCMessage& pushInt64(int64_t h);
	OSCMessage& pushFloat(float f);
	OSCMessage& pushDouble(double d);
	OSCMessage& pushStr(const String& s);
	//OSCMessage& pushBlob(void *ptr, size_t num_bytes);
	void clear();
	oscpkt::Message getMessage() const;
};


class OSCPacketReader : public Reference {
	OBJ_TYPE(OSCPacketReader,Reference);
private:
	oscpkt::PacketReader pr;

protected:
	static void _bind_methods();
public:
	OSCPacketReader();
	//OSCPacketReader(const void *ptr, size_t sz) { pr(ptr, sz); }
	virtual ~OSCPacketReader();

	void init(const Variant& v);
	OSCMessage popMessage();
	bool isOk() const;
	oscpkt::ErrorCode getErr() const;

};

class OSCPacketWriter : public Reference {
	OBJ_TYPE(OSCPacketWriter,Reference);
private:
	oscpkt::PacketWriter pw;

protected:
	static void _bind_methods();
public:
	OSCPacketWriter();
	virtual ~OSCPacketWriter();

	OSCPacketWriter& init();
	OSCPacketWriter& startBundle();
	OSCPacketWriter& endBundle();
	OSCPacketWriter& addMessage(const OSCMessage& message);
	bool isOk();
	oscpkt::ErrorCode getErr();
	uint32_t packetSize();
	char* packetData();
	String get_packet_string();
};


#endif
