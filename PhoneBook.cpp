//This Code Belongs to Ahmed Hossam Khalil
#include <iostream> // The Main Library
#include <vector> //The Library That Called when i use the Vector
#include <iterator> // The Library That Called when i use the iterator
#include <fstream>  // The Library That Called when i use the file stream
#include <iomanip> // The Library That Called when i Need to Handling The output
#include <windows.h> // The Library That Called in Function Call
#include <utility>  // The Library That Called when i use Pair

using namespace std ;

class Duration{
public:
    int minutes , seconds ;
public:
    Duration(int minutes = 0, int seconds = 0 ){
        this -> minutes = minutes ;
        this -> seconds = seconds ;
    }
};

class Contact {     //Member Data
public:
    int id ;
    string name , phone ;
    //Member Function
public:
    Contact(int id = 0, string name = "", string phone = ""){      //Constructor
        this -> id = id ;
        this -> name = name ;
        this -> phone = phone ;
    }
    void Show_contact(){        //Function Definition
        cout << "*****************************************************************\n" ;
        cout << "||ID||.........|| Name ||.........|| Phone.No ||\n" ;
        cout << "*****************************************************************\n" ;
        cout << "  " << id << setw(23) <<  name << setw(21) << phone << "\n" ;
    }
    string lower_case(string word){
        for(int i = 0 ; i < word.size() ; i++) {
            (word[i] >= 65 && word[i] <= 90 ? word[i] += 32 : word[i] += 0);
        }
        return word ;
    }
    bool Find(string word){
        word = lower_case(word) ;
        return lower_case(name).find(word) != string::npos;
    }
    bool Find_phone(string word){
        return lower_case(phone).find(word) != string::npos;
    }
};

class Call_log{
public:
    pair <Contact , Duration> call;
    Call_log(Contact C1 , Duration Time){
        call.first = C1 , call.second = Time ;
    }
    void Show_log(){
        cout << "  " << call.first.id << setw(23) << call.first.name << setw(21) << call.first.phone;
        cout << setw(16) << (call.second.minutes < 10 ? "0" : "" ) << call.second.minutes ;
        cout << ":"  << (call.second.seconds < 10 ? "0" : "" ) << call.second.seconds << "\n";
    }
};

