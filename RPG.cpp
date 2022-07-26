#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;



int GetRandomInt( int From, int To, bool NeedInit = false) {
	int result;
	if(NeedInit) srand(unsigned(time(0)));
	result = rand() % (To - From  + 1);
	return result;
}


struct Position {
	int Str, Col;
	
	Position Move(char Direction) {
		Position result;
		result.Str = Str;
		result.Col = Col;
		switch( Direction ) {
			case 'h': return result;
			case 'l': 
				result.Col--;
			 	return result;
			case 'r':
				result.Col++;
				return result;
			case 'u':
				result.Str--;
				return result;
			case 'd':
				result.Str++;
				return result;
			
		}
	}
	
};


class Person {
	private:
		static int iCount;
	protected:
		int ID, Health, Armor, Damage;
		string Name;
	public:
		Person(string name, int health, int armor, int damage) {
			if( health > 0 ) Health = health;
			else Health = 1;
			if( armor > 0 ) Armor = armor;
			else Armor = 0;
			if( damage > 0 ) Damage = damage;
			else Damage = 0;
			Name = name;
			ID = iCount++;	
		}
		
		int GetId() { return ID; }
		int GetHealth() { return Health; }
		int GetArmor() { return Armor; }
		int GetDamage() { return Damage; }
		string GetName() { return Name; }
		string ToStr() {
			return to_string(ID) + ": " + Name + " ( HP: " + to_string(Health) + " ARM: " + to_string(Armor) + " DMG: " + to_string(Damage) + " )";
		}
};


class PPerson : public Person {
	protected:
		Position Place;
	public:
		Position GetPlace() {
			return Place;
		}
		
		void SetPlace(Position newPlace) {
			Place = newPlace;
		}
		
		PPerson( Person Chars, Position place) : Person(Chars.GetName(), Chars.GetHealth(), Chars.GetArmor(), Chars.GetDamage() ) {
			ID = Chars.GetId(); 

			Place.Str = place.Str; 
			Place.Col = place.Col;
		}
		char WantGo()  { // 0 - hold  1 - :eft, 2 - down, 3 - up, 4 - right
			int dice = GetRandomInt(1, 5); // set(0, 1) to allow hold ;
 			switch(dice) {
				case 0: return 'h';
				case 1: return 'l';
				case 2: return 'd';
				case 3: return 'u';
				case 4: return 'r';
				default: return 'h';
			}
			return 'h';
		}
		
		string ToStr() {
			string sPlace = "( " + to_string(Place.Str) + " ; " + to_string(Place.Col) + " )";
			return Person::ToStr() + " " +sPlace;
 		}
 		
 		bool Damage(int Dmg) {
 			if( Dmg > Armor )
 				Health -= ( Dmg - Armor );
 			return Health > 0;
		}
		
};


class Field {
	protected:
		int **Cells;
		int Height, Width;
		vector<PPerson> PPersons;
	public:
		void AddPerson( Person pers ) {

			Position Place = FindFreeCell();
			Cells[Place.Str][Place.Col] = pers.GetId();
			PPerson PPers(pers, Place);
			PPersons.push_back( PPers );
			
		} 
		
		int FindPPerson( int ppersID ) {
			for( int i = 0; i < PPersons.size(); i++ ) {
				if(PPersons[i].GetId() == ppersID ) {
					return i;
				}
			}
		}
		
		Field(int height = 8, int width = 8) {
			cout << "Constructing field...\n";
			GetRandomInt( 0, 1, true);
			Height = height; Width = width;
			Cells = new int*[height];
			for( int i = 0; i < Height; i++) 
				Cells[i] = new int[Width];
				
			for( int i = 0; i < Height; i++) {
				for( int j = 0; j < Width; j++) 
					Cells[i][j] = -1;
			}
		}
			
		~Field() {
			cout << "Destructing field...\n";
			for( int i = 0; i < Height; i++) {
				delete[] Cells[i];
			}
			delete Cells;
		}
		
		void SetBorders() {
			for(int i = 0; i < Width; i++) {
				Cells[0][i] = -2;
				Cells[Height - 1][i]  = -2;
			}
			for( int i = 0; i < Height; i++) {
				Cells[i][0] = -2;
				Cells[i][Width-1] = -2;
			}
		}
		
		Position FindFreeCell() {
			Position result;
			FindFreeCell(&(result.Str), &(result.Col));
			return result;
		}
		
