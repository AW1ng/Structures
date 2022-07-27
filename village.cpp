#include <iostream>
#include <vector>
using namespace std;


vector<string> Split(string Data, string Delimiter=" ") {
    //cout<<"\nSplitting string: >"<<Data<<"< by delimiter >"<<Delimiter<<"<\n";
    vector<string> result;
    string CurrSubs;
    auto start = 0U;
    auto end = Data.find(Delimiter);
    while (end != string::npos) {
        CurrSubs = Data.substr(start, end - start);
        //cout<<CurrSubs<<endl;
        result.push_back(CurrSubs);
        start = end + Delimiter.length();
        end = Data.find(Delimiter, start);
        }
    CurrSubs = Data.substr(start, end - start);
    //cout<<CurrSubs<<endl;
    //cout << Data.substr(start, end);
    result.push_back(CurrSubs);
    return result;
    }

struct Room {
    bool HasFirePlace;
    enum Room_purpose { BATH, LIVING, CHILDREN, KITCHEN, UNKNOWN } Purpose;
    string to_str() {
        string result = "";
        switch( Purpose ) {
            case BATH:
                result += "[Bathroom";break;
            case LIVING:
                result += "[Livingroom";break;
            case CHILDREN:
                result += "[Childroom";break;
            case KITCHEN:
                result += "[Kitchen";break;
            default:
                result += "[";break;
            }
        if( HasFirePlace ) result += " has fireplace]";
        else result += "]";
        return result;
        }
    
    void from_str(string info) {
        string result = "";
        switch( info[0] ) {
            case 'B':
                Purpose = BATH;break;
            case 'L':
                Purpose = LIVING;break;
            case 'C':
                Purpose = CHILDREN;break;
            case 'K':
                Purpose = KITCHEN;break;
            default:
                Purpose = UNKNOWN;break;
            }
        if( info.length() > 1 ) HasFirePlace = true;
        else HasFirePlace = false;
        }
    };
/*
struct Floor {
    vector<Room> Rooms;
    int Level;
    void add_room(string room) {
        Room temproom;
        temproom.from_str(room);
        Rooms.push_back(temproom);
        }
    string to_str() {
        string result = "[ "+to_string( Level )+":";
        for( int i = 0 ; i < Rooms.size() ; i++ ) result += Rooms[i].to_str();
        return result+" ]";
        }
    void from_str(string info) {
        vector<string> LOther = Split( info, ":" );
        Level = stoi( LOther[0] );
        vector<string> Rooms = Split( LOther[1], "," );
        for ( int i = 0; i < Rooms.size(); i++ ) add_room( Rooms[i] );
        }
    };
*/
struct Floor {
    vector<Room> Rooms;
    enum Floor_Number {ONE, TWO, THREE, UNKNOWN} Level;
    void add_room(string room) {
        Room temproom;
        temproom.from_str(room);
        Rooms.push_back(temproom);
        }
    string to_str() {
        string result;
        switch( Level ) {
            case ONE: result = "[First: "; break;
            case TWO: result = "[Second: "; break;
            case THREE: result = "[Third: "; break;
            default: result = "[ "; break;
            }
        for( int i = 0 ; i < Rooms.size() ; i++ ) result += Rooms[i].to_str();
        return result+" ]";
        }
    void from_str(string info) {
        vector<string> LOther = Split( info, ":" );
        switch( LOther[0][0] ) {
            case '1': Level = ONE; break;
            case '2': Level = TWO; break;
            case '3': Level = THREE; break;
            default: Level = UNKNOWN; break;
            }
        //Level = stoi( LOther[0] );
        vector<string> Rooms = Split( LOther[1], "," );
        for ( int i = 0; i < Rooms.size(); i++ ) add_room( Rooms[i] );
        }
    };

struct Building {
    vector<Floor> Floors;
    string Purpose;
    void add_floor(string floor) {
        Floor tempfloor;
        tempfloor.from_str( floor );
        Floors.push_back( tempfloor );
        }
    string to_str() {
        string result = "{ "+Purpose+".";
        for ( int i = 0 ; i < Floors.size() ; i++ ) result += Floors[i].to_str();
        return result+" }";
        }
    void from_str(string info) {
        vector<string> POther = Split( info, "." );
        Purpose = POther[0];
        vector<string> Floors = Split( POther[1], ";" );
        for ( int i = 0 ; i < Floors.size() ; i++ ) add_floor( Floors[i] );
        }
    };

struct Region {
    vector<Building> Buildings;
    string Purpose;
    void add_building(string building) {
        Building tempbuilding;
        tempbuilding.from_str( building );
        Buildings.push_back( tempbuilding );
        }
    string to_str() {
        string result = "( "+Purpose+"@";
        for ( int i = 0; i < Buildings.size(); i++ ) result += Buildings[i].to_str();
        return result + " )";
        }
    void from_str(string info) {
        vector<string> POther = Split( info, "@" );
        Purpose = POther[0];
        vector<string> Buildings = Split( POther[1], "!" );
        for ( int i = 0 ; i < Buildings.size() ; i++ ) add_building( Buildings[i] );
        }
    };

int main() {
    /*Room testroom;
    testroom.from_str("Z+");
    cout<<testroom.to_str();*/
    /*Floor testfloor;
    testfloor.from_str("3:C,L,K+,B");
    //testfloor.add_room("C"); testfloor.add_room("L"); testfloor.add_room("K+"); testfloor.add_room("B");
    cout<<testfloor.to_str();*/
    /*Building testbuilding;
    testbuilding.from_str("Bordel.1:L,L+,B,B+;2:C,C+;3:K,K+,L,L+");
    cout<<testbuilding.to_str();*/
    
    Region testregion;
    testregion.from_str("Da4a@Bordel.1:L,L+,B,B+;2:C,C+;3:K,K+,L,L+!Banya.1:B+,B!Garage.1:L");
    cout<<testregion.to_str();
/*
    string S = "Mama  myla ramu   ";
    vector<string> SS = Split(S);
    cout<<endl;
    for( int i = 0; i < SS.size() ; i++) cout<<">"<<SS[i]<<"<\n";
*/
    cout<<endl;
    return 0;
}


