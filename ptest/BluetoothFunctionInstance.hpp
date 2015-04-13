#ifndef __BLUETOOTHFUNCTIONINSTANCE_HPP__
#define __BLUETOOTHFUNCTIONINSTANCE_HPP__


class BluetoothFunctionInstance
{
    private:
        uint8 deviceId;
    public:
        BluetoothFunctionInstance(uint8 deviceId)
        {
            this->deviceId = deviceId;
        }

        virtual ~BluetoothFunctionInstance()
        {
            //
        }
};


#endif
