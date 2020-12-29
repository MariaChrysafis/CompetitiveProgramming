#include <iostream>
#include <queue>
#include <unordered_map>
#include <map>
using namespace std;

class Problem1WhyDidTheCowCrossTheRoad {
public:
    struct coord{
      int x,y;
      int magnitude(){
        return abs(this->x) + abs(this->y);
      }
      coord operator+(const coord &myCoord){
        return {this->x + myCoord.x,this->y + myCoord.y};
      }
      bool operator==(const coord &myCoord){
        return (myCoord.x == this->x && myCoord.y == this->y);
      }
      bool operator<(const coord &myCoord) const{
        if(myCoord.x == this->x){
          return (myCoord.y <= this->y);
        }
        return (myCoord.x <= this->x);
      }
    };
    struct Pair{
      coord c;
      int d;
      int cost;
      bool operator<(const Pair &p)const{
        return p.cost < this->cost;
      }
    };
    bool inBounds(coord c, int N){
      if(c.x < 0 || c.y < 0 || c.x >= N || c.y >= N){
        return false;
      }
      return true;
    }
	void solve(std::istream& in, std::ostream& out) {
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      int N, T;
	  in >> N >> T;
	  int arr[N][N];
	  for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	      in >> arr[i][j];
	    }
	  }
	  vector<coord> dist;
	  for(int i = -1; i <= 1; i++){
	    for(int j = -1; j <= 1; j++){
	      coord c = {i,j};
	      if(c.magnitude() == 1){
            dist.push_back(c);
	      }
	    }
	  }
      priority_queue<Pair> pq;
	  pq.push({{0,0},0,0});
	  coord des = {N - 1, N - 1};
	  bool hasVisited[N][N][3];
	  for(int i = 0; i < N; i++){
	    for(int j = 0; j < N; j++){
	      for(int k = 0; k < 3; k++){
	        hasVisited[i][j][k] = false;
	      }
	    }
	  }
	  while(!pq.empty()){
	    coord cur = pq.top().c;
	    int curDist = pq.top().d;
	    int curCost = pq.top().cost;
        pq.pop();
	    if(hasVisited[cur.x][cur.y][curDist % 3]){
	      continue;
	    }
        hasVisited[cur.x][cur.y][curDist % 3] = true;
	    if(cur == des){
	      out << curCost << endl;
	      break;
	    }
	    for(coord myCoord: dist) {
          if (!inBounds(myCoord + cur, N)) {
            continue;
          }
          int x = (myCoord.x + cur.x);
          int y = (myCoord.y + cur.y);
          int delta = arr[x][y] * (curDist % 3 == 2) + T;
          pq.push({{x, y}, curDist + 1, curCost + delta});
        }
	  }

	}

};
