# Обработка ошибок при анализе

При анализе кода могут возникать ошибки. Существует несколько способов реакции на них:
* «Panic-Mode recovery» – анализатор удалит встреченный узел, вызывающий ошибку, и попытается изучить окрестность для восстановления нормальной работы;
* «Phrase-Level Recovery» – анализатор попытается локально разрешить ошибку и продолжить работу;
* «Error Production» – анализатор сохраняет ошибки и после выдает пользователю диагностическое сообщение;
* «Global Correction» – анализатор попытается исправить ошибку, изучив весь код программы (коррекция может быть опасной, так как программа может работать не так, как задумывал пользователь).

Семантический анализатор может вызывать следующие типы ошибок:
* отсутствует функция main;
* использована переменная, не определенная в данной области видимости;
* использована не определенная функция;
* внутри функции, которая не должна возвращать никакого значения, пользователь что-то пытается вернуть;
* ошибки приведения типов;
* переопределение переменной.

При нахождении ошибки анализатор добавляет ее в массив, а после окончания проверки всего дерева оповещает пользователя.

## Пример

Код:

```py
def main() -> None:
    x: int = 1
    y: float = 2 + z
```

Ошибка:

```
SEMANTIZER:
  In line 3 in column 19 in file sample.py error:
    z was not declared in this scope
```

[_Назад_](README.md)