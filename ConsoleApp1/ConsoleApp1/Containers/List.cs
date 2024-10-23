using System;
using System.Collections;
using System.Collections.Generic;

namespace S21
{
    public class List<T> : IEnumerable<T>
{
    private Node<T> head_;
    private Node<T> tail_;
    private Node<T> afterEnd_;
    private int size_;
    public List()
    {
        afterEnd_ = new Node<T>(default(T)); // sentinel node
        afterEnd_.Prev = tail_;
        head_ = null;
        tail_ = null;
        size_ = 0;
    }

    // Конструктор с количеством элементов
    public List(int n) : this()
    {
        while (n > 0)
        {
            PushFront(default(T)); // Заполняем значением по умолчанию
            n--;
        }
    }

    // Конструктор с инициализационным списком
    public List(IEnumerable<T> items) : this()
    {
        foreach (var item in items)
        {
            PushBack(item);
        }
    }

    // // Конструктор копирования
    // public List(List<T> other) : this()
    // {
    //     Copy(other);
    // }
    //
    // // Конструктор перемещения
    // public List(List<T> other)
    // {
    //     afterEnd_ = new Node<T>(default(T));
    //     *this = other; // подразумевается перегрузка оператора перемещения
    // }
    //
    // // Деструктор
    // ~List()
    // {
    //     Clear();
    // }

    // // Перегрузка оператора присваивания (копирование)
    // public List<T> Copy(List<T> other)
    // {
    //     Clear();
    //     foreach (var item in other)
    //     {
    //         PushBack(item);
    //     }
    //     return this;
    // }
    //
    // // Перегрузка оператора присваивания (перемещение)
    // public List<T> Move(List<T> other)
    // {
    //     head_ = other.head_;
    //     tail_ = other.tail_;
    //     afterEnd_.Prev = tail_;
    //     if (tail_ != null) tail_.Next = afterEnd_;
    //     size_ = other.size_;
    //
    //     // Обнуляем оригинальный список
    //     other.head_ = null;
    //     other.tail_ = null;
    //     other.size_ = 0;
    //
    //     return this;
    // }

    public T Front() => head_.Data;

    public T Back() => tail_.Data;
    
    // Метод для проверки пустоты списка
    public bool Empty() => head_ == null && tail_ == null;
    
    public int Size() => size_;

    public void Clear()
    {
        while (head_ != null)
        {
            PopFront();
        }
        head_ = null;
        tail_ = null;
    }

    public IEnumerator<T> GetEnumerator()
    {
        Node<T> current = head_;
        while (current != null)
        {
            yield return current.Data;
            current = current.Next;
        }
    }

    IEnumerator IEnumerable.GetEnumerator() => GetEnumerator();

    public void PushBack(T value)
    {
        var newNode = new Node<T>(value);
        if (head_ == null)
        {
            head_ = newNode;
            tail_ = newNode;
            newNode.Next = afterEnd_;
            afterEnd_.Prev = tail_;
        }
        else
        {
            newNode.Prev = tail_;
            tail_.Next = newNode;
            tail_ = newNode;
            tail_.Next = afterEnd_;
            afterEnd_.Prev = tail_;
        }
        size_++;
    }

    public void PopBack()
    {
        if (tail_ == null) return;
        var buf = tail_;
        tail_ = tail_.Prev;
        if (size_ > 1)
        {
            tail_.Next = afterEnd_;
        }
        else
        {
            head_ = null;
        }
        afterEnd_.Prev = tail_;
        buf = null; // Удаляем ссылку; в C# сборка мусора произойдет автоматически
        size_--;
    }

    public void PushFront(T value)
    {
        var newNode = new Node<T>(value);
        if (head_ == null)
        {
            head_ = newNode;
            tail_ = newNode;
            newNode.Next = afterEnd_;
            afterEnd_.Prev = tail_;
        }
        else
        {
            newNode.Next = head_;
            head_.Prev = newNode;
            head_ = newNode;
        }
        size_++;
    }

    public void PopFront()
    {
        if (head_ == null) return;
        Node<T> buf = head_;
        if (size_ > 1)
        {
            head_ = head_.Next;
            head_.Prev = null;
        }
        else
        {
            head_ = null;
            tail_ = null;
            afterEnd_.Prev = null;
        }
        buf = null; // Удаляем ссылку; в C# сборка мусора произойдет автоматически
        size_--;
    }

