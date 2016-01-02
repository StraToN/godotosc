#ifndef SUMATOR_H
#define SUMATOR_H

#include "reference.h"

#include "include/oscpkt.hh"


class OSCMessage : public Reference {
	OBJ_TYPE(OSCMessage,Reference);
private:
	 oscpkt::Message* message;

protected:
	static void _bind_methods();
public:

	OSCMessage() { message = new oscpkt::Message(); }
	OSCMessage(oscpkt::Message* msg) : message(msg) {}
	virtual ~OSCMessage() { delete message; }

	void init(const String& s);
	void pushBool(bool b);
	void pushInt32(int32_t i);
	void pushInt64(int64_t h);
	void pushFloat(float f);
	void pushDouble(double d);
	void pushStr(const String& s);
	//OSCMessage& pushBlob(void *ptr, size_t num_bytes);
	void clear();
	oscpkt::Message* getMessage() const;
};


class OSCPacketReader : public Reference {
	OBJ_TYPE(OSCPacketReader,Reference);
private:
	oscpkt::PacketReader* pr;

protected:
	static void _bind_methods();
public:

	enum ErrorCode { OK_NO_ERROR=0,
	               // errors raised by the Message class:
	               MALFORMED_ADDRESS_PATTERN, MALFORMED_TYPE_TAGS, MALFORMED_ARGUMENTS, UNHANDLED_TYPE_TAGS,
	               // errors raised by ArgReader
	               TYPE_MISMATCH, NOT_ENOUGH_ARG, PATTERN_MISMATCH,
	               // errors raised by PacketReader/PacketWriter
	               INVALID_BUNDLE, INVALID_PACKET_SIZE, BUNDLE_REQUIRED_FOR_MULTI_MESSAGES } ;

	OSCPacketReader() { pr = new oscpkt::PacketReader(); }
	//OSCPacketReader(const void *ptr, size_t sz) { pr(ptr, sz); }
	virtual ~OSCPacketReader() { delete pr; }

	void init(const String& v);
	String popMessage();
	bool isOk() const;
	oscpkt::ErrorCode getErr() const;

};



class OSCPacketWriter : public Reference {
	OBJ_TYPE(OSCPacketWriter,Reference);
private:
	oscpkt::PacketWriter* pw;

protected:
	static void _bind_methods();
public:
	enum ErrorCode { OK_NO_ERROR=0,
		               // errors raised by the Message class:
		               MALFORMED_ADDRESS_PATTERN, MALFORMED_TYPE_TAGS, MALFORMED_ARGUMENTS, UNHANDLED_TYPE_TAGS,
		               // errors raised by ArgReader
		               TYPE_MISMATCH, NOT_ENOUGH_ARG, PATTERN_MISMATCH,
		               // errors raised by PacketReader/PacketWriter
		               INVALID_BUNDLE, INVALID_PACKET_SIZE, BUNDLE_REQUIRED_FOR_MULTI_MESSAGES } ;

	OSCPacketWriter() { pw = new oscpkt::PacketWriter(); }
	virtual ~OSCPacketWriter() { delete pw; }

	void init();
	void startBundle();
	void endBundle();
	void addMessage(Ref<OSCMessage> message);
	bool isOk();
	oscpkt::ErrorCode getErr();
	uint32_t packetSize();
	char* packetData();
	String get_packet_string();
};


#endif
