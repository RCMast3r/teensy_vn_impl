// #include "libvncxx/rtcmmessage.h"

// namespace vn {
//     namespace xplat {


//         rtcmmessage::rtcmmessage(char* buffer, int bufferSize, int offset, int messageSize)
//         {
//             this->valid = false;
//             this->supported = false;
//             this->id = 0;
//             this->crc = 0;
//             this->buffer = 0;

//             if (messageSize <= 0)
//             {
//                 return;
//             }

//             if (offset + messageSize <= bufferSize)
//             {
//                 // Allocate enough space to make a copy of the message.
//                 this->buffer = new char[messageSize];

//                 // Make a copy of the buffer for just the message data
//                 memcpy(this->buffer, buffer + offset, messageSize);

//                 // Debug: Print buffer
//                 //printBuffer(this->buffer, messageSize);

//                 // process the message data
//                 processBuffer(messageSize);
//             }
//             // else remain an invalid message
//         }

//         void rtcmmessage::processBuffer(int messageSize)
//         {
//             // The ID is made up of 24 bits "AB C0" 
//             this->id = ((buffer[4] & 0xF0) >> 4) + ((buffer[3] & 0x0F) << 4) + (((buffer[3] & 0xF0) >> 4) * 256);


//             switch (this->id)
//             {
//                 //System setup: 1005-1007, 1033  
//             case 1005:
//             case 1006:
//             case 1007:
//             case 1033:
//             {
//                 this->group = "System Setup";
//                 this->supported = true;
//                 break;
//             }

//             //GPS: 1001-1004, 1074, 1075, 1077
//             case 1001:
//             case 1002:
//             case 1003:
//             case 1004:
//             case 1074:
//             case 1075:
//             case 1077:
//             {
//                 this->group = "GPS";
//                 this->supported = true;
//                 break;
//             }

//             //GLONASS: 1009-1012, 1084, 1085, 1087, 1230 
//             case 1009:
//             case 1010:
//             case 1011:
//             case 1012:
//             case 1084:
//             case 1085:
//             case 1087:
//             case 1230:
//             {
//                 this->group = "GLOSNASS";
//                 this->supported = true;
//                 break;
//             }

//             //Galileo: 1094, 1095, 1097
//             case 1094:
//             case 1095:
//             case 1097:
//             {
//                 this->group = "Galileo";
//                 this->supported = true;
//                 break;
//             }

//             //Beidou: 1124, 1125, 1127
//             case 1124:
//             case 1125:
//             case 1127:
//             {
//                 this->group = "Beidou";
//                 this->supported = true;
//                 break;
//             }

//             //uBlox proprietary message
//             case 4072:
//             {
//                 this->group = "uBlox";
//                 this->supported = true;
//                 break;
//             }

//             default:
//             {
//                 this->group = "Unknown";
//                 this->supported = false;
//                 break;
//             }
//             }


//             // The CRC is the last 24 bits
//             this->crc = (unsigned long)((buffer[messageSize - 1] & 0xFF) + ((buffer[messageSize - 2] & 0xFF) << 8) + (((buffer[messageSize - 3] & 0xFF) << 16)));

//             // Calculate the CRC24Q value for the buffer (excluding the 24-bit CRC at the end of the buffer)
//             unsigned long crc = 0;
//             for (int i = 0; i < messageSize - 3; i++)
//             {
//                 crc = ((crc << 8) & 0xFFFFFF) ^ crc24qtab[(crc >> 16) ^ (buffer[i] & 0x0000FF)];
//             }

//             // Record the validity of this message
//             this->valid = (crc == this->crc);

//             if (!this->valid)
//             {
//                 printf("RTCM_Message::ProcessBuffer: CRC Mismatch for ID(%i) Group(%s): crc[%03x] calculated crc[%03x]\n", this->id, this->group.c_str(), (unsigned int)this->crc, (unsigned int)crc);
//             }
//         }

//         void rtcmmessage::printBuffer(char* buffer, int bufferSize)
//         {
//             printf("Buffer: ");
//             for (int i = 0; i < bufferSize; i++)
//             {
//                 printf("0x%02x, ", buffer[i] & 0x0000FF);
//             }
//             printf("\n");
//         }

