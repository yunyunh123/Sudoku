import requests, json, pprint

url = 'http://maps.googleapis.com/maps/api/directions/json'

params = dict(
  origin = 'Chicago, IL',
  destination = 'Los+Angeles,CA',
  waypoints= 'Joplin,MO|Oklahoma+City,OK',
  sensor='false')

data = requests.get(url=url, params=params)
binary = data.content
output = json.loads(binary)

print(output['status'])
#url = 'http://www.cs.utep.edu/cheon/ws/sudoku/new/[?size][&level]'
#response = requests.get("http://www.cs.utep.edu/cheon/ws/sudoku/new/[?size][&level]").json()
# print(response.status_code)
# data = response.json()
# sizes: 4x4, 9x9
# levels: [1, 2, 3] [easy, medium, hard]
# default: size 4, level 1
# print(data['levels'])