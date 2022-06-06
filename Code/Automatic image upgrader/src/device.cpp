 /**********************************************************************************
 *     Class        :   Device
 *
 *     description  :   stores all the details of files like deviceID,
                        magic no, name, data, etc.
 ***********************************************************************************/
class device{
    private:
        //data members
        string deviceId;
        string magicNumber;
        string DeviceName;
        size_t checkSum;
        string data;
        string updatedData;         // if device is updated or not
        bool isDeviceUpdated=false;
    public:
        device(){
            // cout<<"constructor is called"<<endl;
        }  

        // parameterized constructor for the device
        device(string deviceID,string magicNumber,string DeviceName,size_t checkSum,string data,string updatedData, bool isDeviceUpdated){
            this->deviceId = deviceId;
            this->magicNumber = magicNumber;
            this->DeviceName= DeviceName;
            this->checkSum  = checkSum;
            this->data = data;
            this->updatedData=updatedData;
            this->isDeviceUpdated=false;
        }
        ~device(){
            // cout<<"destructor is called"<<endl;
        }
        
         /**********************************************************************************
                               getters and setters for device class
         ***********************************************************************************/
        string getDeviceId()
        {
            return this->deviceId;
        }
        void setDeviceId(string deviceId)
        {
            this->deviceId = deviceId;
        }
        string getMagicNumber()
        {
            return this->magicNumber;
        }
        void setMagicNumber(string magicNumber)
        {
            this->magicNumber = magicNumber;
        }
        string getDeviceName()
        {
            return this->DeviceName;
        }
        void setDeviceName(string DeviceName)
        {
            this->DeviceName = DeviceName;
        }
        size_t getCheckSum()
        {
            return this->checkSum;
        }
        void setCheckSum(size_t checkSum)
        {
            this->checkSum = checkSum;
        }
        string getData()
        {
            return this->data;
        }
        void setData(string data)
        {
            this->data = data;
        }
        string getUpdatedData()
        {
            return this->updatedData;
        }
        void setUpdatedData(string updated_data)
        {
            this->updatedData = updated_data;
        }
        bool getisDeviceUpdated(){
            return this->isDeviceUpdated;
        }

        void setisDeviceUpdated(bool isDeviceUpdated){
            this->isDeviceUpdated = isDeviceUpdated;
        }
};