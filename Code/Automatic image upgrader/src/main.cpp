#include<string>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<unordered_map>
using namespace std;

//header file
#include"validate.cpp"

//Lets you to input device form the users
/**********************************************************************************
 *     FUNCTION NAME    :   inputDeviceDetails
 *
 *     DESCRIPTION      :   takes 4 argument( device pointer, how many device you want to add,
 *                          total number of device available in the system, check device if it exist or not )
 *                          and then add the device into the system
 *
 *     RETURNS          :  void
 ***********************************************************************************/
void inputDeviceDetails(device *p , int addDevice,int &numberOfDevices, unordered_map<string, bool> &checkDevice){
    
    
    for(int i=0;i<addDevice;i++) {

        bool errorFlag=false;    // error handling
        bool duplicatDevice=false;
        string deviceId,devicename,magicNumber;
        size_t checksum;
        do{
            if(errorFlag) cout<<"Not a valid input"<<endl;
            cout<<"Enter the Unique 6 Digit alphanumeric Id for "<<numberOfDevices+1<<" device"<<endl;
            cin>>deviceId;   // input device id
            errorFlag=true;
        }while(deviceId.length()!=6);

        p[numberOfDevices].setDeviceId(deviceId);   
        errorFlag=false;

        do{
            if(errorFlag) cout<<"Not a valid input"<<endl;
            cout<<"Enter Unique Device specific 16 Digit number"<<endl;
            cin>>magicNumber;   // input magic number
            errorFlag=true;
            if(checkDevice[magicNumber]==true) {
                cout<<"Duplicate entry. Device already exit in the system. Try Again from the start"<<endl;
                duplicatDevice=true;
                dotline;
            }
        }while(magicNumber.length()!=16);

        if(duplicatDevice) {
            if(i==addDevice-1) i--;
            continue;
        }

        p[numberOfDevices].setMagicNumber(magicNumber);
        errorFlag=false;
        
        do{
            if(errorFlag) cout<<"Name can't be null"<<endl;
            cout<<"Enter device name"<<endl;
            cin>>devicename;        // input device name
            errorFlag=true;
        }while(devicename.length()==0);

        p[numberOfDevices].setDeviceName(devicename);
        errorFlag=false;

        cout<<"Enter checksum"<<endl;
        cin>>checksum;
        p[numberOfDevices].setCheckSum(checksum);

        string dataString;
        cout<<"Enter the data"<<endl;
        cin.ignore();
        getline(cin,dataString);        // input data
        
        checkDevice[magicNumber]=true;
        p[numberOfDevices].setData(dataString);
        numberOfDevices++;              // increasing the number of device
        cout<<"--------------------------------------------"<<endl;
    }
}


/**********************************************************************************
 *     FUNCTION NAME    :   imageFileUpgrade
 *
 *     DESCRIPTION      :   takes file name from the user, searches file name in 
                            the path provided and calls extractdetails and validate function
 *
 *     RETURNS          :  void
 ***********************************************************************************/
void imageFileUpgrade(device *p , int numberOfDevices){
    int count=1;
    while(true) {
        string filename;
        cout<<"Please enter "<<count<<" filename"<<endl<<"Enter 0 for main menu"<<endl;
        cin>>filename;  // take filename as input
        if(filename=="0") {  // use to go to main menu
            break;
        }
        string parse;
        string line;
        vector<pp> dataMagicNumberStore;
        string path = "/home/priyam_21/Desktop/aiu_project/Automatic image upgrader/src/configuration files/"; // path to the config files
        path+=filename;   // adding the filename to the path
        vector<string> fileContent; // contain the file content line by line
        ifstream ifile(path);
        ifstream fin;
        if(ifile){
            fin.open(path); //open file
        }
        else{                   // if file not found automatically go to the next configuration file
            cout<<"File does not exists"<<endl;  
            count++;
            continue;
        }
        while(fin){                 // push_back into file content of file line by line
            getline(fin,line);
            fileContent.push_back(line);
            if(line=="-1"){
                break;
            }
        }
        extractdetails(dataMagicNumberStore,fileContent); 
        // it will extract the magic number, device id, base address from the config file
        // validate and data update
        validate(p,dataMagicNumberStore,numberOfDevices,filename);  // it will check if config file matches with device
        count++;                                   // if match it will upgrade the data in the device

        ifile.close();                              // clode the file
        dotline;
    }
}


/**********************************************************************************
 *     FUNCTION NAME    :   imageUpgraderCommanddLine
 *
 *     DESCRIPTION      :   takes 3 arguments(i.e. device pointer, no.of devices, 
                            file name) file names are passed through command line
                            and searches file name in the path provided and calls
                            extractdetails validate function
 *
 *     RETURNS          :  void
 ***********************************************************************************/
