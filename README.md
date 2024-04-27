Код с семинаров группы WEB/ML-13

Семинар 1
---------
Запись: https://www.youtube.com/watch?v=zFw1yF_rTQs

**lab1_queue.cpp**

Реализация очереди на односвязных списках. Обращаю внимание, что в ДЗ очередь должна быть реализована на динамическом зацикленном массиве (в варианте 3 -- на стеках, которые в свою очередь реализованы на динамическом массиве). Это значит, что:
1) В процессе работы массив должен уметь расширяться. Нельзя предсоздавать массив гигантского размера, в который гарантированно влезет весь ввод по условию.
2) Расширение массива должно происходить только тогда, когда пустых ячеек в массиве не осталось. Например, если при дописывании в конец достигли последней ячейки массива, нужно попытаться перепрыгнуть в первую и продолжить запись оттуда.

Иллюстрация:
- Картинка б) получилась из а) после добавления в конец очереди элементов 17, 3, 5.
- Картинка в) получилась из б) после извлечения одного элемента из головы очереди.

![Зацикленный буфер](https://user-images.githubusercontent.com/1894130/194703133-14d6ab57-de4f-4cba-b15d-0bdfe4145b10.png)

Семинар 2
---------
Запись: https://www.youtube.com/watch?v=zFw1yF_rTQs

**lab2_comparators.cpp**

Пример пробрасывания компаратора в функцию. В mySort для этой цели добавлен параметр cmp типа "указатель на функцию". В mySort2 мы пошли еще дальше, ввели дополнительный шаблонный тип Comparator, позволяющий пробросить четвертым аргументом что угодно, что можно "вызывать".

При реализации класса Heap компаратор должен храниться внутри кучи, инициализироваться в момент создания кучи. Не надо пробрасывать компаратор при вызове каждого метода.

Семинар 3
---------
Запись: https://www.youtube.com/watch?v=szVpkhFjLXw

**lab3_partition.cpp**

Пример реализации функции partition, где в качестве опорного элемента берется самый левый в массиве, итераторы идут навстречу друг другу. В домашнем задании запрещено использование рекурсии, итераторы сонаправлены, выбор опорного элемента согласно варианту.

**lab3_counting_sort.cpp**

Реализация сортировки подсчетом.

Семинар 4
---------
Запись: https://www.youtube.com/watch?v=sadmpgW8UYY

**lab4_hashtable.cpp**

Реализация хэш-таблицы с разрешением коллизий методом цепочек. В домашних работах нужно использовать метод открытой адресации.

Семинар 5
---------
Запись: https://www.youtube.com/watch?v=1p4TF5XVByE

**lab5_avltree.cpp**

Реализация AVL дерева. Необходимо его доработать:
  - добавить компаратор
  - логику findMin и removeMin нужно объединить в один метод findAndRemoveMin
  - элемент на место удаляемого берется из более глубокого поддерева (либо максимальный из левого, либо минимальный из правого)

**lab5_btree.cpp**

Частичная реализация B-дерева. Для полноценной вставки не хватает метода splitChild, его нужно дописать самому (на слайдах есть псевдокод).

Семинар 6
---------
Запись: https://www.youtube.com/watch?v=X3mzNitI-C0

**lab6_bitwriter.cpp**

Пример реализации логики побитовой записи: накапливаем вывод во внутреннем буфере.
Текстовое описание устройства функций Encode/Decode: https://pastebin.com/raw/CefJ2ykB
