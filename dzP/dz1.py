a = input("Введите строку 1: ")
b = input("Введите строку 2: ")
if (len(a) > len(b)):
  print("Строка 1 длиннее строки 2")
elif (len(b) > len(a)):
  print("Строка 2 длиннее строки 1")
else:
  print("Строки равны")