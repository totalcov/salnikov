name1 = ["Москва", "Питер", "Архангельск"]
name2 = ["Будапешт", "Москва", "Прага", "Новгород"]

r = {}
name1 = set(name1)
name2 = set(name2)

for i in name1:
    if i not in r:
        r[i] = 1
    else:
        r[i] +=1


for i in name2:
    if i not in r:
        r[i] = 1
    else:
        r[i] +=1
flag = 0
for i in r:
    if r[i] != 1:
        print("Есть общий город")
        flag = 1
        break
if not flag:
    print("Нет общих городов")