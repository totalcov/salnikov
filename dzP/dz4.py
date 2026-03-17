width = int(input("Введите ширину в сантиметрах "))
length = int(input("Введите длину в сантиметрах "))
height = int(input("Введите высоту в сантиметрах "))

if (width > 0 and length > 0 and height > 0): # проверка входных данных на положительное значение
  if (width <= 15) and (length <= 15) and (height <= 15):
    print("Коробка №1")
  elif (width > 200) or (length > 200) or (height > 200):
    print("Упаковка для лыж")
  elif (15 < width < 50) or (15 < length < 50) or (15 < height < 50):
    print("Коробка №2")
  else:
    print("Коробка №3")
else:
  print("Ошибка ввода")
