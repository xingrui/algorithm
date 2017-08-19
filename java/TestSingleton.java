class Singleton {
    private Singleton(String name)
    {
        System.out.println("Constructor:" + name);
    }
    private static final Singleton instance = new Singleton("Outer");
    private static class SingletonHolder {
        private static final Singleton instance = new Singleton("Inner");
    }
    public static final Singleton getInstance1()
    {
        return SingletonHolder.instance;
    }
    public static final Singleton getInstance2()
    {
        return instance;
    }
    public static final void print()
    {
        System.out.println("Hello World");
    }
}

public class TestSingleton {
    public static void main(String[] args)
    {
        Singleton.print();
    }
}