//         bool rtcmmessage::unitTest()
//         {
//             char buffer[] = {
//                 // 1005 - System Setup (19)
//                 (char)0xd3, (char)0x00, (char)0x13,
//                 (char)0x3e, (char)0xd0, (char)0x00, (char)0x03, (char)0xbe, (char)0x8a, (char)0xf9, (char)0x06, (char)0xab, (char)0xb3, (char)0x9a, (char)0x5d, (char)0x2a, (char)0x3e, (char)0x88, (char)0x04, (char)0xc7, (char)0x77, (char)0x09,
//                 (char)0x6a, (char)0x44, (char)0xa5,

//                 // 1077 - GPS (294)
//                 (char)0xd3, (char)0x01, (char)0x26,
//                 (char)0x43, (char)0x50, (char)0x00, (char)0x27, (char)0x66, (char)0x6d, (char)0x02, (char)0x00, (char)0x00, (char)0x41, (char)0xc6, (char)0x54, (char)0x0a, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x20, (char)0x00, (char)0x00, (char)0x7f, (char)0xff, (char)0xfe, (char)0x94, (char)0x88, (char)0x96, (char)0xa0, (char)0x9e, (char)0x90, (char)0x96, (char)0xa8, (char)0x96, (char)0x92, (char)0x8a, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x17, (char)0x2a, (char)0xf8, (char)0x5d, (char)0xd4, (char)0x54, (char)0x48, (char)0xa7, (char)0xab, (char)0x50, (char)0x37, (char)0xdb, (char)0x5e, (char)0xae, (char)0x7c, (char)0x82, (char)0x03, (char)0x30, (char)0x47, (char)0x61, (char)0x4e, (char)0xfc, (char)0x87, (char)0xf8, (char)0xbf, (char)0xba, (char)0x5e, (char)0x9e, (char)0xff, (char)0xdb, (char)0xf9, (char)0xef, (char)0xdd, (char)0xe3, (char)0x63, (char)0x34, (char)0x38, (char)0xde, (char)0xa6, (char)0xdb, (char)0xd8, (char)0x6d, (char)0x0d, (char)0x04, (char)0x7b, (char)0x66, (char)0x49, (char)0xb7, (char)0x06, (char)0x5e, (char)0xf6, (char)0x68, (char)0x0b, (char)0x3d, (char)0x8b, (char)0x35, (char)0xd9, (char)0x0b, (char)0xc3, (char)0xb1, (char)0x88, (char)0x3b, (char)0x1f, (char)0x9f, (char)0x1e, (char)0xe3, (char)0xf2, (char)0x49, (char)0x61, (char)0x95, (char)0xfe, (char)0x1b, (char)0x1f, (char)0xbe, (char)0xd9, (char)0x5b, (char)0xed, (char)0x32, (char)0x59, (char)0x4c, (char)0xa3, (char)0x93, (char)0xc6, (char)0xe4, (char)0x47, (char)0xca, (char)0x45, (char)0xf0, (char)0x00, (char)0xf8, (char)0x18, (char)0xa1, (char)0x13, (char)0x56, (char)0x01, (char)0xd3, (char)0xb1, (char)0xa1, (char)0xd0, (char)0x6f, (char)0x21, (char)0x50, (char)0x70, (char)0x81, (char)0x75, (char)0x3b, (char)0x21, (char)0x95, (char)0xa3, (char)0x01, (char)0x9c, (char)0x2e, (char)0x5f, (char)0x6b, (char)0x7b, (char)0x5f, (char)0x75, (char)0xf9, (char)0x61, (char)0x1a, (char)0x7e, (char)0xa1, (char)0x39, (char)0x98, (char)0xbf, (char)0xe9, (char)0xb7, (char)0x9f, (char)0xf6, (char)0x7a, (char)0x80, (char)0x6d, (char)0x08, (char)0xe0, (char)0x74, (char)0xae, (char)0x5f, (char)0xd4, (char)0xdf, (char)0x1f, (char)0xe6, (char)0x0d, (char)0x5e, (char)0x72, (char)0x53, (char)0xde, (char)0x8d, (char)0x93, (char)0x81, (char)0x2d, (char)0xc0, (char)0xa1, (char)0x45, (char)0x51, (char)0x52, (char)0x74, (char)0x9b, (char)0x41, (char)0xd0, (char)0x53, (char)0xf4, (char)0xfd, (char)0x43, (char)0xd0, (char)0xf1, (char)0x8c, (char)0x61, (char)0x32, (char)0xcc, (char)0xb1, (char)0xf4, (char)0x7c, (char)0xf7, (char)0x3d, (char)0xb2, (char)0xac, (char)0xab, (char)0x30, (char)0xcc, (char)0x13, (char)0x5c, (char)0xd6, (char)0x00, (char)0x00, (char)0x05, (char)0xb3, (char)0x15, (char)0x62, (char)0x36, (char)0x0d, (char)0x97, (char)0x75, (char)0x56, (char)0x50, (char)0xb5, (char)0x92, (char)0xf3, (char)0x5e, (char)0x13, (char)0x0d, (char)0xad, (char)0x15, (char)0xcd, (char)0xca, (char)0x85, (char)0xb1, (char)0x0d, (char)0xdc, (char)0x71, (char)0x56, (char)0x41, (char)0x58, (char)0x7f, (char)0x6b, (char)0xfe, (char)0xe0, (char)0x25, (char)0xb4, (char)0x4b, (char)0x76, (char)0xe2, (char)0x4d, (char)0xc4, (char)0x7f, (char)0x75, (char)0x7e, (char)0xed, (char)0x6e, (char)0xe6, (char)0xdd, (char)0xe9, (char)0xe0, (char)0xfb, (char)0xc2, (char)0x2f, (char)0x6a, (char)0x0e, (char)0xd6, (char)0xc3, (char)0xbd, (char)0x87, (char)0x6c, (char)0x8b, (char)0x12, (char)0x16, (char)0x36, (char)0x01, (char)0x64, (char)0x02, (char)0xcf, (char)0xd2, (char)0x5f, (char)0xa5, (char)0xe0,
//                 (char)0xa0, (char)0x24, (char)0xf2,

