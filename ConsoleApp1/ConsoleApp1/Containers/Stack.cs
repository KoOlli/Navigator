namespace S21
{
    public class Stack<T>
    {
        private List<T> list_;
        
        public Stack()
        {
            list_ = new List<T>();
        }

        public Stack(params T[] items) 
        {
            foreach (var item in items)
            {
                Push(item);
            }
        }

        public Stack(Stack<T> other) 
        {
            list_ = new List<T>();
            foreach (var item in other.ToArray())
            {
                Push(item);
            }
        }

        public void Clear()
        {
            list_.Clear();
        }

        public T Top() => list_.Back();

        public bool IsEmpty => list_.Empty();

        public int Size => list_.Size();

        public void Push(T item)
        {
            list_.PushBack(item);
        }

        public void Pop() => list_.PopBack();

        public void Swap(Stack<T> other)
        {
            if (this == other) return;

            var temp = list_;
            list_ = other.list_;
            other.list_ = temp;
        }

        public T[] ToArray() => list_.ToArray();

    }
}