void imageUpgraderCommandLine(device* p, int numberOfDevices, string filename){

    string parse;
    string line;
    vector<pp> dataMagicNumberStore;
    vector<string> fileContent; // contain the file content line by line
    string path = "/home/priyam_21/Desktop/aiu_project/Automatic image upgrader/src/configuration files/"; // path to the config files
    path+=filename;   // adding the filename to the path
    ifstream ifile(path);
    ifstream fin;
    if(ifile){
        fin.open(path);             // open the file
    }
    else{           // if filename not found it will return and go to the next config file
        cout<<"File does not exists -- "<<filename<<endl;
        return;
    }
    while(fin){
        getline(fin,line);      // used to extract file data line by line
        fileContent.push_back(line);            //push file content line by line into filecontent vector
        if(line=="-1"){
            break;
        }
    }
    extractdetails(dataMagicNumberStore,fileContent);   // it will extract the magic number, device id, base address from the config file
    // validate and data update
    validate(p,dataMagicNumberStore,numberOfDevices,filename);      // it will check if config file matches with device
                                                                    // if match it will upgrade the data in the device
    ifile.close();                                                  // close the file                   
    dotline;
}

 /**********************************************************************************
 *     FUNCTION NAME    :   main
 *
 *     DESCRIPTION      :   driver function (takes command line arguments)
 *
 *     RETURNS          :   int
 ***********************************************************************************/
int main(int argc , char* argv[]){
    unordered_map<string,bool> checkDevice;
    int addDevice=0;
    int numberOfDevices=0;      // total number of device
    device *p = new device[5];   // constant
    dotline;
    cout<<"            Welcome to the Automatic Image Updater"<<endl<<endl<<endl;
    dotline;
    cout<<endl;
    while(true) {    // Main menu
        cout<<"1. Enter the no of devices and device details"<<endl;
        cout<<"2. Updation of image files in device"<<endl;
        cout<<"3. Updation of image files in device from command line"<<endl;
        cout<<"4. Display device details"<<endl;
        cout<<"5. Quit "<<endl;
        dotline;
        cout<<"Enter your choice"<<endl;
        string choice;
        cin>>choice;
        if(choice.length()>1){
            choice[0]='7';
        }
        switch (choice[0])
        {
            case '1':
                cout<<"No. of device in the system - "<< numberOfDevices <<endl;
                cout<<"Enter no of devices you want (You can add upto 5 devices) :- "<<endl;
                cin>>addDevice;
                
                if(addDevice+numberOfDevices<=5){
                    inputDeviceDetails(p,addDevice,numberOfDevices,checkDevice);  // input a device
                }
                else if(numberOfDevices!=0 && addDevice+numberOfDevices>5){
                    cout<<"No. of devices exceeds! \nYou can add only "<< abs(addDevice-numberOfDevices-1) <<" devices"<<endl;
                    dotline;
                    break;
                }else{
                    cout<<"Only 5 devices are allowed"<<endl;
                    dotline;
                }
                break;
            case '2':
                if(numberOfDevices<1){
                    cout<<"There are no devices present currently in system, Please enter atleast one device"<<endl;
                    dotline;
                }
                else{
                    imageFileUpgrade(p,numberOfDevices);   // upgrade the image file
                }
                break;
            case '3':
                if(argc==1){
                    cout<<"You have not put any configuration file in command line"<<endl;
                    dotline;
                    break;
                }
                if(numberOfDevices<1) {
                    cout<<"Currently there are no device present in the system"<<endl;
                    dotline;
                    break;
                }
                for(int i=1;i<argc;i++)     
                {
                    char* configFileName = argv[i];
                    string filename( configFileName );      //typecast char to string
                    imageUpgraderCommandLine(p,numberOfDevices,filename);       //Take config file from command line
                                                                                // upgrade the image

                }
                break;
            case '4':
                if(numberOfDevices<1){
                    cout<<"There are no devices present currently in system, Please enter atleast one device"<<endl;
                    dotline;
                }
                else{       //show all the device
                    for(int i=0;i<numberOfDevices;i++) {
                        cout<<" -------------------Device no.  "<< i+1 <<" --------------------"<<endl;
                        cout<<"DeviceId is "<<p[i].getDeviceId()<<endl;
                        cout<<"MagicNumber is "<<p[i].getMagicNumber()<<endl;
                        cout<<"Device name is "<<p[i].getDeviceName()<<endl;
                        cout<<"Device data is "<<p[i].getData()<<endl;
                        cout<<"Device updated data is "<<p[i].getUpdatedData()<<endl;
                        cout<<endl;
                        dotline;
                    }
                        dotline;
                }
                break;
            
            case '5':
                dotline;
                delete []p;
                exit(EXIT_SUCCESS);   // it will exit the software
            default:                    // default case if invalid input type
                cout<<"Invalid choice please select among(1-5) only.."<<endl;
                dotline;
                break;
            }
    }
    return EXIT_SUCCESS;
}
