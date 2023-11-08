#include "libvncxx/teensy_serialport.h"
namespace vn
{
    namespace xplat
    {

        void TeensySerial::open()
        {
            _port->begin(_baud);
        }
        void TeensySerial::close()
        {
            _port->end();
        }
        bool TeensySerial::isOpen()
        {
            return true;
        }

        void TeensySerial::read(char dataBuffer[], size_t numBytesToRead, size_t &numofBytesActuallyRead)
        {

            numofBytesActuallyRead = _port->readBytes(dataBuffer, numBytesToRead);
        }
        void TeensySerial::registerDataReceivedHandler(void *userData, DataReceivedHandler userFunction)
        {
            // _port->attachInterrupt(userFunciton);
            _onDataReceived = userFunction;
            _userData = &userData;
        }
        void TeensySerial::receiveHandleExternal(){
            if(_onDataReceived != nullptr)
            {
                while(_port->available()){

                    _onDataReceived(*_userData);
                }
            }
        }
        void TeensySerial::unregisterDataReceivedHandler()
        {
            _onDataReceived = nullptr;
            _userData = nullptr;
        }
    }
}