		bool CanMove( PPerson PPers, char Direction) {
			return IsInField( PPers.GetPlace().Move(Direction)) && IsFree(PPers.GetPlace().Move(Direction) );
		}
		
		
		bool NeedFight( PPerson PPers, char Direction, int *opponent) {
			Position MyPosition = PPers.GetPlace();
			int Me = PPers.GetId();
			Position AnotherPosition = PPers.GetPlace().Move(Direction);
			if( !IsInField( AnotherPosition ) ) return false;
			int MayBeEnemy = Cells[ AnotherPosition.Str ][ AnotherPosition.Col ];
			if( MayBeEnemy == -2 ) return false;
			if( Me == 0 && MayBeEnemy > 0 || Me > 0 && MayBeEnemy == 0 ) {
				*opponent = MayBeEnemy;
				return true;
			}
			else return false;
		}
		
	
		void Fight( int FirstFighter, int SecondFighter ) {
			cout << "\nFighting ";
			cout << PPersons[FirstFighter].ToStr() << " v.s " << PPersons[SecondFighter].ToStr() << "\n";
			bool FirstAlive, SecondAlive;
			SecondAlive = PPersons[SecondFighter].Damage( PPersons[FirstFighter].GetDamage() );
			if( SecondAlive ) {
				FirstAlive = PPersons[FirstFighter].Damage( PPersons[SecondFighter].GetDamage() );
			}
			if( !FirstAlive ) {
				Cells[ PPersons[FirstFighter].GetPlace().Str ][ PPersons[FirstFighter].GetPlace().Col ] = -1;
				PPersons.erase( PPersons.begin() + FirstFighter );
			}
			if( !SecondAlive ) {
				Cells[ PPersons[SecondFighter].GetPlace().Str ][ PPersons[SecondFighter].GetPlace().Col ] = -1;
				PPersons.erase( PPersons.begin() + SecondFighter );
			}
		}
			
		void FindFreeCell( int *str, int *col) {
			do {
				*str = GetRandomInt(0, Height - 1);
				*col = GetRandomInt(0, Width - 1);
			} while(Cells[*str][*col] != -1);
		}
		
		bool IsFree( int str, int col) {
			return Cells[str][col];
		}
		
		bool IsFree( Position P ) {
			return IsFree(P.Str, P.Col);
		}
		
		bool IsInField( Position P ) {
			return P.Str >= 0 && P.Str < Height && P.Col >= 0 && P.Col < Width;
		}
		
		char Interpret(int Code) {
		
			if( Code == -1 ) return '.';
			if( Code == 0 ) return 'P';
			if( Code > 0 ) return 'E';
			
		}
		
		void Print() {
			cout << "Field:\n";
			for( int i = 0; i < Height; i++) {
				for(int j = 0; j < Width; j++) {
					cout << Interpret( Cells[i][j] );
				}
				cout <<"\n";
			}
			cout << "Persons:\n";
			for( int i = 0; i < PPersons.size(); i++) {
				cout << PPersons[i].ToStr() << endl;
			}
		}
		
		void MovePers( int PersNum ) {
			cout << "Moving " << PPersons[PersNum].ToStr();
			char WannaGo = PPersons[PersNum].WantGo();
			int Opponent;
			cout << " Wants: " << WannaGo;
			if( CanMove(PPersons[PersNum], WannaGo) ) {
				cout << " Yes we can!";
				Position CurPlace = PPersons[PersNum].GetPlace();
				Cells[CurPlace.Str][CurPlace.Col] = -1; // clearing old place on field
				PPersons[PersNum].SetPlace( PPersons[PersNum].GetPlace().Move(WannaGo) ); // settin nep place to 
				CurPlace = PPersons[PersNum].GetPlace(); // getting new place on field
				Cells[CurPlace.Str][CurPlace.Col] = PPersons[PersNum].GetId(); // settin to new place on field

			}
			else if( NeedFight( PPersons[PersNum], WannaGo, &Opponent ) ) {
				cout << "\nFight!!! ";
				int OppNum = FindPPerson( Opponent ); // Second fighter position
				cout << PPersons[PersNum].ToStr() << " v.s " << PPersons[OppNum].ToStr();
				Fight( PersNum, OppNum );
			}
		}
		
		void MovePersons() {
			for( int persnum = 0; persnum < PPersons.size(); persnum++ ) {
				MovePers(persnum);
			}
		}
		
};


int Person::iCount = 0;


int main() {
	Person *testPerson = new Person("Vasya", 100, 23, 30);
	Person *testPerson2 = new Person("Jo", 100, 23, 30);
	cout << testPerson->ToStr() << "\n";
	cout << testPerson2->ToStr() << "\n";
	Field testField;
	testField.AddPerson(*testPerson);
	testField.AddPerson(*testPerson2);
//	testField.Print();
//	testField.MovePers(0);
	for( int i = 0; i < 10; i++) {
		testField.Print();
		testField.MovePers(0);
	}
}

