package Structual;

import java.util.ArrayList;
import java.util.List;

public class Composite
{
    /*
    ■ Composite 패턴
    자식들을 가질 수 있는 복합체(Composite) 와 자식을 가질 수 없는 리프 를
    동일한 클래스로 묶어(상속받게 하여),
    재귀호출 처리를 수월하게 만든 패턴

    파일 시스템[폴더 - 복합체 / 개별파일 - 리프] 와
    UI 시스템[컨테이너(리스트뷰, 스크롤뷰, 프레임레이아웃..) - 복합체 / 개별컴퍼넌트(버튼, EditText..) - 리프]
    가 대표적인 Composite 패턴

    패턴이랄 게 없다. 위 정의만 기억하자
     */
    public static void main(String[] args)
    {
        /*-----------------------
         *         EX 1
         * --------------------- */
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

        /*-----------------------
         *         EX 2
         * --------------------- */
        System.out.printf("\n\n\n");
        Button submitButton = new Button("Submit");
        Button cancelButton = new Button("Cancel");
        TextBox usernameField = new TextBox("Username");

        Panel formPanel = new Panel("Form");
        formPanel.add(submitButton);
        formPanel.add(cancelButton);
        formPanel.add(usernameField);

        Window mainWindow = new Window("Main");
        mainWindow.add(formPanel);

        mainWindow.render();

        System.out.println();

        formPanel.remove(submitButton);
        formPanel.remove(cancelButton);
        mainWindow.render();
    }
    /*-----------------------
     *         EX 1
     * --------------------- */
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








    /*-----------------------
     *         EX 2
     * --------------------- */
    static interface UIComponent
    {
        void render();
        void add(UIComponent component);
        void remove(UIComponent component);
    }

    static class Button implements UIComponent
    {
        private String label;

        public Button(String inLabel)
        {
            label = inLabel;
        }


        @Override
        public void render()
        {
            System.out.printf("Button %s\n", label);

        }

        @Override
        public void add(UIComponent component)
        {
            throw new UnsupportedOperationException();
        }

        @Override
        public void remove(UIComponent component)
        {
            throw new UnsupportedOperationException();
        }
    }

    static class TextBox implements UIComponent
    {
        private String text;

        public TextBox(String inText)
        {
            text = inText;
        }

        @Override
        public void render()
        {
            System.out.printf("TextBox : %s\n", text);
        }

        @Override
        public void add(UIComponent component)
        {
            throw new UnsupportedOperationException();
        }

        @Override
        public void remove(UIComponent component)
        {
            throw new UnsupportedOperationException();
        }
    }

    static class Panel implements UIComponent
    {
        private String name;
        private List<UIComponent> components = new ArrayList<>();

        public Panel(String inName)
        {
            name = inName;
        }

        @Override
        public void render()
        {
            System.out.printf("Panel : %s\n", name);
            components.forEach(UIComponent::render);
        }

        @Override
        public void add(UIComponent component)
        {
            components.add(component);
        }

        @Override
        public void remove(UIComponent component)
        {
            components.remove(component);
        }
    }

    static class Window implements UIComponent
    {
        private String title;
        private List<UIComponent> components = new ArrayList<>();

        public Window(String inTitle)
        {
            title = inTitle;
        }

        @Override
        public void render()
        {
            System.out.printf("Window : %s\n", title);
            components.forEach(UIComponent::render);
        }

        @Override
        public void add(UIComponent component)
        {
            components.add(component);
        }

        @Override
        public void remove(UIComponent component)
        {
            components.remove(component);
        }
    }
}
