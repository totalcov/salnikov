boys = ["Alex", "John", "Richard"]
girls = ["Kira", "Trisha"]


if len(boys) != len(girls):
    print("ВНимание, кто то может остаться без пары")
else:
    boys_sort = sorted(boys)
    girls_sort = sorted(girls)
    for i in range(len(boys_sort)):
        print(boys_sort[i], "и ", girls_sort[i])