//                 // 1087 - GLOSNASS (185)
//                 (char)0xd3, (char)0x00, (char)0xb9,
//                 (char)0x43, (char)0xf0, (char)0x00, (char)0x40, (char)0xc5, (char)0xa1, (char)0xc2, (char)0x00, (char)0x00, (char)0x03, (char)0x01, (char)0xf0, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x80, (char)0x00, (char)0x00, (char)0x5f, (char)0xfe, (char)0x98, (char)0x9a, (char)0x90, (char)0x86, (char)0x92, (char)0x82, (char)0x8c, (char)0x78, (char)0xed, (char)0x69, (char)0x50, (char)0x99, (char)0xc8, (char)0xfc, (char)0x58, (char)0x76, (char)0xcf, (char)0x7d, (char)0xa2, (char)0x04, (char)0x28, (char)0x01, (char)0x10, (char)0x26, (char)0x9f, (char)0xa2, (char)0x04, (char)0xb5, (char)0xfe, (char)0x3f, (char)0xa8, (char)0x21, (char)0x83, (char)0x9a, (char)0x5a, (char)0x83, (char)0xa6, (char)0x1f, (char)0x95, (char)0xdc, (char)0x83, (char)0xde, (char)0x0a, (char)0x16, (char)0x04, (char)0x0d, (char)0x60, (char)0x6e, (char)0x2e, (char)0x3e, (char)0x51, (char)0xe4, (char)0x39, (char)0x99, (char)0xcb, (char)0xc4, (char)0xdd, (char)0x0b, (char)0xe9, (char)0xbf, (char)0x61, (char)0x7c, (char)0x47, (char)0x66, (char)0x05, (char)0x5d, (char)0x92, (char)0x17, (char)0xa8, (char)0xd2, (char)0x1a, (char)0xfe, (char)0xb5, (char)0xf8, (char)0x4c, (char)0x9d, (char)0xfa, (char)0xcf, (char)0x9c, (char)0x03, (char)0x2e, (char)0x20, (char)0x05, (char)0xf8, (char)0xba, (char)0x11, (char)0xfa, (char)0xce, (char)0x13, (char)0x13, (char)0x11, (char)0xf5, (char)0x0f, (char)0x63, (char)0xf7, (char)0x84, (char)0x1d, (char)0xf0, (char)0xfa, (char)0x23, (char)0xf2, (char)0x95, (char)0x9d, (char)0x34, (char)0xc8, (char)0xf2, (char)0x35, (char)0x0f, (char)0x43, (char)0xcd, (char)0xf3, (char)0x7c, (char)0xdd, (char)0x37, (char)0x4c, (char)0x33, (char)0x0c, (char)0x57, (char)0x14, (char)0x00, (char)0x02, (char)0x35, (char)0x9d, (char)0x2d, (char)0x3c, (char)0x1a, (char)0xc7, (char)0xb8, (char)0x6b, (char)0x9b, (char)0xb6, (char)0xcb, (char)0xc5, (char)0xf0, (char)0x99, (char)0x4a, (char)0xa7, (char)0x08, (char)0x5c, (char)0x41, (char)0x40, (char)0x7f, (char)0x98, (char)0xab, (char)0x71, (char)0x5f, (char)0xe4, (char)0x22, (char)0x48, (char)0x8d, (char)0x71, (char)0x11, (char)0xe0, (char)0x53, (char)0xf3, (char)0x3f, (char)0xe8, (char)0x17, (char)0xf8, (char)0x4f, (char)0xe3, (char)0x00,
//                 (char)0xcf, (char)0xce, (char)0x40,

