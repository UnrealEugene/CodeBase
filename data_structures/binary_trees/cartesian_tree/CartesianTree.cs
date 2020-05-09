using System;
using System.Diagnostics;
using System.Linq;
  
namespace CartesianTree {
    internal static class Program {
        public static void Main(string[] args) {
            var c = Console.ReadLine()?.Split(' ');
            int n = int.Parse(c[0]), m = int.Parse(c[1]);
            IImplicitTree tree = new ImplicitCartesianTree();
            for (int i = 0; i < n; i++)
                tree.InsertAt(i, i + 1);
            for (int i = 0; i < m; i++) {
                var arr = Console.ReadLine()?.Split(' ').Select(int.Parse).ToArray();
                tree.MoveToFront(arr[0] - 1, arr[1]);
            }
            Print(tree);
        }
  
        private static void Print(IImplicitTree tree) {
            for (var i = 0; i < tree.Size(); i++) {
                Console.Write(tree.GetAt(i) + " ");
            }
            Console.WriteLine();
        }
    }
  
    internal interface IImplicitTree {
        void InsertAt(int position, int value);
        void RemoveAt(int position);
        int GetAt(int position);
        int Size();
        void MoveToFront(int left, int right);
        Pair<int, int> Min(int left, int right);  // [left; right)  R = {val, pos}
    }
  
    public class Pair<T1, T2> {
        public T1 First;
        public T2 Second;
        public Pair(T1 first, T2 second) {
            First = first;
            Second = second;
        }
    }
      
    public class ImplicitCartesianTree : IImplicitTree  {
        private Node _root;
        private static readonly Random Rand = new Random();
  
        private class Node {
            internal Node Left, Right;
            internal int Size = 1;
            internal int Min, MinPos;
            internal readonly int Value, Priority;
  
            internal Node(int value) {
                Value = value;
                Min = value;
                Priority = Rand.Next();
            }
        }
  
        public void InsertAt(int position, int value) {
            CheckPosition(position, "insert", 1);
            var main = Split(position, _root);
            _root = Merge(main.First, Merge(new Node(value), main.Second));
        }
  
        public void RemoveAt(int position) {
            CheckPosition(position, "remove", 0);
            var main = Split(position, _root);
            var right = Split(1, main.Second);
            _root = Merge(main.First, right.Second);
        }
  
        public int GetAt(int position) {
            CheckPosition(position, "get", 0);
            return GetAt(position, _root).Value;
        }
  
        public int Size() {
            return SizeOf(_root);
        }
 
        public void MoveToFront(int left, int right) {
            CheckSegment(left, right, "move to front");
            var first = Split(left, _root);
            var second = Split(right - left, first.Second);
            _root = Merge(second.First, Merge(first.First, second.Second));
        }
 
        public Pair<int, int> Min(int left, int right) {
            CheckSegment(left, right, "min");
            var first = Split(left, _root);
            var second = Split(right - left, first.Second);
            var result = new Pair<int, int>(MinOf(second.First), MinPosOf(second.First) + SizeOf(first.First));
            first.Second = Merge(second.First, second.Second);
            _root = Merge(first.First, first.Second);
            return result;
        }
  
        private void CheckPosition(int position, string operation, int offset) {
            if (0 > position || position >= Size() + offset) {
                throw new ArgumentException
                    ("Illegal " + operation + " position " + position + " (size " + Size() + ")");
            }
        }
  
        private void CheckSegment(int left, int right, string operation) {
            if (0 > left || left >= right || right > Size()) {
                throw new ArgumentException
                    ("Illegal " + operation + 
                     " segment [" + left + "; " + right + ") (size " + Size() + ")");
            }
        }
  
        private static Node GetAt(int pos, Node cur) {
            while (true) {
                int curPos = SizeOf(cur.Left);
                if (curPos == pos) {
                    return cur;
                }
                if (curPos > pos) {
                    cur = cur.Left;
                    continue;
                }
                pos = pos - curPos - 1;  // curPos < pos
                cur = cur.Right;
            }
        }
          
        private static Node Merge(Node left, Node right) {
            if (left == null || right == null) {
                return left ?? right;
            }
            if (left.Priority < right.Priority) {
                right.Left = Merge(left, right.Left);
                return Updated(right);
            }
            left.Right = Merge(left.Right, right);
            return Updated(left);
        }
  
        private static Pair<Node, Node> Split(int pos, Node cur) {
            if (cur == null) {
                return new Pair<Node, Node>(null, null);
            }
            var curPos = SizeOf(cur.Left);
            if (curPos < pos) {
                var temp = Split(pos - curPos - 1, cur.Right);
                cur.Right = temp.First;
                return new Pair<Node, Node>(Updated(cur), Updated(temp.Second));
            } else {
                var temp = Split(pos, cur.Left);
                cur.Left = temp.Second;
                return new Pair<Node, Node>(Updated(temp.First), Updated(cur));
            }
        }
  
        private static Node Updated(Node cur) {
            if (cur == null)
                return null;
            cur.Size = SizeOf(cur.Left) + SizeOf(cur.Right) + 1;
            cur.Min = Calculate(Math.Min, MinOf(cur.Left), MinOf(cur.Right), cur.Value);
            cur.MinPos = cur.Min == MinOf(cur.Left) ? MinPosOf(cur.Left) :
                cur.Min == cur.Value ? SizeOf(cur.Left) : MinPosOf(cur.Right) + SizeOf(cur.Left) + 1;
            return cur;
        }
  
        private static T Calculate<T>(Func<T, T, T> func, params T[] vars) {
            var result = vars[0];
            for (var i = 1; i < vars.Length; i++) {
                result = func(result, vars[i]);
            }
            return result;
        }
          
        private static int SizeOf(Node node) {
            return node?.Size ?? 0;
        }
  
        private static int MinOf(Node node) {
            return node?.Min ?? int.MaxValue;
        }
          
        private static int MinPosOf(Node node) {
            return node?.MinPos ?? 0;
        }
    }
}
