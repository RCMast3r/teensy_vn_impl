#include <Arduino.h>
#include "libvncxx/vntime.h"
#include "libvncxx/packetfinder.h"
#include <vector>
// instead of doing this, I think im gonna use a raw packetfinder
vn::protocol::uart::PacketFinder processor;
// vn::xplat::TeensySerial serial1(&Serial1, 115200);
using namespace vn::xplat;
void validPacketFoundHandler(void *userData, vn::protocol::uart::Packet &packet, size_t runningIndexOfPacketStart, TimeStamp ts)
{
    if (packet.type() == vn::protocol::uart::Packet::TYPE_BINARY)
    {
        vn::math::vec3f vel;
        // See if this is a binary packet type we are expecting.
        if (!packet.isCompatible(vn::protocol::uart::COMMONGROUP_NONE, vn::protocol::uart::TIMEGROUP_NONE,
                                 vn::protocol::uart::IMUGROUP_NONE,
                                 vn::protocol::uart::GPSGROUP_NONE,
                                 vn::protocol::uart::ATTITUDEGROUP_NONE,
                                 vn::protocol::uart::INSGROUP_VELBODY, vn::protocol::uart::GPSGROUP_NONE))
        {
            // Not the type of binary packet we are expecting.
            return;
        }
        // Ok, we have our expected binary output packet. Since there are many
        // ways to configure the binary data output, the burden is on the user
        // to correctly parse the binary packet. However, we can make use of
        // the parsing convenience methods provided by the VnUartPacket structure.
        // When using these convenience methods, you have to extract them in
        // the order they are organized in the binary packet per the User Manual.
        vel = packet.extractVec3f();
    }
}

void setup()
{
  processor.registerPossiblePacketFoundHandler(nullptr, validPacketFoundHandler);
}

void loop()
{
    if(Serial1.available());
}

void serialEvent1()
{
  std::string recvd;
  auto size = Serial1.available();
  auto data = new char[size];
  auto read_size = Serial1.readBytes(data, size);
  processor.processReceivedData(data, read_size);
  delete[] data;
}