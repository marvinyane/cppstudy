#ifndef __BLUETOOTHHFPINSTANCE_HPP__
#define __BLUETOOTHHFPINSTANCE_HPP__

#include "BluetoothTools.h"

class BluetoothHfpCallList
{
    public:
        uint8 multiparty;
        uint8 index;
        uint8 direction;

        std::string number;

};

class BluetoothHfpInstance : public BluetoothFunctionInstance
{
    private:
        uint8 service;
        uint8 battery;
        uint8 signal;
        uint8 roam;

        std::string operatorName;
        std::string phoneNumber;

        uint8 callState;
        std::vector<BluetoothHfpCallList> callList;

        uint32 supportFeatures;

    public:
        explicit BluetoothHfpInstance(uint8 deviceId, uint32 supportFeatures)
            : BluetoothFunctionInstance(deviceId),
            supportFeatures(supportFeatures)
        {
        }

        ~BluetoothHfpInstance()
        {
            // TODO: 
        }

        void BluetoothHfpDialOut(std::string number);
        void BluetoothHfpDialOutLast();

        void BluetoothHfpAcceptCall();
        void BluetoothHfpRejectCall();
        void BluetoothHfpTerminateCall();

        void BluetoothHfpSwitchCall();
        void BluetoothHfpMergeCall();

        // for event
        
};

#endif
