#ifdef ARDUINO
#else // ARDUINO
#endif // ARDUINO

#ifdef STANDALONE
/** \defgroup xmodem_standalone XModem Stand-alone
  * internal 'standalone' functions, an example for POSIX implementation
*/
#endif // STANDALONE


// determine if arduino build, define ARDUINO if not already done

#if defined(__AVR__) || defined(AVR) || defined(__AVR) || defined(__AVR_ARCH__)
#ifndef ARDUINO
#define ARDUINO /* hopefully I cover all compiler variations */
#endif // ARDUINO
#endif // __AVR__


#include <stdlib.h>

// required include files
#ifdef ARDUINO
// arduino includes
#include <Arduino.h>
#include <SD.h>
#include <HardwareSerial.h> /* may already be included by 'Arduino.h' */
#include <avr/pgmspace.h>

#elif WIN32
// win32 includes
#include <Windows.h>
#include <io.h>
#else // POSIX
// posix includes
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h> // for IOCTL definitions
#include <memory.h>
#endif // OS-dependent includes


// required per-OS definitions
#ifdef ARDUINO

// file and serial types for Arduino
#define FILE_TYPE File
#define SERIAL_TYPE HardwareSerial *

#elif defined(WIN32) // WINDOWS

// file and serial types for WIN32
#define FILE_TYPE HANDLE
#define SERIAL_TYPE HANDLE

#else // POSIX

// file and serial types for POSIX
#define FILE_TYPE int
#define SERIAL_TYPE int

#endif // ARDUINO


// common definitions

#define SILENCE_TIMEOUT 5000 /* 5 seconds */
#define TOTAL_ERROR_COUNT 32
#define ACK_ERROR_COUNT 8


// Arduino build uses C++ so I must define functions properly

#ifdef ARDUINO

short XReceive(SDClass *pSD, HardwareSerial *pSer, const char *szFilename);

int XSend(SDClass *pSD, HardwareSerial *pSer, const char *szFilename);

#ifdef DEBUG_CODE
const char *XMGetError(void);
#endif // DEBUG_CODE

#else // ARDUINO

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

int XReceive(SERIAL_TYPE hSer, const char *szFilename, int nMode);

int XSend(SERIAL_TYPE hSer, const char *szFilename);

#ifdef DEBUG_CODE
const char *XMGetError(void);
#endif // DEBUG_CODE

#ifdef __cplusplus
};
#endif // __cplusplus

#endif // ARDUINO


