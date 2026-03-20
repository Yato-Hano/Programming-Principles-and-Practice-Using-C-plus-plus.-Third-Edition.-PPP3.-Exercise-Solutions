/*
[13] 
Implement a version of the game ‘‘Hunt the Wumpus.’’ ‘‘Hunt the Wumpus’’ (or just
‘‘Wump’’) is a simple (non-graphical) computer game originally invented by Gregory Yob.
The basic premise is that a rather smelly monster lives in a dark cave consisting of connected
rooms. Your job is to slay the wumpus using bow and arrow. In addition to the wumpus, the
cave has two hazards: bottomless pits and giant bats. If you enter a room with a bottomless
pit, it’s the end of the game for you. If you enter a room with a bat, the bat picks you up and
drops you into another room. If you enter the room with the wumpus or he enters yours, he
eats you. When you enter a room, you will be told if a hazard is nearby:
•
‘‘I smell the wumpus’’: It’s in an adjoining room.
•
‘‘I feel a breeze’’: One of the adjoining rooms is a bottomless pit.
•
‘‘I hear a bat’’: A giant bat is in an adjoining room.
For your convenience, rooms are numbered. Every room is connected by tunnels to three
other rooms. When entering a room, you are told something like ‘‘You are in room 12; there
are tunnels to rooms 1, 13, and 4; move or shoot?’’ Possible answers are m13 (‘‘Move to
room 13’’) and s13–4–3 (‘‘Shoot an arrow through rooms 13, 4, and 3’’). The range of an
arrow is three rooms. At the start of the game, you have five arrows. The snag about shoot-
ing is that it wakes up the wumpus and he moves to a room adjoining the one he was in –
that could be your room.
Probably the trickiest part of the exercise is to make the cave by selecting which rooms
are connected with which other rooms. You’ll probably want to use a random number gen-
erator (e.g., randint() from PPP_suppor t) to make different runs of the program use different
caves and to move around the bats and the wumpus. Hint: Be sure to have a way to produce
a debug output of the state of the cave.
*/

import PPP;
using namespace std;

inline int rand_int(int min, int max)
{
	static default_random_engine ran{ unsigned(time(0)) };
	return uniform_int_distribution<>{min, max}(ran);
}

struct Room {
	array<Room*, 3>tunnel{};
	int index{};
	bool bat_here{ false }, wumpus_here{ false }, pit_here{ false };
};
struct Cave {
	Cave();
	array<Room,20>cave ;// dodecahedron
	int player_in_room{};
	int wumpus_in_room()const;
	void debug_print(ostream&);
};
int Cave::wumpus_in_room() const
{
	for (const Room& r : cave)
		if (r.wumpus_here)
			return r.index; 
	throw string{ "wump not found" };
};
void connect_rooms(auto& cave);
void place_wumpus(auto& cave);
void place_bats(auto& cave);
void place_pits(auto& cave);
void Cave::debug_print(ostream&os)
{
	os << "player is in the room " << player_in_room << '\n'
		<< "wumpus is in the room " << wumpus_in_room() << '\n';
	for (int i = 0; i < cave.size(); i++)
	{
		os << "room " << cave[i].index
			<< " connected to "
			<< cave[i].tunnel[0]->index <<' '
			<< cave[i].tunnel[1]->index << ' '
			<< cave[i].tunnel[2]->index 
			<<" wumpus "<< cave[i].wumpus_here
			<< " pit " << cave[i].pit_here
			<< " bat " << cave[i].bat_here
			<<'\n';
	}
}

