import pandas as pd

films = pd.read_csv('dzP/dz7/m.csv')  
OCENKi = pd.read_csv('dzP/dz7/r.csv')  
OCENKi = OCENKi[OCENKi['rating'] == 5.0]

rating_counts = OCENKi.groupby('movieId').size()
# Находим фильм, который получил больше всего оценок 5.0
ret = rating_counts.idxmax()

ret = films[films['movieId'] == ret]


print(f"Фильм с наибольшим количеством оценок 5.0: {ret['title'].values[0]}")
