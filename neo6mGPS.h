#include "Arduino.h"

#ifndef neo6mGPS_cpp

  #define neo6mGPS_cpp
  
  class neo6mGPS
  {
    public:                           
      //array holding all GPS values that can be updated
      float GPS_data[] = {
                            //latitude:
                            0.0,
                            
                            //longitude:
                            0.0,
                          };
      
      //initialize the GPS data extractor class and the GPS itself (overloaded)
      void begin(Stream& _GPS_SERIAL, Stream& _PC_SERIAL, uint32_t _PC_BAUDRATE);
      void begin(Stream& _GPS_SERIAL, Stream& _PC_SERIAL);
      void begin(Stream& _GPS_SERIAL);
      
      //update lat and lon in the GPS_data array
      void grabData_LatLong();
    
    private:
      //serial stream variables (can be hardware or software serial)
      Stream* PC_SERIAL = 0;
      Stream* GPS_SERIAL;
    
      //user defined buad for PC (if given)
      uint32_t PC_BAUDRATE;
    
      //default baudrate is determined by the receiver manufacturer.
      uint32_t GPS_DEFAULT_BAUDRATE 9600

      //wanted buadrate at the moment can be 9600L (not changed after defaults) or 115200L (changed by the
      //`changeBaudrate()`
      uint32_t GPS_WANTED_BAUDRATE 115200
    
      //array of possible baudrates that can be used by the receiver, sorted descending to prevent excess Serial flush/begin
      //after restoring defaults. You can uncomment values that can be used by your receiver before the auto-configuration.
      uint32_t possibleBaudrates[] = {
                                          //921600,
                                          //460800,
                                          //230400,
                                          115200,
                                          //57600,
                                          //38400,
                                          //19200,
                                          9600,
                                          //4800,
                                        };
    
    //create buffer to process incoming info from GPS
    byte buffLen = 64;
    byte buff[buffLen] = {" "};
    
    
    
    //setup GPS and load non-default configuration settings
    void setupGPS();
    
    //send a packet to the receiver to restore default configuration.
    void restoreDefaults();
    
    //send a set of packets to the receiver to disable NMEA messages.
    void disableNmea();
    
    //send a packet to the receiver to change baudrate to 115200.
    void changeBaudrate();
    
    //send a packet to the receiver to change frequency to 100 ms.
    void changeFrequency();
    
    //send a packet to the receiver to disable unnecessary channels.
    void disableUnnecessaryChannels();
      
    //send a packet to the receiver to enable NAV-PVT messages.
    void enableNavPvt();
    
    //send the packet specified to the receiver.
    void sendPacket(byte *packet, byte len);
      
    //print the packet specified to the PC serial in a hexadecimal form.
    void printPacket(byte *packet, byte len);
    
    //extract lat and lon data from the GPS stream buffer
    void extractLatLong();
    
    //convert from minutes seconds to degrees
    void convertLatLong(byte latBuff[], byte lonBuff[]);
  };

#endif
