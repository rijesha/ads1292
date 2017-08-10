#include <UBX_Parser.h>
#include "config.h"


class MyParser : public UBX_Parser {

    void handle_NAV_POSLLH(unsigned long iTOW, 
            long lon, 
            long lat, 
            long height, 
            long hMSL, 
            unsigned long hAcc, 
            unsigned long vAcc) {

        /*
        unsigned long test = 4294967289;
        Serial.write(20);
        Serial.write(4);
        Serial.write((byte*)&test, sizeof(test));
        Serial.write(19);
        */
        #ifdef ENABLE_GPS
        #ifdef DEBUG_GPS
        Serial.print("NAV-POSLLH: iTOW=");
        Serial.print(iTOW);
        Serial.print("ms lat=");
        Serial.print(lat/1e7,7);
        Serial.print("deg lon=");
        Serial.print(lon/1e7,7);
        Serial.print("deg height=");
        Serial.print(height);
        Serial.print("mm hMSL=");
        Serial.print(hMSL);
        Serial.print("mm hAcc=");
        Serial.print(hAcc);
        Serial.print("mm vAcc=");
        Serial.print(vAcc);
        Serial.println("mm");
        #else
        Serial.write(20);
        Serial.write(16);
        Serial.write((byte*)&lon, sizeof(lon));
        Serial.write((byte*)&lat, sizeof(lat));
        Serial.write((byte*)&hMSL, sizeof(hMSL));
        Serial.write((byte*)&hAcc, sizeof(hAcc));
        Serial.write(19);
        #endif
        #endif

    
    }  

    void handle_NAV_DOP(unsigned long iTOW, 
            unsigned short gDOP,
            unsigned short pDOP,
            unsigned short tDOP,
            unsigned short vDOP,
            unsigned short hDOP,
            unsigned short nDOP,
            unsigned short eDOP) {
/*
        Serial.print("NAV-DOP: iTOW=");
        Serial.print(iTOW);
        Serial.print("ms gDOP=");
        Serial.print(gDOP/100., 2);
        Serial.print(" pDOP=");
        Serial.print(gDOP/100., 2);
        Serial.print(" tDOP=");
        Serial.print(tDOP/100., 2);
        Serial.print(" vDOP=");
        Serial.print(vDOP/100., 2);
        Serial.print(" hDOP=");
        Serial.print(hDOP/100., 2);
        Serial.print(" nDOP=");
        Serial.print(nDOP/100., 2);
        Serial.print(" eDOP=");
        Serial.println(eDOP/100., 2); */
    }

    virtual void handle_NAV_VELNED(unsigned long iTOW,
            long velN,
            long velE,
            long velD,
            unsigned long speed,
            unsigned long gSpeed,
            long heading,
            unsigned long sAcc,
            unsigned long cAcc)
    {
      #ifdef ENABLE_GPS
        #ifdef DEBUG_GPS
        Serial.print("NAV-VELNED: iTOW=");
        Serial.print(iTOW);
        Serial.print("ms velN=");
        Serial.print(velN);
        Serial.print("cm/s");
        Serial.print("ms velE=");
        Serial.print(velE);
        Serial.print("cm/s");
        Serial.print("ms velD=");
        Serial.print(velD);
        Serial.print("cm/s speed=");
        Serial.print(speed);
        Serial.print("cm/s gSpeed=");
        Serial.print(gSpeed);
        Serial.print("cm/s heading=");
        Serial.print(heading/1e5, 5);
        Serial.print("deg sAcc=");
        Serial.print(sAcc);
        Serial.print("cm/s cAcc=");
        Serial.print(cAcc/1e5, 5);
        Serial.println("deg");
        #else
        Serial.write(20);
        Serial.write(12);
        Serial.write((byte*)&gSpeed, sizeof(gSpeed));
        Serial.write((byte*)&velD, sizeof(velD));
        Serial.write((byte*)&heading, sizeof(heading));
        Serial.write(19);
        #endif
       #endif
 
    
        
     }


    /* Un-comment this to report IDs of messages available but not yet handled.
    void reportUnhandled(char msgid) {
        Serial.print("Got message ID ");
        Serial.println(msgid&0xFF, HEX);
    }
    */
};