class PhoneBook_System{    //Class Definition
    //Member Data
    vector <Contact> contacts ; vector <Call_log> log ;
public:
    bool End = false ;
    //Member Function
    PhoneBook_System(){
        input_Contacts() , input_Calls() ;
    }
    ~PhoneBook_System(){
        update_Contacts() , update_Calls() ;
    }
    void input_Contacts(){
        ifstream input_Contacts("Contacts.txt") ;
        int id ; string name , phone ;
        while(input_Contacts >> id >> name >> phone) {
            for(int i = 0 ; i < name.size() ; i++)
                if(name[i] == '*') name[i] = ' ' ;
            contacts.emplace_back(id ,name,phone) ;
        }
    }
    void input_Calls() {
        ifstream input_Calls("Calls.txt");
        int id, minutes, seconds; string name, phone ; char c ;
        while (input_Calls >> id >> name >> phone >> minutes >> c >> seconds) {
            for(int i = 0 ; i < name.size() ; i++)
                if(name[i] == '*') name[i] = ' ' ;
            log.emplace_back(Contact(id, name, phone), Duration(minutes, seconds));
        }
    }
    void update_Contacts(){
        ofstream output_Contacts("Contacts.txt") ;
        for(int i = 0 ; i < contacts.size() ; i++){
            for(int j = 0 ; j < contacts[i].name.size() ; j++)
                if (contacts[i].name[j] == ' ') contacts[i].name[j] = '*' ;
            output_Contacts << "  " << contacts[i].id  << setw(23) << contacts[i].name << setw(21) << contacts[i].phone << "\n" ;
        }
    }
    void update_Calls(){
        ofstream output_Calls("Calls.txt") ;
        for(int i = 0 ; i < log.size() ; i++){
            for(int j = 0 ; j < log[i].call.first.name.size() ; j++)
                if (log[i].call.first.name[j] == ' ') log[i].call.first.name[j] = '*' ;
            output_Calls << "  " << log[i].call.first.id << setw(23) << log[i].call.first.name << setw(21) << log[i].call.first.phone;
            output_Calls << setw(12) << log[i].call.second.minutes ;
            output_Calls << ':' << log[i].call.second.seconds << "\n";
        }
    }
    void Swap_Contacts(){
        for(int i = 0 ; i < contacts.size() ; i++)
            for(int j = 0 ; j < contacts.size() ; j++)
                if(lower(contacts[i].name) < lower(contacts[j].name) && i != j)
                    swap(contacts[i] , contacts[j]) ;
    }
    string lower(string name){
        for(int i = 0 ; i < name.size() ; i++){
            if(name[i] >= 'A' && name[i] <= 'Z'){
                name[i] += 32 ;
            }
        }
        return name ;
    }
    void New_Contact(){  //Function to Add New Contact
        system("cls");
        cout << "*****************************************************************\n" ;
        int id, i = 0 ; bool Add = false , Same = false ; string name ,phone ;
        cout << "Enter your New Contact's Name: " ; getline(cin,name) ,getline(cin,name);
        cout << "Enter your New Contact's Phone: " ;  cin >> phone ;
        id = contacts.size() + 1 ;
        for(int k = 0 ; k < name.size() ; k++) {
            if (name[0] >= 97 && name[0] <= 122) {
                name[0] -= 32;
                continue;
            }
            if (name[k] == ' ') {
                if (name[k + 1] >= 97 && name[k + 1] <= 122) name[k + 1] -= 32;
            }
        }
        Contact C1(id,name,phone) ;
        for(int j = 0 ; j < contacts.size() ;j++){
            if(lower(contacts[j].phone) == lower(phone)){
                Same = true ;
                break ;
            }
        }
        if(Same){
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! ... There is a Contact Matched with this Number\n";
            Try:
            cout << "*****************************************************************\n" ;
            cout << "1 -> Try Again\n";
            cout << "2 -> Return To Main Menu\n";
            cout << "*****************************************************************\n" ;
            cout << "Enter Your Choice: " ;
            int Choice_a ;  cin >> Choice_a ;
            if(Choice_a == 1) New_Contact() ;
            else if (Choice_a == 2) Interface() ;
            else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! ... Try Again\n";
                goto Try ;
            }
        }
        for(auto it = contacts.begin() ; it != contacts.end() ; it++ , i++) {
            if (it -> name > name or i == contacts.size()) {
                auto it = contacts.insert(contacts.begin() + i , C1);
                Add = true ;    break;
            }
        }
        if (!Add) contacts.push_back(C1) ;
        for(int j = 0 ; j < contacts.size() ; j++){
            contacts[j].id = j + 1 ;
        }
        for(int j = 0 ; j < log.size() ;j++){
            if(log[j].call.first.phone == phone){
                log[i].call.first.name = name ;
                break ;
            }
        }
        cout << "*****************************************************************\n" ;
        cout << "New Contact Added\n";
        Again_add :
        cout << "*****************************************************************\n" ;
        cout << "Do You Want to Add another Contact (Yes or No): " ;
        string yes_no_Add ;
        cin >> yes_no_Add ;
        if(lower(yes_no_Add) == "yes"){
            New_Contact() ;
        }else if(lower(yes_no_Add) == "no"){
            Interface() ;
        }else {
            cout << "Not Valid! .. Try Again\n" ;
            goto Again_add ;
        }
    }
    void Search_ByName(){   //Function to Search For Contact By Using Name
        system("cls");
        cout << "*****************************************************************\n" ;
        bool is_Found = false , Duplicated = false ; string name ;
        cout << "Enter Your Contact's Name that you want to Search: " ;
        getline(cin,name),getline(cin,name) ;
        for(int it = 0 ; it < contacts.size() ; it++){
            if (lower(contacts[it].name) == lower(name) || contacts[it].Find(name)){
                is_Found = true ;
                if(!Duplicated) {
                    contacts[it].Show_contact() ;
                    Duplicated = true ;
                }else
                    cout << "  " << contacts[it].id << setw(23) << contacts[it].name << setw(21) << contacts[it].phone << "\n" ;
            }
        }
        if(!is_Found) {
            cout << "*****************************************************************\n" ;
            cout << "No Contact Found with this Name\n";
            Try:
            cout << "*****************************************************************\n" ;
            cout << "1 -> Try Again\n";
            cout << "2 -> Return To Main Menu\n";
            cout << "*****************************************************************\n" ;
            cout << "Enter Your Choice: " ;
            int Choice_sn ; cin >> Choice_sn ;
            if(Choice_sn == 1) Search_ByName() ;
            else if (Choice_sn == 2) Interface() ;
            else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! ... Try Again\n";
                goto Try ;
            }
        }
        Again_SN :
        cout << "*****************************************************************\n" ;
        cout << "Do You Want to Search for another Contact (Yes or No): " ;
        string yes_no_SN ;
        cin >> yes_no_SN ;
        if(lower(yes_no_SN) == "yes"){
            Search_ByName() ;
        }else if(lower(yes_no_SN) == "no"){
            Interface() ;
        }else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! .. Try Again\n" ;
            goto Again_SN ;
        }
    }
    void Search_ByID(){     //Function to Search For Contact By Using ID
        system("cls");
        cout << "*****************************************************************\n" ;
        int id ;
        cout << "Enter your Contact's ID that you want to Search: " ;
        cin >> id ;
        if (id - 1 >= contacts.size() || id - 1 < 0 ) {
            cout << "*****************************************************************\nNo Contact Found with this ID\n";
            Try:
            cout << "*****************************************************************\n" ;
            cout << "1 -> Try Again\n";
            cout << "2 -> Return To Main Menu\n";
            cout << "*****************************************************************\n" ;
            cout << "Enter Your Choice: " ;
            int Choice_id ; cin >> Choice_id;
            if(Choice_id == 1) Search_ByID() ;
            else if (Choice_id == 2) Interface() ;
            else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! ... Try Again\n";
                goto Try ;
            }
        }else {
            contacts[id - 1].Show_contact() ;
        }
        Again_SID :
        cout << "*****************************************************************\n" ;
        cout << "Do You Want to Search for another Contact (Yes or No): " ;
        string yes_no_SID ;
        cin >> yes_no_SID ;
        if(lower(yes_no_SID) == "yes"){
            Search_ByID() ;
        }else if(lower(yes_no_SID) == "no"){
            Interface() ;
        }else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! .. Try Again\n" ;
            goto Again_SID ;
        }
    }
    void Search_ByPhone(){      //Function to Search For Contact By Using Phone
        system("cls");
        cout << "*****************************************************************\n" ;
        bool is_Found = false, Duplicated = false;
        string phone;
        cout << "Enter Your Contact's Phone that you want to Search: ";
        cin >> phone ;
        for (int it = 0; it < contacts.size(); it++) {
            if (contacts[it].phone == phone || contacts[it].Find_phone(phone)) {
                is_Found = true;
                if (!Duplicated) {
                    contacts[it].Show_contact();
                    Duplicated = true;
                } else
                    cout << "  " << contacts[it].id << setw(23) << contacts[it].name << setw(21) << contacts[it].phone << "\n";
            }
        }
        if (!is_Found){
            cout << "*****************************************************************\nNo Contact Found with this Phone No.\n";
            Try:
            cout << "*****************************************************************\n" ;
            cout << "1 -> Try Again\n";
            cout << "2 -> Return To Main Menu\n";
            cout << "*****************************************************************\n" ;
            cout << "Enter Your Choice: " ;
            int Choice_sp ; cin >> Choice_sp ;
            if(Choice_sp == 1) Search_ByPhone() ;
            else if (Choice_sp == 2) Interface() ;
            else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! ... Try Again\n";
                goto Try ;
            }
        }
        Again_SP :
        cout << "*****************************************************************\n" ;
        cout << "Do You Want to Search for another Contact (Yes or No): " ;
        string yes_no_SB ;  cin >> yes_no_SB ;
        if(lower(yes_no_SB) == "yes"){
            Search_ByPhone() ;
        }else if(lower(yes_no_SB) == "no"){
            Interface() ;
        }else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! .. Try Again\n" ;
            goto Again_SP ;
        }
    }
    void Modify_Contact(){      //Function that Modify a contact
        bool is_Found = false ,Same = false ;
        string Name , modified_name , modified_phone , choice_modify , Phone ;
        int Id ,Press_modify;
        system("cls");
        cout << "*****************************************************************\n" ;
        show_allContact();
        cout << "*****************************************************************\n" ;
        cout << "1 -> Choose a Contacts that you want Edit with ID:\n" ;
        cout << "2 -> Choose a Contacts that you want Edit with Name:\n" ;
        cout << "3 -> Choose a Contacts that you want Edit with Phone No.:\n" ;
        cout << "4 -> Return to The Main menu\n" ;
        cout << "*****************************************************************\n" ;
        cout << "Press The Number That You want: " ;
        cin >> Press_modify ;
        system("cls");
        cout << "*****************************************************************\n" ;
        if(Press_modify == 1){
            cout << "Enter ID of The Contact that you want to Modify:";
            cin >> Id;
        } else if (Press_modify == 2){
            cout << "Enter Name of The Contact that you want to Modify:";
            getline(cin,Name) ,getline(cin,Name);
        } else if (Press_modify == 3){
            cout << "Enter Phone No. of The Contact that you want to Modify:";
            cin >> Phone ;
        }else if (Press_modify == 4) system("cls"),Interface() ;
        else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! ... Try Again\n" ;
            cout << "*****************************************************************\n" ;
            system("pause");
            Modify_Contact() ;
        }
        cout << "*****************************************************************\n" ;
        system("cls");
        cout << "*****************************************************************\n" ;
        for(int it = 0 ; it < contacts.size() ; it++){
            if (lower(contacts[it].name) == lower(Name) || contacts[it].phone == Phone || it + 1 == Id){
                is_Found = true ;
                cout << "1 -> Edit The Contact's Name: \n" ;
                cout << "2 -> Edit The Contact's Phone No: \n" ;
                cout << "3 -> Edit Both of The Contact's Name & Phone No: \n" ;
                cout << "4 -> Return Main Menu\n";
                cout << "*****************************************************************\n" ;
                cout << "Press The Number That You want: " ;
                int press_mod ;      cin >> press_mod;
                system("cls");
                cout << "*****************************************************************\n" ;
                if(press_mod == 1){
                    cout << "Enter The New Name of The Contact: " ;
                    getline(cin,modified_name),getline(cin,modified_name) ;
                }else if (press_mod == 2){
                    cout << "Enter The New Phone No. of The Contact: ";
                    cin >> modified_phone ;
                }else if (press_mod == 3){
                    cout << "Enter Contact's New Information\n" ;
                    cout << "*****************************************************************\n" ;
                    cout << "Enter The New Name of The Contact: " ;   getline(cin,modified_name),getline(cin,modified_name) ;
                    cout << "Enter The New Phone No. of The  Contact: " ;   cin >> modified_phone ;
                }else if (press_mod == 4) system("cls") ,Interface();
                else {
                    cout << "Not Valid! ... Try Again\n";
                    cout << "*****************************************************************\n" ;
                    system("pause");
                    Modify_Contact() ;
                }
                for(int k = 0 ; k < modified_name.size() ; k++) {
                    if (modified_name[0] >= 97 && modified_name[0] <= 122) {
                        modified_name[0] -= 32;
                        continue;
                    }
                    if (modified_name[k] == ' ') {
                        if (modified_name[k + 1] >= 97 && modified_name[k + 1] <= 122) modified_name[k + 1] -= 32;
                    }
                }
                Contact C1(it + 1 ,modified_name,modified_phone) ;
                for(int j = 0 ; j < contacts.size() ;j++){
                    if(contacts[j].phone == modified_phone){
                        Same = true ;
                        break ;
                    }
                }
                if(press_mod != 1) {
                    if (Same) {
                        cout << "*****************************************************************\n" ;
                        cout << "Not Valid! ... There is a Contact Matched with this Number\n";
                        Try:
                        cout << "*****************************************************************\n" ;
                        cout << "1 -> Try Again\n";
                        cout << "2 -> Return To Main Menu\n";
                        cout << "*****************************************************************\n" ;
                        cout << "Enter Your Choice: " ;
                        int Choice_sn ;  cin >> Choice_sn ;
                        if(Choice_sn == 1) Modify_Contact() ;
                        else if (Choice_sn == 2) Interface() ;
                        else {
                            cout << "*****************************************************************\n" ;
                            cout << "Not Valid! ... Try Again\n";
                            goto Try ;
                        }
                    }
                }
                contacts[it].Show_contact() ;
                Choice:
                cout << "*****************************************************************\n";
                cout << "The Contact that you choose it will be Modified\n" ;
                cout << "*****************************************************************\n" ;
                cout << "Yes or No: " ;  cin >> choice_modify ;
                if(lower(choice_modify) == "yes") {
                    for(int i = 0 ; i < log.size() ;i++){
                        if((press_mod == 2 || press_mod == 3) && log[i].call.first.phone == contacts[it].phone){
                            Contact C2 (contacts.size() + 1,"UnKnown",contacts[it].phone) ;
                            log[i].call.first = C2 ;
                        }
                        if(log[i].call.first.phone == contacts[it].phone && log[i].call.first.name != C1.name && press_mod == 1){
                            Contact C2 (contacts.size() + 1, modified_name, contacts[it].phone);
                            log[i].call.first = C2 ;
                        }
                    }
                    if (press_mod == 1)  contacts[it].name = modified_name ;
                    else if (press_mod == 2) contacts[it].phone = modified_phone ;
                    else if (press_mod == 3) contacts[it] = C1 ;
                    cout << "*****************************************************************\n" ;
                    cout << "The Contact Modified\n" ;
                    Swap_Contacts() ;
                    for(int i = 0 ; i < contacts.size() ; i++){
                        contacts[i].id = i + 1 ;
                    }
                    Again_Modify :
                    cout << "*****************************************************************\n" ;
                    cout << "Do You Want to Edit another Contact (Yes or No): " ;
                    string yes_no_modified ;  cin >> yes_no_modified ;
                    if(lower(yes_no_modified) == "yes"){
                        Modify_Contact() ;
                    }else if(lower(yes_no_modified) == "no"){
                        Interface() ;
                    }else {
                        cout << "*****************************************************************\n" ;
                        cout << "Not Valid! .. Try Again\n" ;
                        goto Again_Modify ;
                    }
                }else if(lower(choice_modify) == "no") {
                        Interface() ;
                }else{
                     cout << "Not Valid! ... Try Again\n" ;
                    cout << "*****************************************************************\n" ;
                    system("pause");
                    goto Choice ;
                }
                break ;
            }
        }
        if(!is_Found) {
            system("cls");
            cout << "*****************************************************************\nNo Contact Matched! ... Try Again\n" ;
            cout << "*****************************************************************\n";
            system("pause") ;
            Modify_Contact();
        }
    }
    void Delete_Contact(){      //Function That Delete Contact by using iterator
        string Name , Phone; bool is_Found = false ; int Id , Press_Delete , counter = 0 ;
        system("cls");
        cout << "*****************************************************************\n" ;
        show_allContact() ;
        cout << "*****************************************************************\n" ;
        cout << "1 -> Choose a Contacts that you want Delete with ID:\n" ;
        cout << "2 -> Choose a Contacts that you want Delete with Name:\n" ;
        cout << "3 -> Choose a Contacts that you want Delete with Phone No.:\n" ;
        cout << "4 -> Return to The Main menu:\n " ;
        cout << "*****************************************************************\n" ;
        cout << "Press The Number That You want: " ;
        cin >> Press_Delete ;
        system("cls");
        cout << "*****************************************************************\n" ;
        if(Press_Delete == 1){
            cout << "Enter ID of The Contact that you want to Delete:";
            cin >> Id;
        } else if (Press_Delete == 2){
            cout << "Enter Name of The Contact that you want to Delete:";
            getline(cin,Name),getline(cin,Name) ;
        } else if (Press_Delete == 3){
            cout << "Enter Phone No. of The Contact that you want to Delete:";
            cin >> Phone ;
        }else if (Press_Delete == 4) system("cls"),Interface() ;
        else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid ... Try Again\n" ;
            cout << "*****************************************************************\n" ;
            system("pause");
            Delete_Contact();
        }
        for(auto it = contacts.begin(); it != contacts.end() ; it++ , counter++) {
            if (lower(it->name) == lower(Name) || it->phone == Phone || counter + 1 == Id) {
                is_Found = true;
                it-> Show_contact() ;
                Choice:
                cout << "*****************************************************************\n";
                cout << "The Contact that you choose it will be Deleted\n";
                cout << "*****************************************************************\n";
                cout << "Yes or No: ";
                string choice;
                cin >> choice;
                if (lower(choice) == "yes") {
                    cout << "*****************************************************************\n";
                    cout << "The Contact Deleted\n";
                    for(int i = 0 ; i < log.size() ; i++){
                        if(log[i].call.first.phone == contacts[counter].phone){
                            Contact C1 (contacts.size() + 1,"UnKnown",contacts[counter].phone) ;
                            log[i].call.first = C1 ;
                        }
                    }
                    contacts.erase(it);
                    Again_Delete :
                    cout << "*****************************************************************\n" ;
                    cout << "Do You Want to Delete another Contact (Yes or No): " ;
                    string yes_no_Delete ;
                     cin >> yes_no_Delete ;
                    if(lower(yes_no_Delete) == "yes"){
                        Delete_Contact() ;
                    }else if(lower(yes_no_Delete) == "no"){
                    }else {
                        cout << "*****************************************************************\n" ;
                        cout << "Not Valid! .. Try Again\n" ;
                        goto Again_Delete ;
                    }
                    break;
                } else if (lower(choice) == "no") {
                    Interface() ;
                } else {
                    cout << "*****************************************************************\n";
                    cout << "Not Valid! ... Try Again\n";
                    cout << "*****************************************************************\n";
                    system("pause");
                    goto Choice;
                }
            }
        }
        for(int i = 0 ; i < contacts.size() ; i++){
            contacts[i].id = i + 1 ;
        }
        if(!is_Found){
            cout << "*****************************************************************\n" << "No Contact Matched! ... Try Again\n" ;
            Try:
            cout << "*****************************************************************\n" ;
            cout << "1 -> Try Again\n";
            cout << "2 -> Return To Main Menu\n";
            cout << "*****************************************************************\n" ;
            cout << "Enter Your Choice: " ;
            int Choice_sn ;  cin >> Choice_sn ;
            if(Choice_sn == 1) Delete_Contact() ;
            else if (Choice_sn == 2) Interface() ;
            else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! ... Try Again\n";
                goto Try ;
            }
        }
    }
    void show_allContact() {        //Function That Display All Contacts
        if (contacts.empty()) {
            cout << "No Contacts Found!\n";
        } else {
            cout << "Information About All Contact is: \n";
            cout << "*****************************************************************\n" ;
            cout << "||ID||.........|| Name ||.........|| Phone.No ||\n" ;
            cout << "*****************************************************************\n" ;
            for (int it = 0; it < contacts.size(); it++) {
                cout << "  " << contacts[it].id << setw(23) << contacts[it].name << setw(21) << contacts[it].phone << "\n" ;
            }
        }
    }
    void Delete_Contacts(){     //Function That Delete All Contact
        system("cls");
        cout << "*****************************************************************\n" ;
        cout << "You Are About Delete All The Contacts\n" ;
        cout << "*****************************************************************\n" ;
        cout << "Yes or No: ";   string choice ;  cin >> choice ;
        if(lower(choice) == "yes") {
            contacts.clear();
            for(int i = 0 ; i < log.size() ; i++){
                log[i].call.first.name = "Un Known" ;
            }
            cout << "*****************************************************************\n" ;
            cout << "All Contacts Deleted\n";
        }else if (lower(choice) != "no"){
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! ... Try Again\n";
            cout << "*****************************************************************\n" ;
            system("pause");
            Delete_Contacts();
        }
    }
    void call() {
        system("cls");
        cout << "*****************************************************************\n" ;
        string choice_Call ;  int Press_Call ;   bool same = false ;
        Contact C1 ;
        cout << "1 -> Call a Number:\n";
        cout << "2 -> Call a contact with the Name: \n" ;
        cout << "3 -> Return to The Main Menu: \n";
        cout << "*****************************************************************\n" ;
        cout << "Press the Number that you want to Do: ";
        cin >> Press_Call ;
        system("cls");
        cout << "*****************************************************************\n" ;
        if (Press_Call == 1 || Press_Call == 2) {
            if (Press_Call == 1) {
                cout << "Enter The Number That you want to Call: ";
                cin >> choice_Call;
                for(int i = 0 ; i < contacts.size() ; i++){
                    if(contacts[i].phone == choice_Call){
                        C1 = contacts[i] ;
                        same = true ;
                    }
                }
                if(!same) {
                    Contact C2(contacts.size() + 1, "UnKnown", choice_Call);
                    C1 = C2;
                }
            }
            else if (Press_Call == 2) {
                cout << "Enter Name of The Contact that you want to Call: ";
                getline(cin,choice_Call),getline(cin,choice_Call);
                bool is_Found = false;
                for (int i = 0; i < contacts.size(); i++) {
                    if (lower(contacts[i].name) == lower(choice_Call)) {
                        is_Found = true, same = true ;
                        C1 = contacts[i] ;
                    }
                }
                if (!is_Found) {
                    cout << "*****************************************************************\n" ;
                    cout << "No Contact Found!\n";
                    Try:
                    cout << "*****************************************************************\n" ;
                    cout << "1 -> Try Again\n";
                    cout << "2 -> Return To Main Menu\n";
                    cout << "*****************************************************************\n" ;
                    cout << "Enter Your Choice: " ;
                    int Choice_sn ;  cin >> Choice_sn ;
                    if(Choice_sn == 1) call() ;
                    else if (Choice_sn == 2) Interface() ;
                    else {
                        cout << "*****************************************************************\n" ;
                        cout << "Not Valid! ... Try Again\n";
                        goto Try ;
                    }
                }
            }
        }else if (Press_Call == 3) Interface();
        else {
            cout << "Not Valid! ... Try Again\n";
            system("pause") ;
            call() ;
        }
        cout << "*****************************************************************\n" ;
        cout << "Hit 'Enter' to start The Call with " << (same ? C1.name : choice_Call) << "\n" ;
        cout << "Hit 'ESC' to stop The Call with " << (same ? C1.name : choice_Call) << "\n" ;
        cout << "*****************************************************************\n" ;
            cin.get();
            unsigned int seconds = 0;
            unsigned int minutes = 0;
            while (!GetAsyncKeyState(0x1B)) {
                seconds++;
                if (seconds == 60) {
                    seconds = 0;
                    minutes++;
                }
                Sleep(1000);
            }
            cout << "The Duration of The Call with " << (same ? C1.name : choice_Call) << " is: " ;
            cout << (minutes < 10 ? "0" : "" ) << minutes << ":" << (seconds < 10 ? "0" : "" ) << seconds << "\n";
            Duration Time(minutes,seconds);
            Call_log log1(C1,Time) ;
            log.push_back(log1) ;
            Again_Call :
            cout << "*****************************************************************\n" ;
            cout << "Do You Want to Make another Call (Yes or No): " ;
            string yes_no_c ;  cin >> yes_no_c ;
            if(lower(yes_no_c) == "yes"){
                call() ;
            }else if(lower(yes_no_c) == "no"){
                Interface() ;
            }else {
                cout << "*****************************************************************\n" ;
                cout << "Not Valid! .. Try Again\n" ;
                goto Again_Call ;
            }
        }
    void Show_Call_log(){
        system("cls") ;
        if(!log.empty()){
            for(int i = 0 ; i < log.size() ; i++){
                log[i].call.first.id = i + 1 ;
            }
            cout << "**************************************************************************\n" ;
            cout << "||ID||.........|| Name ||.........|| Phone.No ||.........|| Duration ||\n" ;
            cout << "**************************************************************************\n" ;
            for(int i = 0 ; i < log.size() ; i++){
                log[i].Show_log() ;
            }
            cout << "**************************************************************************\n\n" ;
        }else{
            cout << "*****************************************************************\nNo Calls Found!\n";
            cout << "*****************************************************************\n" ;
            system("pause");
            Interface() ;
        }
    }
    void Send_Message(){
        system("cls");
        cout << "*****************************************************************\n" ;
        string choice_message ; int Press_Message;   bool same = false ;
        cout << "1 -> Send a Message to any Number:\n";
        cout << "2 -> Send a Message to a contact with the Name: \n" ;
        cout << "3 -> Return to The Main Menu: \n";
        cout << "*****************************************************************\n" ;
        cout << "Press the Number that you want to Do: ";
        cin >> Press_Message ;
        system("cls");
        cout << "*****************************************************************\n" ;
        if (Press_Message == 1 || Press_Message == 2) {
            if (Press_Message == 1) {
                cout << "Enter The Number That you want to send a Message: ";
                cin >> choice_message;
                } else if (Press_Message == 2) {
                cout << "Enter Name of The Contact that you want to send a Message: ";
                getline(cin,choice_message) ,getline(cin,choice_message);
                bool is_Found = false;
                for (int i = 0; i < contacts.size(); i++) {
                    if (lower(contacts[i].name) == lower(choice_message)) {
                        is_Found = true;
                    }
                }
                if (!is_Found) {
                    cout << "*****************************************************************\n" ;
                    cout << "No Contact Found With This Name\n";
                    Try:
                    cout << "*****************************************************************\n" ;
                    cout << "1 -> Try Again\n";
                    cout << "2 -> Return To Main Menu\n";
                    cout << "*****************************************************************\n" ;
                    cout << "Enter Your Choice: " ;
                    int Choice_sn ;  cin >> Choice_sn ;
                    if(Choice_sn == 1) Send_Message() ;
                    else if (Choice_sn == 2) Interface() ;
                    else {
                        cout << "*****************************************************************\n" ;
                        cout << "Not Valid! ... Try Again\n";
                        goto Try ;
                    }
                }
            }
        }else if (Press_Message == 3) system("cls"),Interface();
        else {
            cout << "Not Valid ... Try Again\n";
            cout << "*****************************************************************\n" ;
            system("pause");
            Send_Message() ;
        }
        system("cls");
        cout << "*****************************************************************\n" ;
        cout << "Enter The Message that you want to send:\n";
        cout << "*****************************************************************\n" ;
        string Message ;
        if(Press_Message == 1) getline(cin,Message) ;
        getline(cin,Message) ;
        cout << "*****************************************************************\n" ;
        cout << "Message Sent!\n" ;
        Again_Message :
        cout << "*****************************************************************\n" ;
        cout << "Do You Want to Send another Message (Yes or No): " ;
        string yes_no_m ;  cin >> yes_no_m ;
        if(lower(yes_no_m) == "yes"){
            Send_Message() ;
        }else if(lower(yes_no_m) == "no"){
            Interface() ;
        }else {
            cout << "*****************************************************************\n" ;
            cout << "Not Valid! .. Try Again\n" ;
            goto Again_Message ;
        }
    }
    void Delete_Call_log() {
        if(log.empty()) {
            system("cls");
            cout << "*****************************************************************\n";
            cout << "No Call Found!\n", Interface();
        }
        system("cls");
        cout << "*****************************************************************\n";
        cout << "You Are About Delete The Call Log\n";
        cout << "*****************************************************************\n";
        cout << "Yes or No: ";
        string yes_no_dl;
        cin >> yes_no_dl;
        if (lower(yes_no_dl) == "yes") {
            log.clear();
            cout << "*****************************************************************\n";
            cout << "Call Log Deleted\n";
        } else if (lower(yes_no_dl) == "no") {
            system("cls");
            Interface();
        } else {
            cout << "Not Valid! ... Try Again\n";
            cout << "*****************************************************************\n";
            system("pause");
            Delete_Call_log();
        }
    }
    void Interface(){      //The Interface of The Program
        system("color f6");
        system("cls") ;
        cout << "*****************************************************************\n" ;
        cout << "************************|| Phone Book ||*************************\n" ;
        cout << "1 -> Display All The Contacts\n" ;
        cout << "2 -> Add\n" ;
        cout << "3 -> Search\n" ;
        cout << "4 -> Delete\n" ;
        cout << "5 -> Edit\n" ;
        cout << "6 -> Call\n" ;
        cout << "7 -> Send a Message\n" ;
        cout << "8 -> Exit\n" ;
        cout << "*****************************************************************\n" ;
        cout << "Press the Number that you want to Do: ";
        int main_key ;
        cin >> main_key ;
        system("cls");
        cout << "*****************************************************************\n" ;
        if (main_key == 1) show_allContact() ;
        else if (main_key == 2) New_Contact();
        else if (main_key == 3){
            Again:
            system("cls");
            if (!contacts.empty()) {
                int search_choice;
                cout << "*****************************************************************\n";
                cout << "1 -> Search A Contact By ID\n";
                cout << "2 -> Search A Contact By Name\n";
                cout << "3 -> Search A Contact By Phone.No\n";
                cout << "4 -> Return to The Main Menu\n";
                cout << "*****************************************************************\n";
                cout << "Press The Number of The Way that You Want to Search By it: ";
                cin >> search_choice ;
                cout << "*****************************************************************\n";
                if (search_choice == 1) Search_ByID();
                else if (search_choice == 2) Search_ByName();
                else if (search_choice == 3) Search_ByPhone();
                else if (search_choice == 4) Interface();
                else {
                    cout << "Not Valid ... Try Again\n";
                    cout << "*****************************************************************\n";
                    system("pause");
                    goto Again;
                }
            } else {
                cout << "*****************************************************************\n" ;
                cout << "No Contacts Found!\n";
                cout << "*****************************************************************\n" ;
                system("pause");
                Interface() ;
            }
        }else if (main_key == 4) {
            Again_2:
            system("cls");
            cout << "*****************************************************************\n" ;
            if (!contacts.empty()) {
                int delete_choice;
                cout << "1 -> Delete a Contact\n";
                cout << "2 -> Delete All The Contacts\n";
                cout << "3 -> Return to The Main Menu\n";
                cout << "*****************************************************************\n" ;
                cout << "Press The Number that you Want: ";
                cin >> delete_choice ;
                cout << "*****************************************************************\n" ;
                if (delete_choice == 1) Delete_Contact();
                else if (delete_choice == 2) Delete_Contacts();
                else if (delete_choice == 3) system("cls"),Interface();
                else {
                    cout << "Not Valid! ... Try Again\n";
                    cout << "*****************************************************************\n" ;
                    system("pause");
                    goto Again_2 ;
                }
            }else {
                cout << "No Contacts Found!\n" ;
                cout << "*****************************************************************\n" ;
                system("pause");
                Interface() ;
            }
        }
        else if (main_key == 5) {
            if(!contacts.empty()) {
                Modify_Contact();
            }else cout << "No Contacts Found!\n" ;
        }
        else if (main_key == 6) {
         Again_3 :
         system("cls");
         cout << "*****************************************************************\n" ;
         cout << "1 -> Make a Call\n";
         cout << "2 -> Display Call Log\n" ;
         cout << "3 -> Delete Call Log\n" ;
         cout << "4 -> Return to The Main Menu\n" ;
         cout << "*****************************************************************\n" ;
         cout << "Press The Number that you Want: ";
         int call_choice ; cin >> call_choice ;
         system("cls");
         cout << "*****************************************************************\n" ;
         if(call_choice == 1) call() ;
         else if (call_choice == 2) {
             Show_Call_log() ;
             system("pause");
             Interface() ;
         }
         else if (call_choice == 3) Delete_Call_log() ;
         else if (call_choice == 4) Interface();
         else {
             cout << "*****************************************************************\nNot Valid! ... Try Again\n";
             cout << "*****************************************************************\n" ;
             system("pause");
             goto Again_3 ;
         }
        }
        else if (main_key == 7) Send_Message();
        else if (main_key == 8)  {
            End = true ;
            system("cls");
            cout << "*****************************************************************\n" ;
            cout << "Contact Us\n" ;
            cout << "*****************************************************************\n" ;
            cout << "Name: Ahmed HoSSam\n" ;
            cout << "Phone No: 01208822340\n" ;
            cout << "*****************************************************************\n" ;
            cout << " ######                \n"
                    "##    ##     ##       ##   \n"
                    "##           ##       ##   \n"
                    "##         ######   ###### \n"
                    "##           ##       ##   \n"
                    "##    ##     ##       ##   \n"
                    " ######                \n" ;
            cout << "*****************************************************************\n" ;
            update_Contacts(),update_Calls() ;
            exit(0);
        }
        else cout << "Not Valid ... Try Again\n" ;
        cout << "*****************************************************************\n" ;
        system("pause");
        Interface() ;
    }
};

int main(){
    system("color f7") ;
    PhoneBook_System PhoneBook ;
    while(!PhoneBook.End){
        PhoneBook.Interface() ;
    }
} //Thnak You ♥♥
