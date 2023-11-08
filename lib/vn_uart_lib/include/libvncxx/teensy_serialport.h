#include "port.h"
#include "HardwareSerial.h"
#include "int.h"
#include "port.h"
#include "nocopy.h"
#include "export.h"

// what I want to do here is to implement the simple port interface for the teensy's hardware serial
// class. normal SerialPort class implements this as well and extends it.

namespace vn
{
    namespace xplat
    {
        class TeensySerial : public IPort, util::NoCopy
        {
        public:
            enum StopBits
            {
                ONE_STOP_BIT,
                TWO_STOP_BITS
            };

            TeensySerial(HardwareSerial * serial, uint32_t baud){
                _port = serial;
                _baud = baud;
                _onDataReceived = nullptr;
                _userData = nullptr;
            }
            ~TeensySerial();

            virtual void open() override;

            virtual void close() override;

            virtual bool isOpen() override;

            virtual void write(const char data[], size_t length) override;

            virtual void read(char dataBuffer[], size_t numOfBytesToRead, size_t &numOfBytesActuallyRead) override;

            virtual void registerDataReceivedHandler(void* userData, DataReceivedHandler handler) override;

            virtual void unregisterDataReceivedHandler() override;
            void receiveHandleExternal();
        private:
            HardwareSerial * _port;
            uint32_t _baud;
            DataReceivedHandler _onDataReceived;
            void ** _userData;

        };
        
    }
}