/*
[14] 
Provide a GUI interface and a bit of graphical output to the ‘‘Hunt the Wumpus’’ game
from the exercises in Chapter 16. Take the input in an input box and display a map of the
part of the cave currently known to the player in a window.
[15]
Modify the program from the previous exercise to allow the user to mark rooms based on
knowledge and guesses, such as ‘‘maybe bats’’ and ‘‘bottomless pit.’’
*/

// console version 16_chapter: exercise_13. 

#include "PPP/GUI.h"
#include <numbers>

using namespace Graph_lib;

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
	array<Room, 20>cave;// dodecahedron
	int player_in_room{};
	int arrows_left{5};
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
void Cave::debug_print(ostream& os)
{
	os << "player is in the room " << player_in_room << '\n'
		<< "wumpus is in the room " << wumpus_in_room() << '\n';
	for (int i = 0; i < cave.size(); i++)
	{
		os << "room " << cave[i].index
			<< " connected to "
			<< cave[i].tunnel[0]->index << ' '
			<< cave[i].tunnel[1]->index << ' '
			<< cave[i].tunnel[2]->index
			<< " wumpus " << cave[i].wumpus_here
			<< " pit " << cave[i].pit_here
			<< " bat " << cave[i].bat_here
			<< '\n';
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
		player_in_room = rand_int(0, cave.size() - 1);
	}
}
bool bat_is_nearby(const Room& r)
{
	return r.tunnel[0]->bat_here ||
		r.tunnel[1]->bat_here ||
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
		<< "There are paths to rooms ";
	for (int i = 0; i < 3; i++)
		os << gs.cave[gs.player_in_room].tunnel[i]->index << ' ';
	os << '\n';
	if (wumpus_is_nearby(gs.cave[gs.player_in_room])) os << "I smell the wumpus\n";
	if (pit_is_nearby(gs.cave[gs.player_in_room])) os << "I feel a breeze\n";
	if (bat_is_nearby(gs.cave[gs.player_in_room])) os << "I hear a bat\n";
	os << gs.arrows_left << " arrows left.\n";
	return os;
}

enum class Outcome
{
	not_over,
	fell_into_pit,
	hit_wumpus,
	eaten_by_wumpus,
	ran_out_of_arrows
};

