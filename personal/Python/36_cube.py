#!/usr/bin/python
 
COLORS = dict(zip((1 &lt;&lt; i for i in range(6)), ('P','Y','O','B','R','G')))
COLORS[False] = 'X'
 
used_towers = [0 for i in range(6)]
 
# definition with (1,2) and (3,2) switched
cube = ((1,3,4,5,2,0),
        (2,5,1,4,1,3),
        (0,1,3,2,5,4),
        (5,4,0,3,0,2),
        (4,2,5,0,3,1),
        (3,0,2,1,4,5))
 
solution = [[False for x in range(6)] for x in range(6)]
used = tuple(set() for i in range(6))
 
def test_color(pos, solution, used_towers, color, size):
 #check if tower of this size and color has already been used
 if color &amp; used_towers[size]:
  return False
 #check if tower has already been used in row or column:
 for i in range(6):
  if color == solution[pos/6][i]: return False
  if color == solution[i][pos%6]: return False
 # special conditions for the two special towers
 if (pos/6, pos%6) == (1,2) and color != 2: return False
 if (pos/6, pos%6) == (3,2) and color != 4: return False
 return True
 
def print_solution(solution):
 for i in range(6):
  print zip((COLORS[c] for c in solution[i]), (6 - s for s in cube[i]))
 
def solve(pos, solution, used_towers, best):
 if pos == 36: return best, solution
 size = cube[pos/6][pos%6]
 for i in range(6):
  color = 1 &lt;&lt; i
  if test_color(pos, solution, used_towers, color, size):
   used_towers[size] = used_towers[size] | color
   solution[pos/6][pos%6] = color
   if pos &gt; best:
    print "#######", pos + 1, "towers placed"
    print_solution(solution)
    best = pos
   best, solution = solve(pos+1, solution, used_towers, best)
   if best &gt;= 35:
    return best, solution
   solution[pos/6][pos%6] = False
   used_towers[size] = used_towers[size] ^ color
 return best, solution
 
solve(0, solution, used_towers, 0)