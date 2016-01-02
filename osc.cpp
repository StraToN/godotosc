
#include "osc.h"



void OSCMessage::_bind_methods() {

	ObjectTypeDB::bind_method("init",&OSCMessage::init);
//	ObjectTypeDB::bind_method("match",&OSCMessage::match);
//	ObjectTypeDB::bind_method("partial_match",&OSCMessage::partialMatch);
//	ObjectTypeDB::bind_method("arg",&OSCMessage::arg);
//	ObjectTypeDB::bind_method("build_from_raw_data",&OSCMessage::buildFromRawData);
	ObjectTypeDB::bind_method("push_bool",&OSCMessage::pushBool);
	ObjectTypeDB::bind_method("push_int32",&OSCMessage::pushInt32);
	ObjectTypeDB::bind_method("push_int64",&OSCMessage::pushInt64);
	ObjectTypeDB::bind_method("push_float",&OSCMessage::pushFloat);
	ObjectTypeDB::bind_method("push_double",&OSCMessage::pushDouble);
	ObjectTypeDB::bind_method("push_str",&OSCMessage::pushStr);
//	ObjectTypeDB::bind_method("push_blob",&OSCMessage::pushBlob);
	ObjectTypeDB::bind_method("clear",&OSCMessage::clear);
//	ObjectTypeDB::bind_method("pack_message",&OSCMessage::packMessage);
}

void OSCMessage::init(const String& s) {
	CharString ascii = s.ascii();
	message->init(ascii.get_data());	// TimeTag will be immediate
}

void OSCMessage::pushBool(bool b) {
	message->pushBool(b);
}

void OSCMessage::pushInt32(int32_t i) {
	message->pushInt32(i);
}

void OSCMessage::pushInt64(int64_t h) {
	message->pushInt64(h);
}

void OSCMessage::pushFloat(float f) {
	message->pushFloat(f);
}

void OSCMessage::pushDouble(double d) {
	message->pushDouble(d);
}

void OSCMessage::pushStr(const String& s) {
	CharString ascii = s.ascii();
	message->pushStr(std::string(ascii.get_data()));
}


void OSCMessage::clear() {
	message->clear();
}

oscpkt::Message* OSCMessage::getMessage() const {
	return message;
}

///////////////////////////////////////////////////////////////////////////////////




void OSCPacketReader::_bind_methods() {

	ObjectTypeDB::bind_method("init",&OSCPacketReader::init);
	ObjectTypeDB::bind_method("pop_message",&OSCPacketReader::popMessage);
	ObjectTypeDB::bind_method("is_ok",&OSCPacketReader::isOk);
	ObjectTypeDB::bind_method("get_err",&OSCPacketReader::getErr);

	BIND_CONSTANT(OK_NO_ERROR);
	BIND_CONSTANT(MALFORMED_ADDRESS_PATTERN);
	BIND_CONSTANT(MALFORMED_TYPE_TAGS);
	BIND_CONSTANT(MALFORMED_ARGUMENTS);
	BIND_CONSTANT(UNHANDLED_TYPE_TAGS);
	BIND_CONSTANT(TYPE_MISMATCH);
	BIND_CONSTANT(NOT_ENOUGH_ARG);
	BIND_CONSTANT(PATTERN_MISMATCH);
	BIND_CONSTANT(INVALID_BUNDLE);
	BIND_CONSTANT(INVALID_PACKET_SIZE);
	BIND_CONSTANT(BUNDLE_REQUIRED_FOR_MULTI_MESSAGES);

}


void OSCPacketReader::init(const String& v) {
	CharString cs = v.ascii();
	pr->init(cs.get_data(), cs.size());
}

String OSCPacketReader::popMessage() {
	oscpkt::Message* msg = pr->popMessage();
	oscpkt::Storage stor;
	msg->packMessage(stor, true);
	return String(stor.getBytes(stor.size()));
}

bool OSCPacketReader::isOk() const {
	return pr->isOk();
}

oscpkt::ErrorCode OSCPacketReader::getErr() const {
	return pr->getErr();
}


///////////////////////////////////////////////////////////////////////////////////


void OSCPacketWriter::_bind_methods() {

	ObjectTypeDB::bind_method("init",&OSCPacketWriter::init);
	ObjectTypeDB::bind_method("start_bundle",&OSCPacketWriter::startBundle);
	ObjectTypeDB::bind_method("end_bundle",&OSCPacketWriter::endBundle);
	ObjectTypeDB::bind_method(_MD("add_message", "oscmessage") ,&OSCPacketWriter::addMessage);
	ObjectTypeDB::bind_method("is_ok",&OSCPacketWriter::isOk);
	ObjectTypeDB::bind_method("get_err",&OSCPacketWriter::getErr);
	ObjectTypeDB::bind_method("packet_size",&OSCPacketWriter::packetSize);
	ObjectTypeDB::bind_method("packet_data",&OSCPacketWriter::packetData);
	ObjectTypeDB::bind_method("get_packet_string",&OSCPacketWriter::get_packet_string);

	BIND_CONSTANT(OK_NO_ERROR);
	BIND_CONSTANT(MALFORMED_ADDRESS_PATTERN);
	BIND_CONSTANT(MALFORMED_TYPE_TAGS);
	BIND_CONSTANT(MALFORMED_ARGUMENTS);
	BIND_CONSTANT(UNHANDLED_TYPE_TAGS);
	BIND_CONSTANT(TYPE_MISMATCH);
	BIND_CONSTANT(NOT_ENOUGH_ARG);
	BIND_CONSTANT(PATTERN_MISMATCH);
	BIND_CONSTANT(INVALID_BUNDLE);
	BIND_CONSTANT(INVALID_PACKET_SIZE);
	BIND_CONSTANT(BUNDLE_REQUIRED_FOR_MULTI_MESSAGES);

}



//make a String containing the packet to send - with good bytes size, ofc
String OSCPacketWriter::get_packet_string() {
	String s;
	if (isOk()) {
		s = String(pw->packetData());
	}
	return s;
}

void OSCPacketWriter::init() {
	pw->init();
}

void OSCPacketWriter::startBundle() {
	pw->startBundle(oscpkt::TimeTag::immediate());
}

void OSCPacketWriter::endBundle() {
	pw->endBundle();
}

void OSCPacketWriter::addMessage(Ref<OSCMessage> message) {
	pw->addMessage(*(message->getMessage()));
}

bool OSCPacketWriter::isOk() {
	return pw->isOk();
}

oscpkt::ErrorCode OSCPacketWriter::getErr() {
	return pw->getErr();
}

uint32_t OSCPacketWriter::packetSize() {
	return pw->packetSize();
}

char* OSCPacketWriter::packetData() {
	return pw->packetData();
}

