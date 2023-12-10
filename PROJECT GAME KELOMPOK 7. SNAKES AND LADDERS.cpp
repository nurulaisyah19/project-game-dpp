#include <iostream> //fungsi input output
#include <cstdlib> // menggunakan fumgsi umum
#include <ctime> // waktu
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Struktur data untuk pemain
struct Player {
  string name;
  int position;
  bool isWinner; 
  bool hasExtraTurn;
};

struct snakeLadder {
	int start;
	int end;
	string type;
};

const int winningScore = 100;
vector<Player> players;
vector <snakeLadder> snakesAndLadders;

int rollDice(){
	return (rand() %6) + 1;
	
}
void initializePlayers(int numPlayers){
	players.clear();
	
	for (int i = 1; i<= numPlayers; i++){
		Player player;
		cout << "Masukkan Nama Pemain " << i << ": ";
		cin >> player.name;
		player.position = 1;
		player.isWinner = false;
		player.hasExtraTurn = false;
		players.push_back(player);
		
	}
}

void initializeSnakesAndLadders(){

snakesAndLadders.clear();
snakesAndLadders.push_back({2,38, "Ladder"});
snakesAndLadders.push_back({7,14, "Ladder"});
snakesAndLadders.push_back({8,31, "Ladder"});
snakesAndLadders.push_back({15,26, "Ladder"});
snakesAndLadders.push_back({16,6, "Snake"});
snakesAndLadders.push_back({21,42, "Ladder"});
snakesAndLadders.push_back({28,84, "Ladder"});
snakesAndLadders.push_back({36,44, "Ladder"});
snakesAndLadders.push_back({46,25, "Snake"});
snakesAndLadders.push_back({49,11, "snake"});
snakesAndLadders.push_back({51,67, "Ladder"});
snakesAndLadders.push_back({62,19, "Snake"});
snakesAndLadders.push_back({64,60, "Snake"});
snakesAndLadders.push_back({71,91, "Ladder"});
snakesAndLadders.push_back({74,53, "Snake"});
snakesAndLadders.push_back({78,98, "Ladder"});
snakesAndLadders.push_back({89,6, "Snake"});
snakesAndLadders.push_back({92,88, "Snake"});
snakesAndLadders.push_back({95,75, "Snake"});
}

void pressEnterToContinue(){
	cout<< "Ayo Mainkan Dadumu....";
	cin.ignore();
	cin.get();
	
}

int main (){
	srand(time(0));
	int numPlayers;
	char tryAgain;
	
	cout<< "..............................................................." << endl;
	cout<< "|Welcome to Snakes Ladders, go to 100 and you winning the game|" << endl;
	cout<< "..............................................................." << endl;
	cout<< endl;
	
	do{ 
		cout<< "Masukkan Jumlah Pemain: ";
		cin>> numPlayers;
		
		if (numPlayers < 2 || numPlayers > 4){
			cout << " Pemain hanya dapat terdiri dari 2-4 pemain." << endl;
			do{
				cout << "Apakah ingin ulang? (y/n): ";
				cin >> tryAgain;
				
			}while (tryAgain != 'y' && tryAgain != 'n');
			
			if (tryAgain == 'n'){
				return 1;
			}
		}
	}while (numPlayers  < 2 || numPlayers > 4);
	
	initializePlayers(numPlayers);
	initializeSnakesAndLadders();
	
	int numberOfWinners = 0; 
	
	random_shuffle(players.begin(), players.end());
	
	while (numberOfWinners < numPlayers - 1){
		for (int i = 0; i < players.size(); i++){
			if ( players[i].position >= winningScore && !players[i].isWinner){
				players[i].isWinner = true;
				numberOfWinners++;
				if (numberOfWinners >= 3){
					break;
				}
			}
			
			while ( !players[i].isWinner){
				pressEnterToContinue();
				int dice = rollDice();
				cout<< players[i].name << " Mendapatkan dadu " << dice << endl;
				
				
				// untuk drama pada tangga tertentu
				
				if ( players[i].position == 50){
					cout<< "Kamu telah berada di tengah permainan. "<<endl;
					
				}else if (players[i].position == 80){
					cout<< "Ayo 20 langkah lagi dan anda akan memenangkan game ini "<<endl;
					
				}else if (players[i].position == 99){
					cout<< "Sedikit menginfokan, 1 itu susah di dapat hehe"<<endl;
				}
				
					if (dice == 1) {
						players [i].hasExtraTurn = true;
						cout<< players[i].name << " Bisa bermain sekali lagi"<<endl;
						
					}else{
						players[i].hasExtraTurn= false;
					}
					
					
					
					int newPosition = players[i].position + dice;
					
					for (const auto & snakeLadder : snakesAndLadders){
						if (newPosition == snakeLadder.start){
							cout<<players[i].name << " bertemu "<< snakeLadder.type <<" dari " <<snakeLadder.start << " ke "<< snakeLadder.end << "."<< endl;
							newPosition = snakeLadder.end;
							break;
						}
					}
					
					if (newPosition > winningScore){
						int stepsBack = newPosition - winningScore;
						players[i].position = winningScore - stepsBack;
						cout<< players[i].name << " Melewati finish dan mundur "<< stepsBack <<" langkah."<<endl;
						
					}else {
						players[i].position = newPosition;
						
					}
					
					for (int j = 0; j < numPlayers; j++){
						cout<< players[j].name << " di posisi: "<< players[j].position<<endl;
						
					}
					
					if (!players[i].hasExtraTurn){
						break;
					}
			}
						if (numberOfWinners == numPlayers - 1){
				break;
			}
			
		
			}
			
		}
		

	cout<< endl;
	cout<< ".........................................."<<endl;
	cout<< "| CONGRATS KING, MAHKOTAMU SEDANG DI LAS |"<<endl;
	cout<< ".........................................."<<endl;
	for (int i= 0; i<numPlayers; i++){
		if (players[i].isWinner){
			cout<< endl;
			cout<<" - "<< players[i].name << ": " <<winningScore<< " poin"<< endl;
			
		}
	}
	return 0;
}

