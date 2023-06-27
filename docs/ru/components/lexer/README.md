# Лексический анализатор

Лексический анализатор – модуль, читающий поток символов исходной программы и группирующий их в список токенов (лексем или слов языка программирования).

Существует два варианта взаимодействия лексического анализатора с синтаксическим:
* параллельный – синтаксический анализатор постоянно запрашивает новый токен для своей работы;
* последовательный – сначала лексический анализатор составляет список всех токенов и передает их далее синтаксическому анализатору.

## Подробнее

* [Список токенов](tokens.md)
* [Описание работы анализатора](processing.md)
* [Пример работы анализатора](example.md)
* [Основной класс `Lexer`](class.md)

[_Назад_](../README.md)