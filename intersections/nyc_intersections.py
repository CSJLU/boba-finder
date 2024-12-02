import requests

API_KEY = "You can't see this :)"
BASE_URL = "https://maps.googleapis.com/maps/api/geocode/json"

# Returns the latitude and longitude data for intersections of streets
def get_intersection_coordinates(street_one, street_two):
    address = f"{street_one} and {street_two}, NYC"
    params = {"address": address, "key": API_KEY}
    response = requests.get(BASE_URL, params=params)

    data = response.json()
    if data['results']:
        location = data['results'][0]['geometry']['location']
        return location['lat'], location['lng']
    return None

# Returns the latitude and longitude data for boba shop locations
def get_boba_coordinates(address):
    params = {"address": address, "key": API_KEY}
    response = requests.get(BASE_URL, params=params)
    if response.status_code == 200:
        data = response.json()
        if data['results']:
            location = data['results'][0]['geometry']['location']
            return location['lat'], location['lng']
    return None

intersection_streets = [
    ("5th Ave", "36st St"),
    ("5th Ave", "35th St"),
    ("5th Ave", "34th St"),
    ("5th Ave", "33rd St"),
    ("5th Ave", "32nd St"),
    ("5th Ave", "31st St"),
    ("5th Ave", "30th St"),
    ("6th Ave", "36st St"),
    ("6th Ave", "35th St"),
    ("6th Ave", "34th St"),
    ("6th Ave", "33rd St"),
    ("6th Ave", "32nd St"),
    ("6th Ave", "31st St"),
    ("6th Ave", "30th St"),
    ("7th Ave", "36st St"),
    ("7th Ave", "35th St"),
    ("7th Ave", "34th St"),
    ("7th Ave", "33rd St"),
    ("7th Ave", "32nd St"),
    ("7th Ave", "31st St"),
    ("7th Ave", "30th St"),
    ("8th Ave", "36st St"),
    ("8th Ave", "35th St"),
    ("8th Ave", "34th St"),
    ("8th Ave", "33rd St"),
    ("8th Ave", "32nd St"),
    ("8th Ave", "31st St"),
    ("8th Ave", "30th St"),
    ("9th Ave", "36st St"),
    ("9th Ave", "35th St"),
    ("9th Ave", "34th St"),
    ("9th Ave", "33rd St"),
    ("9th Ave", "32nd St"),
    ("9th Ave", "31st St"),
    ("9th Ave", "30th St"),
    ("10th Ave", "36st St"),
    ("10th Ave", "35th St"),
    ("10th Ave", "34th St"),
    ("10th Ave", "33rd St"),
    ("10th Ave", "32nd St"),
    ("10th Ave", "31st St"),
    ("10th Ave", "30th St")
]

intersection_coordinates = []
for street_one, street_two in intersection_streets:
    result = get_intersection_coordinates(street_one, street_two)
    if result:
        intersection_coordinates.append(result)

print("Street intersection coordinates")
for lat, lng in intersection_coordinates:
    print(lat, lng)


# Boba shop specific addresses
addresses = [
    ("20 Hudson Yards, New York, NY 10001"), # Xing Fu Tang
    ("TRYP WYNDHAM HOTEL, 345 W 35th St, New York, NY 10001"), # BOBA KAFE
    ("875 6th Ave, New York, NY 10001"), # FIFTYLAN Koreatown 
    ("75 W 38th St, New York, NY 10018"), # Gong Cha
    ("42 W 38th St, New York, NY 10018"), # Kung Fu Tea
    ("1271 Broadway, New York, NY 10001"), # Biao Sugar
]

boba_coordinates = []
for address in addresses:
    result = get_boba_coordinates(address)
    if result:
        boba_coordinates.append(result)

print("\n\n\n")
print("Boba shop coordinates:")
for lat, lng in boba_coordinates:
   print(lat, lng)