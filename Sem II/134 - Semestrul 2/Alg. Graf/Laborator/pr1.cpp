#include <iostream>
#include <fstream>
#include <vector> // STL pentru vectori; am folosit metoda .resize(lungimea vectorului) si am luat un vector de perechi (pair)
using namespace std;
/* alocarea dinamica a vectorilor si matricelor
int* a =  new int [size];
int** M = new int* [rowSize];
for(int i = 0; i < rowSize; i++)
  M[i] = new int[colSize];

*/
int main()
{
  int n, m, i;
  ifstream fin("graf.in");
  vector <pair<int, int> >V;
  fin >> n >> m;
  V.resize(m);
  for(i = 0; i < m; i++)
    fin >> V[i].first >> V[i].second;
 /* for(pair<int, int> x : V)
    cout << x.first << ' ' << x.second << '\n'; */

    /* sau metoda 2
    for(vector<pair<int,int> >::iterator it = V.begin(); it != V.end(); it++)
      cout << (*it).first << ' ' << (*it).second << '\n'; */

  fin.close();

}