Cave::Cave()
	:player_in_room{ rand_int(0,cave.size() - 1) }
{
	connect_rooms(cave);
	place_wumpus(cave);
	place_bats(cave);
	place_pits(cave);

	while (cave[player_in_room].bat_here ||
		cave[player_in_room].pit_here ||
		cave[player_in_room].wumpus_here)
	{
		player_in_room = rand_int(0,cave.size() - 1);
	}
}
bool bat_is_nearby(const Room& r)
{
	return r.tunnel[0]->bat_here ||
	r.tunnel[1]->bat_here||
	r.tunnel[2]->bat_here;
}
bool pit_is_nearby(const Room& r)
{
	return r.tunnel[0]->pit_here ||
		r.tunnel[1]->pit_here ||
		r.tunnel[2]->pit_here;
}
bool wumpus_is_nearby(const Room& r)
{
	return r.tunnel[0]->wumpus_here ||
		r.tunnel[1]->wumpus_here ||
		r.tunnel[2]->wumpus_here;
}
ostream& operator<<(ostream& os, const Cave& gs)
{
	os << "You are in room " << gs.player_in_room << '\n'
		<<"There are paths to rooms ";
	for (int i = 0; i < 3; i++)
		os << gs.cave[gs.player_in_room].tunnel[i]->index << ' ';
	os << '\n';
	if (wumpus_is_nearby(gs.cave[gs.player_in_room])) os << "I smell the wumpus\n";
	if (pit_is_nearby(gs.cave[gs.player_in_room])) os << "I feel a breeze\n";
	if (bat_is_nearby(gs.cave[gs.player_in_room])) os << "I hear a bat\n";
	return os;
}

enum class Outcome
{
	not_over,
	fell_into_pit,
	hit_wumpus,
	eaten_by_wumpus
};

struct Action
{
	enum  A_type{	none,move,shoot	};
	vector<int>rooms;
	A_type what{ none };
	Outcome affect(Cave&);
};
bool is_connected(const Room& r1, const Room& r2)
{
	return r1.tunnel[0] == &r2 ||
		r1.tunnel[1] == &r2||
		r1.tunnel[2] == &r2;
}
void validate_action(const Action&a,const Cave& c)
{
	if (a.rooms.empty()) throw string{ "provide a room number" };
	if (!is_connected(c.cave[c.player_in_room], c.cave[a.rooms[0]]))
		throw string{ "invalid first room number, not connected to player's room" };

	if (a.what == Action::shoot)
	{
		for (int i = 1; i < a.rooms.size(); i++)
			if (!is_connected(c.cave[a.rooms[i]], c.cave[a.rooms[i - 1]]))
				throw string{ "shoot: invalid room number, not connected" };
	}

}
Room* rand_adj_room(Room* r)
{
	return r->tunnel[rand_int(0, 2)];
}
Outcome Action::affect(Cave&c)
{
	validate_action(*this, c); //throws 

	switch (what)
	{
	case move:
		c.player_in_room = rooms[0];
		while (c.cave[c.player_in_room].bat_here)
		{
			cout << "Caught by giant bat.\n";
			Room* new_room = rand_adj_room(&c.cave[c.player_in_room]);
			c.player_in_room = new_room->index;
		}
		break;
	case shoot:
	{
		for (int n : rooms)
			if (c.cave[n].wumpus_here)
				return Outcome::hit_wumpus;
		cout << "You woke up the wumpus and it moved to another room.\n";
		Room* wump_room = &c.cave[c.wumpus_in_room()];
		wump_room->wumpus_here = false;
		Room* new_room = rand_adj_room(wump_room);
		new_room->wumpus_here = true;
		break;
	}
	default:
		throw string{ "affect() invalid action" };
	}

	if (c.cave[c.player_in_room].wumpus_here)
		return Outcome::eaten_by_wumpus;
	if (c.cave[c.player_in_room].pit_here)
		return Outcome::fell_into_pit;

	return Outcome::not_over;
}
istream& operator>>(istream& is, Action& a)
//s13–4–3
//m13
{
	a = {};
	string s;
	getline( is,s);
	istringstream istr{ s };

	char ch{};
	istr >> ch;
	if (ch == 'm')a.what = Action::move;
	else 
		if (ch == 's')a.what = Action::shoot;
	else 
		throw string{ "invalid action (use m or s)" };
	int room_n{ 0 };
	char dash{  };

	for (int i = 0; i < 3&&istr>> room_n; i++)
	{
		if(room_n<0|| 19< room_n) 
			throw string{ "invalid room number" };

		a.rooms.push_back(room_n);
		istr >> dash;
		if (dash != '-')break;
	}
	if(a.rooms.empty()) throw string{ "provide a room number" };
	return is;
}
class Game
{
public:
	void run();
	void debug_print(ostream& os);
private:
	Outcome result{ Outcome::not_over };
	Cave cs; //cave_state
};
void Game::debug_print(ostream& os)
{
	cs.debug_print(os);
}
void print_result(Outcome result)
{
	switch (result)
	{
	case Outcome::fell_into_pit:
		cout << "You fell into bottomless pit.\n";
		break;
	case Outcome::hit_wumpus:
		cout << "You hit the wumpus.\n";
		break;
	case Outcome::eaten_by_wumpus:
		cout << "You were eaten by the wumpus.\n";
		break;
	}
}
void Game::run()
{
	while (result==Outcome::not_over)
		try {

			//debug_print(cout);
			cout << cs;
			cout << "move or shoot (m or s) ";
			Action act;
			cin >> act;
			result=act.affect(cs);
			print_result(result);
		}
	catch (string& err_message)
	{
		cerr << err_message << '\n';
		system("pause");
	}
}

