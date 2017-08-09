public class ThreadTest implements Runnable {
    public static void main(String[] args)
    {
        ThreadTest i1 = new ThreadTest("Thread1", 1000);
        ThreadTest i2 = new ThreadTest("Thread2", 100);
        Thread t1 = new Thread(i1);
        Thread t2 = new Thread(i2);
        t1.start();
        t2.start();
        System.out.println("Hello World!");
    }
    private String name;
    private int sleepTime;
    public ThreadTest(String name, int sleepTime)
    {
        this.name = name;
        this.sleepTime = sleepTime;
    }
    public void run()
    {
        try {
            Thread.sleep(this.sleepTime);
        } catch (Exception e) {
            System.out.println(e);
        }

        System.out.println("This is in thread " + name);
    }
}
