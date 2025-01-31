#include <iostream>
#include <fstream>
#include <string>
#include <thread>
using namespace std;

void encryptMessage(int shift){

    string input, line;
    fstream file;

    file.open("EncryptedMessage.txt", ios::out);
    if(!file.is_open()){
        cout << "Error! File does not exist." << endl;
    }

    cout << "Your message(Type 'q' and press enter to finish): ";
    
    while (true)
    {
        getline(cin, input );

        if(input == "q"){
            break;
        }

        for (auto &ch : input) {
            if (ch >= 'A' && ch <= 'Z') {
                ch = ((ch - 'A' + shift) % 26) + 'A';
            } 
            else if (ch >= 'a' && ch <= 'z') {
                ch = ((ch - 'a' + shift) % 26) + 'a';
            }
        }
        file << input << endl;
    }

    file.close();
    cout << "\t\tMessage encrypted and saved to 'EncryptedMessage.txt'.\n\n" << endl;
}

void decryptMessage(int shift){

    fstream efile, dfile;
    string line;

    efile.open("EncryptedMessage.txt", ios::in);
    dfile.open("DecryptedMessage.txt", ios::out);

    if(efile.is_open() && dfile.is_open()){
        while (getline(efile, line))
        {
            for(auto &ch : line){
                if (ch >= 'A' && ch <= 'Z') {
                    ch = ((ch - 'A' - shift + 26) % 26) + 'A'; // Büyük harf
                } 
                else if (ch >= 'a' && ch <= 'z') {
                    ch = ((ch - 'a' - shift + 26) % 26) + 'a'; // Küçük harf
                }
            }
            dfile << line << endl;
        }
        efile.close();
        dfile.close();
        cout << "\t\tMessage decrypted and saved to 'DecryptedMessage.txt'.\n\n" << endl;
    }
    else{
        cout << "Error! File cannot be opened." << endl;
    }
}

void clearMessage(){

    fstream efile, dfile;

    efile.open("EncryptedMessage.txt", ios::out | ios::trunc);
    dfile.open("DecryptedMessage.txt", ios::out | ios::trunc);
    if(efile.is_open() && dfile.is_open()){
        cout << "\t\tMessage cleared!\n\n" << endl;
    }
    else{
        cout << "\t\tError! File cannot be opened.\n" << endl;
    }

   efile.close();
   dfile.close();
}

int main(){

    int shift = 5;
    int choice;

    while(true){
        cout << endl << "\t\t\tEncryption and Decryption\n\n\n";
        cout << "\t\t1 - Encrypt" << endl;
        cout << "\t\t2 - Decrypt" << endl;
        cout << "\t\t3 - Clear messages" << endl;
        cout << "\t\t4 - Exit" << endl;
        cout << "\t\tSelect an option: ";
        cin >> choice;
        cin.ignore();

        if(choice == 1){
            encryptMessage(shift);
        }
        else if(choice == 2){
            decryptMessage(shift);
        }
        else if (choice == 3){
            clearMessage();
        }
        else if(choice == 4){
            cout << "\t\tExiting program..." << endl;
            this_thread::sleep_for(chrono::seconds(3));
            system("clear");
            break;
        }
        else{
            cout << endl << "\t\tInvalid option!" << endl;
            this_thread::sleep_for(chrono::seconds(2));
            system("clear");
            main();
        }
    }

    return 0;
}