void connect_rooms(auto& cave)
{
	cave[0].tunnel = { &cave[1],&cave[4],&cave[7] };
	cave[1].tunnel = { &cave[0],&cave[2],&cave[9] };
	cave[2].tunnel = { &cave[1],&cave[3],&cave[11] };
	cave[3].tunnel = { &cave[2],&cave[4],&cave[13] };
	cave[4].tunnel = { &cave[0],&cave[3],&cave[5] };
	cave[5].tunnel = { &cave[4],&cave[6],&cave[14] };
	cave[6].tunnel = { &cave[5],&cave[7],&cave[16] };
	cave[7].tunnel = { &cave[0],&cave[6],&cave[8] };
	cave[8].tunnel = { &cave[7],&cave[9],&cave[17] };
	cave[9].tunnel = { &cave[1],&cave[8],&cave[10] };
	cave[10].tunnel = { &cave[9],&cave[11],&cave[18] };
	cave[11].tunnel = { &cave[2],&cave[10],&cave[12] };
	cave[12].tunnel = { &cave[11],&cave[13],&cave[19] };
	cave[13].tunnel = { &cave[3],&cave[12],&cave[14] };
	cave[14].tunnel = { &cave[5],&cave[13],&cave[15] };
	cave[15].tunnel = { &cave[14],&cave[16],&cave[19] };
	cave[16].tunnel = { &cave[6],&cave[15],&cave[17] };
	cave[17].tunnel = { &cave[8],&cave[16],&cave[18] };
	cave[18].tunnel = { &cave[10],&cave[17],&cave[19] };
	cave[19].tunnel = { &cave[12],&cave[15],&cave[18] };

	for (int i = 0; i < cave.size(); i++)
		cave[i].index = i;
}
void place_wumpus(auto& cave)
{
	int w=	rand_int(0, cave.size() - 1);
	cave[w].wumpus_here = true;
}
void place_bats(auto& cave)
{
	int w = rand_int(0, cave.size() - 1);
	cave[w].bat_here = true;
	w = rand_int(0, cave.size() - 1);
	cave[w].bat_here = true;
}
void place_pits(auto& cave)
{
	int w = rand_int(0, cave.size() - 1);
	cave[w].pit_here = true;
	w = rand_int(0, cave.size() - 1);
	cave[w].pit_here = true;
}

int main()
try {
	Game g;
	g.run();
	system("pause");
	return 0;
}
catch (const exception& surprise)
{
	cerr << "Exception: " << surprise.what() << '.' << endl;
	system("pause");
	return 2;
}
catch (...) {
	cerr << "Caught an unknown exception." << endl;
	system("pause");
	return 3;
}