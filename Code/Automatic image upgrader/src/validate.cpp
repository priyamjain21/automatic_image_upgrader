//header files
#include<iostream>
#include"device.cpp"
#include"parse.cpp"

// macro for designing console
#define dotline cout<<"-----------------------------------------------------------------------"<<endl

using namespace std;

/**********************************************************************************
 *     FUNCTION NAME    :   validate
 *
 *     DESCRIPTION      :   takes 4 argument(i.e. device pointer, magic number,
                            no.of devices, and filename ) and check if the config 
                            file matches with the device then update the data in device
 *
 *     RETURNS          :  void
 ***********************************************************************************/
void validate(device *p, vector<pp> &dataMagicNumberStore, int numberOfDevices, string filename){

    bool isUpdated  = false;
    for(int i=0;i<numberOfDevices;i++) {

        if(dataMagicNumberStore[0].first == p[i].getMagicNumber() && !p[i].getisDeviceUpdated()) {

            cout<<"Device number "<< p[i].getDeviceId() <<" is related with this "<< filename <<endl;

            p[i].setUpdatedData(dataMagicNumberStore[0].second);
            cout<<"Device updated data/ updated image file is ->"<<p[i].getUpdatedData()<<endl;

            p[i].setUpdatedData(dataMagicNumberStore[0].second);
            p[i].setisDeviceUpdated(true);      

            isUpdated=true;     // if device updated complete
            dotline;
            break;
        }
        
        // if device is already updated with any config file then print the below message
        else if(dataMagicNumberStore[0].first == p[i].getMagicNumber() && p[i].getisDeviceUpdated()==true){
            cout<<"Device is already updated and this "<<filename<< " is duplicate" <<endl;
            dotline;
            isUpdated = true;
        }
    }

    // if config file is not related with any device it will show the below msg and go to the next config file
    if(!isUpdated){
        cout<<"This "<<filename<<" file is not related with any device"<<endl;
        dotline;
    }
 }

