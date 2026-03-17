day = int(input("Введите день в месяце "))
month = input("Введите месяц ")
month = month.lower() # понижаем регистр для проверки


if (21 <= day <= 31 and month == "март") or (1 <= day <= 19 and month == "апрель"):
  print("Ваш знак зодиака - Овен")
elif (20 <= day <= 30 and month == "апрель") or (1 <= day <= 20 and month == "май"):
  print("Ваш знак зодиака - Телец")
elif (21 <= day <= 31 and month == "май") or (1 <= day <= 20 and month == "июнь"):
  print("Ваш знак зодиака - Близнецы")
elif (21 <= day <= 30 and month == "июнь") or (1 <= day <= 22 and month == "июль"):
  print("Ваш знак зодиака - Рак")
elif (23 <= day <= 31 and month == "июль") or (1 <= day <= 22 and month == "август"):
  print("Ваш знак зодиака - Лев")
elif (23 <= day <= 31 and month == "август") or (1 <= day <= 22 and month == "сентябрь"):
  print("Ваш знак зодиака - Дева")
elif (23 <= day <= 30 and month == "сентябрь") or (1 <= day <= 23 and month == "октябрь"):
  print("Ваш знак зодиака - Весы")
elif (24 <= day <= 31 and month == "октябрь") or (1 <= day <= 21 and month == "ноябрь"):
  print("Ваш знак зодиака - Скорпион")
elif (22 <= day <= 30 and month == "ноябрь") or (1 <= day <= 21 and month == "декабрь"):
  print("Ваш знак зодиака - Стрелец")
elif (22 <= day <= 31 and month == "декабрь") or (1 <= day <= 19 and month == "январь"):
  print("Ваш знак зодиака - Козерог")
elif (20 <= day <= 30 and month == "январь") or (1 <= day <= 18 and month == "февраль"):
  print("Ваш знак зодиака - Водолей")
elif (19 <= day <= 29 and month == "февраль") or (1 <= day <= 20 and month == "март"):
  print("Ваш знак зодиака - Рыбы")
else:
  print("Ошибка ввода")


