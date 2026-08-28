package Behaviour;

import java.nio.file.FileSystem;
import java.util.*;

public class Iterator
{
    /*
    ■ Iterator 패턴
    워낙에 자주 봐서 설명할 필요도 없다.

    hasNext, next 두 함수가 핵심이다.
    두 함수의 이터레이터별 세부 구현은 모두 다르지만,
    두 함수를 기반으로 작동한다
     */

    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        MyList list = new MyList(3);
        list.add("A");
        list.add("B");
        list.add("C");

        MyIterator iterator = list.createIterator();
        while(iterator.hasNext())
        {
            System.out.println(iterator.next());
        }



        /*-----------------------
         *         EX 2
         * --------------------- */
        Directory root = new Directory("root");
        Directory home = new Directory("home");
        Directory user = new Directory("user");
        File file1 = new File("file1.txt");
        File file2 = new File("file2.txt");
        File file3 = new File("file3.txt");

        root.add(home);
        home.add(user);
        user.add(file1);
        user.add(file2);
        home.add(file3);

        FileSystem fileSystem = new FileSystem(root);

        System.out.println("\nDFS : ");
        FileSystemIterator depthIterator = fileSystem.depthFirstIterator();
        while(depthIterator.hasNext())
        {
            System.out.println(depthIterator.next().getName());
        }

        System.out.println("\nBFS : ");
        FileSystemIterator breadthIterator = fileSystem.breadthFirstIterator();
        while(breadthIterator.hasNext())
        {
            System.out.println(breadthIterator.next().getName());
        }
    }


    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface MyIterator
    {
        boolean hasNext();
        Object next();
    }

    static interface Collection
    {
        MyIterator createIterator();
    }

    static class MyList implements Collection
    {
        private Object[] items;
        private int last = 0;

        public MyList(int size)
        {
            items = new Object[size];
        }

        public void add(Object item)
        {
            if(last < items.length)
            {
                items[last] = item;
                last++;
            }
        }

        public Object get(int index)
        {
            return items[index];
        }

        public int size() { return last;}

        @Override
        public MyIterator createIterator()
        {
            return new MyListIterator(this);
        }
    }

    static class MyListIterator implements MyIterator
    {
        private MyList list;
        private int index;

        public MyListIterator(MyList inList)
        {
            list = inList;
            index = 0;
        }

        @Override
        public boolean hasNext()
        {
            return index < list.size();
        }

        @Override
        public Object next()
        {
            if(hasNext())
            {
                return list.get(index++);
            }
            return null;
        }
    }





    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface FileSystemItem
    {
        String getName();
    }

    static class File implements FileSystemItem
    {
        private String name;

        public File(String inName)
        {
            name = inName;
        }

        @Override
        public String getName()
        {
            return name;
        }
    }

    static class Directory implements FileSystemItem
    {
        private String name;
        private List<FileSystemItem> contents = new ArrayList<>();

        public Directory(String inName)
        {
            name = inName;
        }

        public void add(FileSystemItem item)
        {
            contents.add(item);
        }

        public List<FileSystemItem> getContents()
        {
            return contents;
        }

        @Override
        public String getName()
        {
            return name;
        }
    }

    static interface FileSystemIterator
    {
        boolean hasNext();
        FileSystemItem next();
    }

    static class DepthFirstIterator implements FileSystemIterator
    {
        private Stack<FileSystemItem> stack = new Stack<>();

        public DepthFirstIterator(Directory root)
        {
            stack.push(root);
        }

        @Override
        public boolean hasNext()
        {
            return stack.isEmpty() == false;
        }

        @Override
        public FileSystemItem next()
        {
            if(hasNext() == false)
            {
                throw new NoSuchElementException();
            }

            FileSystemItem current = stack.pop();
            if(current instanceof Directory)
            {
                List<FileSystemItem> contents = ((Directory)current).getContents();
                for(int i = contents.size() - 1; i >= 0; i--)
                {
                    stack.push(contents.get(i));
                }
            }

            return current;
        }
    }

    static class BreadthFirstIterator implements FileSystemIterator
    {
        private Queue<FileSystemItem> queue = new LinkedList<>();

        public BreadthFirstIterator(Directory root)
        {
            queue.offer(root);
        }

        @Override
        public boolean hasNext()
        {
            return queue.isEmpty() == false;
        }

        @Override
        public FileSystemItem next()
        {
            if(hasNext() == false)
            {
                throw new NoSuchElementException();
            }

            FileSystemItem current = queue.poll();
            if(current instanceof Directory)
            {
                queue.addAll(((Directory)current).getContents());
            }

            return current;
        }
    }

    static class FileSystem
    {
        private Directory root;

        public FileSystem(Directory inRoot)
        {
            root = inRoot;
        }

        public FileSystemIterator depthFirstIterator()
        {
            return new DepthFirstIterator(root);
        }

        public FileSystemIterator breadthFirstIterator()
        {
            return new BreadthFirstIterator(root);
        }
    }
}
