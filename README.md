# Solitaire

Асташкин Фёдор Кириллович

Задача №5 / Алгоритмы



# Команды, чтобы  запустить програму:

1) git clone https://github.com/FflashkingF/Solitaire

2) cd Solitaire

3) mkdir build

4) cd build

6) cmake ..
   
7) make (после этой команды появился исполняемый файл - ../bin/Solitaire (Solitaire/bin/Solitaire)


# Корректный ввод:
AKQJt9876 

AKQJt9876

AKQJt9876

AKQJt9876

AKQJt9876

AKQJt9876

AKQJt9876

AKQJt9876

(нужно ввести 8 кучек по 9 карт от нижней до верхней)

(шестёрка - 6)
(семёрка - 7)

(восьмёрка - 8)
(девятка - 9)

(десятка - t)
(Валет -J)
 
(Дама - Q)
(Король - K)

(Туз - A)

Изначально для решения задачи использовался BFS с полным перебором(но отсечением одинаковых состояний игры), 

Однако потом был задействован оптимизационный алгоритм с введением эвристической функции (по кол-ву оставшихся карт, по уже частично собранным последовательностям)
