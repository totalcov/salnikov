ids = {
    'user1': [213, 213, 213, 15, 213],
    'user2': [54, 54, 119, 119, 119],
    'user3': [213, 98, 98, 35]
}

unique_geo = set()


for geo_list in ids.values():

    unique_geo.update(geo_list)

print("Результат:", unique_geo)