//                 // 1097 - Galileo (335)
//                 (char)0xd3, (char)0x01, (char)0x4f,
//                 (char)0x44, (char)0x90, (char)0x00, (char)0x27, (char)0x66, (char)0x6d, (char)0x02, (char)0x00, (char)0x00, (char)0x14, (char)0x58, (char)0x00, (char)0xc1, (char)0x40, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x01, (char)0x01, (char)0x00, (char)0x7f, (char)0xff, (char)0xff, (char)0xf5, (char)0x85, (char)0x65, (char)0x84, (char)0xf4, (char)0xe5, (char)0x15, (char)0x45, (char)0xa5, (char)0xc0, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x58, (char)0x25, (char)0x42, (char)0x4d, (char)0xa1, (char)0x21, (char)0x9b, (char)0x78, (char)0xfa, (char)0xf9, (char)0xff, (char)0x00, (char)0x12, (char)0x06, (char)0x98, (char)0x21, (char)0x3f, (char)0x7e, (char)0xbf, (char)0xa9, (char)0x01, (char)0x47, (char)0xf1, (char)0x70, (char)0x4a, (char)0xc1, (char)0x68, (char)0xdb, (char)0x7f, (char)0x8d, (char)0xd1, (char)0x69, (char)0xdd, (char)0xc3, (char)0x0f, (char)0xac, (char)0x2a, (char)0xfc, (char)0x03, (char)0xbf, (char)0xcd, (char)0xd3, (char)0xcc, (char)0x2a, (char)0x0c, (char)0xe1, (char)0x6a, (char)0xce, (char)0xe8, (char)0xec, (char)0x68, (char)0xf5, (char)0xc6, (char)0x2a, (char)0xcc, (char)0x6e, (char)0x9c, (char)0xdc, (char)0x41, (char)0xdd, (char)0xbb, (char)0xb1, (char)0xdc, (char)0x98, (char)0xd1, (char)0x19, (char)0xf6, (char)0x11, (char)0x97, (char)0xe1, (char)0x26, (char)0x34, (char)0x07, (char)0x03, (char)0x90, (char)0x7e, (char)0x8c, (char)0x08, (char)0xca, (char)0x52, (char)0xe8, (char)0xd9, (char)0x2f, (char)0xfe, (char)0xc3, (char)0x0e, (char)0x06, (char)0x34, (char)0x05, (char)0x83, (char)0x4a, (char)0x6c, (char)0x35, (char)0xbc, (char)0x3f, (char)0x74, (char)0xdc, (char)0x3f, (char)0x7b, (char)0xfc, (char)0x4f, (char)0x80, (char)0x02, (char)0x1f, (char)0xeb, (char)0x7b, (char)0xdf, (char)0xf1, (char)0xde, (char)0xff, (char)0xf4, (char)0x65, (char)0xcf, (char)0x22, (char)0x0c, (char)0xef, (char)0x24, (char)0x56, (char)0x2f, (char)0x27, (char)0x34, (char)0x0f, (char)0x27, (char)0xdf, (char)0xaf, (char)0x31, (char)0xd4, (char)0x0f, (char)0x3d, (char)0x6c, (char)0xbf, (char)0x80, (char)0xea, (char)0x4f, (char)0x85, (char)0xc0, (char)0x4f, (char)0x8b, (char)0x7e, (char)0xd0, (char)0x54, (char)0xf1, (char)0xd0, (char)0x60, (char)0x1d, (char)0x50, (char)0x65, (char)0x7e, (char)0x10, (char)0x37, (char)0x49, (char)0x30, (char)0x45, (char)0x7e, (char)0x90, (char)0x4a, (char)0x4a, (char)0xe0, (char)0xbc, (char)0xfc, (char)0x80, (char)0xc5, (char)0x40, (char)0x40, (char)0xcb, (char)0x6f, (char)0x20, (char)0xd9, (char)0x97, (char)0xf0, (char)0xe5, (char)0x95, (char)0x80, (char)0xe8, (char)0x17, (char)0x89, (char)0x86, (char)0x61, (char)0x98, (char)0x68, (char)0x2a, (char)0x0a, (char)0x82, (char)0xa6, (char)0x29, (char)0x8a, (char)0x62, (char)0x4e, (char)0x93, (char)0xa4, (char)0xf9, (char)0x9e, (char)0x61, (char)0x98, (char)0x68, (char)0x9a, (char)0x26, (char)0x89, (char)0x9b, (char)0x66, (char)0xd9, (char)0xb6, (char)0x97, (char)0xa5, (char)0xe9, (char)0x79, (char)0xa2, (char)0x6e, (char)0x9b, (char)0x80, (char)0x00, (char)0x00, (char)0x05, (char)0x19, (char)0x96, (char)0x60, (char)0xf6, (char)0xfe, (char)0x2f, (char)0x7e, (char)0x51, (char)0x95, (char)0x9d, (char)0x21, (char)0x50, (char)0xde, (char)0xb6, (char)0xbd, (char)0x79, (char)0x76, (char)0xdc, (char)0x78, (char)0x06, (char)0x99, (char)0x94, (char)0xdc, (char)0x79, (char)0x4e, (char)0x39, (char)0x4e, (char)0x5b, (char)0xb6, (char)0x5c, (char)0x47, (char)0x5d, (char)0x59, (char)0x63, (char)0x17, (char)0x85, (char)0xf9, (char)0x0c, (char)0x45, (char)0x11, (char)0xa4, (char)0x21, (char)0xf0, (char)0x45, (char)0xa8, (char)0x69, (char)0x80, (char)0xcd, (char)0xa1, (char)0xb9, (char)0x86, (char)0xc8, (char)0x8e, (char)0x7e, (char)0x1b, (char)0x67, (char)0xb7, (char)0x4f, (char)0x6c, (char)0xbe, (char)0xd9, (char)0xc1, (char)0x36, (char)0x82, (char)0x5d, (char)0xc4, (char)0xcc, (char)0x04, (char)0x92, (char)0x0a, (char)0x22, (char)0x13, (char)0xdc, (char)0x93, (char)0xc1, (char)0x26, (char)0x82, (char)0x55, (char)0x9f, (char)0xb4, (char)0xff, (char)0xce, (char)0xff, (char)0x79,
//                 (char)0xbe, (char)0xfb, (char)0x29,

