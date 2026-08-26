package Behaviour;

import java.util.ArrayList;
import java.util.List;

public class Visitor
{
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
        Shape circle = new Circle(5);
        Shape rec = new Rectangle(4, 6);

        Visitor1 areaVisitor = new AreaVisitor();
        Visitor1 perimeterVisitor = new PerimeterVisitor();

        System.out.println("Calc Area : ");
        circle.accept(areaVisitor);
        rec.accept(areaVisitor);

        System.out.println("Calc perimeter : ");
        circle.accept(perimeterVisitor);
        rec.accept(perimeterVisitor);



        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        File file1 = new File("file1.txt", 100);
        File file2 = new File("file2.txt", 200);
        File file3 = new File("file3.txt", 300);

        Directory dir1 = new Directory("Folder1");
        dir1.addElement(file1);
        dir1.addElement(file2);

        Directory dir2 = new Directory("Folder2");
        dir2.addElement(file3);

        Directory rootDir = new Directory("Root");
        rootDir.addElement(dir1);
        rootDir.addElement(dir2);

        SizeCalculatorVisitor sizeVisitor = new SizeCalculatorVisitor();
        rootDir.accept(sizeVisitor);
        System.out.printf("Total size of files : %d\n\n", sizeVisitor.getTotalSize());

        FileSearchVisitor searchVisitor = new FileSearchVisitor("file3.txt");
        rootDir.accept(searchVisitor);
        File foundFile = searchVisitor.getFoundFile();
        if(foundFile != null)
        {
            System.out.printf("File Found : %s, Size : %d\n", foundFile.getName(), foundFile.getSize());
        }
        else
        {
            System.out.println("File not found");
        }
    }

    /*-----------------------
     *         EX 1
     * --------------------- */
    static interface Shape
    {
        void accept(Visitor1 visitor);
    }

    static class Circle implements Shape
    {
        private double radius;

        public Circle(double InRadius)
        {
            radius = InRadius;
        }

        public double getRadius()
        {
            return radius;
        }

        @Override
        public void accept(Visitor1 visitor)
        {
            visitor.visit(this);
        }
    }

    static class Rectangle implements Shape
    {
        private double width, height;

        public Rectangle(double InWidth, double InHeight)
        {
            width = InWidth;
            height = InHeight;
        }

        public double getWidth(){ return width;}
        public double getHeight(){ return height;}

        @Override
        public void accept(Visitor1 visitor)
        {
            visitor.visit(this);
        }
    }

    static interface Visitor1
    {
        void visit(Circle circle);
        void visit(Rectangle rectangle);
    }

    static class AreaVisitor implements Visitor1
    {
        @Override
        public void visit(Circle circle)
        {
            double area = circle.getRadius();
            area = area * area * Math.PI;
            System.out.printf("Circle area : %f\n", area);
        }

        @Override
        public void visit(Rectangle rectangle)
        {
            double area = rectangle.getWidth() * rectangle.getHeight();
            System.out.printf("Rec area : %f\n", area);
        }
    }

    static class PerimeterVisitor implements Visitor1
    {
        @Override
        public void visit(Circle circle)
        {
            double perimeter = 2 * Math.PI  * circle.getRadius();
            System.out.printf("Circle perimeter : %f\n", perimeter);
        }

        @Override
        public void visit(Rectangle rectangle)
        {
            double perimeter = 2 * (rectangle.getHeight() + rectangle.getWidth());
            System.out.printf("Rec perimeter : %f\n", perimeter);
        }
    }




    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface FileSystemElement
    {
        void accept(Visitor2 visitor);
    }

    static class File implements FileSystemElement
    {
        private String name;
        private long size;

        public File(String InName, long InSize)
        {
            name = InName;
            size= InSize;
        }
        public String getName() { return name;}
        public long getSize() { return size;}

        @Override
        public void accept(Visitor2 visitor)
        {
            visitor.visit(this);
        }
    }

    static class Directory implements FileSystemElement
    {
        private String name;
        private List<FileSystemElement> elements;

        public Directory(String InName)
        {
            name = InName;
            elements = new ArrayList<>();
        }

        public String getName(){ return name;}

        public void addElement(FileSystemElement element)
        {
            elements.add(element);
        }

        public List<FileSystemElement> getElements() { return elements;}

        @Override
        public void accept(Visitor2 visitor)
        {
            visitor.visit(this);
        }
    }

    static interface Visitor2
    {
        void visit(File file);
        void visit(Directory directory);
    }

    static class SizeCalculatorVisitor implements Visitor2
    {
        private long totalSize = 0;

        @Override
        public void visit(File file)
        {
            totalSize += file.getSize();
        }

        @Override
        public void visit(Directory directory)
        {
            for(FileSystemElement element : directory.getElements())
            {
                element.accept(this);
            }
        }

        public long getTotalSize(){ return totalSize;}
    }

    static class FileSearchVisitor implements Visitor2
    {
        private String searchFileName;
        private File foundFile;

        public FileSearchVisitor(String InSearchFileName)
        {
            searchFileName = InSearchFileName;
        }

        @Override
        public void visit(File file)
        {
            if(file.getName().equals(searchFileName))
            {
                foundFile = file;
            }
        }

        @Override
        public void visit(Directory directory)
        {
            for(FileSystemElement element : directory.getElements())
            {
                element.accept(this);
            }
        }

        public File getFoundFile()
        {
            return foundFile;
        }
    }


}
