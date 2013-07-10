#include "stdafx.h"
#include "collection.h"
#include "Map.h"
#include "Matrix.h"

using namespace std;

typedef int dist;

pair<dist, collection<Point>> failure = make_pair((dist)-1, collection<Point>());

dist dist_between(const Point& a, const Point& b)
{
	return (dist)1;
}

dist heuristic_cost_estimate(const Point& start, const Point& goal)
{
	return (dist)(abs(goal.X() - start.X()) + abs(goal.Y() - start.Y()));
}

#define CLOSEDSET 0x1
#define OPENSET 0x2
#define CAME_FROM 0x4

pair<dist, collection<Point>> reconstruct_path(
	const Matrix<Point>& came_from, const Matrix<int>& flags, Point current_node)
{
	stack<Point> backward;
	while (true)
	{
		backward.push(current_node);
		if (!(flags[current_node] & CAME_FROM)) break;
		current_node = came_from[current_node];
	}
	collection<Point> forward;
	forward.reserve(backward.size());
	while (!backward.empty())
	{
		forward.push_back(backward.top());
		backward.pop();
	}
	return make_pair((dist)forward.size(), forward);
}

pair<dist, collection<Point>> astar(Map world, Point start, Point goal)
{
	if (!world.IsFree(start) || !world.IsFree(goal)) return failure;

	Matrix<int> flags(world.Width(), world.Height());
	flags[start] |= OPENSET;

	multimap<dist, Point, less<dist>> openset;
	openset.insert(make_pair(heuristic_cost_estimate(start, goal), start));

	Matrix<Point> came_from(world.Width(), world.Height());

	Matrix<dist> g_score(world.Width(), world.Height());
	g_score.Set(start, 0);

	while (!openset.empty())
	{
		Point current = openset.begin()->second;
		dist current_f = openset.begin()->first;
		if (current == goal)
			return reconstruct_path(came_from, flags, goal);

		openset.erase(openset.begin());
		flags[current] &= ~OPENSET;
		flags[current] |= CLOSEDSET;

		collection<Point> neighbors = world.Neighbors(current);
		for (collection<Point>::const_iterator i = neighbors.begin();
			i != neighbors.end(); ++i)
		{
			Point neighbor = *i;

			dist tentative_g_score = g_score[current] + dist_between(current, neighbor);
			if ((flags[neighbor] & CLOSEDSET) && tentative_g_score >= g_score[neighbor])
				continue;

			if (!(flags[neighbor] & OPENSET) || tentative_g_score < g_score[neighbor])
			{
				came_from.Set(neighbor, current);
				flags[neighbor] |= CAME_FROM;
				g_score.Set(neighbor, tentative_g_score);

				if (flags[neighbor] & OPENSET)
				{
					for (auto i = openset.begin(); i != openset.end(); ++i)
					{
						if (i->second == neighbor)
						{
							openset.erase(i);
							break;
						}
					}
				}
				openset.insert(make_pair(g_score[neighbor] + heuristic_cost_estimate(neighbor, goal), neighbor));
				flags[neighbor] |= OPENSET;
			}
		}
	}

	return failure;
}

#define DEBUG

void Main(collection<wstring> args)
{
	if (args.size() < 5) throw exception("Usage: astar.exe MapFileName StartX StartY EndX EndY [showmap]");

	Map world(args[0]);
	Point start(_wtoi(args[1].c_str()), _wtoi(args[2].c_str()));
	Point end(_wtoi(args[3].c_str()), _wtoi(args[4].c_str()));

	wcout << endl
		<< "Start position: (" << args[1] << ", " << args[2] << ")" << endl
		<< "End position:   (" << args[3] << ", " << args[4] << ")" << endl;

	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	QueryPerformanceCounter(&t1);
	pair<dist, collection<Point>> result = astar(world, start, end);
	QueryPerformanceCounter(&t2);

	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);

	float dt = (t2.QuadPart - t1.QuadPart) / (float)freq.QuadPart * 1000;

	wcout << endl
		<< "Path found:     " << (result == failure ? "false" : "true") << endl
		<< endl
		<< "Total duration: " << dt << " ms" << endl;

	if (args.contains(L"showmap")) world.Show(result.second);
#ifdef DEBUG
	world.Show(result.second, ofstream("result.txt"));
#endif
}

int wmain(int argc, wchar_t** argv)
{
	int result = 0;
	try
	{
		collection<wstring> args;
#ifdef DEBUG
		args.push_back(wstring(L"C:\\Users\\Ansis\\Desktop\\AStar\\AStarMap.txt"));
		args.push_back(wstring(L"20"));
		args.push_back(wstring(L"20"));
		args.push_back(wstring(L"120"));
		args.push_back(wstring(L"10"));
#else
		args.reserve(argc);
		for (int i = 1; i < argc; i++) args.push_back(wstring(argv[i]));
#endif
		Main(args);
	}
	catch (const exception& ex)
	{
		wcerr << ex.what() << endl;
		result = 1;
	}
#ifdef DEBUG
	char _debug;
	cin >> _debug;
#endif
	return result;
}