//                 // 1127 - Beidou (124)
//                 (char)0xd3, (char)0x00, (char)0x7c,
//                 (char)0x46, (char)0x70, (char)0x00, (char)0x27, (char)0x65, (char)0x92, (char)0x40, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x12, (char)0x1a, (char)0x0c, (char)0x00, (char)0x00, (char)0x00, (char)0x20, (char)0x00, (char)0x00, (char)0x00, (char)0x7f, (char)0x57, (char)0x59, (char)0x49, (char)0x54, (char)0x4c, (char)0x51, (char)0x51, (char)0x00, (char)0x00, (char)0x00, (char)0x02, (char)0x1a, (char)0xef, (char)0x81, (char)0x6b, (char)0xdc, (char)0xb2, (char)0xca, (char)0x65, (char)0x41, (char)0xa9, (char)0x02, (char)0xd4, (char)0x02, (char)0xf0, (char)0x83, (char)0x7e, (char)0x0c, (char)0xf9, (char)0x28, (char)0x16, (char)0x20, (char)0xf7, (char)0x77, (char)0xdb, (char)0x6c, (char)0x8d, (char)0x2c, (char)0x7d, (char)0xe5, (char)0xa5, (char)0x7f, (char)0xfb, (char)0x2f, (char)0x06, (char)0xd4, (char)0xbc, (char)0x3e, (char)0xa2, (char)0x03, (char)0x36, (char)0xe3, (char)0xf6, (char)0xcc, (char)0x7b, (char)0xf6, (char)0x2f, (char)0x7c, (char)0xfa, (char)0x61, (char)0x88, (char)0x01, (char)0x2d, (char)0xa5, (char)0x02, (char)0xd8, (char)0xec, (char)0xf1, (char)0x6f, (char)0x15, (char)0x9e, (char)0x25, (char)0x09, (char)0xbe, (char)0x7e, (char)0x94, (char)0xa5, (char)0x3a, (char)0x48, (char)0x05, (char)0x7f, (char)0x2a, (char)0x67, (char)0x96, (char)0x66, (char)0x67, (char)0x7a, (char)0xdf, (char)0x7d, (char)0xe3, (char)0x80, (char)0xe0, (char)0x6e, (char)0xde, (char)0xf7, (char)0xaa, (char)0x4b, (char)0x10, (char)0x0c, (char)0xf0, (char)0x40, (char)0x40,
//                 (char)0xc2, (char)0x7a, (char)0xd4,