    public void Insert(int index, T value)
    {
        if (index < 0 || index > size_)
            throw new ArgumentOutOfRangeException(nameof(index));

        var newNode = new Node<T>(value);

        if (index == 0)
        {
            PushFront(value);
        }
        else if (index == size_)
        {
            PushBack(value);
        }
        else
        {
            Node<T> current = head_;
            for (int i = 0; i < index; i++)
            {
                current = current.Next;
            }
            newNode.Prev = current.Prev;
            newNode.Next = current;
            current.Prev.Next = newNode;
            current.Prev = newNode;
            size_++;
        }
    }

    public void Erase(int index)
    {
        if (index < 0 || index >= size_)
            throw new ArgumentOutOfRangeException(nameof(index));

        if (index == 0)
        {
            PopFront();
        }
        else if (index == size_ - 1)
        {
            PopBack();
        }
        else
        {
            Node<T> current = head_;
            for (int i = 0; i < index; i++)
            {
                current = current.Next;
            }
            Node<T> prev = current.Prev;
            Node<T> next = current.Next;
            prev.Next = next;
            next.Prev = prev;
            current = null; // Удаляем ссылку; в C# сборка мусора произойдет автоматически
            size_--;
        }
    }

    public void Swap(List<T> other)
    {
        // Используем временный список для выполнения обмена
        var temp = head_;
        head_ = other.head_;
        other.head_ = temp;

        temp = tail_;
        tail_ = other.tail_;
        other.tail_ = temp;

        int tempSize = size_;
        size_ = other.size_;
        other.size_ = tempSize;
    }

    public void Merge(List<T> other)
    {
        // К примеру, здесь просто комбинируем списки
        foreach (var item in other)
        {
            PushBack(item);
        }
        other.Clear();
    }

    public void Splice(int index, List<T> other)
    {
        if (index < 0 || index > size_)
            throw new ArgumentOutOfRangeException(nameof(index));

        if (other.size_ == 0) return;

        if (index == 0)
        {
            // Добавляем в начало
            afterEnd_.Prev = other.tail_;
            other.tail_.Next = head_;
            head_ = other.head_;
        }
        else
        {
            // Добавляем в указанное место
            Node<T> current = head_;
            for (int i = 0; i < index - 1; i++)
            {
                current = current.Next;
            }

            Node<T> temp = current.Next;
            current.Next = other.head_;
            other.tail_.Next = temp;
            if (temp != null)
            {
                temp.Prev = other.tail_;
            }
            else
            {
                tail_ = other.tail_;
            }
        }

        size_ += other.size_;
        other.Clear();
    }

    public void Reverse()
    {
        List<T> reverseList = new List<T>();
        Node<T> current = head_;
        while (current != null)
        {
            reverseList.PushFront(current.Data);
            current = current.Next;
        }
        head_ = reverseList.head_;
        tail_ = reverseList.tail_;
        size_ = reverseList.size_;
    }

    public void Unique()
    {
        List<T> newList = new List<T>();

        if (head_ != null)
        {
            newList.PushBack(head_.Data);
            for (Node<T> current = head_.Next; current != null; current = current.Next)
            {
                if (!EqualityComparer<T>.Default.Equals(current.Data, newList.tail_.Data))
                {
                    newList.PushBack(current.Data);
                }
            }
        }

        head_ = newList.head_;
        tail_ = newList.tail_;
        size_ = newList.size_;
    }

    public void Sort()
    {
        if (size_ <= 1) return;

        var sortedList = new List<T>();
        Node<T> current = head_;
        while (current != null)
        {
            sortedList.PushBack(current.Data);
            current = current.Next;
        }

        sortedList.Sort(); // Используем стандартный метод сортировки

        // Теперь обновляем сам список с отсортированными данными
        head_ = null;
        tail_ = null;
        size_ = 0;

        foreach (var item in sortedList)
        {
            PushBack(item);
        }
    }

    private void Copy(List<T> other)
    {
        if (other == null) throw new ArgumentNullException(nameof(other));
        Clear();
        Node<T> current = other.head_;
        while (current != null)
        {
            PushBack(current.Data);
            current = current.Next;
        }
    }
    // Здесь можно добавить другие методы из исходного C++ класса.
    
    // public T[] ToArray()
    // {
    //     var array = new T[size_];
    //     foreach (var VARIABLE in COLLECTION)
    //     {
    //         
    //     }
    //     return array;
    // }
    
    public T[] ToArray()
    {
        // Создаем массив размером size_
        T[] array = new T[size_];
        Node<T> current = head_; // Начинаем с головы
    
        int index = 0;
        for(int i = 0; i < size_; i++)
        {
            array[index++] = current.Data; // Сохраняем значение в массив
            current = current.Next; // Переходим к следующему узлу
        }

        return array; // Возвращаем конечный массив
    }

}
}