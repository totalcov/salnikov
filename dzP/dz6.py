from math import *
figure = input("Введите тип фигуры:")
figure = figure.lower() # понижаем регистр для проверки типа фигуры

if figure == "круг":
  rad = int(input("Введите радиус круга" ))
  if (rad > 0):
    s = 3.1415 * (rad ** 2)
    print("Площадь круга примерно равна", s)
  else:
    print("Ошибка ввода")
elif figure == "прямоугольник":
  a = int(input("Введите сторону a "))
  b = int(input("Введите сторону b "))
  if (a > 0 and b > 0):
    print("Площадь прямоугольника равна ", a*b)
  else:
    print("Ошибка ввода")
elif figure == "треугольник":
  a = int(input("Введите сторону a "))
  b = int(input("Введите сторону b "))
  c = int(input("Введите сторону c "))
  if (a > 0 and b > 0 and c > 0):
    if (a + b > c) and (a + c > b) and (b + c > a): #проверка на неравенство треугольника
      p = (a+b+c) / 2
      s = sqrt(p*(p-a)*(p-b)*(p-c)) # формула Герона
      print("Площадь треугольника равна", s)
    else:
      print("Данного треугольника не существует")
  else:
    print("Ошибка ввода")
else:
  print("Ошибка ввода")
