package Structual;

import java.util.ArrayList;
import java.util.List;

public class Composite
{
    public static void main(String[] args)
    {
        File f1 = new File("Doc.txt", 100);
        File f2 = new File("Image.jpg", 200);

        Directory d1 = new Directory("Subfolder");
        d1.add(new File("Subfile.txt", 50));

        Directory rootDir = new Directory("RootDir");
        rootDir.add(f1);
        rootDir.add(f2);
        rootDir.add(d1);

        System.out.println("Initial Structure:");
        rootDir.printName("");
        System.out.println();

        System.out.printf("Total Size : %d\n", rootDir.getSize());

        rootDir.remove("Image.jpg");
        System.out.printf("After img deleted size : %d\n", rootDir.getSize());

    }

    static interface FileSystemComponent
    {
        public void printName(String parent);
        int getSize();
        String getName();
    }


    static class File implements FileSystemComponent
    {
        private String name;
        private int size;

        public File(String inName, int inSize)
        {
            name = inName;
            size = inSize;
        }


        @Override
        public void printName(String parent)
        {
            System.out.printf(parent + "/" + getName() + "\n");
        }

        @Override
        public int getSize()
        {
            return size;
        }

        @Override
        public String getName()
        {
            return name;
        }
    }

    static class Directory implements FileSystemComponent
    {
        private String name;
        private List<FileSystemComponent> components = new ArrayList<>();

        public Directory(String inName)
        {
            name = inName;
        }

        public void add(FileSystemComponent component)
        {
            components.add(component);
        }
        public void remove(FileSystemComponent component)
        {
            components.remove(component);
        }

        public void remove(String name)
        {
            components.removeIf(component ->
                    component.getName().equals(name));
        }


        @Override
        public void printName(String parent)
        {
            String me = parent + "/" + getName();
            System.out.printf(me + "\n");
            for(FileSystemComponent component : components)
            {
                component.printName(me);
            }
        }

        @Override
        public int getSize()
        {
            int totalSize = 0;
            for(FileSystemComponent component : components)
            {
                totalSize += component.getSize();
            }

            return totalSize;
        }

        @Override
        public String getName() {
            return name;
        }
    }
}
