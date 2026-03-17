year = int(input("Введите год: "))

if (year > 0): # проверка на правильность года
  if (year % 4 == 0 and year % 100 != 0) or (year % 400 == 0):
    print("Год високосный")
  else:
    print("Год невисокосный")
else:
  print("Ошибка ввода")
  