//Rotting Oranges

//TC = O(m*n) each cell in the grid is explored once.
//SC = O(m*n) in the worst case, the queue would have to store all the cells.

/*
Intuition : 
  1.  each cell can be treated as a node, and unweighted edges exist between adjacent nodes => unweighted graph
  2. "wave"-like spread. rotting spreads uniformly in all directions and resembles a level-by-level traversal => bfs
  3. "wavelets" can emerge from multiple points, i.e., rotting starts at the same time from all rotten oranges => multi-source
*/

/*
Approach: 
  1. if initially there are no fresh oranges to rot, we can simply return 0 (no time spent on rotting)
  2. otherwise, implement multi-source bfs
  3. the levels (0-indexed) correspond to the minutes passed.
  4. if even after bfs, a fresh orange remains, it is impossible to rot the entire grid.
*/

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        
        queue<pair<int,int>> q; //for exploring the nodes (rotten oranges)
        int time = 0; //to track time
        int fresh = 0; //initially, we haven't counted any fresh oranges
        
        //traversing the grid
        for (int i = 0; i<grid.size(); i++)
        {
            for (int j = 0; j<grid[0].size(); j++)
            {
                if (grid[i][j]==2) //rotten oranges are the sources for bfs
                {
                    q.push({i,j});
                }
                else if (grid[i][j]==1) //count of fresh oranges
                {
                    fresh++;
                }
            }
        }
        if (fresh==0) return 0; //no need to implement bfs
        
        
        while (!q.empty()) //until all (reachable) nodes are explored
        {
            int levelSize = q.size(); //all similar level nodes 
            for (int i = 0; i<levelSize; i++) 
            {
                pair<int,int> node = q.front(); //node to be explored
                q.pop(); 
                int x = node.first; //row index
                int y = node.second; //col index

                //possible moves -> up, down, left, and right respectively
                vector<pair<int,int>> dir = {{-1,0},{1,0},{0,-1},{0,1}};

                for (pair<int,int> p : dir) //for all these moves
                {
                    int nx = x + p.first; //new row index
                    int ny = y + p.second; //new col index

                    //if the new indexes are valid (i.e. they exist)
                    if (nx>=0 && nx<grid.size() && ny>=0 && ny<grid[0].size())
                    {
                        if (grid[nx][ny] == 1) //if not rotten
                        {
                            grid[nx][ny] = 2; //rot it
                            q.push({nx,ny}); //will potentially spread the rot in the next minute. i.e., a new source
                        }
                    }
                }
            }
            time++; //one full level processed, so a minute elapses
        }
        
        //grid traversal
        for (int i = 0; i<grid.size(); i++)
        {
            for (int j = 0; j<grid[0].size(); j++)
            {
                if (grid[i][j]==1) //if despite of bfs, any fresh orange spotted
                    return -1; //unreachable, rot doesn't spread completely
            }
        }
        
        // time is incremented after each BFS level.
        // the last level does not cause any new orange to rot,
        // hence we subtract 1 to get the actual minutes required.
        return time-1;  
    }
};
