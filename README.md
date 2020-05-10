# CodeBase
Это хранилище кода алгоритмов, структур данных и программ, написанных мной в течение обучения в университете ИТМО. Хранилище будет пополняться (если, конечно, не буду забывать это делать) с такой же скоростью, с какой я буду решать лабораторные работы или просто задания. Ниже представлено содержание данного репозитория для быстрого ориентирования, а также некоторые планы, отмеченные **(TODO)**. 

## Алгоритмы
---
#### Сортировки и подобное

+ **Квадратичные сортировки**
    + **(TODO)** Пузырьковая сортировка (Bubble sort)
    + **(TODO)** Сортировка вставками (Insertion sort)
    + **(TODO)** Сортировка выбором (Selection sort)
+ **Квазилинейные сортировки на сравнениях**
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/algorithms/sortings/quick_sort.cpp)) Быстрая сортировка Хоара (Quicksort) 
    + **(TODO)** Сортировка слиянием (Merge sort)
    + **(TODO)** Сортировка кучей (Heap sort)
+ **Прочие сортировки**
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/algorithms/miscellaneous/kth_element.cpp)) Поиск k-ой порядковой статистики (k-th element) 
    + **(TODO)** Поиск k-ой порядковой статистика за линейное время
    + **(TODO)** Сортировка подсчётом (Counting sort)
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/algorithms/sortings/radix_sort.cpp)) Поразрядная сортировка (LSD Radix sort)
    + **(TODO)** Битонная многопоточная сортировка

#### Алгоритмы поиска
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/algorithms/miscellaneous/binary_search.cpp)) Целочисленный двоичный поиск (Binary search) 

#### Алгоритмы на графах
+ **Алгоритмы обхода графов и их применение**
    + **(TODO)** Обход графа в глубину рукерсивно
    + **(TODO)** Обход графа в глубину с помощью стека
    + **(TODO)** Обход графа в ширину послойно
    + **(TODO)** Обход графа в ширину с помощью очереди
    + **(TODO)** Поиск мостов и компонент рёберной двусвязности в неориентированном графе
    + **(TODO)** Поиск точек сочленения в неориентированном графе
    + **(TODO)** Топологическая сортировка графа
    + **(TODO)** Алгоритм Косарайю поиска конденсации графа в два обхода в глубину 
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/algorithms/graphs/condensation_tarjan.cpp)) Алгоритм Тарьяна поиска конденсации графа в один обход в глубину
+ **Алгоритмы поиска кратчайшего пути**
    + **(TODO)** Алгоритм Дейкстры
    + **(TODO)** Алгоритм Форда - Беллмана
    + **(TODO)** Алгоритм Флойда - Уоршелла
+ **Алгоритмы поиска минимального остова графа** 
    + **(TODO)** Алгоритм Краскала с использованием СНМ
    + **(TODO)** Алгоритм Прима (модификация алгоритма Дейкстры)
    + **(TODO)** Алгоритм Борувки
    + **(TODO)** Алгоритм двух китайцев (для ориентированных графов)
+ **Алгоритмы на деревьях**
    + **(TODO)** Поиск диаметра дерева с помощью двух обходов в глубину
    + **(TODO)** Поиск диаметра дерева с помощью динамического программирования
+ **Алгоритмы в транспортных сетях**
    + **(TODO)** Алгоритм Форда - Фалкерсона поиска максимального потока
    + **(TODO)** Алгоритм Эдмондса - Карпа поиска максимального потока
    + **(TODO)** Алгоритм Диница поиска максимального потока
    + **(TODO)** Алгоритм проталкивания предпотока
    + **(TODO)** Поиск минимального разреза транспортной сети

#### Динамическое программирование
+ **Линейное динамическое программирование**
    + **(TODO)** Числа Фибоначчи (или задача о кузнечике)
    + **(TODO)** Задача о черепашке
    + ...
+ **Динамическое программирование на подотрезках**
    + **(TODO)** Задача про распил брусьев 
    + ...
+ **Динамическое программирование на подмножествах**
    + ... 
+ **Динамическое программирование по профилю** 
    + **(TODO)** Симпатичные узоры
    + **(TODO)** Задача про паркет из домино
    + ...
+ [**Оптимизации в динамическом программировании**](https://codeforces.com/blog/entry/8219?locale=ru)
    + **(TODO)** Техника "разделяй и властвуй" (Divide and Conquer) **(O(kn^2) -> O(knlogn))**
    + **(TODO)** Convex-hull trick **(O(n^2) -> O(nlogn))**
    + **(TODO)** Оптимизация Кнута **(O(n^3) -> O(n^2))**
    + **(TODO)** Lambda - оптимизация **(O(n^2) -> O(nlogn))**

## Структуры данных
---

#### Линейные структуры данных
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/linear_data_structures/stack_on_list.cpp)) Стек на односвязном списке
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/linear_data_structures/stack_on_vector.cpp)) Стек на динамиеском массиве (vector)
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/linear_data_structures/queue_on_list.cpp)) Очередь на односвязном списке
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/linear_data_structures/queue_on_vector.cpp)) Очередь на динамическом массиве
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/linear_data_structures/priority_queue_on_stacks.cpp)) Приоритетная очередь на двух стеках

#### Система непересекающихся множеств
+ **(TODO)** СНМ на динамических массивах с переливанием
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/set_structures/dsu.cpp)) СНМ с помощью леса деревьев

#### Хеш структуры
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/hash_structures/linked_hash_set.cpp)) Множество с сохранением порядка (set)
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/hash_structures/hash_map.cpp)) Отображение (map)
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/hash_structures/linked_hash_map.cpp)) Отображение с сохранением порядка
+ ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/hash_structures/linked_hash_multimap.cpp)) Мультиотображение (multimap) с сохранением порядка
+ **(TODO)** Полиномиальный хеш для строк
#### Двоичные деревья
+ **Деревья поиска**
    +  (*явный ключ*: [**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/splay_tree/splay_tree.cpp)) Самобалансирующееся Splay - дерево
    +  (*явный ключ*: [**Java**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/avl_tree/AVLTree.java)) AVL - дерево
    +  (*явный ключ*: [**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/cartesian_tree/treap.cpp), *неявный ключ*: [**C#**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/cartesian_tree/CartesianTree.cs), [**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/cartesian_tree/implicit_treap.cpp)) Декартово дерево (Treap)
+ **Куча (Heap)**
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/heap/priorty_queue_on_heap.cpp)) Приоритетная очередь с помощью кучи
    + ([**C++**](https://github.com/UnrealEugene/CodeBase/blob/master/data_structures/binary_trees/heap/heap_check.cpp)) Проверка на инвариант кучи
