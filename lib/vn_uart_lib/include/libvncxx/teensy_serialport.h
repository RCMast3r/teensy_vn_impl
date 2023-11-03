#include "port.h"
#include "HardwareSerial.h"
#include "int.h"
#include "port.h"
#include "nocopy.h"
#include "export.h"

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

            TeensySerial(uint32_t baudrate);
            ~TeensySerial();

            virtual void open();

            virtual void close();

            virtual bool isOpen();

            virtual void write(const char data[], size_t length);

            virtual void read(char dataBuffer[], size_t numOfBytesToRead, size_t &numOfBytesActuallyRead);

            virtual void registerDataReceivedHandler(void* userData, DataReceivedHandler handler);

            virtual void unregisterDataReceivedHandler();
        };

    }
}