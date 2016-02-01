#pragma once
#include <vector>
#include <unordered_map>
#include "TileType.h"
#include "map.h"
#include "path.h"


class Astar
{
	struct NodeEqual;
	struct NodeHash;
public:
	Astar();
	~Astar();

	static Path* findPath(Position begin, Map *map);

	static size mapWidth, mapHeight;
private:
	//klasa pomocnicza
	//reprezentuje węzeł w grafie
	class Node
	{
	public:
		class vectorCompare;
		typedef std::vector<Node *> NodeVector;

		Position position;
		float g_score,
			f_score;

		Node(Position position, float _g = 0.f, float _f = 0.f) : position(position), g_score(_g), f_score(_f)
		{
		}


		float estimate_cost(size mapHeight);
	//	float estimate_cost(Node *goal);
		static Path* reconstructPath(std::unordered_map<Position, Node*, NodeHash, NodeEqual>&, Path *path, Node *currentNode, Position begin);

		bool operator >(Node *rhp) {
			return (this->f_score > rhp->f_score ? true : false);
		}

		bool operator <(Node *rhp) {
			return (this->f_score < rhp->f_score ? true : false);
		}

		bool operator >=(Node *rhp) {
			return (this->f_score >= rhp->f_score ? true : false);
		}

		bool operator <=(Node *rhp) {
			return (this->f_score <= rhp->f_score ? true : false);
		}

		//it's checking if the positions is same
		bool operator ==(Node *rhp);
		bool operator ==(Position &rhp);



		class PositionCompare
		{
		public:
			bool operator()(const Position left, const Position right);
		};
	};

	struct NodeHash
	{
		long operator() (const Position&  key)const;// {return key.tile->x + key.tile->y * Astar::mapWidth; }
	};

	struct NodeEqual
	{
		bool operator() (const Position&  x, const Position&  y) const;
	};

};

