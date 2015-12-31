/* register_types.cpp */

#include "register_types.h"
#include "object_type_db.h"
#include "osc.h"

void register_godotosc_types() {

        ObjectTypeDB::register_type<OSCMessage>();
        ObjectTypeDB::register_type<OSCPacketReader>();
        ObjectTypeDB::register_type<OSCPacketWriter>();
}

void unregister_godotosc_types() {
   //nothing to do here
}