//                 // 1230 - Unknown (12)
//                 (char)0xd3, (char)0x00, (char)0x0c,
//                 (char)0x4c, (char)0xe0, (char)0x00, (char)0x8f, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
//                 (char)0xe0, (char)0x3f, (char)0x61
//             };

//             int bufferSize = sizeof(buffer);
//             int packetSize = 0;
//             int offset = 0;

//             // System Setup (packetSize = 19 + 6 = 25)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1005 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1005.valid != true)
//             {
//                 return false;
//             }

//             // GPS (packetSize = 294 + 6 = 300)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1077 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1077.valid != true)
//             {
//                 return false;
//             }

//             // GLOSNASS (packetSize = 185 + 6 = 191)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1087 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1087.valid != true)
//             {
//                 return false;
//             }

//             // Galileo (packetSize = 335 + 6 = 341)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1097 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1097.valid != true)
//             {
//                 return false;
//             }

//             // Beidou (packetSize = 124 + 6 = 130)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1127 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1127.valid != true)
//             {
//                 return false;
//             }

//             // Unknown (packetSize = 12 + 6 = 18)
//             offset += packetSize;
//             packetSize = (((buffer[offset + 1] & 0xFF) & 0x03) * 256) + (buffer[offset + 2] & 0xFF) + 6;
//             rtcmmessage message_1230 = rtcmmessage(buffer, bufferSize, offset, packetSize);
//             if (message_1230.valid != true)
//             {
//                 return false;
//             }

//             return true;
//         }

//     }
// }