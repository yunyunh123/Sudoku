# Copyright 2021 Julia Hua jhua2@bu.edu
import requests, json, pprint
from random import randint
CELL_NUM = 81
SIZE = 9
PROBLEMS_NUM = 100 # append 100 puzzles to "problems.txt"

# Check file
with open("problems.txt", "r") as file:
  file.seek(0) # Move read cursor to start of file
  data = file.read(100)
  if len(data) > 0: # checks if file is not emtpy
    grid = "\n"
  else:
    grid = ""

for i in range(PROBLEMS_NUM):
  if i != 0:
    grid = grid + "\n"

  # Access API
  form = 'http://www.cs.utep.edu/cheon/ws/sudoku/new/?size={SIZE}&level={level}'
  level = randint(1, 3) # difficulty levels 1, 2, 3 available
  url = form.format(SIZE = SIZE, level = level)

  try:
    r = requests.get(url)
    data = r.json()
  except:
    print("Failed to receive Sudoku problem.")

  # Formatting data
  list = data['squares']
  setval = False

  try:
    cell = list.pop(0)
    cell_id = cell.get('x') * SIZE + cell.get('y')
  except:
    print("End of list")

  for x in range(CELL_NUM):

    if x % SIZE == 0 and x != 0:
      grid = grid + "\n"

    if setval == True:
      try:
        cell = list.pop(0)
        cell_id = cell.get('x') * SIZE + cell.get('y')
      except: # End of list reached
        setval = False

    if cell_id == x:
      grid = grid + str(cell.get('value'))
      setval = True
    else: 
      grid = grid + "0"
      setval = False

# Export/Append grid to file
with open("problems.txt", "a") as file:
  file.write(grid)