struct Action
{
	enum  A_type { none, move, shoot,label };
	vector<int>rooms;
	A_type what{ none };
	Outcome affect(Cave&, ostream&);
};
bool is_connected(const Room& r1, const Room& r2)
{
	return r1.tunnel[0] == &r2 ||
		r1.tunnel[1] == &r2 ||
		r1.tunnel[2] == &r2;
}
void validate_action(const Action& a, const Cave& c)
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
Outcome Action::affect(Cave& c,ostream&os)
{
	if (what == Action::label) 	return Outcome::not_over;

	validate_action(*this, c); //throws 

	switch (what)
	{
	case move:
		c.player_in_room = rooms[0];
		while (c.cave[c.player_in_room].bat_here)
		{
			os << "You've been caught by a giant bat.\n";
			Room* new_room = rand_adj_room(&c.cave[c.player_in_room]);
			c.player_in_room = new_room->index;
		}
		break;
	case shoot:
	{
		for (int n : rooms)
			if (c.cave[n].wumpus_here)
				return Outcome::hit_wumpus;
		os << "You woke up the wumpus and it moved to another room.\n";
		c.arrows_left--;
		Room* wump_room = &c.cave[c.wumpus_in_room()];
		wump_room->wumpus_here = false;
		Room* new_room = rand_adj_room(wump_room);
		new_room->wumpus_here = true;
		break;
	}
	case label:
		break;
	default:
		throw string{ "affect() invalid action" };
	}

	if (c.cave[c.player_in_room].wumpus_here)
		return Outcome::eaten_by_wumpus;
	if (c.cave[c.player_in_room].pit_here)
		return Outcome::fell_into_pit;
	if (c.arrows_left==0)
		return Outcome::ran_out_of_arrows;

	return Outcome::not_over;
}
istream& operator>>(istream& is, Action& a)
//s13–4–3
//m13
//l13
{
	a = {};
	string s;
	getline(is, s);
	istringstream istr{ s };

	char ch{};
	istr >> ch;
	Action::A_type at{ Action::none };
	switch (ch)
	{
	case 'm':
		at = Action::move;
		break;
	case 's':
		at= Action::shoot;
		break;
	case 'l':
		at = Action::label;
		break;
	default:
		throw string{ "invalid action (use m or s)" };

	}
	int room_n{ 0 };
	char dash{  };
	vector<int>r;
	for (int i = 0; i < 3 && istr >> room_n; i++)
	{
		if (room_n < 0 || 19 < room_n)
			throw string{ "invalid room number" };

		r.push_back(room_n);
		istr >> dash;
		if (dash != '-')break;
	}
	if (r.empty()) throw string{ ">> provide a room number" };
	a.rooms = r;
	a.what = at;
	return is;
}
class Game
{
public:
	Action run(ostream&, istream&);
	void debug_print(ostream& os);
	const Cave& cave_state()const { return cs; }
	const Outcome& outcome()const { return result; }
private:
	Outcome result{ Outcome::not_over };
	Cave cs; //cave_state
};
void Game::debug_print(ostream& os)
{
	cs.debug_print(os);
}
void print_outcome(ostream& os,Outcome result)
{
	switch (result)
	{
	case Outcome::fell_into_pit:
		os << "You fell into bottomless pit.\n";
		break;
	case Outcome::hit_wumpus:
		os << "You hit the Wumpus.\n";
		break;
	case Outcome::eaten_by_wumpus:
		os << "You were eaten by the Wumpus.\n";
		break;
	case Outcome::ran_out_of_arrows:
		os << "You ran out of arrows.\n";
		break;
		
	}
}
Action Game::run(ostream&os, istream& is)
{
	Action act;
	try
	{
		is >> act;
		result = act.affect(cs,os);
	}
	catch (string& err_message)
	{
		os << err_message<<'.'<<'\n';
	}
	return act;
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
	int w = rand_int(0, cave.size() - 1);
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

struct My_Out_box : Shape {//handles newline
	My_Out_box(Point p){Shape::add(p);	}

	void put(const string& s)
	{
		istringstream is{ s };
		text_lines.clear();
		for (string i; getline(is, i);)
			text_lines.push_back(i);
		redraw();
	}

	void draw_specifics(Painter& painter) const override;
	vector<string> text_lines;
};
void My_Out_box::draw_specifics(Painter& painter) const
{
	Vector_ref<const Text> texts;
	for (const string& s: text_lines)
		texts.push_back(make_unique<Text>(Point{ 0,0 }, s));
	painter.draw_text_column(point(0), texts);
}



struct Index_Circle :Circle
{
	Index_Circle(Point p,string index) 
		:Circle{ p,27 }, label{{p.x-15,p.y-10},index} {
		set_fill_color(Color::black);
		label.set_font_size(20);
		label.set_color(Color::white);
	}
	void draw_specifics(Painter& painter) const override;
	Text label;
};
void Index_Circle::draw_specifics(Painter& painter) const
{
	Circle::draw_specifics(painter);
	label.draw(painter);
}

Point get_point_on(const Circle& e, double angle_degree)
{
	double angle_radians{ angle_degree * (std::numbers::pi / 180.0) };
	int x = e.center().x + e.radius() * cos(angle_radians);
	int y = e.center().y + e.radius() * sin(angle_radians);
	return { x,y };
}

class Cave_Map :public Shape
{
public:
	enum Status { been_here,maybe_bat, maybe_pit};
	Cave_Map(Point center);
	void mark_map_rooms(const Game&, Action c);
	void mark_room_status(int index, Status);
	void draw_specifics(Painter& painter) const override;
private:
	Vector_ref<Circle>connect_circles;
	Lines connect_lines;
	Vector_ref<Index_Circle>rooms;
};
void Cave_Map::mark_map_rooms(const Game& g, Action act)
{
	mark_room_status(g.cave_state().player_in_room, Cave_Map::Status::been_here);
	if (act.what == Action::label)
	{
		mark_room_status(act.rooms[0], Cave_Map::Status::maybe_pit);
	}
}
void Cave_Map::mark_room_status(int index, Status st)
{
	if(index<0||19< index)
		throw out_of_range{ "invalid room index" };

	switch (st)
	{
	case Cave_Map::been_here:
		rooms[index].set_fill_color(Color::cyan);
		break;
	case Cave_Map::maybe_pit:
		rooms[index].set_fill_color(Color::dark_red);
		break;
	default:
		throw exception{ "invalid room status" };
		break;
	}
}
Cave_Map::Cave_Map(Point center)
{
	Shape::add(center);

	connect_circles.push_back(make_unique<Circle>(center, 225));
	connect_circles.push_back(make_unique<Circle>(center, 150));
	connect_circles.push_back(make_unique<Circle>(center, 75));
	for (Circle* c : connect_circles) {
		c->set_style(Line_style{ Line_style::solid,10 });
		c->set_color(Color::dark_green);
	}
	double angle{ -90 };
	double increment{ 360 / 5 };
	for (int i = 0; i < 5; i++)
	{
		rooms.push_back(make_unique<Index_Circle>(get_point_on(connect_circles[0], angle), to_string(i)));
		if (i < 4)angle += increment;
	}
	increment = 360 / 10;
	for (int i = 5; i < 15; i++)
	{
		rooms.push_back(make_unique<Index_Circle>(get_point_on(connect_circles[1], angle), to_string(i)));
		if (i < 14)angle += increment;
	}
	increment = 360 / 5;
	for (int i = 15; i < 20; i++, angle += increment)
	{
		rooms.push_back(make_unique<Index_Circle>(get_point_on(connect_circles[2], angle), to_string(i)));
	}

	connect_lines.set_style(Line_style{ Line_style::solid,10 });
	connect_lines.set_color(Color::dark_green);

	connect_lines.add(rooms[0].center(), rooms[7].center());
	connect_lines.add(rooms[1].center(), rooms[9].center());
	connect_lines.add(rooms[4].center(), rooms[5].center());
	connect_lines.add(rooms[3].center(), rooms[13].center());
	connect_lines.add(rooms[11].center(), rooms[2].center());

	connect_lines.add(rooms[6].center(), rooms[16].center());
	connect_lines.add(rooms[14].center(), rooms[15].center());
	connect_lines.add(rooms[8].center(), rooms[17].center());
	connect_lines.add(rooms[10].center(), rooms[18].center());
	connect_lines.add(rooms[19].center(), rooms[12].center());

}
void Cave_Map::draw_specifics(Painter& painter) const
{
	for (const Circle*c : connect_circles) 
		c->draw(painter);

	connect_lines.draw(painter);

	for (const Index_Circle* c : rooms) 
		c->draw(painter);
}

class HW_Game :public Window
{
public:
	HW_Game(Application&);
private:
	Game g;
	Application* app;
	In_box input_b;
	My_Out_box text_res_box;
	Button quit;
	Cave_Map map;
	void run_cb();
};

void HW_Game::run_cb()
{
	if (input_b.last_result() == In_box::accepted)
	{
		istringstream is;
		is.str(input_b.last_string_value());
		ostringstream os;
		if (g.outcome() == Outcome::not_over)
		{
			Action act = g.run(os, is);
			map.mark_map_rooms(g, act);

			if (g.outcome() == Outcome::not_over)
			{
				os << g.cave_state() << '\n';
				os << "move of shoot (m or s)\n";
			}
		}
		print_outcome(os, g.outcome()); // an end game message
		text_res_box.put(os.str());
	}
	
}
HW_Game::HW_Game(Application& a)
	:Window{ 1000,600,"Hunt The Wumpus" }
	, app{ &a }
, input_b{ {0,0},70,20,"Input: ",[this] { run_cb(); } }
, text_res_box{ {0,100} }
, quit{ {x_max() - 70,0},70,20,"Quit",[this] {close(); app->quit(); } }
, map{{700,300}}
{
	attach(map);

	attach(quit);

	ostringstream os;
	os << g.cave_state() << '\n';
	os << "move of shoot (m or s)\n";
	text_res_box.put(os.str());
	map.mark_room_status(g.cave_state().player_in_room, Cave_Map::been_here);
	attach(text_res_box);

	attach(input_b);
	input_b.hide_buttons();
	input_b.show();
}

int main(int /*argc*/, char* /*argv*/[])
try {
    Application app;
	HW_Game hwg{ app };
    app.gui_main();
}
catch (exception& e)
{
    ofstream ofs{ "errors.txt" };
    ofs << e.what() << '.' << endl;
}
catch (...)
{
    ofstream ofs{ "errors.txt" };
    ofs << "Some error." << endl;
}
