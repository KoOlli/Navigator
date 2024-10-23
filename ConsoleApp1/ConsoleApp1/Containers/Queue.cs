namespace S21
{
    public class Queue<T>
    {
        private List<T> list;

        public Queue()
        {
            list = new List<T>();
        }

        public Queue(params T[] items)
        {
            list = new List<T>();
            foreach (var item in items)
            {
                Push(item);
            }
        }

        public Queue(Queue<T> q)
        {
            list = new List<T>();
            foreach (var item in q.ToArray())
            {
                Push(item);
            }
        }

        public T Front() => list.Front();
        public T Back() => list.Back();
        

        public void Push(T value)
        {
            list.PushBack(value);
        }

        public void Pop()
        {
            list.PopFront();
        }

        public bool IsEmpty()
        {
            return list.Size() == 0;
        }

        public int Size()
        {
            return list.Size();
        }

        public void Swap(Queue<T> other)
        {
            var tempList = other.list;
            other.list = list;
            list = tempList;
        }

        public T[] ToArray() => list.ToArray();
    }
}