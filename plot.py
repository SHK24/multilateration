import pandas as pd
import matplotlib.pyplot as plt

# Замените 'your_file.csv' на путь к вашему файлу
file_path = 'plot_data3.txt'

# Чтение данных из CSV файла
data = pd.read_csv(file_path, sep=';', header=0)

# Удаляем пустые столбцы, если они есть
data = data.dropna(axis=1, how='all')

# Преобразуем столбец 'dev' в числовой формат
data['dev'] = pd.to_numeric(data['dev'], errors='coerce')

# Удаляем строки с NaN после преобразования
data = data.dropna()

# Извлекаем столбец dev
x = data['dev']

# Создаем график
plt.figure(figsize=(10, 6))

# Словарь для стилей линий
styles = {
    'Bancroft': {'color': 'blue', 'linestyle': '-', 'marker': 'o'},
    'Beck': {'color': 'orange', 'linestyle': '--', 'marker': 's'},
    'Grad': {'color': 'green', 'linestyle': '-.', 'marker': 'D'},
    'Linear': {'color': 'purple', 'linestyle': '-', 'marker': 'x'},
    'LSQ': {'color': 'red', 'linestyle': '--', 'marker': 'P'},
    'RTK': {'color': 'cyan', 'linestyle': '-', 'marker': '^'},
    'Simple': {'color': 'magenta', 'linestyle': ':', 'marker': 'h'}
}

# Проходим по всем остальным столбцам и строим линии
for column in data.columns[1:]:
    if column in styles:
        plt.plot(x, data[column], label=column,
                 color=styles[column]['color'],
                 linestyle=styles[column]['linestyle'],
                 marker=styles[column]['marker'],
                 alpha=0.7)  # Увеличиваем прозрачность
    else:
        # Общий стиль для остальных линий
        plt.plot(x, data[column], label=column,
                 color='gray', linestyle='-', alpha=0.5)

# Настраиваем ось Y как логарифмическую
plt.yscale('log')

# Добавляем подписи и легенду
plt.xlabel('dev')
plt.ylabel('Значения (логарифмическая шкала)')
plt.title('График значений по столбцам')
plt.legend()
plt.grid()

# Показываем график
plt.show()
