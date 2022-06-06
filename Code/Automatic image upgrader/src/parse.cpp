/*macros*/
#define pp pair<string,string>          //pair of magic number and data of device

#define MAGICNUMBERINDEX 1              //index of magic number in configuration file
#define MAGICNUMBEREXTRACT 14           //to remove first 14 i.e(magicnumber -) character from config files
#define BASEADDRESSINDEX 4              //index of base address in configuration file
#define BASEADDRESSEXTRACT 15           //to remove first 15 character i.e.(base address -) from config files
#define DEVICEIDINDEX    0               //index of device index in configuration file
#define DEVICEIDEXTRACT 11              //to remove first 11 i.e(deviceid -) character from config files



/**********************************************************************************
 *     FUNCTION NAME    :   extractdetails
 *
 *     DESCRIPTION      :   Function parse the details from configuration
                            files and store them for further operation
 *
 *     RETURNS          :  void
 ***********************************************************************************/

void extractdetails(vector<pp> &dataMagicNumberStore,vector<string> &fileContent) {

    string magicNumber= fileContent[MAGICNUMBERINDEX];
    magicNumber = magicNumber.substr(MAGICNUMBEREXTRACT);           //extracting magic number
    magicNumber.pop_back();

    string baseAddress = fileContent[BASEADDRESSINDEX];
    baseAddress = baseAddress.substr(BASEADDRESSEXTRACT);           //extracting base addreess
    baseAddress.pop_back();

    string deviceId = fileContent[DEVICEIDINDEX];
    deviceId = deviceId.substr(DEVICEIDEXTRACT);                    //extracting device id

    ifstream ifile(baseAddress);
    ifstream fin;

    if(ifile){
        fin.open(baseAddress);                                      //opening file from base path
    }
    else{
        cout<<"Data file does not exists"<<endl;                    //if not open then show this messeage
    }

    string extractData;
    string line;

    while(fin){
        getline(fin,line);                  //to take one complete line from configuration file
        extractData=line;

        if(line=="-1"){
            break;
        }
    }
    dataMagicNumberStore.push_back({magicNumber,extractData});          //push magic number and extract line into the vector
}
