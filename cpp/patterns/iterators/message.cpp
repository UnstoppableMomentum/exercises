#include "./message.h"


Message::Message(TFields &&  fields)
    : fields_(std::move(fields)) {

}