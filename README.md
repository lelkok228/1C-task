# First practical work in Formal Languages and Broadcasts

#### Задача:

*(Код задачи: 141)*

Две колоды карт (по 36 штук) соединяются и перемешиваются, а после раскладываются в 8 кучек по 9 карт. Будем считать, что в каждой колоде есть 4 набора вида туз-король-дама-валет-10-9-8-7-6, а масти **всех** 72 карт(т.е. и в первой колоде и во второй) совпадают.В каждой куче верхняя карта лежит лицом вверх(открытая карта), а все остальные - рубашкой(закрытые карты). 

Можно работать только с открытыми картами в каждой из кучек, а именно перекладывать одну или несколько последовательных карт меньшего номинала на карту большего. Если перекладываются несколько карт, то они должны быть соседними по значению и убывать. Например, можно переложить с кучи три карты валет-10-9, если девятка лежит на вершине. Также, самая нижняя карта должна отличаться по значению на один от той, на которую ее кладут. Например, 6 можно перекладывать на 7, 7 можно перекладывать на 8 и т.д. Набор карт, например, валет-10-9, можно перекладывать на даму. Также, всегда можно перекладывать наборы карт в пустую стопку.
Если в одной из кучек оказалось 9 карт в правильном порядке (туз-король-дама-валет-10-9-8-7-6), то этот набор убирается. Если после какого-то перемещения есть кучка, в которой на вершине лежит закрытая карта, то она становится открытой.
Необходимо реализовать программу, которая по информации об исходном состоянии восьми кучек посчитает, можно ли будет убрать все карты.

#### Алгоритм:

Ограничимся 100.000 ходами. Каждый ход будет состоять в случайном выборе двух кучек и переносе максимально возможного числа карт из первой кучи во вторую. Если за эти ходы все стопки опустеют, то можно удалить все карты, в противном случае решение не было найдено этим алгоритмом.

#### Возможные модификации:

Так как задача формулируется для колод с одной мастью, то для более 90% раскладок существует решение, что не достигается данным алгоритмом, поэтому можно прибегнуть к следующим оптимизациям:
1. Старайться открывать лежащие рубашкой вверх карты при любом удобном случае.
2. Пытаться как можно быстрее освободить хотя бы одну игровую стопку.
3. В первую очередь собирать последовательности карт на картах старшего достоинства.

#### Ввод:

На ввод подаются 8 строк, каждая из который описывает одну стопку. Одна стопка описывается 9-ью картами, введеными через пробел, последняя карта в строке является самой верхней. Каждая карта задается набором символов: карты достоинством от 6 до 10, задаются соответствующим числом, валет - "J", дама - "Q", король - "K", туз - "A".
Приммер ввода:
```
A A A A K K K K Q
Q Q Q J J J J 10 10
10 10 9 9 9 9 8 8 8
8 7 7 7 7 6 6 6 6
A A A A K K K K Q
Q Q Q J J J J 10 10
10 10 9 9 9 9 8 8 8
8 7 7 7 7 6 6 6 6
```

