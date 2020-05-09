import java.io.PrintStream;
import java.util.Random;
import java.util.Scanner;
import java.util.TreeSet;
 
public class AVLTree {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        AVLTreeSet treeSet = new AVLTreeSet();
        while (in.hasNext()) {
            String query = in.next();
            int arg = in.nextInt();
            switch (query) {
                case "insert":
                    treeSet.insert(arg);
                    System.out.println(treeSet.insert(arg));
                    break;
                case "delete":
                    treeSet.remove(arg);
                    System.out.println(treeSet.remove(arg));
                    break;
                case "exists":
                    System.out.println(treeSet.exists(arg));
                    break;
                case "next":
                    int tNext = treeSet.higher(arg);
                    System.out.println(tNext == arg ? "none" : tNext);
                    break;
                case "prev":
                    int tPrev = treeSet.lower(arg);
                    System.out.println(tPrev == arg ? "none" : tPrev);
                    break;
                default:
                    throw new AssertionError("Unknown query '" + query + "'");
            }
        }
    }
 
    static class AVLTreeSet {
        private int size;
        Node root;
 
        AVLTreeSet() {
            root = null;
            size = 0;
        }
 
        private static class Node {
            Node left = null;
            Node right = null;
            Node parent = null;
            public int height = 1;
            public int value;
            Node(final int value) {
                this.value = value;
            }
        }
 
 
        public boolean insert(final int value) {
            if (exists(value)) {
                return false;
            }
            root = insert(root, value);
            size++;
            return true;
        }
 
        public int successor(final int value) {
            Node t = successor(find(root, value));
            if (t == null) {
                return value;
            }
            return t.value;
        }
 
        public int predecessor(final int value) {
            Node t = predecessor(find(root, value));
            if (t == null) {
                return value;
            }
            return t.value;
        }
 
        public boolean exists(final int value) {
            return find(root, value) != null;
        }
 
        public boolean remove(final int value) {
            if (!exists(value)) {
                return false;
            }
            root = remove(root, value);
            size--;
            return true;
        }
 
        public int size() {
            return size;
        }
 
        public int height() {
            return root.height;
        }
 
        public void traverse(PrintStream out) {
            print(root, out);
        }
 
        // Returns minimal value in tree > argument, if such exists, else returns argument
        public int higher(final int value) {
            Node t = higher(root, value);
            return t == null ? value : t.value;
        }
 
        // Returns maximal value in tree < argument, if such exists, else returns argument
        public int lower(final int value) {
            Node t = lower(root, value);
            return t == null ? value : t.value;
        }
 
 
        private Node insert(Node cur, final int value) {
            if (cur == null) {
                return new Node(value);
            }
            if (value < cur.value) {
                connectLeft(cur, insert(cur.left, value));
            } else {
                connectRight(cur, insert(cur.right, value));
            }
            return balance(cur);
        }
 
        private Node remove(Node cur, final int value) {
            if (cur == null) {
                return null;
            }
            if (cur.value == value) {
                if (cur.right == null) {
                    return cur.left;
                }
                Node t = findMin(cur.right);
                Node q = removeMin(cur.right);
                connectLeft(t, cur.left);
                connectRight(t, q);
                return balance(t);
            }
            if (value < cur.value) {
                connectLeft(cur, remove(cur.left, value));
            }
            if (value > cur.value) {
                connectRight(cur, remove(cur.right, value));
            }
            return balance(cur);
        }
 
        private Node removeMin(Node cur) {
            assert cur != null;
            if (cur.left == null) {
                return cur.right;
            }
            connectLeft(cur, removeMin(cur.left));
            return balance(cur);
        }
 
        private void connectLeft(Node parent, Node child) {
            if (parent != null) {
                parent.left = child;
            }
            if (child != null) {
                child.parent = parent;
            }
        }
 
        private void connectRight(Node parent, Node child) {
            if (parent != null) {
                parent.right = child;
            }
            if (child != null) {
                child.parent = parent;
            }
        }
 
        private Node findMin(Node cur) {
            if (cur == null) {
                return null;
            }
            if (cur.left == null) {
                return cur;
            }
            return findMin(cur.left);
        }
 
        private Node findMax(Node cur) {
            if (cur == null) {
                return null;
            }
            if (cur.right == null) {
                return cur;
            }
            return findMax(cur.right);
        }
 
        private Node successor(Node cur) {
            if (cur == null) {
                return null;
            }
            if (cur.right != null) {
                return findMin(cur.right);
            }
            while (cur.parent != null) {
                if (cur == cur.parent.left) {
                    return cur.parent;
                }
                cur = cur.parent;
            }
            return null;
        }
 
        private Node predecessor(Node cur) {
            if (cur == null) {
                return null;
            }
            if (cur.left != null) {
                return findMax(cur.left);
            }
            while (cur.parent != null) {
                if (cur == cur.parent.right) {
                    return cur.parent;
                }
                cur = cur.parent;
            }
            return null;
        }
 
        // Returns node with minimal value > second argument, if such exists, else returns null
        private Node higher(Node cur, int value) {
            if (cur == null) {
                return null;
            }
            if (cur.value <= value) {
                return higher(cur.right, value);
            }
            if (cur.left == null) {
                return cur;
            }
            Node t = higher(cur.left, value);
            if (t == null) {
                return cur;
            }
            return t.value > cur.value ? cur : t;
        }
 
        // Returns node with maximal value < second argument, if such exists, else returns null
        private Node lower(Node cur, int value) {
            if (cur == null) {
                return null;
            }
            if (value <= cur.value) {
                return lower(cur.left, value);
            }
            if (cur.right == null) {
                return cur;
            }
            Node t = lower(cur.right, value);
            if (t == null) {
                return cur;
            }
            return t.value < cur.value ? cur : t;
        }
 
        private Node balance(Node node) {
            recalculate(node);
            if (diff(node) == -2) {
                if (diff(node.right) > 0) {
                    node.right = rotateRight(node.right);
                    connectRight(node, node.right);
                }
                return rotateLeft(node);
            }
            if (diff(node) == 2) {
                if (diff(node.left) < 0) {
                    node.left = rotateLeft(node.left);
                    connectLeft(node, node.left);
                }
                return rotateRight(node);
            }
            return node;
        }
 
        private Node rotateLeft(Node a) {
            if (a == null || a.right == null) {
                return a;
            }
            Node b = a.right;
            connectRight(a, b.left);
            connectLeft(b, a);
            recalculate(a);
            recalculate(b);
            return b;
        }
 
        private Node rotateRight(Node a) {
            if (a == null || a.left == null) {
                return a;
            }
            Node b = a.left;
            connectLeft(a, b.right);
            connectRight(b, a);
            recalculate(a);
            recalculate(b);
            return b;
        }
 
        private int diff(Node node) {
            if (node == null) {
                return 0;
            }
            int leftHeight = node.left != null ? node.left.height : 0;
            int rightHeight = node.right != null ? node.right.height : 0;
            return leftHeight - rightHeight;
        }
 
        private void recalculate(Node node) {
            if (node == null) {
                return;
            }
            int leftHeight = node.left != null ? node.left.height : 0;
            int rightHeight = node.right != null ? node.right.height : 0;
            node.height = Math.max(leftHeight, rightHeight) + 1;
        }
 
        private Node find(Node cur, final int value) {
            if (cur == null) {
                return null;
            }
            if (cur.value == value) {
                return cur;
            }
            if (value < cur.value) {
                return find(cur.left, value);
            } else {
                return find(cur.right, value);
            }
        }
 
        private void print(Node node, PrintStream out) {
            if (node == null) {
                return;
            }
            if (node.left != null) {
                out.println("-> left");
                print(node.left, out);
                out.println("<- up");
            }
            out.println(node.value);
            if (node.right != null) {
                out.println("-> right");
                print(node.right, out);
                out.println("<- up");
            }
        }
    }
}
