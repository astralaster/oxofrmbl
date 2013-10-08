#include "OtrMessageHandler.h"

extern "C" {
    #include <libotr/proto.h>
}

OtrMessageHandler::OtrMessageHandler()
{
    OTRL_INIT;
}
